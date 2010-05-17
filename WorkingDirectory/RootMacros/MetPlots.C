// -----------------------------------------------------------------------------
/*
Arguments to createPlot():
- path to input files
- canvas title
- histogram title
- histogram directory
- rebin histograms?
- normalize all histograms to unit area?
- logarithmic y-scale
- Projection
- output file
*/
int MetPlots() {

  // Path to input files
  TString path = "./";

  // Output file
  TFile* output = new TFile( "Plots.root", "RECREATE" );
  if ( !output || output->IsZombie() ) { return -1; }

  if (1) {

//MT2 Plots
    // createPlot( path, "MHT", "MHT_all" , "MT2", 10, true, true,false ,output);
    // createPlot( path, "MHT X", "MHT X_all" , "MT2", 2, false, true,false ,output);
    // createPlot( path, "MHT Y", "MHT Y_all" , "MT2", 2, false, true,false ,output);
    createPlot( path, "HT vs MHT", "HT vs MHT_all" , "MT2", false, false, true,true, output);
    createPlot( path, "SumEt vs Calo MET", "#sum{E_{T}} vs Calo MET_all" , "MT2", false, false, true,true, output);


  }

  if ( 0 ){

    createPlot( path, "HT vs MHT2", "HT vs MHT_all" , "MT2", false, false, false,false, output);
    createPlot( path, "Alpha T Dijet", "AlphaT_2", "KinSuitePlots", false , true, true,false, output);
    createPlot( path, "Calo Met", "Callo MET_all" , "MT2", 10, true, true,false ,output);

      // projection plots
    createPlot( path, "HT vs MHT_X", "HT vs MHT_X_all" , "MT2", false, false, true,true, output);
    createPlot( path, "HT vs MHT_Y", "HT vs MHT_Y_all" , "MT2", false, false, true,true, output);
    createPlot( path, "SumEt vs HT", "#sum{E_{T}} vs HT_all" , "MT2", false, false, true,true, output);
    createPlot( path, "SumEt vs Calo MET", "#sum{E_{T}} vs Calo MET_all" , "MT2", false, false, true,true, output);

      // createPlot( path, "MT2", "Mt2_all", "MT2", 10, true, true, output );
      // createPlot( path, "MT2 vs aplha T", "Mt2 vs AlphaT_all", "MT2", 10, false, false, output );

  //Common Jet Plots
    createPlot( path, "Multiplicity", "Multiplicity", "CommonJetPlots", false, true, true,false ,output );
    createPlot( path, "Pt alljet spectrium", "Pt_all", "CommonJetPlots", 10, true, true, false,output );
    createPlot( path, "Pt leading Jet", "Pt_1", "CommonJetPlots", 10, true, true, false,output );
    createPlot( path, "Pt second Jet", "Pt_2", "CommonJetPlots", 10, true, true, false,output );
    createPlot( path, "ET", "Et_all", "CommonJetPlots", 10, true, true,false ,output );

    // Object Kine Plots
    createPlot( path, "eta leading Jet", "eta_1", "ObjectKinePlots", 5,true, true, false,output);
    createPlot( path, "eta second Jet", "eta_2", "ObjectKinePlots",5 ,true, true,false, output);
    createPlot( path, "#Delta #eta(j#_{1},j#_{2})", "DeltaEta_1", "ObjectKinePlots",5 ,true, true,false, output);




  }


  if (0) {

    createPlot( path, "MT2 vs mt(j1+j2)", "hDalitzMT2Mjj_all", "MT2", false, true, true, output );
    createPlot( path, "MT2 vs mt(j2+mht)", "hDalitzMT2mt_j2_mht_all", "MT2", false, true, true, output );
    createPlot( path, "MT2 vs mt(j1+mht)", "hDalitzMT2mt_j1_mht_all", "MT2", false, true, true, output );

    // createPlot( path, "SecondJetEta", "Eta_2", "Hadronic", 10, false, true, output );
    // createPlot( path, "DeltaEta", "DeltaEta_1", "Hadronic", 10, false, true, output );
    // createPlot( path, "DeltaR", "DeltaR_1", "Hadronic", 10, false, true, output );
    // createPlot( path, "LeadingJetEtaNorm", "Eta_1", "Hadronic", 10, true, true, output );
    // createPlot( path, "SecondJetEtaNorm", "Eta_2", "Hadronic", 10, true, true, output );
    // createPlot( path, "DeltaEtaNorm", "DeltaEta_1", "Hadronic", 10, true, true, output );
    // createPlot( path, "DeltaRNorm", "DeltaR_1", "Hadronic", 10, true, true, output );
  }

  output->Write();
  output->Close();
  delete output;

}

// -----------------------------------------------------------------------------
//
TCanvas* createPlot( TString path,
  TString canvas_name,
  TString name,
  TString dirmame,
  int rebin,
  bool norm,
  bool log,
  bool project,
  TDirectory* file
  )
{

  // SetSomeStyles();

  // Create legend
  TLegend* legend = new TLegend( 0.75, 0.65, 0.92, 0.92, NULL, "brNDC" );
  legend->SetFillColor(0);
  legend->SetLineColor(0);

  // Create canvas
  TCanvas* aCanvas = createCanvas( canvas_name, file, log );

  // Create histograms

  TH1D* MC  = getHisto( path, name, "IC5Calo_MinBias MC.root", dirmame, rebin );
  TH1D* Data  = getHisto( path, name, "IC5Calo_NewData.root", dirmame, rebin );

  // Line colour and fill
  if ( MC ) MC->SetLineColor(kRed);
  // if ( MC ) MC->SetFillColor(kRed);
  if ( MC ) MC->SetFillStyle(3003);
  if ( Data ) Data->SetLineColor(kBlack);
  if ( Data ) Data->SetLineStyle(1);
  if ( Data ) Data->SetLineWidth(1);
  if ( Data ) Data->SetMarkerStyle(20);
  // Populate legend
  legend->AddEntry( Data, " All Data ", "L" );
  legend->AddEntry( MC, " MC ", "f" );
  // Calc maximum number of entries
  double aMax = 0.;
  if ( Data->GetMaximum()     > aMax ) { aMax = Data->GetMaximum(); }
  if ( MC->GetMaximum() > aMax ) { aMax = MC->GetMaximum(); }


  // Calc minimum number of entries
  double aMin = 1.e12;
  if ( Data->GetMinimum(1.e-12)     < aMin ) { aMin = Data->GetMinimum(1.e-12); }
  if ( MC->GetMinimum(1.e-12) < aMin ) { aMin = MC->GetMinimum(1.e-12); }
  // if ( Data ) Data->GetXaxis()->SetRangeUser(0.,400.);
  // if ( MC ) MC->GetXaxis()->SetRangeUser(0.,400.);
  if ( Data ) Data->GetYaxis()->SetTitleOffset(1.43);
  if ( Data ) Data->GetYaxis()->SetTitleSize(0.06);
  if ( Data ) Data->GetXaxis()->SetTitleSize(0.06);
  if ( Data ) Data->GetXaxis()->SetTitleOffset(0.9);

  if ( log ) {
    if ( Data ) Data->SetMaximum( aMax * 10. );
    if ( Data ) Data->SetMinimum( aMin * 0.1 );
  } else {
    if ( Data ) Data->SetMaximum( aMax * 1.1 );
    if ( Data ) Data->SetMinimum( aMin * 0.9 );
  }
  if ( project ){
    TCanvas *c1 = new TCanvas("c1","projecton",10,10,800,600);
    c1->cd();
    Int_t n = Data->GetYaxis()->GetNbins();
    // Int_t w = Data->GetYaxis()->GetBinWidth();
    for(int i = 0; i < n; i+=4){

      Int_t up = Data->GetYaxis()->GetBinUpEdge(i+4);
      Int_t low = Data->GetYaxis()->GetBinLowEdge(i+1);
      std::cout << "Lower bin value " << low << " upper bin value " << up << std::endl;

      TString bins("MHT in Bins of HT (");
      bins+=low;
      TString mid("<HT<");
      bins+=mid;
      bins+=up;
      TString end(")");
      bins+=end;
      std::cout << bins << endl;

      TH1D *px1 = Data->TH2D::ProjectionY("px1",i+1,i+4,"o");
      if(px1->Integral() == 0) continue;// bool can put in else where.
      px1->GetXaxis()->SetRangeUser(0.,200.);
      px1->GetYaxis()->SetTitle(bins);
      px1->GetXaxis()->SetTitle("MHT (GeV)");
      TH1D *px2 = MC->TH2D::ProjectionY("px2",i+1,i+4,"o");
      px2->Scale(px1->Integral()/px2->Integral());






      px1->Draw("LPEBh");
      px2->Draw("sameh");
      //Save as a png with name of orig plot + sting. to append Integer to string
      // TString a("string");
      // a+=integer;
      // a = stringinteger <---- so far the only way I know to do this.
      TString type(".png");
      bins+=canvas_name;
      bins+=type;

      c1->SetFillColor(0);
      c1->SetBorderMode(0);
      c1->SetBorderSize(2);
      if ( log == true)c1->SetLogy();
      c1->SetLeftMargin(0.1765705);
      c1->SetRightMargin(0.05772496);
      c1->SetTopMargin(0.04778761);
      c1->SetBottomMargin(0.1256637);
      c1->SetFrameFillStyle(0);
      c1->SetFrameLineWidth(2);
      c1->SetFrameBorderMode(0);
      c1->SetFrameFillStyle(0);
      c1->SetFrameLineWidth(2);
      c1->SetFrameBorderMode(0);


      c1->SaveAs(bins);
    }

    if (Data) { TH1D *px19 = Data->TH2D::ProjectionY("px19",1,40,"o");
    px19->GetXaxis()->SetRangeUser(0.,200.);
    px19->GetYaxis()->SetTitle("");
    px19->GetXaxis()->SetTitle("MHT (GeV)");
    px19->Draw("LPEBh");}


    if (MC)   { TH1D *px20 = MC->TH2D::ProjectionY("px20",1,40,"o");
    px20->GetXaxis()->SetRangeUser(0.,200.);
    px20->Scale(px19->Integral()/px20->Integral());
    px20->Draw("sameh");}
    c1->SaveAs("MHT_all.png");


  }
  // bool percentile = true;


  if ( canvas_name == TString("HT vs MHT") || canvas_name == TString("SumEt vs Calo MET") ){
      //
    TCanvas *c2 = new TCanvas("c2","outliers",10,10,1024,640);
    double p1[8]; // 90%
    double p2[8]; // 95%
    double p3[8]; // 99%
    double p1M[8]; // 90%
    double p2M[8]; // 95%
    double p3M[8]; // 99%
    double htVal[8];
    c2->Divide(1,2);
    c2->cd();
    Int_t n = Data->GetYaxis()->GetNbins();
          // Int_t w = Data->GetYaxis()->GetBinWidth();
    int points = 0;
    for(int i = 0; i < n; i+=4){
      c2->Clear();
      c2->cd(1);
      TH1D *px5 = Data->TH2D::ProjectionY("px5",i+1,i+4,"o");
      if(px5->Integral() == 0) continue;
      // if(px6->Integral() == 0) Double_t fractionsMC = 0; continue;

      TH1D *px6 = MC->TH2D::ProjectionY("px6",i+1,i+4,"o");
      px6->Scale(px5->Integral()/px6->Integral());
      double quantileD_points[3];
      double quantileM_points[3];
      double probD[3]; probD[0]= 0.9; probD[1]=0.95; probD[2]=0.99;
      double probM[3]; probM[0]= 0.9; probM[1]=0.95; probM[2]=0.99;
      px5->GetQuantiles( 3 , quantileD_points , probD );
      px6->GetQuantiles( 3 , quantileM_points , probM );
      htVal[points]= (i+1) * 5.0 ;
      p1[points] = quantileD_points[0];
      p2[points] = quantileD_points[1];
      p3[points] = quantileD_points[2];
      p1M[points] = quantileM_points[0];
      p2M[points] = quantileM_points[1];
      p3M[points] = quantileM_points[2];
      TGraph *grM = new TGraph( 3, quantileM_points, probM );
      TGraph *grD = new TGraph( 3, quantileD_points, probD );
      grM->SetMarkerStyle( 21 );
      grD->SetMarkerStyle( 23 );
      // c2->Divide(1,2);
      c2->cd();
      // px5->Draw("LPEBh");
      // px6->Draw("sameh");
      // TMultiGraph *mg = new TMultiGraph();
      // mg->Add(grM,"P");
      // mg->Add(grD,"P");

// show the quantiles in the bottom pad
      // c2->cd(2);
        // gPad->SetGrid();
        // TGraph *gr = new TGraph(nq,xq,yq);
        // gr->SetMarkerStyle(21);
      // TLegend* legend = new TLegend( 0.75, 0.65, 0.92, 0.92, NULL, "brNDC" );
      // legend->SetFillColor(0);
      // legend->SetLineColor(0);
      // legend->AddEntry( grD, " All Data ","P");
      // legend->AddEntry( grM, " MC ","P");

      // mg->Draw("a");
      // legend->Draw();


      TString name("quantile_");
      name+=points;
      name+=TString(".png");
      c2->SaveAs(name);

      // Double_t pxMC[8];
      //       Double_t pyMC[8];
      //       pxMC[points]=points;
      //       pyMC[points]=fractionsMC;
      //
      //       Double_t px[8];
      //       Double_t py[8];
      //       px[points]=points;
      //       py[points]=fractions;
      //
      points++;
    }

      c2->SetFillColor(0);
      c2->SetBorderMode(0);
      c2->SetBorderSize(2);
      c2->SetFrameFillStyle(0);
      c2->SetFrameLineWidth(2);
      c2->SetFrameBorderMode(0);
      c2->SetFrameFillStyle(0);
      c2->SetFrameLineWidth(2);
      c2->SetFrameBorderMode(0);
    TMultiGraph *quantz = new TMultiGraph();
    TGraph *g1 = new TGraph(points, htVal,p1); // 90% data
    TGraph *g2 = new TGraph(points, htVal,p2); // 95% data
    TGraph *g3 = new TGraph(points, htVal,p3); // 99% data
    TGraph *g4 = new TGraph(points, htVal,p1M); // 90% MC
    TGraph *g5 = new TGraph(points, htVal,p2M); // 95% MC
    TGraph *g6 = new TGraph(points, htVal,p3M); // 99% MC

    g1->SetLineColor(1);
    g1->SetFillColor(1);
    g2->SetLineColor(1);
    g3->SetLineColor(1);
    g4->SetLineColor(2);
    g5->SetLineColor(2);
    g6->SetLineColor(2);
    g1->SetMarkerColor(1);
    g2->SetMarkerColor(1);
    g3->SetMarkerColor(1);
    g4->SetMarkerColor(2);
    g5->SetMarkerColor(2);
    g6->SetMarkerColor(2);
    g1->SetMarkerStyle(20);
    g2->SetMarkerStyle(23);
    g3->SetMarkerStyle(29);
    g4->SetMarkerStyle(20);
    g5->SetMarkerStyle(23);
    g6->SetMarkerStyle(29);
    quantz->Add(g1,"Pl");
    quantz->Add(g2,"Pl");
    quantz->Add(g3,"Pl");
    quantz->Add(g4,"Pl");
    quantz->Add(g5,"Pl");
    quantz->Add(g6,"Pl");
    quantz->Draw("a");
    if( canvas_name == TString("SumEt vs Calo MET")){quantz->GetXaxis()->SetTitle("#sum{E_{T}}");
    quantz->GetYaxis()->SetTitle("MET");}
else{
    quantz->GetXaxis()->SetTitle("HT");
    quantz->GetYaxis()->SetTitle("MHT");}
    TLegend* L1 = new TLegend(0.8, 0.9, 0.94, 1.0);// x1, y1, x2, y2
    TLegend* L2 = new TLegend(0.45, 0.9, 0.55, 1.0);// x1, y1, x2, y2
    L2->AddEntry( g1 , " 90% ", "P");
    L2->AddEntry( g2 , " 95% ", "P");
    L2->AddEntry( g3 , " 99% ", "P");
    L2->Draw();
// L1->SetFillColor(0);
// L1->SetLineColor(0);
    L1->AddEntry( g1, " Data ", "L" );
    L1->AddEntry( g4, " MC ", "L" );
    L1->Draw();

    c2->SaveAs(canvas_name + "percentile.png");

    // TMultiGraph *mg = new TMultiGraph();



    // TGraph *g1 = new TGraph(8, px, py);
    // g1->GetYaxis()->SetTitle("Fraction of events above 2sig");
    // g1->GetXaxis()->SetTitle("MHT (GeV)");
    //
    // TGraph *g2 = new TGraph(8, pxMC, pyMC);
    // g2->SetMarkerStyle(20);
    // mg->Add(g2,"P");
    // mg->Add(g1,"*");
    // mg->Draw("a");
    // TLegend* legend = new TLegend( 0.75, 0.65, 0.92, 0.92, NULL, "brNDC" );
    // legend->SetFillColor(0);
    // legend->SetLineColor(0);
    // legend->AddEntry( g1, " All Data ", "*" );
    // legend->AddEntry( g2, " MC ", "P" );
    // legend->Draw();
    c2->SetFillColor(0);
    c2->SetBorderMode(0);
    c2->SetBorderSize(2);
                // if ( log == true)c1->SetLogy();
    c2->SetLeftMargin(0.1765705);
    c2->SetRightMargin(0.05772496);
    c2->SetTopMargin(0.04778761);
    c2->SetBottomMargin(0.1256637);
    c2->SetFrameFillStyle(0);
    c2->SetFrameLineWidth(2);
    c2->SetFrameBorderMode(0);
    c2->SetFrameFillStyle(0);
    c2->SetFrameLineWidth(2);
    c2->SetFrameBorderMode(0);


    c2->SaveAs("outliers.png");
  }



  if( canvas_name == TString("MHT X") || canvas_name == TString("MHT Y") ){ bool fit_ = true;}
  else { bool fit_ = false;}
// fit_ = true;


  if ( fit_ ) {

    Double_t Fmax = Data->GetMean(1) + 4*(Data->GetRMS(1));
    Double_t Fmin = Data->GetMean(1) - 4*(Data->GetRMS(1));
    TF1 *gfit = new TF1("ga1","gaus",Fmin,Fmax); // Create the fit function
    MC->Scale(Data->Integral()/MC->Integral());
    Data->Fit("ga1","QR");
    Data->GetFunction("ga1")->SetLineColor(5);
    Double_t FmaxMC = MC->GetMean(1) + 4*(MC->GetRMS(1));
    Double_t FminMC = MC->GetMean(1) - 4*(MC->GetRMS(1));
    TF1 *gfit2 = new TF1("ga2","gaus",FminMC,FmaxMC);
    MC->Fit("ga2","QR+");
    MC->GetFunction("ga2")->SetLineColor(3); // Create the fit function
    Data->Draw("LPEBh");
    if( Data ) Data->GetXaxis()->SetRangeUser(-175.,175.);
    MC->Draw("sameh");

    for(int i = 0 ; i < 6 ; i++){

      Double_t max = 0 + i*(Data->GetRMS(1));
      Double_t maxMC = 0 + i*(MC->GetRMS(1));
      Double_t min = 0 - i*(Data->GetRMS(1));
      Double_t minMC = 0 - i*(MC->GetRMS(1));


      Double_t remUP = 0.5*( Data->Interpolate( max ) + Data->GetBinContent( ( Data->FindBin( max ) ) ) )*fabs( max-Data->GetBinLowEdge( Data->FindBin( max ) ) );

      Double_t remLOW = 0.5*( Data->Interpolate(min) + Data->GetBinContent( (Data->FindBin(min) ) ) )*fabs( min - Data->GetBinLowEdge( Data->FindBin( min ) + 1 ) );
      std::cout << "Rem Low edge = " << remLOW << std::endl;
      Double_t remUPMC = 0.5*( Data->Interpolate( maxMC ) + Data->GetBinContent( (Data->FindBin(maxMC) ) ) )*fabs( maxMC- Data->GetBinLowEdge( Data->FindBin( maxMC ) ) );

      Double_t remLOWMC = 0.5*( MC->Interpolate( minMC ) + MC->GetBinContent( (MC->FindBin(minMC) ) ) )*fabs( minMC - MC->GetBinLowEdge( MC->FindBin( minMC )+1 ) ) ;




      Double_t fractions = ( Data->Integral( "width" ) - ( Data->Integral( Data->FindBin( min )+1,Data->FindBin( max )-1,"width" ) + remUP + remLOW ) )/( Data->Integral( "width" ) );

      Double_t fractionsMC = (MC->Integral("width") - ( MC->Integral( MC->FindBin( minMC ) + 1,MC->FindBin( maxMC ) - 1 ,"width")+ remUPMC +remLOWMC ) )/(MC->Integral("width") );



      cout << " Values between " << min << " and " << max << " corrosponding to a mean of " << 0 << " and an RMS of " << Data->GetRMS(1) << " have number of events over " << i <<" sigma = " << (Data->Integral("width") - (Data->Integral(Data->FindBin(min)+1,Data->FindBin(max)-1,"width")+remUP+remLOW)) << " Giving fraction "<< fractions  << endl;



      cout << "NOW FOR MC!!!! Values between " << minMC << " and " << maxMC << " corrosponding to a mean of " << 0 << " and an RMS of " << MC->GetRMS(1) << " have number of events over " << i <<" sigma = " << (MC->Integral("width") - (MC->Integral(MC->FindBin(minMC)+1,MC->FindBin(maxMC)-1,"width")+remUPMC+remLOWMC)) << " Giving fraction "<< fractionsMC  << endl;}





    }






    if ( norm ) {
      if ( Data ) Data->DrawNormalized("LPEBhist");


      if ( MC->GetEntries() > 0. ) { MC->DrawNormalized("hsame"); }
    } else {
      if ( Data ) Data->Draw("LPEBh");
      if ( MC ) MC->Draw("sameh");
    }



    file->cd();
    legend->Draw("same");
    aCanvas->SaveAs( std::string(canvas_name+".png").c_str() );
    aCanvas->Write();
    return aCanvas;

  }

// -----------------------------------------------------------------------------
//
  TH1* getHisto( TString path,
    TString nameHist,
    TString nameFile,
    TString Dirname,
  int rebin ) {
    TString name = path + nameFile;
    TFile* file =  new TFile(name);
    TDirectory* dir = (TDirectory*)file->Get(Dirname);
    TH1* hist = (TH1*)dir->Get(nameHist);
    if (!hist) {
      std::cout << " name: " << nameHist
        << " file: " << nameFile
        << " dir: " <<  Dirname
        << std::endl;
      abort();

    }
    hist->SetLineWidth(1);
    if ( rebin > 0 ) { hist->Rebin(rebin); }
    hist->GetXaxis()->SetTitleSize(0.055);
    hist->GetYaxis()->SetTitleSize(0.055);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->SetStats(kFALSE);
    return hist;
  }

// -----------------------------------------------------------------------------
//
  TCanvas* createCanvas(TString name,TDirectory* afile, bool log)
  {
    afile->cd();
    TCanvas* aCanvas = new TCanvas(name);
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);
    aCanvas->Range(-288.2483,-2.138147,1344.235,6.918939);
    aCanvas->SetFillColor(0);
    aCanvas->SetBorderMode(0);
    aCanvas->SetBorderSize(2);
    if ( log == true)aCanvas->SetLogy();
    aCanvas->SetLeftMargin(0.1765705);
    aCanvas->SetRightMargin(0.05772496);
    aCanvas->SetTopMargin(0.04778761);
    aCanvas->SetBottomMargin(0.1256637);
    aCanvas->SetFrameFillStyle(0);
    aCanvas->SetFrameLineWidth(2);
    aCanvas->SetFrameBorderMode(0);
    aCanvas->SetFrameFillStyle(0);
    aCanvas->SetFrameLineWidth(2);
    aCanvas->SetFrameBorderMode(0);


    return aCanvas;
  }


