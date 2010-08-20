{
  TFile* MC = new TFile("AK5Calo_MatchingMC.root");
  TFile* Data = new TFile("AK5Calo_Skims_clean.root");


  TCanvas *c2 = new TCanvas("c2","outliers",10,10,1024,640);
  TLegend *L1 = new TLegend(0.8, 0.9, 0.94, 1.0);// x1, y1, x2, y2
  TLegend *L2 = new TLegend(0.45, 0.9, 0.55, 1.0);// x1, y1, x2, y2

  c2->SetFillColor(0);
  c2->SetBorderMode(0);
  c2->SetBorderSize(2);
  c2->SetFrameFillStyle(0);
  c2->SetFrameLineWidth(2);
  c2->SetFrameBorderMode(0);
  c2->SetFrameFillStyle(0);
  c2->SetFrameLineWidth(2);
  c2->SetFrameBorderMode(0);

  double p1[8]; // 90%
  double p2[8]; // 95%
  double p3[8]; // 99%
  double p1M[8]; // 90%
  double p2M[8]; // 95%
  double p3M[8]; // 99%
  double htVal[8];

  double cal1[8]; // 90%
  double cal2[8]; // 95%
  double cal3[8]; // 99%
  double cal1M[8]; // 90%
  double cal2M[8]; // 95%
  double cal3M[8]; // 99%
  double EtVal[8];
  double prob[3]; prob[0]= 0.9; prob[1]=0.95; prob[2]=0.99;
  Data->cd();
  TDirectory* DirDmht = (TDirectory*)Data->Get("MT2");
  MC->cd();
  TDirectory* DirMmht = (TDirectory*)MC->Get("MT2");
  TH1* MHTd = (TH1*)DirDmht->Get("HT vs MHT_all");
  TH1* METd = (TH1*)DirDmht->Get("#sum{E_{T}} vs Calo MET_all");


  TH1* MHTdX = (TH1*)DirDmht->Get("HT vs MHTx_all");
  TH1* MHTdY = (TH1*)DirDmht->Get("HT vs MHTy_all");
  TH1* MHTmX = (TH1*)DirMmht->Get("HT vs MHTx_all");
  TH1* MHTmY = (TH1*)DirMmht->Get("HT vs MHTy_all");

  TH1* METdX = (TH1*)DirDmht->Get("#sum{E_{T}} vs METx_all");
  TH1* METdY = (TH1*)DirDmht->Get("#sum{E_{T}} vs METy_all");
  TH1* METmX = (TH1*)DirMmht->Get("#sum{E_{T}} vs METx_all");
  TH1* METmY = (TH1*)DirMmht->Get("#sum{E_{T}} vs METy_all");


  TH1* MHTm = (TH1*)DirMmht->Get("HT vs MHT_all");
  TH1* METm = (TH1*)DirMmht->Get("#sum{E_{T}} vs Calo MET_all");

  Int_t n = MHTd->GetYaxis()->GetNbins();
    // cout << "Number of bins " << n << endl;
  int points = 0;
  for(int i = 0; i < 40; i+=4){
      // cout << "looking at bin " << i << endl;
    double quantileD_points[3];
    double quantileM_points[3];
    htVal[points]= (i) * 5.0;

    TH1D *px1 = MHTd->TH2D::ProjectionY("px1",i+1,i+4,"o");
    if(px1->Integral() == 0) continue;
    px1->GetQuantiles( 3 , quantileD_points , prob );
    p1[points] = quantileD_points[0];
    p2[points] = quantileD_points[1];
    p3[points] = quantileD_points[2];



    TH1D *px3 = MHTm->TH2D::ProjectionY("px3",i+1,i+4,"o");
    px3->Scale(px1->Integral()/px3->Integral());

    if(px3->Integral() == 0) continue;
    px3->GetQuantiles( 3 , quantileM_points , prob );
    p1M[points] = quantileM_points[0];
    p2M[points] = quantileM_points[1];
    p3M[points] = quantileM_points[2];




    points++;
  }




  Int_t n = MHTm->GetYaxis()->GetNbins();
    // cout << "Number of bins " << n << endl;
  int points = 0;
  for(int i = 0; i < 40; i+=4){
      // cout << "looking at bin " << i << endl;
    double quantileCal_points[3];
    double quantileCalMC_points[3];
    EtVal[points]= (i) * 5.0;


    TH1D *px2 = METd->TH2D::ProjectionY("px2",i+1,i+4,"o");
    if(px2->Integral() == 0) continue;
    px2->GetQuantiles( 3 , quantileCal_points , prob );
    cal1[points] = quantileCal_points[0];
    cal2[points] = quantileCal_points[1];
    cal3[points] = quantileCal_points[2];


    TH1D *px4 = METm->TH2D::ProjectionY("px4",i+1,i+4,"o");
    px4->Scale(px2->Integral()/px4->Integral());

    if(px4->Integral() == 0) continue;
    px4->GetQuantiles( 3 , quantileCalMC_points , prob );
    cal1M[points] = quantileCalMC_points[0];
    cal2M[points] = quantileCalMC_points[1];
    cal3M[points] = quantileCalMC_points[2];

    points++;
  }


  TMultiGraph *quantz = new TMultiGraph();
  TMultiGraph *quantzb = new TMultiGraph();
  TGraphErrors *g1 = new TGraphErrors(points, htVal,p1); // 90% data
  TGraphErrors *g2 = new TGraphErrors(points, htVal,p2); // 95% data
  TGraphErrors *g3 = new TGraphErrors(points, htVal,p3); // 99% data
  TGraphErrors *g4 = new TGraphErrors(points, htVal,p1M); // 90% MC
  TGraphErrors *g5 = new TGraphErrors(points, htVal,p2M); // 95% MC
  TGraphErrors *g6 = new TGraphErrors(points, htVal,p3M); // 99% MC

  TGraphErrors *g7 = new TGraphErrors(points, EtVal,cal1); // 90% data
  TGraphErrors *g8 = new TGraphErrors(points, EtVal,cal2); // 95% data
  TGraphErrors *g9 = new TGraphErrors(points, EtVal,cal3); // 99% data
  TGraphErrors *g10 = new TGraphErrors(points, EtVal,cal1M); // 90% MC
  TGraphErrors *g11 = new TGraphErrors(points, EtVal,cal2M); // 95% MC
  TGraphErrors *g12 = new TGraphErrors(points, EtVal,cal3M); // 99% MC

  g1->SetLineColor(1);
  g2->SetLineColor(1);
  g3->SetLineColor(1);
  g7->SetLineColor(4);
  g8->SetLineColor(4);
  g9->SetLineColor(4);
  g4->SetLineColor(2);
  g5->SetLineColor(2);
  g6->SetLineColor(2);
  g10->SetLineColor(3);
  g11->SetLineColor(3);
  g12->SetLineColor(3);
  g1->SetMarkerColor(1);
  g2->SetMarkerColor(1);
  g3->SetMarkerColor(1);
  g7->SetMarkerColor(4);
  g8->SetMarkerColor(4);
  g9->SetMarkerColor(4);
  g4->SetMarkerColor(2);
  g5->SetMarkerColor(2);
  g6->SetMarkerColor(2);
  g10->SetMarkerColor(3);
  g11->SetMarkerColor(3);
  g12->SetMarkerColor(3);
  g1->SetMarkerStyle(20);
  g2->SetMarkerStyle(23);
  g3->SetMarkerStyle(29);
  g4->SetMarkerStyle(20);
  g5->SetMarkerStyle(23);
  g6->SetMarkerStyle(29);
  g7->SetMarkerStyle(20);
  g8->SetMarkerStyle(23);
  g9->SetMarkerStyle(29);
  g10->SetMarkerStyle(20);
  g11->SetMarkerStyle(22);
  g12->SetMarkerStyle(29);
  quantz->Add(g1,"Pl");
  quantz->Add(g2,"Pl");
  quantz->Add(g3,"Pl");
  quantz->Add(g4,"Pl");
  quantz->Add(g5,"Pl");
  quantz->Add(g6,"Pl");
  quantz->Add(g7,"Pl");
  quantz->Add(g8,"Pl");
  quantz->Add(g9,"Pl");
  quantz->Add(g10,"Pl");
  quantz->Add(g11,"Pl");
  quantz->Add(g12,"Pl");
    // c2->Divide(1,2);
  c2->cd();
      // c2->Clear();
    // c2->cd(1);
  quantz->Draw("a");
    // c2->cd(2);
    // quantzb->Draw("a");
  quantz->GetXaxis()->SetTitle("HT , #sum{E_{T}}");
  quantz->GetYaxis()->SetTitle("MHT , MET");
    // quantz->GetYaxis()->SetRangeUser(0.,100.);
    // quantz->GetXaxis()->SetRangeUser(0.,200.);
    // quantza->GetYaxis()->SetRangeUser(0.,100.);
    // quantzb->GetXaxis()->SetRangeUser(0.,200.);


  L2->AddEntry( g1 , " 90% ", "P");
  L2->AddEntry( g2 , " 95% ", "P");
  L2->AddEntry( g3 , " 99% ", "P");
  L2->Draw();
  // L1->SetFillColor(0);
  // L1->SetLineColor(0);
  L1->AddEntry( g1, " Data HT - MHT ", "L" );
  L1->AddEntry( g4, " MC HT - MHT", "L" );
  L1->AddEntry( g7, " Data #sum{E_{T}} - MET ", "L" );
  L1->AddEntry( g12, " MC #sum{E_{T}} - MET", "L" );
  L1->Draw();
  c2->SaveAs("overlay.pdf");



  double Siga[8];
  double Sigb[8];
  double Sigc[8];
  double Sigd[8];
  double Sige[8];
  double SigMCa[8];
  double SigMCb[8];
  double SigMCc[8];
  double SigMCd[8];
  double SigMCe[8];
  double SigCaloa[8];
  double SigCalob[8];
  double SigCaloc[8];
  double SigCalod[8];
  double SigCaloe[8];
  double SigCaloMCa[8];
  double SigCaloMCb[8];
  double SigCaloMCc[8];
  double SigCaloMCd[8];
  double SigCaloMCe[8];
  double XVal[8];//={40.,60.,80.,90.,100.,120.,140.,160.};
  int count = 0;
  for(int i = 0; i < 40; i+=4){

    TH1D *h1 = MHTd->TH2D::ProjectionY("h1",i+1,i+4,"o");
    TH1D *h2 = MHTm->TH2D::ProjectionY("h2",i+1,i+4,"o");
    TH1D *h3 = METd->TH2D::ProjectionY("h3",i+1,i+4,"o");
    TH1D *h4 = METm->TH2D::ProjectionY("h4",i+1,i+4,"o");
    cout << h1->Integral() << endl;
    if(h1->Integral() == 0) continue;
    h2->Scale(h1->Integral()/h2->Integral());
    count++;
    cout<<count<<endl;
    Double_t maxi1 = h1->GetMean(1)+ (1*h1->GetRMS(1));
    Double_t maxi2 = h1->GetMean(1)+ (2*h1->GetRMS(1));
    Double_t maxi3 = h1->GetMean(1)+ (3*h1->GetRMS(1));
    Double_t maxi4 = h1->GetMean(1)+ (4*h1->GetRMS(1));
    Double_t maxi5 = h1->GetMean(1)+ (5*h1->GetRMS(1));

    Double_t remUP1 = 0.5*( h1->Interpolate( maxi1 ) + h1->GetBinContent( (h1->FindBin(maxi1) ) ) )*fabs( maxi1 - h1->GetBinLowEdge( h1->FindBin( maxi1 ) ) );
    Double_t remUP2 = 0.5*( h1->Interpolate( maxi2 ) + h1->GetBinContent( (h1->FindBin(maxi2) ) ) )*fabs( maxi2 - h1->GetBinLowEdge( h1->FindBin( maxi2 ) ) );
    Double_t remUP3 = 0.5*( h1->Interpolate( maxi3 ) + h1->GetBinContent( (h1->FindBin(maxi3) ) ) )*fabs( maxi3 - h1->GetBinLowEdge( h1->FindBin( maxi3 ) ) );
    Double_t remUP4 = 0.5*( h1->Interpolate( maxi4 ) + h1->GetBinContent( (h1->FindBin(maxi4) ) ) )*fabs( maxi4 - h1->GetBinLowEdge( h1->FindBin( maxi4 ) ) );
    Double_t remUP5 = 0.5*( h1->Interpolate( maxi5 ) + h1->GetBinContent( (h1->FindBin(maxi5) ) ) )*fabs( maxi5 - h1->GetBinLowEdge( h1->FindBin( maxi5 ) ) );

    Siga[i/5] = ( h1->Integral( "width" ) - h1->Integral( 1, h1->FindBin( maxi1 )-1 ,"width" ) + remUP1) / (h1->Integral( "width" )) ;
    Sigb[i/5] = ( h1->Integral( "width" ) - h1->Integral( 1, h1->FindBin( maxi2 )-1 ,"width" ) + remUP2) / (h1->Integral( "width" )) ;
    Sigc[i/5] = ( h1->Integral( "width" ) - h1->Integral( 1, h1->FindBin( maxi3 )-1 ,"width" ) + remUP3) / (h1->Integral( "width" )) ;
    Sigd[i/5] = ( h1->Integral( "width" ) - h1->Integral( 1, h1->FindBin( maxi4 )-1 ,"width" ) + remUP4) / (h1->Integral( "width" )) ;
    Sige[i/5] = ( h1->Integral( "width" ) - h1->Integral( 1, h1->FindBin( maxi5 )-1 ,"width" ) + remUP5) / (h1->Integral( "width" )) ;
    cout << Siga[i/5] << " calculated value" <<endl;
    XVal[count]= (i) * 5.0;



    Double_t maxiMC1 = h2->GetMean(1)+ (1*h2->GetRMS(1));
    Double_t maxiMC2 = h2->GetMean(1)+ (2*h2->GetRMS(1));
    Double_t maxiMC3 = h2->GetMean(1)+ (3*h2->GetRMS(1));
    Double_t maxiMC4 = h2->GetMean(1)+ (4*h2->GetRMS(1));
    Double_t maxiMC5 = h2->GetMean(1)+ (5*h2->GetRMS(1));

    Double_t remUPMC1 = 0.5*( h2->Interpolate( maxiMC1 ) + h2->GetBinContent( (h2->FindBin(maxiMC1) ) ) )*fabs( maxiMC1 - h2->GetBinLowEdge( h2->FindBin( maxiMC1 ) ) );
    Double_t remUPMC2 = 0.5*( h2->Interpolate( maxiMC2 ) + h2->GetBinContent( (h2->FindBin(maxiMC2) ) ) )*fabs( maxiMC2 - h2->GetBinLowEdge( h2->FindBin( maxiMC2 ) ) );
    Double_t remUPMC3 = 0.5*( h2->Interpolate( maxiMC3 ) + h2->GetBinContent( (h2->FindBin(maxiMC3) ) ) )*fabs( maxiMC3 - h2->GetBinLowEdge( h2->FindBin( maxiMC3 ) ) );
    Double_t remUPMC4 = 0.5*( h2->Interpolate( maxiMC4 ) + h2->GetBinContent( (h2->FindBin(maxiMC4) ) ) )*fabs( maxiMC4 - h2->GetBinLowEdge( h2->FindBin( maxiMC4 ) ) );
    Double_t remUPMC5 = 0.5*( h2->Interpolate( maxiMC5 ) + h2->GetBinContent( (h2->FindBin(maxiMC5) ) ) )*fabs( maxiMC5 - h2->GetBinLowEdge( h2->FindBin( maxiMC5 ) ) );

    SigMCa[i/5] = ( h2->Integral( "width" ) - h2->Integral( 1, h2->FindBin( maxiMC1 )-1 ,"width" ) + remUPMC1) / (h2->Integral( "width" )) ;
    SigMCb[i/5] = ( h2->Integral( "width" ) - h2->Integral( 1, h2->FindBin( maxiMC2 )-1 ,"width" ) + remUPMC2) / (h2->Integral( "width" )) ;
    SigMCc[i/5] = ( h2->Integral( "width" ) - h2->Integral( 1, h2->FindBin( maxiMC3 )-1 ,"width" ) + remUPMC3) / (h2->Integral( "width" )) ;
    SigMCd[i/5] = ( h2->Integral( "width" ) - h2->Integral( 1, h2->FindBin( maxiMC4 )-1 ,"width" ) + remUPMC4) / (h2->Integral( "width" )) ;
    SigMCe[i/5] = ( h2->Integral( "width" ) - h2->Integral( 1, h2->FindBin( maxiMC5 )-1 ,"width" ) + remUPMC5) / (h2->Integral( "width" )) ;
    cout << SigMCe[i/5] << " calculated value" <<endl;

    if(h3->Integral() == 0) continue;

    h4->Scale(h3->Integral()/h4->Integral());

    Double_t maxiCalo1 = h3->GetMean(1)+ (1*h3->GetRMS(1));
    Double_t maxiCalo2 = h3->GetMean(1)+ (2*h3->GetRMS(1));
    Double_t maxiCalo3 = h3->GetMean(1)+ (3*h3->GetRMS(1));
    Double_t maxiCalo4 = h3->GetMean(1)+ (4*h3->GetRMS(1));
    Double_t maxiCalo5 = h3->GetMean(1)+ (5*h3->GetRMS(1));

    Double_t remCaloUP1 = 0.5*( h3->Interpolate( maxiCalo1 ) + h3->GetBinContent( (h3->FindBin(maxiCalo1) ) ) )*fabs( maxiCalo1 - h3->GetBinLowEdge( h3->FindBin( maxiCalo1 ) ) );
    Double_t remCaloUP2 = 0.5*( h3->Interpolate( maxiCalo2 ) + h3->GetBinContent( (h3->FindBin(maxiCalo2) ) ) )*fabs( maxiCalo2 - h3->GetBinLowEdge( h3->FindBin( maxiCalo2 ) ) );
    Double_t remCaloUP3 = 0.5*( h3->Interpolate( maxiCalo3 ) + h3->GetBinContent( (h3->FindBin(maxiCalo3) ) ) )*fabs( maxiCalo3 - h3->GetBinLowEdge( h3->FindBin( maxiCalo3 ) ) );
    Double_t remCaloUP4 = 0.5*( h3->Interpolate( maxiCalo4 ) + h3->GetBinContent( (h3->FindBin(maxiCalo4) ) ) )*fabs( maxiCalo4 - h3->GetBinLowEdge( h3->FindBin( maxiCalo4 ) ) );
    Double_t remCaloUP5 = 0.5*( h3->Interpolate( maxiCalo5 ) + h3->GetBinContent( (h3->FindBin(maxiCalo5) ) ) )*fabs( maxiCalo5 - h3->GetBinLowEdge( h3->FindBin( maxiCalo5 ) ) );

    SigCaloa[i/5] = ( h3->Integral( "width" ) - h3->Integral( 1, h3->FindBin( maxiCalo1 )-1 ,"width" ) + remCaloUP1) / (h3->Integral( "width" )) ;
    SigCalob[i/5] = ( h3->Integral( "width" ) - h3->Integral( 1, h3->FindBin( maxiCalo2 )-1 ,"width" ) + remCaloUP2) / (h3->Integral( "width" )) ;
    SigCaloc[i/5] = ( h3->Integral( "width" ) - h3->Integral( 1, h3->FindBin( maxiCalo3 )-1 ,"width" ) + remCaloUP3) / (h3->Integral( "width" )) ;
    SigCalod[i/5] = ( h3->Integral( "width" ) - h3->Integral( 1, h3->FindBin( maxiCalo4 )-1 ,"width" ) + remCaloUP4) / (h3->Integral( "width" )) ;
    SigCaloe[i/5] = ( h3->Integral( "width" ) - h3->Integral( 1, h3->FindBin( maxiCalo5 )-1 ,"width" ) + remCaloUP5) / (h3->Integral( "width" )) ;
    cout << SigCaloc[i/5] << " calculated value CALO C" <<endl;



    Double_t maxiCaloMC1 = h4->GetMean(1)+ (1*h4->GetRMS(1));
    Double_t maxiCaloMC2 = h4->GetMean(1)+ (2*h4->GetRMS(1));
    Double_t maxiCaloMC3 = h4->GetMean(1)+ (3*h4->GetRMS(1));
    Double_t maxiCaloMC4 = h4->GetMean(1)+ (4*h4->GetRMS(1));
    Double_t maxiCaloMC5 = h4->GetMean(1)+ (5*h4->GetRMS(1));

    Double_t remCaloUPMC1 = 0.5*( h4->Interpolate( maxiCaloMC1 ) + h4->GetBinContent( (h4->FindBin(maxiCaloMC1) ) ) )*fabs( maxiCaloMC1 - h4->GetBinLowEdge( h4->FindBin( maxiCaloMC1 ) ) );
    Double_t remCaloUPMC2 = 0.5*( h4->Interpolate( maxiCaloMC2 ) + h4->GetBinContent( (h4->FindBin(maxiCaloMC2) ) ) )*fabs( maxiCaloMC2 - h4->GetBinLowEdge( h4->FindBin( maxiCaloMC2 ) ) );
    Double_t remCaloUPMC3 = 0.5*( h4->Interpolate( maxiCaloMC3 ) + h4->GetBinContent( (h4->FindBin(maxiCaloMC3) ) ) )*fabs( maxiCaloMC3 - h4->GetBinLowEdge( h4->FindBin( maxiCaloMC3 ) ) );
    Double_t remCaloUPMC4 = 0.5*( h4->Interpolate( maxiCaloMC4 ) + h4->GetBinContent( (h4->FindBin(maxiCaloMC4) ) ) )*fabs( maxiCaloMC4 - h4->GetBinLowEdge( h4->FindBin( maxiCaloMC4 ) ) );
    Double_t remCaloUPMC5 = 0.5*( h4->Interpolate( maxiCaloMC5 ) + h4->GetBinContent( (h4->FindBin(maxiCaloMC5) ) ) )*fabs( maxiCaloMC5 - h4->GetBinLowEdge( h4->FindBin( maxiCaloMC5 ) ) );

    SigCaloMCa[i/5] = ( h4->Integral( "width" ) - h4->Integral( 1, h4->FindBin( maxiCaloMC1 )-1 ,"width" ) + remCaloUPMC1) / (h4->Integral( "width" )) ;
    SigCaloMCb[i/5] = ( h4->Integral( "width" ) - h4->Integral( 1, h4->FindBin( maxiCaloMC2 )-1 ,"width" ) + remCaloUPMC2) / (h4->Integral( "width" )) ;
    SigCaloMCc[i/5] = ( h4->Integral( "width" ) - h4->Integral( 1, h4->FindBin( maxiCaloMC3 )-1 ,"width" ) + remCaloUPMC3) / (h4->Integral( "width" )) ;
    SigCaloMCd[i/5] = ( h4->Integral( "width" ) - h4->Integral( 1, h4->FindBin( maxiCaloMC4 )-1 ,"width" ) + remCaloUPMC4) / (h4->Integral( "width" )) ;
    SigCaloMCe[i/5] = ( h4->Integral( "width" ) - h4->Integral( 1, h4->FindBin( maxiCaloMC5 )-1 ,"width" ) + remCaloUPMC5) / (h4->Integral( "width" )) ;
    cout << SigCaloMCe[i/5] << " calculated value" <<endl;






  }
  c2->Clear();
  TMultiGraph *multia = new TMultiGraph();
  TMultiGraph *multib = new TMultiGraph();
  TMultiGraph *multic = new TMultiGraph();
  TMultiGraph *multid = new TMultiGraph();
  TMultiGraph *multie = new TMultiGraph();
  // TMultiGraph *multib = new TMultiGraph();
  TGraphErrors *siga = new TGraphErrors(8, XVal, Siga);
// siga->GetXaxis()->SetRangeUser(0.,180.);

  siga->SetMarkerStyle(20);
  TGraphErrors *sigb = new TGraphErrors(8, XVal, Sigb);
  sigb->SetMarkerStyle(20);
  TGraphErrors *sigc = new TGraphErrors(8, XVal, Sigc);
  sigc->SetMarkerStyle(20);
  TGraphErrors *sigd = new TGraphErrors(8, XVal, Sigd);
  sigd->SetMarkerStyle(20);
  TGraphErrors *sige = new TGraphErrors(8, XVal, Sige);
  sige->SetMarkerStyle(20);

  TGraphErrors *sigMCa = new TGraphErrors(8, XVal, SigMCa);
  sigMCa->SetMarkerStyle(21);
  sigMCa->SetMarkerColor(2);
  sigMCa->SetLineColor(2);
  TGraphErrors *sigMCb = new TGraphErrors(8, XVal, SigMCb);
  sigMCb->SetLineColor(2);
  sigMCb->SetMarkerColor(2);
  sigMCb->SetMarkerStyle(21);
  TGraphErrors *sigMCc = new TGraphErrors(8, XVal, SigMCc);
  sigMCc->SetLineColor(2);
  sigMCc->SetMarkerStyle(21);
  sigMCc->SetMarkerColor(2);
  TGraphErrors *sigMCd = new TGraphErrors(8, XVal, SigMCd);
  sigMCd->SetLineColor(2);
  sigMCd->SetMarkerStyle(21);
  sigMCd->SetMarkerColor(2);
  TGraphErrors *sigMCe = new TGraphErrors(8, XVal, SigMCe);
  sigMCe->SetLineColor(2);
  sigMCe->SetMarkerStyle(21);
  sigMCe->SetMarkerColor(2);


  TGraphErrors *sigCaloa = new TGraphErrors(8, XVal, SigCaloa);
  sigCaloa->SetMarkerStyle(22);
  sigCaloa->SetLineColor(3);
  sigCaloa->SetMarkerColor(4);
  TGraphErrors *sigCalob = new TGraphErrors(8, XVal, SigCalob);
  sigCalob->SetLineColor(3);
  sigCalob->SetMarkerColor(4);
  sigCalob->SetMarkerStyle(22);
  TGraphErrors *sigCaloc = new TGraphErrors(8, XVal, SigCaloc);
  sigCaloc->SetLineColor(3);
  sigCaloc->SetMarkerColor(4);
  sigCaloc->SetMarkerStyle(22);
  TGraphErrors *sigCalod = new TGraphErrors(8, XVal, SigCalod);
  sigCalod->SetLineColor(3);
  sigCalod->SetMarkerColor(4);
  sigCalod->SetMarkerStyle(22);
  TGraphErrors *sigCaloe = new TGraphErrors(8, XVal, SigCaloe);
  sigCaloe->SetLineColor(3);
  sigCaloe->SetMarkerStyle(22);
  sigCaloe->SetMarkerColor(4);

  TGraphErrors *sigCaloMCa = new TGraphErrors(8, XVal, SigCaloMCa);
  sigCaloMCa->SetMarkerStyle(23);
  sigCaloMCa->SetLineColor(4);
  sigCaloMCa->SetMarkerColor(3);
  TGraphErrors *sigCaloMCb = new TGraphErrors(8, XVal, SigCaloMCb);
  sigCaloMCb->SetLineColor(4);
  sigCaloMCb->SetMarkerStyle(23);
  sigCaloMCb->SetMarkerColor(3);
  TGraphErrors *sigCaloMCc = new TGraphErrors(8, XVal, SigCaloMCc);
  sigCaloMCc->SetLineColor(4);
  sigCaloMCc->SetMarkerStyle(23);
  sigCaloMCc->SetMarkerColor(3);
  TGraphErrors *sigCaloMCd = new TGraphErrors(8, XVal, SigCaloMCd);
  sigCaloMCd->SetLineColor(4);
  sigCaloMCd->SetMarkerStyle(23);
  sigCaloMCd->SetMarkerColor(3);
  TGraphErrors *sigCaloMCe = new TGraphErrors(8, XVal, SigCaloMCe);
  sigCaloMCe->SetLineColor(4);
  sigCaloMCe->SetMarkerStyle(23);
  sigCaloMCe->SetMarkerColor(3);





  // c2->Divide(1,2);
    // c2->SetLogy();

  L2->Clear();

  multia->Add(siga,"P");
  multib->Add(sigb,"P");
  multic->Add(sigc,"P");
  multid->Add(sigd,"P");
  multie->Add(sige,"P");
  multia->Add(sigMCa,"P");
  multib->Add(sigMCb,"P");
  multic->Add(sigMCc,"P");
  multid->Add(sigMCd,"P");
  multie->Add(sigMCe,"P");


  multia->Add(sigCaloa,"P");
  multib->Add(sigCalob,"P");
  multic->Add(sigCaloc,"P");
  multid->Add(sigCalod,"P");
  multie->Add(sigCaloe,"P");
  multia->Add(sigCaloMCa,"P");
  multib->Add(sigCaloMCb,"P");
  multic->Add(sigCaloMCc,"P");
  multid->Add(sigCaloMCd,"P");
  multie->Add(sigCaloMCe,"P");
  L2->AddEntry( siga , " Data (MHT)", "P");
  L2->AddEntry( sigMCa , " MC (MHT) ", "P");
  L2->AddEntry( sigCaloa , " Data (MET) ", "P");
  L2->AddEntry( sigCaloMCa , " MC (MET) ", "P");

  // L2->Clear();
  // L1->Clear();

  // c2->cd(1);
  multia->Draw("a e");
  multia->GetXaxis()->SetTitle("HT Bin (GeV)");
  multia->GetYaxis()->SetTitle("Fraction of events > 1 #sigma away from mean");
  multia->GetXaxis()->SetRangeUser(0.,180.);
  L2->Draw();
  c2->SaveAs("1sigma.pdf");

  c2->Clear();
  multib->Draw("a e");
  multib->GetXaxis()->SetTitle("HT Bin (GeV)");
  multib->GetYaxis()->SetTitle("Fraction of events > 2 #sigma away from mean");
  multib->GetXaxis()->SetRangeUser(0.,180.);
  L2->Draw();
  c2->SaveAs("2sigma.pdf");

  c2->Clear();
  multic->Draw("a e");
  multic->GetXaxis()->SetTitle("HT Bin (GeV)");
  multic->GetYaxis()->SetTitle("Fraction of events > 3 #sigma away from mean");
  multic->GetXaxis()->SetRangeUser(0.,180.);
  L2->Draw();
  c2->SaveAs("3sigma.pdf");

  c2->Clear();
  multid->Draw("a e");
  multid->GetXaxis()->SetTitle("HT Bin (GeV)");
  multid->GetYaxis()->SetTitle("Fraction of events > 4 #sigma away from mean");
  multid->GetXaxis()->SetRangeUser(0.,180.);
  L2->Draw();
  c2->SaveAs("4sigma.pdf");

  c2->Clear();
  multie->Draw("a e");
  multie->GetXaxis()->SetTitle("HT Bin (GeV)");
  multie->GetYaxis()->SetTitle("Fraction of events > 5 #sigma away from mean");
  multie->GetXaxis()->SetRangeUser(0.,180.);
  L2->Draw();
  c2->SaveAs("5sigma.pdf");


  // TH1* MHTdX = (TH1*)DirDmht->Get("HT vs MHT_X_all");
  // TH1* MHTdY = (TH1*)DirDmht->Get("HT vs MHT_Y_all");
  // TH1* MHTmX = (TH1*)DirMmht->Get("HT vs MHT_X_all");
  // TH1* MHTmY = (TH1*)DirMmht->Get("HT vs MHT_Y_all");



  Double_t htVal[9];
  Double_t fract1[9];
  Double_t fract2[9];
  Double_t fract3[9];

  Double_t fractMC1[9];
  Double_t fractMC2[9];
  Double_t fractMC3[9];

  Double_t ef1[9];
  Double_t ef2[9];
  Double_t ef3[9];

  Double_t efMC1[9];
  Double_t efMC2[9];
  Double_t efMC3[9];

  Double_t fractCALO1[9];
  Double_t fractCALO2[9];
  Double_t fractCALO3[9];

  Double_t fractCALOMC1[9];
  Double_t fractCALOMC2[9];
  Double_t fractCALOMC3[9];

  Double_t efCALO1[9];
  Double_t efCALO2[9];
  Double_t efCALO3[9];

  Double_t efCALOMC1[9];
  Double_t efCALOMC2[9];
  Double_t efCALOMC3[9];

  Int_t c = 0;
  Int_t b = MHTdY->GetXaxis()->GetNbins();
  cout << "number of bins is "<< b << endl;
  for(int i = 0; i < b ; i+=4){
    TH1D *mhtxy = MHTdY->TH2D::ProjectionY("mhtxy",i+1,i+4,"o");
    TH1D *mhtxyMC = MHTmY->TH2D::ProjectionY("mhtxyMC",i+1,i+4,"o");
    TH1D *metxyCALO = METdY->TH2D::ProjectionY("metxyCALO",i+1,i+4,"o");
    TH1D *metxyCALOMC = METmY->TH2D::ProjectionY("metxyCALOMC",i+1,i+4,"o");


    if(mhtxy->Integral() == 0) continue;// bool can put in else where.
    mhtxyMC->Scale(mhtxy->Integral()/mhtxyMC->Integral());



    if(metxyCALO->Integral() == 0) continue;// bool can put in else where.
    metxyCALOMC->Scale(metxyCALO->Integral()/metxyCALOMC->Integral());


    htVal[c]=i*5;
    Double_t Fmax = 1.5*(mhtxy->GetRMS(1));
    Double_t Fmin = -1.5*(mhtxy->GetRMS(1));
    TF1 *gfit = new TF1("ga1","gaus",Fmin,Fmax); // Create the fit function
    mhtxy->Fit("ga1","QR");
    mhtxy->Draw("h");
    Double_t FmaxMC = 1.5*(mhtxyMC->GetRMS(1));
    Double_t FminMC = -1.5*(mhtxyMC->GetRMS(1));
    TF1 *gfit2 = new TF1("ga2","gaus",FminMC,FmaxMC); // Create the fit function
    mhtxy->Fit("ga1","QR");
    mhtxyMC->Fit("ga2","QR");

    mhtxy->SetMarkerStyle(20);
    mhtxyMC->GetFunction("ga2")->SetLineColor(6);
    mhtxy->GetFunction("ga1")->SetLineColor(4);
    mhtxyMC->SetLineColor(2);
    mhtxy->GetXaxis()->SetRangeUser(-150.,150.);
    // mhtxy->GetYaxis()->SetRangeUser(0.,10000.);
    c2->Clear();
    c2->SetLogy();

    mhtxy->Draw("LPEBh");
    mhtxyMC->Draw("sameh");
    TString save("MHTyBin_");
      save+=i;
      c2->SaveAs(save+"_.pdf");

    Double_t  sigma = mhtxy->GetFunction("ga1")->GetParameter(2);
    Double_t  sigmaMC = mhtxyMC->GetFunction("ga2")->GetParameter(2);
    Double_t max1 = 0 + 1*(sigma);
    Double_t maxMC1 = 0 + 1*(sigmaMC);
    Double_t min1 = 0 - 1*(sigma);
    Double_t minMC1 = 0 - 1*(sigmaMC);
    Double_t max2 = 0 + 2*(sigma);
    Double_t maxMC2 = 0 + 2*(sigmaMC);
    Double_t min2 = 0 - 2*(sigma);
    Double_t minMC2 = 0 - 2*(sigmaMC);
    Double_t max3 = 0 + 3*(sigma);
    Double_t maxMC3 = 0 + 3*(sigmaMC);
    Double_t min3 = 0 - 3*(sigma);
    Double_t minMC3 = 0 - 3*(sigmaMC);


    Double_t genErrFac = ( sqrt(mhtxy->Integral("width"))/mhtxy->Integral("width"))* ( sqrt(mhtxy->Integral("width"))/mhtxy->Integral("width"));
    Double_t genErrFacMC = ( sqrt(mhtxyMC->Integral("width"))/mhtxyMC->Integral("width"))* ( sqrt(mhtxyMC->Integral("width"))/mhtxyMC->Integral("width"));

    Double_t remUP1 = 0.5*( mhtxy->Interpolate( max1 ) + mhtxy->GetBinContent( ( mhtxy->FindBin( max1 ) ) ) )*fabs( max1-mhtxy->GetBinLowEdge( mhtxy->FindBin( max1 ) ) );
    Double_t remLOW1 = 0.5*( mhtxy->Interpolate(min1) + mhtxy->GetBinContent( (mhtxy->FindBin(min1) ) ) )*fabs( min1 - mhtxy->GetBinLowEdge( mhtxy->FindBin( min1 ) + 1 ) );
    Double_t remUPMC1 = 0.5*( mhtxyMC->Interpolate( maxMC1 ) + mhtxyMC->GetBinContent( (mhtxyMC->FindBin(maxMC1) ) ) )*fabs( maxMC1- mhtxyMC->GetBinLowEdge( mhtxyMC->FindBin( maxMC1 ) ) );
    Double_t remLOWMC1 = 0.5*( mhtxyMC->Interpolate( minMC1 ) + mhtxyMC->GetBinContent( (mhtxyMC->FindBin(minMC1) ) ) )*fabs( minMC1 - mhtxyMC->GetBinLowEdge( mhtxyMC->FindBin( minMC1 )+1 ) ) ;

    Double_t remUP2 = 0.5*( mhtxy->Interpolate( max2 ) + mhtxy->GetBinContent( ( mhtxy->FindBin( max2 ) ) ) )*fabs( max2-mhtxy->GetBinLowEdge( mhtxy->FindBin( max2 ) ) );
    Double_t remLOW2 = 0.5*( mhtxy->Interpolate(min2) + mhtxy->GetBinContent( (mhtxy->FindBin(min2) ) ) )*fabs( min2 - mhtxy->GetBinLowEdge( mhtxy->FindBin( min2 ) + 1 ) );
    Double_t remUPMC2 = 0.5*( mhtxyMC->Interpolate( maxMC2 ) + mhtxyMC->GetBinContent( (mhtxyMC->FindBin(maxMC2) ) ) )*fabs( maxMC2- mhtxyMC->GetBinLowEdge( mhtxyMC->FindBin( maxMC2 ) ) );
    Double_t remLOWMC2 = 0.5*( mhtxyMC->Interpolate( minMC2 ) + mhtxyMC->GetBinContent( (mhtxyMC->FindBin(minMC2) ) ) )*fabs( minMC2 - mhtxyMC->GetBinLowEdge( mhtxyMC->FindBin( minMC2 )+1 ) ) ;

    Double_t remUP3 = 0.5*( mhtxy->Interpolate( max3 ) + mhtxy->GetBinContent( ( mhtxy->FindBin( max3 ) ) ) )*fabs( max3-mhtxy->GetBinLowEdge( mhtxy->FindBin( max3 ) ) );
    Double_t remLOW3 = 0.5*( mhtxy->Interpolate(min3) + mhtxy->GetBinContent( (mhtxy->FindBin(min3) ) ) )*fabs( min3 - mhtxy->GetBinLowEdge( mhtxy->FindBin( min3 ) + 1 ) );
    Double_t remUPMC3 = 0.5*( mhtxyMC->Interpolate( maxMC3 ) + mhtxyMC->GetBinContent( (mhtxyMC->FindBin(maxMC3) ) ) )*fabs( maxMC3- mhtxyMC->GetBinLowEdge( mhtxyMC->FindBin( maxMC3 ) ) );
    Double_t remLOWMC3 = 0.5*( mhtxyMC->Interpolate( minMC3 ) + mhtxyMC->GetBinContent( (mhtxyMC->FindBin(minMC3) ) ) )*fabs( minMC3 - mhtxyMC->GetBinLowEdge( mhtxyMC->FindBin( minMC3 )+1 ) ) ;





    fract1[c] = ( mhtxy->Integral( "width" ) - ( mhtxy->Integral( mhtxy->FindBin( min1 )+1,mhtxy->FindBin( max1 )-1,"width" ) + remUP1 + remLOW1) )/( mhtxy->Integral( "width" ) );

    double errorStart1 = ( mhtxy->Integral( "width" ) - ( mhtxy->Integral( mhtxy->FindBin( min1 )+1,mhtxy->FindBin( max1 )-1,"width" ) + remUP1 + remLOW1) );
    ef1[c] = (sqrt(errorStart1) / errorStart1) * (sqrt(errorStart1) / errorStart1) + genErrFac;
    cout << "error on point " << ef1[c] << endl;

    fract2[c] = ( mhtxy->Integral( "width" ) - ( mhtxy->Integral( mhtxy->FindBin( min2 )+1,mhtxy->FindBin( max2 )-1,"width" ) + remUP2 + remLOW2) )/( mhtxy->Integral( "width" ) );
    double errorStart2 = ( mhtxy->Integral( "width" ) - ( mhtxy->Integral( mhtxy->FindBin( min2 )+1,mhtxy->FindBin( max2 )-1,"width" ) + remUP2 + remLOW2) );
    ef2[c]=(sqrt(errorStart2) / errorStart2) * (sqrt(errorStart2) / errorStart2) + genErrFac;


    fract3[c] = ( mhtxy->Integral( "width" ) - ( mhtxy->Integral( mhtxy->FindBin( min3 )+1,mhtxy->FindBin( max3 )-1,"width" ) + remUP3 + remLOW3) )/( mhtxy->Integral( "width" ) );
    double errorStart3 =( mhtxy->Integral( "width" ) - ( mhtxy->Integral( mhtxy->FindBin( min3 )+1,mhtxy->FindBin( max3 )-1,"width" ) + remUP3 + remLOW3) );
    ef3[c]=(sqrt(errorStart3) / errorStart3) * (sqrt(errorStart3) / errorStart3) + genErrFac;





    cout << fract1[c] << "fract 1" << endl;
    cout << fract2[c] << "fract 1" << endl;
    cout << fract3[c] << "fract 1" << endl;


        // fract3[c]=fractions;
    cout << " C " << c << " Fract[c] " << fract3[c] << endl;

      fractMC1[c] = ( mhtxyMC->Integral( "width" ) - ( mhtxyMC->Integral( mhtxyMC->FindBin( minMC1 )+1,mhtxyMC->FindBin( maxMC1 )-1,"width" ) + remUPMC1 + remLOWMC1) )/( mhtxyMC->Integral( "width" ) );

    double errorStartMC1 = ( mhtxyMC->Integral( "width" ) - ( mhtxyMC->Integral( mhtxyMC->FindBin( minMC1 )+1,mhtxyMC->FindBin( maxMC1 )-1,"width" ) + remUPMC1 + remLOWMC1) );
    efMC1[c] = (sqrt(errorStartMC1) / errorStartMC1) * (sqrt(errorStartMC1) / errorStartMC1) + genErrFacMC;
    cout << "error on point efMC1[c]" << efMC1[c] << endl;

    fractMC2[c] = ( mhtxyMC->Integral( "width" ) - ( mhtxyMC->Integral( mhtxyMC->FindBin( minMC2 )+1,mhtxyMC->FindBin( maxMC2 )-1,"width" ) + remUPMC2 + remLOWMC2) )/( mhtxyMC->Integral( "width" ) );
    double errorStartMC2 = ( mhtxyMC->Integral( "width" ) - ( mhtxyMC->Integral( mhtxyMC->FindBin( minMC2 )+1,mhtxyMC->FindBin( maxMC2 )-1,"width" ) + remUPMC2 + remLOWMC2) );
    efMC2[c]=(sqrt(errorStartMC2) / errorStartMC2) * (sqrt(errorStartMC2) / errorStartMC2) + genErrFacMC;


    fractMC3[c] = ( mhtxyMC->Integral( "width" ) - ( mhtxyMC->Integral( mhtxyMC->FindBin( minMC3 )+1,mhtxyMC->FindBin( maxMC3 )-1,"width" ) + remUPMC3 + remLOWMC3) )/( mhtxyMC->Integral( "width" ) );
    double errorStartMC3 =( mhtxyMC->Integral( "width" ) - ( mhtxyMC->Integral( mhtxyMC->FindBin( minMC3 )+1,mhtxyMC->FindBin( maxMC3 )-1,"width" ) + remUPMC3 + remLOWMC3) );
    efMC3[c]=(sqrt(errorStartMC3) / errorStartMC3) * (sqrt(errorStartMC3) / errorStartMC3) + genErrFacMC;




//start CALO

    Double_t FmaxCALO = 1.5*(metxyCALO->GetRMS(1));
    Double_t FminCALO = -1.5*(metxyCALO->GetRMS(1));
    TF1 *gfit3 = new TF1("ga3","gaus",FminCALO,FmaxCALO); // Create the fit function
    metxyCALO->Fit("ga3","QR");
    metxyCALO->Draw("h");
    Double_t FmaxCALOMC = 1*(metxyCALOMC->GetRMS(1));
    Double_t FminCALOMC = -1*(metxyCALOMC->GetRMS(1));
    TF1 *gfit4 = new TF1("ga4","gaus",FminCALOMC,FmaxCALOMC); // Create the fit function
    metxyCALO->Fit("ga3","QR");
    metxyCALOMC->Fit("ga4","QR");

    metxyCALO->SetMarkerStyle(20);
    metxyCALOMC->GetFunction("ga4")->SetLineColor(6);
    metxyCALO->GetFunction("ga3")->SetLineColor(4);
    metxyCALOMC->SetLineColor(2);
    metxyCALO->GetXaxis()->SetRangeUser(-150.,150.);
      metxyCALO->GetXaxis()->SetRangeUser(-150.,150.);
      // metxyCALO->GetYaxis()->SetRangeUser(0.,10000.);
        c2->Clear();
        c2->SetLogy();
    metxyCALO->Draw("LPEBh");
    metxyCALOMC->Draw("sameh");
    TString save("metyBin_");
    save+=i;
    c2->SaveAs(save+"_.pdf");

    Double_t  sigma = metxyCALO->GetFunction("ga3")->GetParameter(2);
    Double_t  sigmaMC = metxyCALOMC->GetFunction("ga4")->GetParameter(2);
    Double_t maxCALO1 = 0 + 1*(sigma);
    Double_t maxCALOMC1 = 0 + 1*(sigmaMC);
    Double_t minCALO1 = 0 - 1*(sigma);
    Double_t minCALOMC1 = 0 - 1*(sigmaMC);
    Double_t maxCALO2 = 0 + 2*(sigma);
    Double_t maxCALOMC2 = 0 + 2*(sigmaMC);
    Double_t minCALO2 = 0 - 2*(sigma);
    Double_t minCALOMC2 = 0 - 2*(sigmaMC);
    Double_t maxCALO3 = 0 + 3*(sigma);
    Double_t maxCALOMC3 = 0 + 3*(sigmaMC);
    Double_t minCALO3 = 0 - 3*(sigma);
    Double_t minCALOMC3 = 0 - 3*(sigmaMC);


    Double_t genErrFacCALO = ( sqrt(metxyCALO->Integral("width"))/metxyCALO->Integral("width"))* ( sqrt(metxyCALO->Integral("width"))/metxyCALO->Integral("width"));
    Double_t genErrFacCALOMC = ( sqrt(metxyCALOMC->Integral("width"))/metxyCALOMC->Integral("width"))* ( sqrt(metxyCALOMC->Integral("width"))/metxyCALOMC->Integral("width"));

    Double_t remCALOUP1 = 0.5*( metxyCALO->Interpolate( maxCALO1 ) + metxyCALO->GetBinContent( ( metxyCALO->FindBin( maxCALO1 ) ) ) )*fabs( maxCALO1-metxyCALO->GetBinLowEdge( metxyCALO->FindBin( maxCALO1 ) ) );
    Double_t remCALOLOW1 = 0.5*( metxyCALO->Interpolate(minCALO1) + metxyCALO->GetBinContent( (metxyCALO->FindBin(minCALO1) ) ) )*fabs( minCALO1 - metxyCALO->GetBinLowEdge( metxyCALO->FindBin( minCALO1 ) + 1 ) );
    Double_t remCALOUPMC1 = 0.5*( metxyCALOMC->Interpolate( maxCALOMC1 ) + metxyCALOMC->GetBinContent( (metxyCALOMC->FindBin(maxCALOMC1) ) ) )*fabs( maxCALOMC1- metxyCALOMC->GetBinLowEdge( metxyCALOMC->FindBin( maxCALOMC1 ) ) );
    Double_t remCALOLOWMC1 = 0.5*( metxyCALOMC->Interpolate( minCALOMC1 ) + metxyCALOMC->GetBinContent( (metxyCALOMC->FindBin(minCALOMC1) ) ) )*fabs( minCALOMC1 - metxyCALOMC->GetBinLowEdge( metxyCALOMC->FindBin( minCALOMC1 )+1 ) ) ;

    Double_t remCALOUP2 = 0.5*( metxyCALO->Interpolate( maxCALO2 ) + metxyCALO->GetBinContent( ( metxyCALO->FindBin( maxCALO2 ) ) ) )*fabs( maxCALO2-metxyCALO->GetBinLowEdge( metxyCALO->FindBin( maxCALO2 ) ) );
    Double_t remCALOLOW2 = 0.5*( metxyCALO->Interpolate(minCALO2) + metxyCALO->GetBinContent( (metxyCALO->FindBin(minCALO2) ) ) )*fabs( minCALO2 - metxyCALO->GetBinLowEdge( metxyCALO->FindBin( minCALO2 ) + 1 ) );
    Double_t remCALOUPMC2 = 0.5*( metxyCALOMC->Interpolate( maxCALOMC2 ) + metxyCALOMC->GetBinContent( (metxyCALOMC->FindBin(maxCALOMC2) ) ) )*fabs( maxCALOMC2- metxyCALOMC->GetBinLowEdge( metxyCALOMC->FindBin( maxCALOMC2 ) ) );
    Double_t remCALOLOWMC2 = 0.5*( metxyCALOMC->Interpolate( minCALOMC2 ) + metxyCALOMC->GetBinContent( (metxyCALOMC->FindBin(minCALOMC2) ) ) )*fabs( minCALOMC2 - metxyCALOMC->GetBinLowEdge( metxyCALOMC->FindBin( minCALOMC2 )+1 ) ) ;

    Double_t remCALOUP3 = 0.5*( metxyCALO->Interpolate( maxCALO3 ) + metxyCALO->GetBinContent( ( metxyCALO->FindBin( maxCALO3 ) ) ) )*fabs( maxCALO3-metxyCALO->GetBinLowEdge( metxyCALO->FindBin( maxCALO3 ) ) );
    Double_t remCALOLOW3 = 0.5*( metxyCALO->Interpolate(minCALO3) + metxyCALO->GetBinContent( (metxyCALO->FindBin(minCALO3) ) ) )*fabs( minCALO3 - metxyCALO->GetBinLowEdge( metxyCALO->FindBin( minCALO3 ) + 1 ) );
    Double_t remCALOUPMC3 = 0.5*( metxyCALOMC->Interpolate( maxCALOMC3 ) + metxyCALOMC->GetBinContent( (metxyCALOMC->FindBin(maxCALOMC3) ) ) )*fabs( maxCALOMC3- metxyCALOMC->GetBinLowEdge( metxyCALOMC->FindBin( maxCALOMC3 ) ) );
    Double_t remCALOLOWMC3 = 0.5*( metxyCALOMC->Interpolate( minCALOMC3 ) + metxyCALOMC->GetBinContent( (metxyCALOMC->FindBin(minCALOMC3) ) ) )*fabs( minCALOMC3 - metxyCALOMC->GetBinLowEdge( metxyCALOMC->FindBin( minCALOMC3 )+1 ) ) ;





    fractCALO1[c] = ( metxyCALO->Integral( "width" ) - ( metxyCALO->Integral( metxyCALO->FindBin( minCALO1 )+1,metxyCALO->FindBin( maxCALO1 )-1,"width" ) + remCALOUP1 + remCALOLOW1) )/( metxyCALO->Integral( "width" ) );

    double errorStartCALO1 = ( metxyCALO->Integral( "width" ) - ( metxyCALO->Integral( metxyCALO->FindBin( minCALO1 )+1,metxyCALO->FindBin( maxCALO1 )-1,"width" ) + remCALOUP1 + remCALOLOW1) );
    efCALO1[c] = (sqrt(errorStartCALO1) / errorStartCALO1) * (sqrt(errorStartCALO1) / errorStartCALO1) + genErrFacCALO;
    cout << "error on point " << efCALO1[c] << endl;

    fractCALO2[c] = ( metxyCALO->Integral( "width" ) - ( metxyCALO->Integral( metxyCALO->FindBin( minCALO2 )+1,metxyCALO->FindBin( maxCALO2 )-1,"width" ) + remCALOUP2 + remCALOLOW2) )/( metxyCALO->Integral( "width" ) );
    double errorStartCALO2 = ( metxyCALO->Integral( "width" ) - ( metxyCALO->Integral( metxyCALO->FindBin( minCALO2 )+1,metxyCALO->FindBin( maxCALO2 )-1,"width" ) + remCALOUP2 + remCALOLOW2) );
    efCALO2[c]=(sqrt(errorStartCALO2) / errorStartCALO2) * (sqrt(errorStartCALO2) / errorStartCALO2) + genErrFacCALO;


    fractCALO3[c] = ( metxyCALO->Integral( "width" ) - ( metxyCALO->Integral( metxyCALO->FindBin( minCALO3 )+1,metxyCALO->FindBin( maxCALO3 )-1,"width" ) + remCALOUP3 + remCALOLOW3) )/( metxyCALO->Integral( "width" ) );
    double errorStartCALO3 =( metxyCALO->Integral( "width" ) - ( metxyCALO->Integral( metxyCALO->FindBin( minCALO3 )+1,metxyCALO->FindBin( maxCALO3 )-1,"width" ) + remCALOUP3 + remCALOLOW3) );
    efCALO3[c]=(sqrt(errorStartCALO3) / errorStartCALO3) * (sqrt(errorStartCALO3) / errorStartCALO3) + genErrFacCALO;





    cout << fractCALO1[c] << "fractCALO 1" << endl;
    cout << fractCALO2[c] << "fractCALO 1" << endl;
    cout << fractCALO3[c] << "fractCALO 1" << endl;


    // fractCALO3[c]=fractCALOions;
    cout << " C " << c << " fractCALO[c] " << fractCALO3[c] << endl;

    fractCALOMC1[c] = ( metxyCALOMC->Integral( "width" ) - ( metxyCALOMC->Integral( metxyCALOMC->FindBin( minCALOMC1 )+1,metxyCALOMC->FindBin( maxCALOMC1 )-1,"width" ) + remCALOUPMC1 + remCALOLOWMC1) )/( metxyCALOMC->Integral( "width" ) );

    double errorStartCALOMC1 = ( metxyCALOMC->Integral( "width" ) - ( metxyCALOMC->Integral( metxyCALOMC->FindBin( minCALOMC1 )+1,metxyCALOMC->FindBin( maxCALOMC1 )-1,"width" ) + remCALOUPMC1 + remCALOLOWMC1) );
    efCALOMC1[c] = (sqrt(errorStartCALOMC1) / errorStartCALOMC1) * (sqrt(errorStartCALOMC1) / errorStartCALOMC1) + genErrFacCALOMC;
    cout << "error on point efCALOMC1[c]" << efCALOMC1[c] << endl;

    fractCALOMC2[c] = ( metxyCALOMC->Integral( "width" ) - ( metxyCALOMC->Integral( metxyCALOMC->FindBin( minCALOMC2 )+1,metxyCALOMC->FindBin( maxCALOMC2 )-1,"width" ) + remCALOUPMC2 + remCALOLOWMC2) )/( metxyCALOMC->Integral( "width" ) );
    double errorStartCALOMC2 = ( metxyCALOMC->Integral( "width" ) - ( metxyCALOMC->Integral( metxyCALOMC->FindBin( minCALOMC2 )+1,metxyCALOMC->FindBin( maxCALOMC2 )-1,"width" ) + remCALOUPMC2 + remCALOLOWMC2) );
    efCALOMC2[c]=(sqrt(errorStartCALOMC2) / errorStartCALOMC2) * (sqrt(errorStartCALOMC2) / errorStartCALOMC2) + genErrFacCALOMC;


    fractCALOMC3[c] = ( metxyCALOMC->Integral( "width" ) - ( metxyCALOMC->Integral( metxyCALOMC->FindBin( minCALOMC3 )+1,metxyCALOMC->FindBin( maxCALOMC3 )-1,"width" ) + remCALOUPMC3 + remCALOLOWMC3) )/( metxyCALOMC->Integral( "width" ) );
    double errorStartCALOMC3 =( metxyCALOMC->Integral( "width" ) - ( metxyCALOMC->Integral( metxyCALOMC->FindBin( minCALOMC3 )+1,metxyCALOMC->FindBin( maxCALOMC3 )-1,"width" ) + remCALOUPMC3 + remCALOLOWMC3) );
    efCALOMC3[c]=(sqrt(errorStartCALOMC3) / errorStartCALOMC3) * (sqrt(errorStartCALOMC3) / errorStartCALOMC3) + genErrFacCALOMC;








        // cout << " Values between " << min << " and " << max << " corrosponding to a mean of " << 0 << " and an RMS of " << mhtxy->GetRMS(1) << " have number of events over " << h <<" sigma = " << (mhtxy->Integral("width") - (mhtxy->Integral(mhtxy->FindBin(min)+1,mhtxy->FindBin(max)-1,"width")+remUP+remLOW)) << " Giving fraction "<< fractions  << endl;
      // }
    c++;

    }
    TCanvas *canvas  = new TCanvas("canvas","a name", 800,600);
    TMultiGraph *q   = new TMultiGraph();
    canvas->Clear();
    canvas->cd();
    TGraphErrors *g1 = new TGraphErrors(8,htVal,fract1,0,ef1);
    TGraphErrors *g2 = new TGraphErrors(8,htVal,fractMC1,0,efMC1);
    g1->SetMarkerStyle(23);
    g1->SetMarkerColor(1);
    // g1->Draw("a");
    g1->SetLineColor(1);
    g2->SetMarkerStyle(29);
    g2->SetMarkerColor(1);
    q->Add(g1,"P");
    q->Add(g2,"P");
    // q->GetXaxis()->SetTitle("HT Bin");
    // q->GetYaxis()->SetTitle("Fraction above 2 sigma");
    TGraphErrors *g3 = new TGraphErrors(8,htVal,fract2,0,ef2);
    TGraphErrors *g4 = new TGraphErrors(8,htVal,fractMC2,0,efMC2);
    g3->SetMarkerStyle(23);
    g4->SetMarkerStyle(29);
    g3->SetLineColor(2);
    g4->SetLineColor(2);

    g3->SetMarkerColor(2);
    g4->SetMarkerColor(2);
    q->Add(g4,"P");
    q->Add(g3,"P");
    TGraphErrors *g5 = new TGraphErrors(8,htVal,fract3,0,ef3);
    TGraphErrors *g6 = new TGraphErrors(8,htVal,fractMC3,0,efMC3);
    g5->SetMarkerStyle(23);
    g5->SetMarkerColor(4);
    g5->SetLineColor(4);
    g6->SetMarkerStyle(29);
    g6->SetMarkerColor(4);
    q->Add(g5,"P");
    q->Add(g6,"P");



    TGraphErrors *g7 = new TGraphErrors(8,htVal,fractCALO1,0,efCALO1);
    TGraphErrors *g8 = new TGraphErrors(8,htVal,fractCALOMC1,0,efCALOMC1);
    g7->SetMarkerStyle(27);
    g8->SetMarkerColor(1);
    // g1->Draw("a");
    g7->SetLineColor(1);
    g8->SetMarkerStyle(28);
    g8->SetMarkerColor(1);
    q->Add(g7,"P");
    q->Add(g8,"P");
    // q->GetXaxis()->SetTitle("HT Bin");
    // q->GetYaxis()->SetTitle("Fraction above 2 sigma");
    TGraphErrors *g9 = new TGraphErrors(8,htVal,fractCALO2,0,efCALO2);
    TGraphErrors *g10 = new TGraphErrors(8,htVal,fractCALOMC2,0,efCALOMC2);
    g9->SetMarkerStyle(27);
    g10->SetMarkerStyle(2);
    g9->SetLineColor(2);
    g10->SetLineColor(2);

    g10->SetMarkerColor(2);
    g9->SetMarkerColor(2);
    q->Add(g9,"P");
    q->Add(g10,"P");
    TGraphErrors *g11 = new TGraphErrors(8,htVal,fractCALO3,0,efCALO3);
    TGraphErrors *g12 = new TGraphErrors(8,htVal,fractCALOMC3,0,efCALOMC3);
    g11->SetMarkerStyle(27);
    g11->SetMarkerColor(4);
    g11->SetLineColor(4);
    g12->SetMarkerStyle(28);
    g12->SetMarkerColor(4);
    q->Add(g11,"P");
    q->Add(g12,"P");






    L2->Clear();
    L1->Clear();
    L1->AddEntry( g1, "1 #sigma" ,"l");
    L1->AddEntry( g3, "2 #sigma" ,"l");
    L1->AddEntry( g5, "3 #sigma" ,"l");
    L2->AddEntry( g1 , " Data (MHT)", "P");
    L2->AddEntry( g2 , " MC (MHT) ", "P");
    L2->AddEntry( g7 , " Data (MET)", "P");
    L2->AddEntry( g8 , " MC (MET) ", "P");
    L2->Draw("same");
    L1->Draw("same");
    q->Draw("a");
    q->GetXaxis()->SetTitle("HT Bin");
    q->GetYaxis()->SetTitle("Fraction above N sigma");
 q->GetYaxis()->SetRangeUser(0.,0.5);


    // can->SetLogy();
    canvas->SaveAs("nSigY.pdf");





}

Data->Close();
MC->Close();
delete Data;
delete MC;

}