
{
TFile *A = new TFile("AK5PF_Skims_clean.root");
TFile *B = new TFile("AK5PF_MatchingMC.root");



TCanvas *c1 = new TCanvas("c1","awesome!",10,10,1024,640);
TLegend *L1 = new TLegend(0.8, 0.9, 0.94, 1.0);// x1, y1, x2, y2
TLegend *L2 = new TLegend(0.45, 0.9, 0.55, 1.0);// x1, y1, x2, y2
c1->cd();
A->cd();
TDirectory* D1 = (TDirectory*)A->Get("MT2");
B->cd();
TDirectory* D2 = (TDirectory*)B->Get("MT2");

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


// TH1* h1 = (TH1*)D2->Get("Pt mean vs CaloMETy_all");
// TH1* h2 = (TH1*)D2->Get("Pt mean vs TCMETy_all");
// TH1* h3 = (TH1*)D2->Get("Pt mean vs AK5METy_all");
// TH1* h4 = (TH1*)D2->Get("Pt mean vs PF METy_all");
// TH1* h5 = (TH1*)D2->Get("Pt mean vs MHTy_all");
// TH1* h6 = (TH1*)D2->Get("Pt mean vs CaloMETx_all");
// TH1* h7 = (TH1*)D2->Get("Pt mean vs TCMETx_all");
// TH1* h8 = (TH1*)D2->Get("Pt mean vs AK5METx_all");
// TH1* h9 = (TH1*)D2->Get("Pt mean vs PF METx_all");
// TH1* h10 = (TH1*)D2->Get("Pt mean vs MHTx_all");



int n = h1->GetNbinsX();
TH1D *px1 = h1->TH2D::ProjectionY("px1",1,n,"e");
TH1D *px2 = h2->TH2D::ProjectionY("px2",1,n,"e");
TH1D *px3 = h3->TH2D::ProjectionY("px3",1,n,"e");
TH1D *px4 = h4->TH2D::ProjectionY("px4",1,n,"e");
TH1D *px5 = h5->TH2D::ProjectionY("px5",1,n,"e");
TH1D *px6 = h6->TH2D::ProjectionY("px6",1,n,"e");
TH1D *px7 = h7->TH2D::ProjectionY("px7",1,n,"e");
TH1D *px8 = h8->TH2D::ProjectionY("px8",1,n,"e");
TH1D *px9 = h9->TH2D::ProjectionY("px9",1,n,"e");
TH1D *px10 = h10->TH2D::ProjectionY("px10",1,n,"e");


Double_t F1 = 1*(px1->GetRMS(1)); Double_t f1 = -1*(px1->GetRMS(1));
Double_t F2 = 1*(px2->GetRMS(1)); Double_t f2 = -1*(px2->GetRMS(1));
Double_t F3 = 1*(px3->GetRMS(1)); Double_t f3 = -1*(px3->GetRMS(1));
Double_t F4 = 1*(px4->GetRMS(1)); Double_t f4 = -1*(px4->GetRMS(1));
Double_t F5 = 1*(px5->GetRMS(1)); Double_t f5 = -1*(px5->GetRMS(1));
Double_t F6 = 1*(px6->GetRMS(1)); Double_t f6 = -1*(px6->GetRMS(1));
Double_t F7 = 1*(px7->GetRMS(1)); Double_t f7 = -1*(px7->GetRMS(1));
Double_t F8 = 1*(px8->GetRMS(1)); Double_t f8 = -1*(px8->GetRMS(1));
Double_t F9 = 1*(px9->GetRMS(1)); Double_t f9 = -1*(px9->GetRMS(1));
Double_t F10 = 1*(px10->GetRMS(1)); Double_t f10 = -1*(px10->GetRMS(1));

TF1 *gfit = new TF1("ga1","gaus",f1,F1);
TF1 *gfit2 = new TF1("ga2","gaus",f2,F2);
TF1 *gfit3 = new TF1("ga3","gaus",f3,F3);
TF1 *gfit4 = new TF1("ga4","gaus",f4,F4);
TF1 *gfit5 = new TF1("ga5","gaus",f5,F5);
TF1 *gfit6 = new TF1("ga6","gaus",f6,F6);
TF1 *gfit7 = new TF1("ga7","gaus",f7,F7);
TF1 *gfit8 = new TF1("ga8","gaus",f8,F8);
TF1 *gfit9 = new TF1("ga9","gaus",f9,F9);
TF1 *gfit10 = new TF1("ga10","gaus",f10,F10);


px1->Fit("ga1","R");
px2->Fit("ga2","R");
px3->Fit("ga3","R");
px4->Fit("ga4","R");
px5->Fit("ga5","R");
px6->Fit("ga6","R");
px7->Fit("ga7","R");
px8->Fit("ga8","R");
px9->Fit("ga9","R");
px10->Fit("ga10","R");

// TH1D *oneside = new TH1D("oneisde","side1",80,0.,400);
    TH1 *abs1;
    TH1 *abs2;
    TH1 *abs3;
    TH1 *abs4;
    TH1 *abs5;
    TH1 *abs6;
    TH1 *abs7;
    TH1 *abs8;
    TH1 *abs9;
    TH1 *abs10;
    abs1=(TH1F*)px1->Clone("abs1");
    abs2=(TH1F*)px2->Clone("abs2");
    abs3=(TH1F*)px3->Clone("abs3");
    abs4=(TH1F*)px4->Clone("abs4");
    abs5=(TH1F*)px5->Clone("abs5");
    abs6=(TH1F*)px6->Clone("abs6");
    abs7=(TH1F*)px7->Clone("abs7");
    abs8=(TH1F*)px8->Clone("abs8");
    abs9=(TH1F*)px9->Clone("abs9");
    abs10=(TH1F*)px10->Clone("abs10");
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
           double temp11 = px6->GetBinContent(a-i);
           double temp12 = px6->GetBinContent(a-i);
           double temp13 = px7->GetBinContent(a-i);
           double temp14 = px7->GetBinContent(a-i);
           double temp15 = px8->GetBinContent(a-i);
           double temp16 = px8->GetBinContent(a-i);
           double temp17 = px9->GetBinContent(a-i);
           double temp18 = px9->GetBinContent(a-i);
           double temp19 = px10->GetBinContent(a-i);
           double temp20 = px10->GetBinContent(a-i);

          if(i < px1->GetBin(81) ) {
                                    abs1->SetBinContent(i,0);
                                    abs2->SetBinContent(i,0);
                                    abs3->SetBinContent(i,0);
                                    abs4->SetBinContent(i,0);
                                    abs5->SetBinContent(i,0);
                                    abs6->SetBinContent(i,0);
                                    abs7->SetBinContent(i,0);
                                    abs8->SetBinContent(i,0);
                                    abs9->SetBinContent(i,0);
                                    abs10->SetBinContent(i,0);
                                    }
          else{ abs1->SetBinContent(i,temp1+temp2);
                abs2->SetBinContent(i,temp3+temp4);
                abs3->SetBinContent(i,temp5+temp6);
                abs4->SetBinContent(i,temp7+temp8);
                abs5->SetBinContent(i,temp9+temp10);
                abs6->SetBinContent(i,temp11+temp12);
                abs7->SetBinContent(i,temp13+temp14);
                abs8->SetBinContent(i,temp15+temp16);
                abs9->SetBinContent(i,temp17+temp18);
                abs10->SetBinContent(i,temp19+temp20);
}
}
    // abs->GetXaxis()->SetRangeUser(-400.,400.);
    double prob[50];// prob[0]= 0.683; prob[1]=0.954; prob[2]=0.998;
    double sig[50];
    for(int h = 0; h < 50; h++){ prob[h] = TMath::Erf((0.1*(h+1))/sqrt(2)) ; sig[h]= (0.1*(h+1));
      cout << " percentile  " << h << " " << TMath::Erf((0.1*(h+1))/sqrt(2)) <<endl;}
    double quantileD_points1[50];
    double quantileD_points2[50];
    double quantileD_points3[50];
    double quantileD_points4[50];
    double quantileD_points5[50];
    double quantileD_points6[50];
    double quantileD_points7[50];
    double quantileD_points8[50];
    double quantileD_points9[50];
    double quantileD_points10[50];
    abs1->GetQuantiles( 50 , quantileD_points1 , prob );
    abs2->GetQuantiles( 50 , quantileD_points2 , prob );
    abs3->GetQuantiles( 50 , quantileD_points3 , prob );
    abs4->GetQuantiles( 50 , quantileD_points4 , prob );
    abs5->GetQuantiles( 50 , quantileD_points5 , prob );
    abs6->GetQuantiles( 50 , quantileD_points6 , prob );
    abs7->GetQuantiles( 50 , quantileD_points7 , prob );
    abs8->GetQuantiles( 50 , quantileD_points8 , prob );
    abs9->GetQuantiles( 50 , quantileD_points9 , prob );
    abs10->GetQuantiles( 50 , quantileD_points10 , prob );

    px1->Fit("ga1","R");
    double SIGMA1 =  px1->GetFunction("ga1")->GetParameter(2);
    double SIGMA2 =  px2->GetFunction("ga2")->GetParameter(2);
    double SIGMA3 =  px3->GetFunction("ga3")->GetParameter(2);
    double SIGMA4 =  px4->GetFunction("ga4")->GetParameter(2);
    double SIGMA5 =  px5->GetFunction("ga5")->GetParameter(2);
    double SIGMA6 =  px6->GetFunction("ga6")->GetParameter(2);
    double SIGMA7 =  px7->GetFunction("ga7")->GetParameter(2);
    double SIGMA8 =  px8->GetFunction("ga8")->GetParameter(2);
    double SIGMA9 =  px9->GetFunction("ga9")->GetParameter(2);
    double SIGMA10 =  px10->GetFunction("ga10")->GetParameter(2);
    cout <<  px1->GetFunction("ga1")->GetParameter(2) << " Gausian range of px1 histo" << endl;


    c1->Clear();
    double sigQuant1[50];
    double sigQuant2[50];
    double sigQuant3[50];
    double sigQuant4[50];
    double sigQuant5[50];
    double sigQuant6[50];
    double sigQuant7[50];
    double sigQuant8[50];
    double sigQuant9[50];
    double sigQuant10[50];
    for(int j = 0 ; j < 50; j++){
      sigQuant1[j] = quantileD_points1[j]/ ( SIGMA1 );
      sigQuant2[j] = quantileD_points2[j]/ ( SIGMA2 );
      sigQuant3[j] = quantileD_points3[j]/ ( SIGMA3 );
      sigQuant4[j] = quantileD_points4[j]/ ( SIGMA4 );
      sigQuant5[j] = quantileD_points5[j]/ ( SIGMA5 );
      sigQuant6[j] = quantileD_points6[j]/ ( SIGMA6 );
      sigQuant7[j] = quantileD_points7[j]/ ( SIGMA7 );
      sigQuant8[j] = quantileD_points8[j]/ ( SIGMA8 );
      sigQuant9[j] = quantileD_points9[j]/ ( SIGMA9 );
      sigQuant10[j] = quantileD_points10[j]/ ( SIGMA10 );
    }
    TGraphErrors *graph1 = new TGraphErrors(50, sig,sigQuant1 );
    TGraphErrors *graph2 = new TGraphErrors(50, sig,sigQuant2 );
    TGraphErrors *graph3 = new TGraphErrors(50, sig,sigQuant3 );
    TGraphErrors *graph4 = new TGraphErrors(50, sig,sigQuant4 );
    TGraphErrors *graph5 = new TGraphErrors(50, sig,sigQuant5 );
    TGraphErrors *graph6 = new TGraphErrors(50, sig,sigQuant6 );
    TGraphErrors *graph7 = new TGraphErrors(50, sig,sigQuant7 );
    TGraphErrors *graph8 = new TGraphErrors(50, sig,sigQuant8 );
    TGraphErrors *graph9 = new TGraphErrors(50, sig,sigQuant9 );
    TGraphErrors *graph10 = new TGraphErrors(50, sig,sigQuant10 );
    graph1->SetMarkerColor(1);
    graph1->SetMarkerStyle(20);
    graph2->SetMarkerColor(2);
    graph2->SetMarkerStyle(21);
    graph3->SetMarkerColor(3);
    graph3->SetMarkerStyle(22);
    graph4->SetMarkerColor(4);
    graph4->SetMarkerStyle(23);
    graph5->SetMarkerColor(6);
    graph5->SetMarkerStyle(24);
    graph6->SetMarkerColor(1);
    graph6->SetMarkerStyle(20);
    graph7->SetMarkerColor(2);
    graph7->SetMarkerStyle(21);
    graph8->SetMarkerColor(3);
    graph8->SetMarkerStyle(22);
    graph9->SetMarkerColor(4);
    graph9->SetMarkerStyle(23);
    graph10->SetMarkerColor(6);
    graph10->SetMarkerStyle(24);

    c1->Clear();
    // c1->SetLogy();
      // abs->Draw("h");
      c1->SaveAs("double.png");


    c1->Clear();
    TMultiGraph *mg = new TMultiGraph();
    TMultiGraph *mg2 = new TMultiGraph();
L1->AddEntry( graph1, "Calo METy" ,"P");
L1->AddEntry( graph2, "TCMETy" ,"P");
L1->AddEntry( graph3, "AK5METy" ,"P");
L1->AddEntry( graph4, "PFMETy" ,"P");
L1->AddEntry( graph5, "AK5 MHTy" ,"P");

    graph1->GetXaxis()->SetTitle("caloMETy, Sigma");
    graph1->GetYaxis()->SetTitle("Meassured quantity");
    // graph->Draw("a");
    mg->Add(graph1,"P");
    mg->Add(graph2,"P");
    mg->Add(graph3,"P");
    mg->Add(graph4,"P");
    mg->Add(graph5,"P");
    mg->Draw("a");
    L1->Draw();
    c1->SaveAs("MCcurveY.png");
    c1->Clear();
    mg2->Add(graph6,"P");
    mg2->Add(graph7,"P");
    mg2->Add(graph8,"P");
    mg2->Add(graph9,"P");
    mg2->Add(graph10,"P");
    mg2->Draw("a");
    L1->Draw();
    c1->SaveAs("MCcurveX.png");

  c1->Clear();
  c1->SetLogy();
px1->Draw("h");
px2->Draw("hsame");
px3->Draw("hsame");
px4->Draw("hsame");
px5->Draw("hsame");
// px2->Draw("same");
c1->SaveAs("FILE.png");

}