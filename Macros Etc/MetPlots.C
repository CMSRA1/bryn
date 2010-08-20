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
    // createPlot( path, "MHT", "MHT_all" , "MET Plots N=2", 10, true, true,false ,output);
    // createPlot( path, "MHT X", "MHT X_all" , "MET Plots N=2", 2, false, true,false ,output);
    // createPlot( path, "MHT Y", "MHT Y_all" , "MET Plots N=2", 2, false, true,false ,output);
    createPlot( path, "HT vs MHT", "HT vs MHT_all" , "MET Plots N=2", false, false, true,true, output);
    createPlot( path, "SumEt vs Calo MET", "#sum{E_{T}} vs Calo MET_all" , "MET Plots N=2", false, false, true,true, output);
    createPlot( path, "HT vs MHTx", "HT vs MHTx_all" , "MET Plots N=2", false, false, true,true, output);
    createPlot( path, "HT vs MHTy", "HT vs MHTy_all" , "MET Plots N=2", false, false, true,true, output);

  }

  if ( 1 ){

    createPlot( path, "HT vs MHT2", "HT vs MHT_all" , "MET Plots N=2", false, false, false,false, output);
    // createPlot( path, "Alpha T Dijet", "AlphaT_2", "KinSuitePlots", false , true, true,false, output);
    createPlot( path, "Calo Met", "Callo MET_all" , "MET Plots N=2", 10, true, true,false ,output);

      // projection plots
    createPlot( path, "HT vs MHTx", "HT vs MHTx_all" , "MET Plots N=2", false, false, true,true, output);
    createPlot( path, "HT vs MHTy", "HT vs MHTy_all" , "MET Plots N=2", false, false, true,true, output);
    createPlot( path, "SumEt vs HT", "#sum{E_{T}} vs HT_all" , "MET Plots N=2", false, false, true,true, output);
    createPlot( path, "SumEt vs Calo MET", "#sum{E_{T}} vs Calo MET_all" , "MET Plots N=2", false, false, true,true, output);

      // createPlot( path, "MET Plots N=2", "Mt2_all", "MET Plots N=2", 10, true, true, output );
      // createPlot( path, "MT2 vs aplha T", "Mt2 vs AlphaT_all", "MET Plots N=2", 10, false, false, output );

  //Common Jet Plots
    // createPlot( path, "Multiplicity", "Multiplicity", "CommonJetPlots", false, true, true,false ,output );
    // createPlot( path, "EM frac", "emfrac_all", "CommonJetPlots", false, true, true, false,output );
    // createPlot( path, "Pt alljet spectrium", "Pt_all", "CommonJetPlots", 10, true, true, false,output );
       // createPlot( path, "Pt leading Jet", "Pt_1", "CommonJetPlots", 5, true, true, false,output );
       // createPlot( path, "Pt second Jet", "Pt_2", "CommonJetPlots", 5, true, true, false,output );
       // createPlot( path, "ET", "Et_all", "CommonJetPlots", 10, true, true,false ,output );

    // Object Kine Plots
    // createPlot( path, "eta leading Jet", "eta_1", "ObjectKinePlots", 5,true, true, false,output);
    // createPlot( path, "eta second Jet", "eta_2", "ObjectKinePlots",5 ,true, true,false, output);
    // createPlot( path, "#Delta #eta(j#_{1},j#_{2})", "DeltaEta_1", "ObjectKinePlots",5 ,true, true,false, output);




  }


  if (0) {

    createPlot( path, "MT2 vs mt(j1+j2)", "hDalitzMT2Mjj_all", "MET Plots N=2", false, true, true, output );
    createPlot( path, "MT2 vs mt(j2+mht)", "hDalitzMT2mt_j2_mht_all", "MET Plots N=2", false, true, true, output );
    createPlot( path, "MT2 vs mt(j1+mht)", "hDalitzMT2mt_j1_mht_all", "MET Plots N=2", false, true, true, output );

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

  TH1D* MC  = getHisto( path, name, "AK5Calo_ICMCSkim.root", dirmame, rebin );
  TH1D* Data  = getHisto( path, name, "AK5Calo_ICDataSkim.root", dirmame, rebin );

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
      // std::cout << "Lower bin value " << low << " upper bin value " << up << std::endl;

      TString bins("MET in Bins of #sum{E_{T}} (");
      bins+=low;
      TString mid("<#sum{E_{T}}<");
      bins+=mid;
      bins+=up;
      TString end(")");
      bins+=end;
      // std::cout << bins << endl;

      TH1D *px1 = Data->TH2D::ProjectionY("px1",i+1,i+4,"o");
      if(px1->Integral() == 0) continue;// bool can put in else where.
      px1->GetXaxis()->SetRangeUser(0.,200.);
      px1->GetYaxis()->SetTitle(bins);
      px1->GetXaxis()->SetTitle("MET (GeV)");
      TH1D *px2 = MC->TH2D::ProjectionY("px2",i+1,i+4,"o");
      px2->Scale(px1->Integral()/px2->Integral());
      px1->GetXaxis()->SetTitleSize(0.055);
      px1->GetYaxis()->SetTitleSize(0.045);
      px1->GetXaxis()->SetLabelSize(0.05);
      px1->GetYaxis()->SetLabelSize(0.05);
      px1->SetStats(kFALSE);



      px1->Draw("LPEBh");
      px2->Draw("sameh");
      //Save as a png with name of orig plot + sting. to append Integer to string
      // TString a("string");
      // a+=integer;
      // a = stringinteger <---- so far the only way I know to do this.
      TString type(".pdf");
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
    px19->GetXaxis()->SetTitleSize(0.055);
    px19->GetYaxis()->SetTitleSize(0.055);
    px19->GetXaxis()->SetLabelSize(0.05);
    px19->GetYaxis()->SetLabelSize(0.05);
    px19->SetStats(kFALSE);

    if (MC)   { TH1D *px20 = MC->TH2D::ProjectionY("px20",1,40,"o");
    px20->GetXaxis()->SetRangeUser(0.,200.);
    px20->Scale(px19->Integral()/px20->Integral());
    px20->Draw("sameh");}
    c1->SaveAs("MHT_all.pdf");


  }




  if( canvas_name == TString("HT vs MHT_X") || canvas_name == TString("HT vs MHT_Y") ){ bool fit_ = true;}
  else { bool fit_ = false;}
// fit_ = true;

  if ( fit_ ) {
    TMultiGraph *a = new TMultiGraph();
    Double_t htVal[9];
    Double_t fract[9];
    Double_t fractMC[9];
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


    Int_t c = 0;
    Int_t b = Data->GetYaxis()->GetNbins();
    cout << "number of bins is "<< b << endl;
    for(int i = 0; i < b ; i+=4){
      TH1D *mhtxy = Data->TH2D::ProjectionY("mhtxy",i+1,i+4,"o");
      if(mhtxy->Integral() == 0) continue;// bool can put in else where.
      TH1D *mhtxyMC = MC->TH2D::ProjectionY("mhtxyMC",i+1,i+4,"o");
      mhtxyMC->Scale(mhtxy->Integral()/mhtxyMC->Integral());
      htVal[c]=i*5;
      for(int h = 1 ; h < 6 ; h++){

        Double_t max = 0 + h*(mhtxy->GetRMS(1));
        Double_t maxMC = 0 + h*(mhtxyMC->GetRMS(1));
        Double_t min = 0 - h*(mhtxy->GetRMS(1));
        Double_t minMC = 0 - h*(mhtxyMC->GetRMS(1));


        Double_t remUP = 0.5*( mhtxy->Interpolate( max ) + mhtxy->GetBinContent( ( mhtxy->FindBin( max ) ) ) )*fabs( max-mhtxy->GetBinLowEdge( mhtxy->FindBin( max ) ) );

        Double_t remLOW = 0.5*( mhtxy->Interpolate(min) + mhtxy->GetBinContent( (mhtxy->FindBin(min) ) ) )*fabs( min - mhtxy->GetBinLowEdge( mhtxy->FindBin( min ) + 1 ) );
      // // std::cout << "Rem Low edge = " << remLOW << std::endl;
        Double_t remUPMC = 0.5*( mhtxyMC->Interpolate( maxMC ) + mhtxyMC->GetBinContent( (mhtxyMC->FindBin(maxMC) ) ) )*fabs( maxMC- mhtxyMC->GetBinLowEdge( mhtxyMC->FindBin( maxMC ) ) );
      //
        Double_t remLOWMC = 0.5*( mhtxyMC->Interpolate( minMC ) + mhtxyMC->GetBinContent( (mhtxyMC->FindBin(minMC) ) ) )*fabs( minMC - mhtxyMC->GetBinLowEdge( mhtxyMC->FindBin( minMC )+1 ) ) ;



        Double_t fractions = ( mhtxy->Integral( "width" ) - ( mhtxy->Integral( mhtxy->FindBin( min )+1,mhtxy->FindBin( max )-1,"width" ) + remUP + remLOW ) )/( mhtxy->Integral( "width" ) );


        fract[c]=fractions;
        cout << " C " << c << " Fract[c] " << fract[c] << endl;

        Double_t fractionsMC = (mhtxyMC->Integral("width") - ( mhtxyMC->Integral( mhtxyMC->FindBin( minMC ) + 1,mhtxyMC->FindBin( maxMC ) - 1 ,"width")+ remUPMC +remLOWMC ) )/(mhtxyMC->Integral("width") );


        fractMC[c] = fractionsMC;
        cout << " C " << c << " FractMC[c] " << fractMC[c] << endl;

        cout << " Values between " << min << " and " << max << " corrosponding to a mean of " << 0 << " and an RMS of " << mhtxy->GetRMS(1) << " have number of events over " << h <<" sigma = " << (mhtxy->Integral("width") - (mhtxy->Integral(mhtxy->FindBin(min)+1,mhtxy->FindBin(max)-1,"width")+remUP+remLOW)) << " Giving fraction "<< fractions  << endl;
      }
      c++;

    }
    TCanvas *can = new TCanvas("can","a name", 800,600);

// can->Clear();
    can->cd();
    TGraph *g1 = new TGraph(8,htVal,fract);
    TGraph *g2 = new TGraph(8,htVal,fractMC);
    g1->SetMarkerStyle(20);
        g2->SetMarkerStyle(21);
    a->Add(g1,"P");
    a->Add(g2,"P");
    a->Draw("a");
    a->GetXaxis()->SetTitleSize(0.055);
    a->GetYaxis()->SetTitleSize(0.055);
    a->GetXaxis()->SetLabelSize(0.05);
    a->GetYaxis()->SetLabelSize(0.05);
    a->SetStats(kFALSE);

    can->SaveAs( canvas_name+"testcanvas.pdf");

  }



  if ( norm ) {
    if(canvas_name == TString( "Pt_1" ) ||canvas_name == TString( "Pt_1" )){Data->GetXaxis()->SetRangeUser(0.,300.);}
        MC->Scale(Data->Integral("width")/MC->Integral("width"));
         if ( Data ) Data->Draw("LPEBh");
          if ( MC ) MC->Draw("sameh");
  } else {
    if ( Data ) Data->Draw("LPEBh");
    if ( MC ) MC->Draw("sameh");
  }



  file->cd();
  legend->Draw("same");
  aCanvas->SaveAs( std::string(canvas_name+".pdf").c_str() );
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
  aCanvas->SetBorderSize(1);
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


