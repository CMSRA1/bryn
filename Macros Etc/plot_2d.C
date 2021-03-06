#include <string>

// -----------------------------------------------------------------------------
// Top-level method
void plot_2d() {

  std::string path = "./";
  //std::string path = "../../../RESULTS/10-AllFixedForTalk/";
  //std::string path = "../../../RESULTS/12-Talk/";
  //TString path = "../../../RESULTS/16-Dalitz0.606AlphaT0.576/";

  // Jet algorithm and type (IC5Calo,AK5Calo,AK5JPT,AK5PF)
  std::vector<std::string> type;
  type.push_back("AK5Calo");
  type.push_back("AK5PF");
//   type.push_back("AK5Calo");
  // type.push_back("AK5JPT");
//   type.push_back("AK5PF");

  // Samples to be used
  std::vector<std::string> samples;
//   samples.push_back("LM0");
//   samples.push_back("LM1");
   samples.push_back("ICDataSkim");
   samples.push_back("ICMCSkim");
  // samples.push_back("SD_JMT");
//   samples.push_back("WJets");
//   samples.push_back("ZJets");
//   samples.push_back("TTbar");
//   samples.push_back("Zinv");

  //samples.push_back("QCD_Pythia_Merged");
  //samples.push_back("TTbarJets");

  // Directories and names of histograms
  std::vector<std::string> dirs;
  std::vector<std::string> histos;

  // MT2/MHT plots

  if ( true ) {
     dirs.push_back("MET Plots N=2");
      histos.push_back("Mt2 vs AlphaT_all");
      dirs.push_back("MET Plots N=2");
      histos.push_back("HT vs MHT_all");
      dirs.push_back("MET Plots N=2");
      histos.push_back("HT vs MHTx_all");
      dirs.push_back("MET Plots N=2");
      histos.push_back("HT vs MHTy_all");
      dirs.push_back("MET Plots N=2");
      histos.push_back("#sum{E_{T}} vs Calo MET_all");
      // dirs.push_back("MET Plots N=2");
      // histos.push_back("#sum{E_{T}} vs Calo HT_all");
      dirs.push_back("MET Plots N=2");
      histos.push_back("# MHTx vs MHTy_all");
      dirs.push_back("MET Plots N=2");
      histos.push_back("# METx vs METy_all");
      dirs.push_back("MET Plots N=2");
      histos.push_back("# MHT vs MET_all");
     // dirs.push_back("MET Plots N=2");
      // histos.push_back("# MHT vs MET_all");
}

  // Kine plots
  if ( false ) {
//     dirs.push_back("CommonPlotsPost");
//     histos.push_back("MHTovHT_biasdPhijets:2");
//     dirs.push_back("ResponsePre");
//     histos.push_back("ResponseCorr_all");
//     dirs.push_back("ResponsePre");
//     histos.push_back("ResponseEtaCorr_all");
    dirs.push_back("DeadRegions");
    histos.push_back("Response_all");
    dirs.push_back("ResponsePre");
    histos.push_back("ResponseCorr_1");
    dirs.push_back("ResponsePre");
    histos.push_back("ResponseEtaCorr_1");
    dirs.push_back("ResponsePost");
    histos.push_back("ResponseCorr_1");
    dirs.push_back("ResponsePost");
    histos.push_back("ResponseEtaCorr_1");
//      dirs.push_back("ResponsePre");
//      histos.push_back("ResponseCorr_2");
//     dirs.push_back("ResponsePre");
//     histos.push_back("ResponseEtaCorr_2");
//     dirs.push_back("ResponsePre");
//     histos.push_back("ResponseEtaRaw_1");
//     dirs.push_back("ResponsePre");
//     histos.push_back("ResponseEtaRaw_2");
  }

  // Create plots
  loop( path, type, samples, dirs, histos );

}

// -----------------------------------------------------------------------------
// Loop over files and histograms
void loop( const std::string& path,
     const std::vector<std::string>& type,
     const std::vector<std::string>& samples,
     const std::vector<std::string>& dirs,
     const std::vector<std::string>& histos ) {

  // Create output file
  TFile* file = new TFile( "Plots2D.root", "RECREATE" );
  if ( !file || file->IsZombie() ) { return -1; }

  // Check
  if ( dirs.size() != histos.size() ) {
    std::cout << "dirs.size() != histos.size()" << std::endl;
    abort();
  }

  // Create plots
  for ( int i = 0; i < histos.size(); ++i ) {
    for ( int j = 0; j < samples.size(); ++j ) {
      for ( int k = 0; k < type.size(); ++k ) {
  plot( path.c_str(),
        type[k].c_str(),
        samples[j].c_str(),
        dirs[i].c_str(),
        histos[i].c_str() );
      }
    }
  }

  file->Write();
  file->Close();
  delete file;

}

// -----------------------------------------------------------------------------
// Create plots
void plot( std::string& path,
     std::string& type,
     std::string& sample,
     std::string& dir,
     std::string& histo ) {

  std::string canvas_name = histo + "_" + type + "_" + sample;

  // Create canvas
  TCanvas* canvas = new TCanvas(canvas_name.c_str(),"");
  canvas->SetFillColor(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetFrameFillColor(0);
  canvas->SetTopMargin(0.10);
  canvas->SetBottomMargin(0.12);
  canvas->SetLeftMargin(0.12);
  canvas->SetRightMargin(0.15);

  // Retrieve histogram
  std::string file_name = path + type + "_" + sample + ".root";
  TFile* f =  new TFile(file_name.c_str(),"READ");
  TDirectory* d = (TDirectory*)f->Get(dir.c_str());
  TH2D* his = (TH1*)d->Get(histo.c_str());
  if ( !his ) return;

  if ( true ) { gPad->SetLogz(); }
  his->SetMaximum( his->GetMaximum() );
  his->SetMinimum( his->GetMinimum(1.e-12) );
//   his->SetMaximum( 1.e-0 );
//   his->SetMinimum( 1.e-7 );

  double xmin = his->GetXaxis()->GetXmin();
  double xmax = his->GetXaxis()->GetXmax();
  double ymin = his->GetYaxis()->GetXmin();
  double ymax = his->GetYaxis()->GetXmax();

  // Reset title
  std::string title = ";" + std::string(his->GetXaxis()->GetTitle()) + ";" + std::string(his->GetYaxis()->GetTitle());
  his->SetTitle(title.c_str());
  his->GetXaxis()->SetTitleOffset(1.2);
  his->GetYaxis()->SetTitleOffset(1.4);
  his->Draw("COLZ");
  gPad->Update();

  // Jet type
  {
    double xpos = 0.05 * (xmax-xmin)+xmin;
    double ypos = 0.90 * (ymax-ymin)+ymin;
    TText* text = new TText(xpos,ypos,type.c_str());
    text->SetTextAlign(12);
    text->SetTextSize(0.035);
    text->Draw();
  }

  // Sample
  {
    double xpos = 0.05 * (xmax-xmin)+xmin;
    double ypos = 0.95 * (ymax-ymin)+ymin;
    TText* text = new TText(xpos,ypos,sample.c_str());
    text->SetTextAlign(12);
    text->SetTextSize(0.035);
    text->Draw();
  }

  // No stats
  //gStyle->SetOptStat(1000000);
  gStyle->SetOptStat(1001110);
  //his->SetStats(1);
  TPaveStats* stats = (TPaveStats*)his->GetListOfFunctions()->FindObject("stats");
  std::string stats_pos = "tr";
  if ( stats ) {
    if ( stats_pos == "tr" ) {
      stats->SetX1NDC(0.70); stats->SetY1NDC(0.68); stats->SetX2NDC(0.83); stats->SetY2NDC(0.88);
    } else if ( stats_pos == "br" ) {
      stats->SetX1NDC(0.70); stats->SetY1NDC(0.18); stats->SetX2NDC(0.83); stats->SetY2NDC(0.38);
    } else {
      stats->SetX1NDC(0.70); stats->SetY1NDC(0.68); stats->SetX2NDC(0.83); stats->SetY2NDC(0.88);
    }
  }

   // Scale
  gStyle->SetPalette(1);
  TPaletteAxis* palette = (TPaletteAxis*)his->GetListOfFunctions()->FindObject("palette");
  if ( palette ) {
    palette->SetY1NDC(0.2);
    palette->SetY2NDC(0.8);
  }

  canvas->Modified();
  canvas->cd();
  canvas->SetSelected(canvas);
  TString a("2Dplot_");
  a+=canvas_name;
  canvas->SaveAs(std::string(a+".pdf").c_str());
  canvas->Write();

}

