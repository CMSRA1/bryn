
{
// #include "QuantileError.h"


  gROOT->SetStyle("tdrStyle");
  gROOT->ForceStyle();
  // TFile *A = new TFile("AK5PF_Skims_clean.root");
  // TFile *B = new TFile("AK5PF_MatchingMC.root");
  //
  TFile *A = new TFile("AK5Calo_ICDataSkim.root");
  // TFile *A = new TFile("AK5Calo_SD_JMT.root");

  TFile *B = new TFile("AK5Calo_ICMCSkim.root");



  TCanvas *c1 = new TCanvas("c1","awesome!",10,10,1024,640);
  TLegend *L1 = new TLegend(0.3, 0.7, 0.6, 0.9);// x1, y1, x2, y2
  L1->SetFillColor(0);
  L1->SetLineColor(0);
  TLegend *L2 = new TLegend(0.2, 0.7, 0.4, 0.9);// x1, y1, x2, y2
 L2->SetFillColor(0);
  L1->SetShadowColor(0);
  L2->SetLineColor(0);
  L2->SetShadowColor(0);
  c1->cd();
  A->cd();
  TDirectory* D1 = (TDirectory*)A->Get("MT2");
  // B->cd();
  //  TDirectory* D2 = (TDirectory*)B->Get("MT2");

  TH1* h1 = (TH1*)D1->Get("Pt mean vs CaloMETy_all");
  TH1* h2 = (TH1*)D1->Get("Pt mean vs TCMETy_all");
  TH1* h3 = (TH1*)D1->Get("Pt mean vs AK5METy_all");
  TH1* h4 = (TH1*)D1->Get("Pt mean vs PF METy_all");
  TH1* h5 = (TH1*)D1->Get("Pt mean vs MHTy_all");

  TH1* h6 = (TH1*)D1->Get("Pt mean vs CaloMETx_all");
  TH1* h7 = (TH1*)D1->Get("Pt mean vs TCMETx_all");
  TH1* h8 = (TH1*)D1->Get("Pt mean vs AK5METx_all");
  TH1* h9 = (TH1*)D1->Get("Pt mean vs PF METx_all");
  TH1* h10 = (TH1*)D1->Get("Pt mean vs MHTx_all");
  B->cd();
  TDirectory* D2 = (TDirectory*)B->Get("MT2");
  //
  // TH1 h1;
  // TH1 h2;
  // TH1 h3;

  h1->Add(h6);
  h2->Add(h7);
  h3->Add(h8);
  h4->Add(h9);
  h5->Add(h10);

  TH1* hm1 = (TH1*)D2->Get("Pt mean vs CaloMETy_all");
  TH1* hm2 = (TH1*)D2->Get("Pt mean vs TCMETy_all");
  TH1* hm3 = (TH1*)D2->Get("Pt mean vs AK5METy_all");
  TH1* hm4 = (TH1*)D2->Get("Pt mean vs PF METy_all");
  TH1* hm5 = (TH1*)D2->Get("Pt mean vs MHTy_all");

  TH1* hm6 = (TH1*)D2->Get("Pt mean vs CaloMETx_all");
  TH1* hm7 = (TH1*)D2->Get("Pt mean vs TCMETx_all");
  TH1* hm8 = (TH1*)D2->Get("Pt mean vs AK5METx_all");
  TH1* hm9 = (TH1*)D2->Get("Pt mean vs PF METx_all");
  TH1* hm10 = (TH1*)D2->Get("Pt mean vs MHTx_all");

  hm1->Add(hm6);
  hm2->Add(hm7);
  hm3->Add(hm8);
  hm4->Add(hm9);
  hm5->Add(hm10);

  int n = h1->GetNbinsX();
  TH1D *px1 = h1->TH2D::ProjectionY("px1",1,n,"e");
  TH1D *px2 = h2->TH2D::ProjectionY("px2",1,n,"e");
  TH1D *px3 = h3->TH2D::ProjectionY("px3",1,n,"e");
  TH1D *px4 = h4->TH2D::ProjectionY("px4",1,n,"e");
  TH1D *px5 = h5->TH2D::ProjectionY("px5",1,n,"e");
  // TH1D *px6 = h6->TH2D::ProjectionY("px6",1,n,"e");
  // TH1D *px7 = h7->TH2D::ProjectionY("px7",1,n,"e");
  // TH1D *px8 = h8->TH2D::ProjectionY("px8",1,n,"e");
  // TH1D *px9 = h9->TH2D::ProjectionY("px9",1,n,"e");
  // TH1D *px10 = h10->TH2D::ProjectionY("px10",1,n,"e");


  int n = h1->GetNbinsX();
  TH1D *pm1 = hm1->TH2D::ProjectionY("pm1",1,n,"e");
  TH1D *pm2 = hm2->TH2D::ProjectionY("pm2",1,n,"e");
  TH1D *pm3 = hm3->TH2D::ProjectionY("pm3",1,n,"e");
  TH1D *pm4 = hm4->TH2D::ProjectionY("pm4",1,n,"e");
  TH1D *pm5 = hm5->TH2D::ProjectionY("pm5",1,n,"e");
  // TH1D *pm6 = hm6->TH2D::ProjectionY("pm6",1,n,"e");
  // TH1D *pm7 = hm7->TH2D::ProjectionY("pm7",1,n,"e");
  // TH1D *pm8 = hm8->TH2D::ProjectionY("pm8",1,n,"e");
  // TH1D *pm9 = hm9->TH2D::ProjectionY("pm9",1,n,"e");
  // TH1D *pm10 = hm10->TH2D::ProjectionY("pm10",1,n,"e");

  pm1->Scale(px1->Integral()/pm1->Integral());
  pm2->Scale(px2->Integral()/pm2->Integral());
  pm3->Scale(px3->Integral()/pm3->Integral());
  pm4->Scale(px4->Integral()/pm4->Integral());
  pm5->Scale(px5->Integral()/pm5->Integral());
  // pm6->Scale(px6->Integral()/pm6->Integral());
  // pm7->Scale(px7->Integral()/pm7->Integral());
  // pm8->Scale(px8->Integral()/pm8->Integral());
  // pm9->Scale(px9->Integral()/pm9->Integral());
  // pm10->Scale(px10->Integral()/pm10->Integral());

  Double_t F1 = 2.0*(px1->GetRMS(1)); Double_t f1 = -2.0*(px1->GetRMS(1));
  Double_t F2 = 2.0*(px2->GetRMS(1)); Double_t f2 = -2.0*(px2->GetRMS(1));
  Double_t F3 = 2.0*(px3->GetRMS(1)); Double_t f3 = -2.0*(px3->GetRMS(1));
  Double_t F4 = 2.0*(px4->GetRMS(1)); Double_t f4 = -2.0*(px4->GetRMS(1));
  Double_t F5 = 2.0*(px5->GetRMS(1)); Double_t f5 = -2.0*(px5->GetRMS(1));
  // Double_t F6 = 2.0*(px6->GetRMS(1)); Double_t f6 = -2.0*(px6->GetRMS(1));
  // Double_t F7 = 2.0*(px7->GetRMS(1)); Double_t f7 = -2.0*(px7->GetRMS(1));
  // Double_t F8 = 2.0*(px8->GetRMS(1)); Double_t f8 = -2.0*(px8->GetRMS(1));
  // Double_t F9 = 2.0*(px9->GetRMS(1)); Double_t f9 = -2.0*(px9->GetRMS(1));
  // Double_t F10 = 2.0*(px10->GetRMS(1)); Double_t f10 = -2.0*(px10->GetRMS(1));

  Double_t Fm1 = 2.0*(pm1->GetRMS(1)); Double_t fm1 = -2.0*(pm1->GetRMS(1));
  Double_t Fm2 = 2.0*(pm2->GetRMS(1)); Double_t fm2 = -2.0*(pm2->GetRMS(1));
  Double_t Fm3 = 2.0*(pm3->GetRMS(1)); Double_t fm3 = -2.0*(pm3->GetRMS(1));
  Double_t Fm4 = 2.0*(pm4->GetRMS(1)); Double_t fm4 = -2.0*(pm4->GetRMS(1));
  Double_t Fm5 = 2.0*(pm5->GetRMS(1)); Double_t fm5 = -2.0*(pm5->GetRMS(1));
  // Double_t Fm6 = 2.0*(pm6->GetRMS(1)); Double_t fm6 = -2.0*(pm6->GetRMS(1));
  //  Double_t Fm7 = 2.0*(pm7->GetRMS(1)); Double_t fm7 = -2.0*(pm7->GetRMS(1));
  //  Double_t Fm8 = 2.0*(pm8->GetRMS(1)); Double_t fm8 = -2.0*(pm8->GetRMS(1));
  //  Double_t Fm9 = 2.0*(pm9->GetRMS(1)); Double_t fm9 = -2.0*(pm9->GetRMS(1));
  //  Double_t Fm10 = 2.0*(pm10->GetRMS(1)); Double_t fm10 = -2.0*(pm10->GetRMS(1));

  TF1 *gfit = new TF1("ga1","gaus",f1,F1);
  TF1 *gfit2 = new TF1("ga2","gaus",f2,F2);
  TF1 *gfit3 = new TF1("ga3","gaus",f3,F3);
  TF1 *gfit4 = new TF1("ga4","gaus",f4,F4);
  TF1 *gfit5 = new TF1("ga5","gaus",f5,F5);
  // TF1 *gfit6 = new TF1("ga6","gaus",f6,F6);
  // TF1 *gfit7 = new TF1("ga7","gaus",f7,F7);
  // TF1 *gfit8 = new TF1("ga8","gaus",f8,F8);
  // TF1 *gfit9 = new TF1("ga9","gaus",f9,F9);
  // TF1 *gfit10 = new TF1("ga10","gaus",f10,F10);

  TF1 *gfitm = new TF1("gam1","gaus",fm1,Fm1);
  TF1 *gfitm2 = new TF1("gam2","gaus",fm2,Fm2);
  TF1 *gfitm3 = new TF1("gam3","gaus",fm3,Fm3);
  TF1 *gfitm4 = new TF1("gam4","gaus",fm4,Fm4);
  TF1 *gfitm5 = new TF1("gam5","gaus",fm5,Fm5);
  // TF1 *gfitm6 = new TF1("gam6","gaus",fm6,Fm6);
  // TF1 *gfitm7 = new TF1("gam7","gaus",fm7,Fm7);
  // TF1 *gfitm8 = new TF1("gam8","gaus",fm8,Fm8);
  // TF1 *gfitm9 = new TF1("gam9","gaus",fm9,Fm9);
  // TF1 *gfitm10 = new TF1("gam10","gaus",fm10,Fm10);

  px1->Fit("ga1","R");
  px2->Fit("ga2","R");
  px3->Fit("ga3","R");
  px4->Fit("ga4","R");
  px5->Fit("ga5","R");
  // px6->Fit("ga6","R");
  // px7->Fit("ga7","R");
  // px8->Fit("ga8","R");
  // px9->Fit("ga9","R");
  // px10->Fit("ga10","R");

  pm1->Fit("gam1","R");
  pm2->Fit("gam2","R");
  pm3->Fit("gam3","R");
  pm4->Fit("gam4","R");
  pm5->Fit("gam5","R");
  // pm6->Fit("gam6","R");
  // pm7->Fit("gam7","R");
  // pm8->Fit("gam8","R");
  // pm9->Fit("gam9","R");
  // pm10->Fit("gam10","R");







// TH1D *oneside = new TH1D("oneisde","side1",80,0.,400);
  TH1 *abs1;
  TH1 *abs2;
  TH1 *abs3;
  TH1 *abs4;
  TH1 *abs5;
  // TH1 *abs6;
  // TH1 *abs7;
  // TH1 *abs8;
  // TH1 *abs9;
  // TH1 *abs10;
  abs1=(TH1F*)px1->Clone("abs1");
  abs2=(TH1F*)px2->Clone("abs2");
  abs3=(TH1F*)px3->Clone("abs3");
  abs4=(TH1F*)px4->Clone("abs4");
  abs5=(TH1F*)px5->Clone("abs5");
  // abs6=(TH1F*)px6->Clone("abs6");
  // abs7=(TH1F*)px7->Clone("abs7");
  // abs8=(TH1F*)px8->Clone("abs8");
  // abs9=(TH1F*)px9->Clone("abs9");
  // abs10=(TH1F*)px10->Clone("abs10");

  TH1 *absm1;
  TH1 *absm2;
  TH1 *absm3;
  TH1 *absm4;
  TH1 *absm5;
  // TH1 *absm6;
  // TH1 *absm7;
  // TH1 *absm8;
  // TH1 *absm9;
  // TH1 *absm10;
  absm1=(TH1F*)pm1->Clone("absm1");
  absm2=(TH1F*)pm2->Clone("absm2");
  absm3=(TH1F*)pm3->Clone("absm3");
  absm4=(TH1F*)pm4->Clone("absm4");
  absm5=(TH1F*)pm5->Clone("absm5");
  // absm6=(TH1F*)pm6->Clone("absm6");
  // absm7=(TH1F*)pm7->Clone("absm7");
  // absm8=(TH1F*)pm8->Clone("absm8");
  // absm9=(TH1F*)pm9->Clone("absm9");
  // absm10=(TH1F*)pm10->Clone("absm10");


  double a = px1->GetNbinsX()+1;
  for(Int_t i=1; i<=a; i++) {
    double temp1 = px1->GetBinContent(i);
    double temp2 = px1->GetBinContent(a-i);
    double temp3 = px2->GetBinContent(i);
    double temp4 = px2->GetBinContent(a-i);
    double temp5 = px3->GetBinContent(i);
    double temp6 = px3->GetBinContent(a-i);
    double temp7 = px4->GetBinContent(i);
    double temp8 = px4->GetBinContent(a-i);
    double temp9 = px5->GetBinContent(i);
    double temp10 = px5->GetBinContent(a-i);


    double tempm1 = pm1->GetBinContent(i);
    double tempm2 = pm1->GetBinContent(a-i);
    double tempm3 = pm2->GetBinContent(i);
    double tempm4 = pm2->GetBinContent(a-i);
    double tempm5 = pm3->GetBinContent(i);
    double tempm6 = pm3->GetBinContent(a-i);
    double tempm7 = pm4->GetBinContent(i);
    double tempm8 = pm4->GetBinContent(a-i);
    double tempm9 = pm5->GetBinContent(i);
    double tempm10 = pm5->GetBinContent(a-i);


    if(i < px1->FindBin(0) ) {
        abs1->SetBinContent(i,0);
      abs2->SetBinContent(i,0);
      abs3->SetBinContent(i,0);
      abs4->SetBinContent(i,0);
      abs5->SetBinContent(i,0);
      // abs6->SetBinContent(i,0);
      // abs7->SetBinContent(i,0);
      // abs8->SetBinContent(i,0);
      // abs9->SetBinContent(i,0);
      // abs10->SetBinContent(i,0);
      absm1->SetBinContent(i,0);
      absm2->SetBinContent(i,0);
      absm3->SetBinContent(i,0);
      absm4->SetBinContent(i,0);
      absm5->SetBinContent(i,0);
      // absm6->SetBinContent(i,0);
      // absm7->SetBinContent(i,0);
      // absm8->SetBinContent(i,0);
      // absm9->SetBinContent(i,0);
      // absm10->SetBinContent(i,0);
    }
    else{ abs1->SetBinContent(i,temp1+temp2);
      abs2->SetBinContent(i,temp3+temp4);
      abs3->SetBinContent(i,temp5+temp6);
      abs4->SetBinContent(i,temp7+temp8);
      abs5->SetBinContent(i,temp9+temp10);
      // abs6->SetBinContent(i,temp11+temp12);
      // abs7->SetBinContent(i,temp13+temp14);
      // abs8->SetBinContent(i,temp15+temp16);
      // abs9->SetBinContent(i,temp17+temp16);
      // abs10->SetBinContent(i,temp19+temp16);
      absm1->SetBinContent(i,tempm1+tempm2);
      absm2->SetBinContent(i,tempm3+tempm4);
      absm3->SetBinContent(i,tempm5+tempm6);
      absm4->SetBinContent(i,tempm7+tempm8);
      absm5->SetBinContent(i,tempm9+tempm10);
      // absm6->SetBinContent(i,tempm11+tempm12);
      // absm7->SetBinContent(i,tempm13+tempm14);
      // absm8->SetBinContent(i,tempm15+tempm16);
      // absm9->SetBinContent(i,tempm17+tempm16);
      // absm10->SetBinContent(i,tempm19+tempm16);
    }
  }

  double prob[16];// prob defined in loop for prob[N] values using TMathErf
  double sig[16];
  for(int h = 0; h < 16; h++){ prob[h] = TMath::Erf((0.25*(h+1))/sqrt(2)) ; sig[h]= (0.25*(h+1));
    cout << " percentile  " << h << " " << TMath::Erf((0.25*(h+1))/sqrt(2)) <<endl;}
    double quantileD_points1[16];
    double quantileD_points2[16];
    double quantileD_points3[16];
    double quantileD_points4[16];
    double quantileD_points5[16];
    // double quantileD_points6[16];
    // double quantileD_points7[16];
    // double quantileD_points8[16];
    // double quantileD_points9[16];
    // double quantileD_points10[16];
    double quantileM_points1[16];
    double quantileM_points2[16];
    double quantileM_points3[16];
    double quantileM_points4[16];
    double quantileM_points5[16];
    // double quantileM_points6[16];
    // double quantileM_points7[16];
    // double quantileM_points8[16];
    // double quantileM_points9[16];
    // double quantileM_points10[16];
    abs1->GetQuantiles( 16 , quantileD_points1 , prob );
    abs2->GetQuantiles( 16 , quantileD_points2 , prob );
    abs3->GetQuantiles( 16 , quantileD_points3 , prob );
    abs4->GetQuantiles( 16 , quantileD_points4 , prob );
    abs5->GetQuantiles( 16 , quantileD_points5 , prob );
    // abs6->GetQuantiles( 16 , quantileD_points6 , prob );
    // abs7->GetQuantiles( 16 , quantileD_points7 , prob );
    // abs8->GetQuantiles( 16 , quantileD_points8 , prob );
    // abs9->GetQuantiles( 16 , quantileD_points9 , prob );
    // abs10->GetQuantiles( 16 , quantileD_points10 , prob );
    absm1->GetQuantiles( 16 , quantileM_points1 , prob );
    absm2->GetQuantiles( 16 , quantileM_points2 , prob );
    absm3->GetQuantiles( 16 , quantileM_points3 , prob );
    absm4->GetQuantiles( 16 , quantileM_points4 , prob );
    absm5->GetQuantiles( 16 , quantileM_points5 , prob );
    // absm6->GetQuantiles( 16 , quantileM_points6 , prob );
    // absm7->GetQuantiles( 16 , quantileM_points7 , prob );
    // absm8->GetQuantiles( 16 , quantileM_points8 , prob );
    // absm9->GetQuantiles( 16 , quantileM_points9 , prob );
    // absm10->GetQuantiles( 16 , quantileM_points10 , prob );








    double SIGMA1 =  px1->GetFunction("ga1")->GetParameter(2);
    double SIGMA2 =  px2->GetFunction("ga2")->GetParameter(2);
    double SIGMA3 =  px3->GetFunction("ga3")->GetParameter(2);
    double SIGMA4 =  px4->GetFunction("ga4")->GetParameter(2);
    double SIGMA5 =  px5->GetFunction("ga5")->GetParameter(2);
    // double SIGMA6 =  px6->GetFunction("ga6")->GetParameter(2);
    // double SIGMA7 =  px7->GetFunction("ga7")->GetParameter(2);
    // double SIGMA8 =  px8->GetFunction("ga8")->GetParameter(2);
    // double SIGMA9 =  px9->GetFunction("ga9")->GetParameter(2);
    // double SIGMA10 =  px10->GetFunction("ga10")->GetParameter(2);

    double SIGMAm1 =  pm1->GetFunction("gam1")->GetParameter(2);
    double SIGMAm2 =  pm2->GetFunction("gam2")->GetParameter(2);
    double SIGMAm3 =  pm3->GetFunction("gam3")->GetParameter(2);
    double SIGMAm4 =  pm4->GetFunction("gam4")->GetParameter(2);
    double SIGMAm5 =  pm5->GetFunction("gam5")->GetParameter(2);
    // double SIGMAm6 =  pm6->GetFunction("gam6")->GetParameter(2);
    // double SIGMAm7 =  pm7->GetFunction("gam7")->GetParameter(2);
    // double SIGMAm8 =  pm8->GetFunction("gam8")->GetParameter(2);
    // double SIGMAm9 =  pm9->GetFunction("gam9")->GetParameter(2);
    // double SIGMAm10 =  pm10->GetFunction("gam10")->GetParameter(2);




    c1->Clear();
    gROOT->ForceStyle();

    double sigQuant1[16];
    double sigQuant2[16];
    double sigQuant3[16];
    double sigQuant4[16];
    double sigQuant5[16];

    double sigQuantM1[16];
    double sigQuantM2[16];
    double sigQuantM3[16];
    double sigQuantM4[16];
    double sigQuantM5[16];

    for(int j = 0 ; j < 16; j++){
      sigQuant1[j] = quantileD_points1[j]/ ( SIGMA1 );
      sigQuant2[j] = quantileD_points2[j]/ ( SIGMA2 );
      sigQuant3[j] = quantileD_points3[j]/ ( SIGMA3 );
      sigQuant4[j] = quantileD_points4[j]/ ( SIGMA4 );
      sigQuant5[j] = quantileD_points5[j]/ ( SIGMA5 );
      sigQuantM1[j] = quantileM_points1[j]/ ( SIGMAm1 );
      sigQuantM2[j] = quantileM_points2[j]/ ( SIGMAm2 );
      sigQuantM3[j] = quantileM_points3[j]/ ( SIGMAm3 );
      sigQuantM4[j] = quantileM_points4[j]/ ( SIGMAm4 );
      sigQuantM5[j] = quantileM_points5[j]/ ( SIGMAm5 );

    }



    double range1[16];
    double range2[16];
    double range3[16];

    double error1[16];
    for(int o = 0; o < 16; o++){
           range1[o]=sig[o]+0.04;
            range2[o]=range1[o]+0.04;
             range3[o]=sig[o]-0.04;
    Quantile q(abs1);
    std::pair<double,double> x = q[1-prob[o]];
    error1[o] = sqrt(  (x.second/quantileD_points1[o])*(x.second/quantileD_points1[o]) +(px1->GetFunction("ga1")->GetParError(2)/px1->GetFunction("ga1")->GetParameter(2))*(px1->GetFunction("ga1")->GetParError(2)/px1->GetFunction("ga1")->GetParameter(2)))*sigQuant1[o];
    cout << error1[o] << " Compound error " << endl;

  //sqrt((x.second)*(x.second)+(px1->GetFunction("ga1")->GetParError(2))*(px1->GetFunction("ga1")->GetParError(2)));
    }

    double error2[16];
    for(int o = 0; o < 16; o++){
      // range2[o]=sig[o]-0.05;

    Quantile q(abs2);
    std::pair<double,double> x = q(prob[o]);
       error2[o] = sqrt(  (x.second/quantileD_points2[o])*(x.second/quantileD_points2[o]) +(px2->GetFunction("ga2")->GetParError(2)/px2->GetFunction("ga2")->GetParameter(2))*(px2->GetFunction("ga2")->GetParError(2)/px2->GetFunction("ga2")->GetParameter(2)))*sigQuant2[o];
    }
    double error3[16];
    for(int o = 0; o < 16; o++){
    Quantile q(abs3);
    std::pair<double,double> x = q(prob[o]);
       error3[o] = sqrt(  (x.second/quantileD_points3[o])*(x.second/quantileD_points3[o]) +(px3->GetFunction("ga3")->GetParError(2)/px3->GetFunction("ga3")->GetParameter(2))*(px3->GetFunction("ga3")->GetParError(2)/px3->GetFunction("ga3")->GetParameter(2)))*sigQuant3[o];
    }
    double error4[16];
    for(int o = 0; o < 16; o++){
    Quantile q(abs4);
    std::pair<double,double> x = q(prob[o]);
       error4[o] = sqrt(  (x.second/quantileD_points4[o])*(x.second/quantileD_points4[o]) +(px4->GetFunction("ga4")->GetParError(2)/px4->GetFunction("ga4")->GetParameter(2))*(px4->GetFunction("ga4")->GetParError(2)/px4->GetFunction("ga4")->GetParameter(2)))*sigQuant4[o];
    }
    double error5[16];
    for(int o = 0; o < 16; o++){
    Quantile q(abs5);
    std::pair<double,double> x = q(prob[o]);
       error5[o] = sqrt(  (x.second/quantileD_points5[o])*(x.second/quantileD_points5[o]) +(px5->GetFunction("ga5")->GetParError(2)/px5->GetFunction("ga5")->GetParameter(2))*(px5->GetFunction("ga5")->GetParError(2)/px5->GetFunction("ga5")->GetParameter(2)))*sigQuant5[o];
    }


      double errorM1[16];
      for(int o = 0; o < 16; o++){
      Quantile q(abs1);
      std::pair<double,double> x = q[1-prob[o]];
      errorM1[o] = sqrt(  (x.second/quantileM_points1[o])*(x.second/quantileM_points1[o]) +(pm1->GetFunction("gam1")->GetParError(2)/pm1->GetFunction("gam1")->GetParameter(2))*(pm1->GetFunction("gam1")->GetParError(2)/pm1->GetFunction("gam1")->GetParameter(2)))*sigQuantM1[o];
      cout << errorM1[o] << "  errorM1 " << endl;

    //sqrt((x.second)*(x.second)+(pm1->GetFunction("gam1")->GetParError(2))*(pm1->GetFunction("gam1")->GetParError(2)));
      }

      double errorM2[16];
      for(int o = 0; o < 16; o++){
      Quantile q(abs2);
      std::pair<double,double> x = q(prob[o]);
         errorM2[o] = sqrt(  (x.second/quantileM_points2[o])*(x.second/quantileM_points2[o]) +(pm2->GetFunction("gam2")->GetParError(2)/pm2->GetFunction("gam2")->GetParameter(2))*(pm2->GetFunction("gam2")->GetParError(2)/pm2->GetFunction("gam2")->GetParameter(2)))*sigQuantM2[o];
      }
      double errorM3[16];
      for(int o = 0; o < 16; o++){
      Quantile q(abs3);
      std::pair<double,double> x = q(prob[o]);
         errorM3[o] = sqrt(  (x.second/quantileM_points3[o])*(x.second/quantileM_points3[o]) +(pm3->GetFunction("gam3")->GetParError(2)/pm3->GetFunction("gam3")->GetParameter(2))*(pm3->GetFunction("gam3")->GetParError(2)/pm3->GetFunction("gam3")->GetParameter(2)))*sigQuantM3[o];
      }
      double errorM4[16];
      for(int o = 0; o < 16; o++){
      Quantile q(abs4);
      std::pair<double,double> x = q(prob[o]);
         errorM4[o] = sqrt(  (x.second/quantileM_points4[o])*(x.second/quantileM_points4[o]) +(pm4->GetFunction("gam4")->GetParError(2)/pm4->GetFunction("gam4")->GetParameter(2))*(pm4->GetFunction("gam4")->GetParError(2)/pm4->GetFunction("gam4")->GetParameter(2)))*sigQuantM4[o];
 cout << errorM4[o] << "error on M4" << endl;
      }
      double errorM5[16];
      for(int o = 0; o < 16; o++){
      Quantile q(abs5);
      std::pair<double,double> x = q(prob[o]);
         errorM5[o] = sqrt(  (x.second/quantileM_points5[o])*(x.second/quantileM_points5[o]) +(pm5->GetFunction("gam5")->GetParError(2)/pm5->GetFunction("gam5")->GetParameter(2))*(pm5->GetFunction("gam5")->GetParError(2)/pm5->GetFunction("gam5")->GetParameter(2)))*sigQuantM5[o];

        cout << errorM5[o] << "error on M5" << endl;
      }






    // TGraphErrors *graph1 = new TGraphErrors(16, range1,sigQuant1,0 ,error1);
    TGraphErrors *xy = new TGraphErrors(16, sig,sig);
    // TGraphErrors *graph2 = new TGraphErrors(16, range1,sigQuant2,0 ,error2);
    TGraphErrors *graph3 = new TGraphErrors(16, sig,sigQuant3,0 ,error3);
    TGraphErrors *graph4 = new TGraphErrors(16, sig,sigQuant4,0 ,error4);
    TGraphErrors *graph5 = new TGraphErrors(16, range1,sigQuant5,0 ,error5);



    // TGraphErrors *graphM1 = new TGraphErrors(16, range1,sigQuantM1,0 ,errorM1);
    // TGraphErrors *graphM2 = new TGraphErrors(16, range1,sigQuantM2,0 ,errorM2);
    TGraphErrors *graphM3 = new TGraphErrors(16, range3,sigQuantM3,0 ,errorM3);
    TGraphErrors *graphM4 = new TGraphErrors(16, sig,sigQuantM4,0 ,errorM4);
    TGraphErrors *graphM5 = new TGraphErrors(16, range2,sigQuantM5,0 ,errorM5);








    // graph1->SetMarkerColor(1);
    // graph1->SetMarkerStyle(16);
    // graphM1->SetMarkerColor(2);
    // graphM1->SetLineColor(2);
    // graphM1->SetMarkerStyle(24);
    graph4->SetMarkerColor(1);
    graph4->SetMarkerStyle(21);
    graphM4->SetMarkerColor(kOrange-3);
    graphM4->SetLineColor(kOrange-3);
    graphM4->SetMarkerStyle(21);
    graph3->SetMarkerColor(1);
    graph3->SetMarkerStyle(22);
    graphM3->SetMarkerStyle(22);
    graphM3->SetMarkerColor(kOrange-3);
    graphM3->SetLineColor(kOrange-3);
    graph5->SetMarkerColor(1);
    graph5->SetMarkerStyle(16);
    graphM5->SetMarkerStyle(16);
    graphM5->SetMarkerColor(kOrange-3);
    graphM5->SetLineColor(kOrange-3);




    c1->Clear();
    gROOT->ForceStyle();

    // c1->SetLogy();
      // abs->Draw("h");
    // c1->SaveAs("double.pdf");


    c1->Clear();
    gROOT->ForceStyle();
    // c1->SetLogy();
    TMultiGraph *mg = new TMultiGraph();
    TMultiGraph *mg2 = new TMultiGraph();
    // L1->AddEntry( graph1, "Uncorrected  #slash{E}_{T}" ,"P");
    // L1->AddEntry( graphM1, "Uncorrected #slash{E}_{T} (MC)" ,"P");
    // L1->AddEntry( graph2, "TCMETy" ,"P");

    // L1->AddEntry( graph4, "PFMET y" ,"P");
    L1->AddEntry( graph5, "#slash{H}_{T} (Data)" ,"P");
    L1->AddEntry( graphM5, "#slash{H}_{T} (MC)" ,"P");
     L1->AddEntry( graph3, "Type-1 corrected #slash{E}_{T} (Data)" ,"P");
      L1->AddEntry( graphM3, "Type-1 corrected #slash{E}_{T} (MC)" ,"P");
 L1->AddEntry(xy, "Gaussian", "L");

    // graph1->GetXaxis()->SetTitle("caloMETy, Sigma");
    // graph1->GetYaxis()->SetTitle("Meassured quantity");
    // graph->Draw("a");
    // mg->Add(graph1,"P");
    // mg->Add(graphM1,"P");
    mg->Add(graph3,"P");
    mg->Add(graphM3,"P");
    mg->Add(xy,"l");

    mg->Add(graph5,"P");
    mg->Add(graphM5,"P");
    mg->Draw("a");
    mg->GetXaxis()->SetTitle("#sigma_{gaus}");
    mg->GetYaxis()->SetTitle("#frac{quantile(#sigma_{gaus})}{#sigma_{core}}");
    mg->GetYaxis()->SetRangeUser(0.,7.0.);



    L1->Draw();
    c1->SaveAs("CaloJetsSigmaTailsY.pdf");
    c1->Clear();
    gROOT->ForceStyle();


    c1->Clear();
    gROOT->ForceStyle();

    TMultiGraph *pfy = new TMultiGraph();
    pfy->Add(graph5,"P");
    pfy->Add(graphM5,"P");
    pfy->Add(graph4,"P");
    pfy->Add(graphM4,"P");
    pfy->Add(xy,"l");

    pfy->Draw("a");
    pfy->GetXaxis()->SetTitle("#sigma expected");
    pfy->GetYaxis()->SetTitle("#sigma observed");
    pfy->GetYaxis()->SetRangeUser(0.,7.0);
    L1->Clear();
    L1->AddEntry(graph5, "#slash{H}_{T} (Data) ","P");
    L1->AddEntry(graphM5, "#slash{H}_{T} (MC)","P");
    L1->AddEntry(graph4, "#slash{E}_{T} (Data)","P");
    L1->AddEntry(graphM4, "#slash{E}_{T} (MC)","P");
    L1->AddEntry(xy, "Gaussian", "L");
    L1->Draw();
    // c1->SaveAs("ParticleFlowQuantitiesYaxis.pdf");
    c1->Clear();
    gROOT->ForceStyle();



    c1->Clear();
    gROOT->ForceStyle();


    c1->SetLogy();


    px5->SetLineColor(1);
    px5->SetMarkerStyle(16);
    pm5->SetLineColor(kOrange-3);
    pm5->SetFillColor(5);

    px5->GetXaxis()->SetRangeUser(-180.,180.);

    px5->GetFunction("ga5")->SetLineColor(1);
    px5->GetFunction("ga5")->SetLineWidth(2);

    // pm5->Draw("hsame");
    pm5->GetFunction("gam5")->SetLineColor(kRed);
    pm5->GetFunction("gam5")->SetLineStyle(1);
    pm5->GetFunction("gam5")->SetLineWidth(2);
    pm5->SetMarkerStyle(0);
          TH1 *error;



          error = (TH1F*)pm5->Clone("pm5");
             double a = pm5->GetNbinsX()+1;
             for(Int_t i=1; i<=a; i++) {
               double temp1 = pm5->GetBinContent(i);
               double temp2 = pm5->GetBinError(i);
               error->SetBinContent(i,temp1+temp2);

          }
          error->GetXaxis()->SetRangeUser(-180.,180.);
          error->GetXaxis()->SetTitleSize(0.048);
          // ->SetErrorY(1);
          error->GetXaxis()->SetTitle("#slash{H}_{T}x,y");
          error->SetLineColor(0);
          error->Draw("h");

error->SetFillColor(kOrange-3);
    c1->Modified();
    pm5->Draw("hsame");
    px5->Draw("Psame");



    L2->Clear();
    L2->AddEntry(px5, "(Data)","P");
    L2->AddEntry(pm5, "(MC)","f");
    L2->AddEntry(px5->GetFunction("ga5"),"Fit to Data","l");
    L2->AddEntry(pm5->GetFunction("gam5"),"Fit to MC","l");
    L2->Draw();
    c1->SaveAs("FromAK5_mhtx.pdf");



   //
   //   cout <<"##########################################################################################################"<<endl;
   //   cout <<"##########################################################################################################"<<endl;
   //   cout <<"##########################################################################################################"<<endl;
   //
   // cout << "##########################################################################################################"<<endl;
   //    cout << abs1->Integral() << " Total number of events " << " Quantile point " << quantileD_points1[23] <<  " Integral to quantile point "<< abs1->Integral(1,abs1->FindBin(quantileD_points1[23])) <<endl;
   //
   //    Quantile Test(abs1);
   //        std::pair<double,double> x = Test(prob[23]);
   //        cout << " Burt's code makes the quantile point as " << x.first << " And the error as " << x.second << endl;
   //
   //        cout << " interperlation function part 1 " << abs1->GetBinLowEdge(abs1->FindBin(quantileD_points1[23]))+abs1->GetBinWidth(abs1->FindBin(quantileD_points1[23])) << endl;
   //        cout << " interperlation function part 2 " << abs1->GetBinLowEdge(abs1->FindBin(quantileD_points1[23])-1)+abs1->GetBinWidth(abs1->FindBin(quantileD_points1[23])-1) << endl;
   //
   //        cout << " interperlation function part 3 " << abs1->GetBinContent(abs1->FindBin(quantileD_points1[23])) << endl;
   //        cout << " interperlation function part 4 " << abs1->GetBinContent(abs1->FindBin(quantileD_points1[23])-1) << endl;
   //
   //
   //
   //
   // cout <<"##########################################################################################################"<<endl;
   // cout <<"##########################################################################################################"<<endl;
   // cout <<"##########################################################################################################"<<endl;
   // cout <<"##########################################################################################################"<<endl;

  }
