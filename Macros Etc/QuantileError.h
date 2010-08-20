#include "TH1.h"
#include "TMath.h"
#include "TF1.h"


void QuantileError(TH1 *h1, int Number, double *whatever){

  TH1 *abs1;
  abs1=(TH1F*)h1->Clone("abs1");

double a = h1->GetXaxis()->GetNbins()+1;
for( Int_t i = 1; i <=a; i++){
   double temp1 = h1->GetBinContent(i);
    double temp2 = h1->GetBinContent(a-i);
  if(i < h1->GetBin(81) ) {
    abs1->SetBinContent(i,0);
  }
else{ abs1->SetBinContent(i,temp1+temp2);}
}
double prob[Number];
for(int h = 0; h < Number; h++){
  prob[h] = TMath::Erf((0.1*(h+1))/sqrt(2)) ; }


      for(int h = 0; h < Number; h++){

        double small = 0.01;
          double g = 0.000001;
        while( g < (prob[h] + small)){
          g += ((abs1->Integral(1,abs1->FindBin(g)-1)+(abs1->GetBinContent(abs1->FindBin(g))*(g - abs1->GetBinLowEdge(abs1->FindBin(g)))/abs1->GetBinWidth(81)))/ abs1->Integral());// /

        }

        double x = 0.000001;
        while(x < prob[h]){
          x+= ((abs1->Integral(1,abs1->FindBin(x)-1)+(abs1->GetBinContent(abs1->FindBin(x))*(x - abs1->GetBinLowEdge(abs1->FindBin(x)))/abs1->GetBinWidth(81)))/ abs1->Integral());// /
        }
        if((sqrt(prob[h]*(1-prob[h])/abs1->Integral())*(g-x) / small) > 0.05){
          whatever[h] = sqrt(prob[h]*(1-prob[h])/abs1->Integral())*(g-x) / small;}
        else{whatever[h] = sqrt(prob[h]*(1-prob[h]));}

  }

}