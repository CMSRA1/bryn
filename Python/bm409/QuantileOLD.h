#include "TH1.h"
#include "TMath.h"

double Quantile(TH1 h1, int Number){


  Double_t F1 = 1*(h1->GetRMS(1)); Double_t f1 = -1*(h1->GetRMS(1));

  TH1 *abs1;
  abs1=(TH1F*)h1->Clone("abs1");
  // TF1 *gfit = new TF1("ga1","gaus",f1,F1);
  // h1->Fit("ga1","R");

double a = h1->GetNBinsX()+1;
for( Int_t i = 1; i <=a; i++){
   double temp1 = h1->GetBinContent(i);
    double temp2 = h1->GetBinContent(a-i);
  if(i < px1->GetBin(81) ) {
    abs1->SetBinContent(i,0);
  }
else{ abs1->SetBinContent(i,temp1+temp2);}
}
double prob[Number];
double sig[Number];
doouble Quantile[Number];
for(int h = 0; h < Number; h++){
  prob[h]== TMath::Erf((0.1*(h+1))/sqrt(2)) ; sig[h]= (0.1*(h+1));}

abs1->GetQuantiles(Number, Quantile, prob);

return Quantile;

}


