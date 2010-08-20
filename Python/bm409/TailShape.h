#ifndef TAIL_SHAPE
#define TAIL_SHAPE

#include "TF1.h"
#include "TH1F.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include "Quantile.h"

class TailShape {
 public:
  TailShape(TH1*);

  const TH1F* absXY() {return  absXY_;}
  const TF1* halfGaus() {return  halfGaus_;}
  const TGraphAsymmErrors* graph() {return  graph_;}

 private:

  TF1* halfGaus_;
  TH1F* absXY_;
  TGraphAsymmErrors* graph_;
  double sigma_;

  void initAbsXY(TH1*);
  void initHalfGaus();
  void fitSigma();
  void initGraph();
};
#endif


TailShape::TailShape(TH1* hist) {
  initAbsXY(hist);
  initHalfGaus();
  fitSigma();
  initGraph();
}

void TailShape::initAbsXY(TH1* hist) {
  const int nbins = hist->GetNbinsX();
  const double
    xlow = hist->GetBinLowEdge(1),
    xup = hist->GetBinLowEdge(nbins)+hist->GetBinWidth(nbins),
    xupF = std::max(xup,-xlow);
  cout << " xlow " << xlow << " xup " << xup << " XupF " << xupF << " Xlow+Xup " << xlow+xup << endl;
   assert (fabs(xlow+xup)<0.1);

  std::string name = std::string("abs_") + hist->GetName();
  absXY_ = new TH1F(name.c_str(),"", int(xupF*nbins/fabs(xup-xlow)), 0, xupF );
  for(int i = 0; i<=nbins+1; i++)
    absXY_->Fill(fabs(hist->GetBinCenter(i)),hist->GetBinContent(i));
  absXY_->Sumw2();
}

void TailShape::initHalfGaus() {
  halfGaus_ = new TF1("halfGaus","[0]*TMath::Exp(-0.5*x**2/[1])");
  halfGaus_->SetParameter(0,absXY_->GetEntries()/absXY_->GetNbinsX());
  halfGaus_->SetParameter(1,pow(absXY_->GetRMS(),2));
}

void TailShape::fitSigma() {
  absXY_->Fit(halfGaus_,"QN","");
  absXY_->Fit(halfGaus_,"0+","",0, 1.5 * sqrt(halfGaus_->GetParameter(1)));
  const Int_t kNotDraw = 1<<9;
  absXY_->GetFunction("halfGaus")->ResetBit(kNotDraw);
  sigma_= sqrt(halfGaus_->GetParameter(1));
}

void TailShape::initGraph() {
  Quantile quant(absXY_);

  std::vector<float> n;
  std::vector<float> T_nup;
  std::vector<float> T_n;
  std::vector<float> T_nlow;

  for(unsigned i = 1; i<=20; i++) {
    const double ni = (5.0*i)/20;
    const std::pair<float,float> q = quant( TMath::Erf(ni/sqrt(2)));
    if( q.second ) {
      n.push_back(ni);
      T_nlow.push_back((q.first-q.second)/sigma_);
      T_n.push_back(q.first/sigma_);
      T_nup.push_back((q.first+q.second)/sigma_);
    }
  }
  for(unsigned i=1; i<n.size(); i++) {
    const unsigned j = n.size()-i-1;
    T_nlow[i] = std::max(T_nlow[i],T_nlow[i-1]);
    T_nup[j] = std::min(T_nup[j],T_nup[j+1]);
  }

  graph_= new TGraphAsymmErrors();
  for(unsigned i=0; i<n.size(); i++) {
    graph_->SetPoint(i,n[i],T_n[i]);
    graph_->SetPointEYhigh(i, T_nup[i]-T_n[i]);
    graph_->SetPointEYlow(i, T_n[i]-T_nlow[i]);
  }
  graph_->GetXaxis()->SetLimits(0.0,5);
}
