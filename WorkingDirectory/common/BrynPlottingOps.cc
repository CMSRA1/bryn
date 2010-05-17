#include "BrynPlottingOps.hh"
#include "CommonOps.hh"
#include "EventData.hh"
#include "KinSuite.hh"
#include "TH1D.h"
#include "TH2D.h"
#include "Types.hh"
#include "mt2_bisect.hh"
#include "AlphaT.hh"
#include "Jet.hh"
#include "Math/VectorUtil.h"

#include "JetData.hh"


using namespace Operation;

// -----------------------------------------------------------------------------
//
BrynPlottingOps::BrynPlottingOps( const Utils::ParameterSet& ps ) :
// Misc
dirName_( ps.Get<std::string>("DirName") ),
  nMin_( ps.Get<int>("MinObjects") ),
  nMax_( ps.Get<int>("MaxObjects") ),
// MT2
  mt2_( ps.Get<bool>("Mt2DiJet") ),
  mt2_Multi_jet_( ps.Get<bool>("Mt2Multi_Jet") ),
  mt2_comparison_( ps.Get<bool>("Mt2Compare") ),
  Mht_plots_( ps.Get<bool>("MHT") ),
  Dev_( ps.Get<bool>("Development") ),
  DalitzMT2_( ps.Get<bool>("DalitzMT2") ),
  hMt2_()
  {}

// -----------------------------------------------------------------------------
//
BrynPlottingOps::~BrynPlottingOps() {}

// -----------------------------------------------------------------------------
//
void BrynPlottingOps::Start( Event::Data& ev ) {
  initDir( ev.OutputFile(), dirName_.c_str() );
  BookHistos();
}

// -----------------------------------------------------------------------------
//
void BrynPlottingOps::BookHistos() {
  if ( mt2_ )           { mt2(); }
  if ( mt2_Multi_jet_)  { mt2_Multi_Jet(); }
  if ( mt2_comparison_) { mt2_Comparison(); }
  if ( Mht_plots_ )     { MHTPlots(); }
  if ( Dev_ )           { DevPlots(); }
  if ( DalitzMT2_ )     { DalitzMT2();}
}

// -----------------------------------------------------------------------------
//
bool BrynPlottingOps::Process( Event::Data& ev ) {
  if ( mt2_ )               { mt2(ev); }
  if ( mt2_Multi_jet_ )     { mt2_Multi_Jet(ev); }
  if ( mt2_comparison_ )    { mt2_Comparison(ev); }
  if ( Mht_plots_ )         { MHTPlots(ev); }
  if ( Dev_ )               { DevPlots(ev); }
  if ( DalitzMT2_ )         { DalitzMT2(ev);}
  return true;
}

// -----------------------------------------------------------------------------
//
std::ostream& BrynPlottingOps::Description( std::ostream& ostrm ) {
  ostrm << "Bryn's PlottingOps ";
  ostrm << "(bins " << nMin_ << " to " << nMax_ << ") ";
  return ostrm;
}

// -----------------------------------------------------------------------------
//
void BrynPlottingOps::mt2() {

  BookHistArray( hMt2_,
    "Mt2",
    "",
    200, 0., 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( hMt2_vs_alphaT_,
    "Mt2 vs AlphaT",
    "",
    200,0.,1000.,
    40,0.,4.,
    nMax_+1, 0, 1, true );

  BookHistArray( hMHT_over_MT2_,
    "MHT over MT2",
    "",
    100, 0., 50.,
    nMax_+1, 0, 1, true );

  BookHistArray( hMT2_over_MHT_,
    "MT2 over MHT",
    "",
    100, 0., 20.,
    nMax_+1, 0, 1, true );

}

// -----------------------------------------------------------------------------
//
void BrynPlottingOps::mt2_Multi_Jet() {

  BookHistArray( hMt2_Multi_Jet_,
    "Mt2_Multi_Jet",
    "",
    200,0.,1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( hMt2_vs_alphaT_Multi_,
    "Mt2 vs AlphaT Multi Jet",
    "",
    200,0.,1000.,
    40,0.,4.,
    nMax_+1, 0, 1, true );

  BookHistArray( hMHT_over_MT2_Multi_,
    "MHT over MT2 Multi Jet",
    "",
    100, 0., 50.,
    nMax_+1, 0, 1, true );

  BookHistArray( hMT2_over_MHT_Multi_,
    "MT2 over MHT Multi Jet",
    "",
    100, 0., 20.,
    nMax_+1, 0, 1, true );

}

// -----------------------------------------------------------------------------
//
void BrynPlottingOps::mt2_Comparison() {
  BookHistArray( hMT2Val_,
    "Mt2 dijet vs Mt2 Psudo Jet",
    "",
    100,0.,2000.,
    100,0.,2000.,
    nMax_+1, 0, 1, true );



}



// -----------------------------------------------------------------------------
//
void BrynPlottingOps::MHTPlots() {
  BookHistArray( hMht_recoil_,
    "MHT",
    "MHT",
    100,0. ,1000.,
    nMax_+1, 0 , 1, true);

}


// -----------------------------------------------------------------------------
//
void BrynPlottingOps::DalitzMT2() {
  BookHistArray( hDalitzMT2Mjj_,
    "Mass of Dijet vs MT2",
    ";M_{T2}(j_{1},j_{2});M_{T}(j_{1},j_{2})",
    200,0.,1000.,
    200,0.,1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( hDalitzMT2mt_j1_mht_,
    "Mass of j1 + mht vs MT2",
    ";M_{T2}(j_{1},j_{2});M_{T}(j_{1},#slash{E}_{T})",
    200,0.,1000.,
    200,0.,1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( hDalitzMT2mt_j2_mht_,
    "Mass ofj2 + mht vs MT2",
    ";M_{T2}(j_{1},j_{2});M_{T}(j_{2},#slash{E}_{T})",
    200,0.,1000.,
    200,0.,1000.,
    nMax_+1, 0, 1, true );
}


// -----------------------------------------------------------------------------
//
void BrynPlottingOps::DevPlots() {

  BookHistArray( MassReco_,
    "Mass Reco from single Jet",
    "",
    200,0.,1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( HTvsMHT_,
    "HT vs MHT",
    ";HT;MHT",
    40,0.,200.,
    40,0.,200.,
    nMax_+1, 0, 1, true );

  BookHistArray( HTvsMHT_X_,
    "HT vs MHT_X",
    ";HT;MHT",
    40,0.,200.,
    160,-400.,400.,
    nMax_+1, 0, 1, true );

  BookHistArray( HTvsMHT_Y_,
    "HT vs MHT_Y",
    ";HT;MHT",
    40,0.,200.,
    160,-400.,400.,
    nMax_+1, 0, 1, true );

  BookHistArray( MHT_Y_,
    "MHT Y",
    ";MHT Y (GeV);",
    160,-400.,400.,
    nMax_+1, 0, 1, true );

  BookHistArray( MHT_X_,
    "MHT X",
    ";MHT X (GeV);",
    160,-400.,400.,
    nMax_+1, 0, 1, true );

  BookHistArray( MET_Pt_,
    "MET PT",
    ";Pt (GeV);",
    100,0.,1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( CALO_MET_,
    "Callo MET",
    ";Pt (GeV);",
    100,0.,1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( CaloMetvsSUMET_,
    "#sum{E_{T}} vs Calo MET",
    ";#sum{E_{T}};Calo MET",
    50,0.,500.,
    50,0.,500.,
    nMax_+1, 0, 1, true );

  BookHistArray( SumETvsHT_,
    "#sum{E_{T}} vs HT",
    ";#sum{E_{T}}; HT",
    50,0.,500.,
    50,0.,500.,
    nMax_+1, 0, 1, true );


  BookHistArray( SumETvsMHT_,
    "#sum{E_{T}} vs MHT",
    ";#sum{E_{T}}; MHT",
    50,0.,500.,
    50,0.,500.,
    nMax_+1, 0, 1, true );

}


// -----------------------------------------------------------------------------
//
LorentzV BrynPlottingOps::RecoilMET( Event::Data& ev ) {

  LorentzV mData(0.,0.,0.,0.);

  std::vector<Event::Jet>::const_iterator ijet = ev.JD_Jets().begin();
  std::vector<Event::Jet>::const_iterator jjet = ev.JD_Jets().end();
  for ( ; ijet != jjet; ++ijet ) { mData -= (*ijet); }

  std::vector<Event::Lepton>::const_iterator imuon = ev.LD_Muons().begin();
  std::vector<Event::Lepton>::const_iterator jmuon = ev.LD_Muons().end();
  for ( ; imuon != jmuon; ++imuon ) { mData -= (*imuon); }

  std::vector<Event::Lepton>::const_iterator ielectron = ev.LD_Electrons().begin();
  std::vector<Event::Lepton>::const_iterator jelectron = ev.LD_Electrons().end();
  for ( ; ielectron != jelectron; ++ielectron ) { mData -= (*ielectron); }

  std::vector<Event::Photon>::const_iterator iphoton = ev.PD_Photons().begin();
  std::vector<Event::Photon>::const_iterator jphoton = ev.PD_Photons().end();
  for ( ; iphoton != jphoton; ++iphoton ) { mData -= (*iphoton); }

  return mData;

}

// -----------------------------------------------------------------------------
//

Double_t BrynPlottingOps::MassReco( Event::Data& ev){
  std::vector<Event::Jet const *> jet = ev.JD_CommonJets().accepted;

  LorentzV Jet(0.,0.,0.,0.) ;
  Jet += (*jet[0]);
  Jet -= (*jet[0]);

  return Jet.Mt();
}
// -----------------------------------------------------------------------------
//

Double_t BrynPlottingOps::MT2_DiJet( Event::Data& ev){


  std::vector<Event::Jet const *> jets = ev.JD_CommonJets().accepted;
  UInt_t n = jets.size();
  if ( n < 1 || n > Event::KS_MinDEt_MaxN() ) { return false; }

  mt2_bisect::mt2 mt2_event;

  LorentzV lv1(0.,0.,0.,0.);
  LorentzV lv2(0.,0.,0.,0.);

  lv1 = *jets[0];
  lv2 = *jets[1];
  double pa[3]; // px py m of object 1
  double pb[3]; // px py m of object 2
  double pm[3];       //jet1
  pa[0] = lv1.Px();
  pa[1] = lv1.Py();
  pa[2] = lv1.Mt();//KS_MT(objects[0]);
          //jet2
  pb[0] = lv2.Px();
  pb[1] = lv2.Py();
  pb[2] = lv2.Mt();//KS_MT(objects[1]);

  pm[1]= (BrynPlottingOps::RecoilMET(ev)).Px();
  pm[2]= (BrynPlottingOps::RecoilMET(ev)).Py();

  // set invisable mass
  double mn = 0.;
  mt2_event.set_momenta(pa,pb,pm);
  mt2_event.set_mn(mn);

  return mt2_event.get_mt2();


}
// -----------------------------------------------------------------------------
//
Double_t BrynPlottingOps::MT2_NJet( Event::Data& ev){

  std::vector<Event::Jet const *> jet = ev.JD_CommonJets().accepted;
  UInt_t n = jet.size();
  if ( n < 1 || n > Event::KS_MinDEt_MaxN() ) { return false; }

  mt2_bisect::mt2 mt2_event;

  LorentzV lv1(0.,0.,0.,0.);
  LorentzV lv2(0.,0.,0.,0.);

  // Alpha_t variable
  std::vector<bool> pseudo;
  double alpha_t = AlphaT()( jet, pseudo, false );
  if ( pseudo.size() != jet.size() ) { abort(); }
    // use this to get the pseudo jets

  if ( n == 2 ) {
    if ( jet[0] ) lv1 = *jet[0];
    if ( jet[1] ) lv2 = *jet[1];
  } else if ( n > 2 ) {
    for ( unsigned int i = 0; i < jet.size(); ++i ) {
      if ( jet[i] ) {
        if ( pseudo[i] ) { lv1 += *jet[i];
          // std::cout << "Jets included in Jet 1 = " << i << std::endl;
        }
        else             { lv2 += *jet[i];
          // std::cout << "Jets included in Jet 2 = " << i << std::endl;
        }
      }
    }
    if ( lv2.Pt() > lv1.Pt() ) { LorentzV tmp = lv1; lv1 = lv2; lv2 = tmp; }

  }



  double pa[3]; // px py m of object 1
  double pb[3]; // px py m of object 2
  double pm[3];       //jet1
  pa[0] = lv1.Px();
  pa[1] = lv1.Py();
  pa[2] = lv1.Mt();//KS_MT(objects[0]);
            //jet2
  pb[0] = lv2.Px();
  pb[1] = lv2.Py();
  pb[2] = lv2.Mt();//KS_MT(objects[1]);

  pm[1]= (BrynPlottingOps::RecoilMET(ev)).Px();
  pm[2]= (BrynPlottingOps::RecoilMET(ev)).Py();


  // set invisable mass
  double mn = 0.;
  mt2_event.set_momenta(pa,pb,pm);
  mt2_event.set_mn(mn);

  return mt2_event.get_mt2();
}

// -----------------------------------------------------------------------------
//



bool BrynPlottingOps::mt2( Event::Data& ev ) {


    // Event weight
  Double_t weight = ev.GetEventWeight();

    // Common objects
  std::vector<Event::Jet const *> jets = ev.JD_CommonJets().accepted;
  UInt_t n = jets.size();


  // Alpha_t variable
  std::vector<bool> pseudo;
  double alpha_t = AlphaT()( jets, pseudo, false );
  if ( pseudo.size() != jets.size() ) { abort(); }


    // MT2 plots
  if ( mt2_ ){
    if ( !hMt2_.empty() && hMt2_[0] ) { hMt2_[0]->Fill( BrynPlottingOps::MT2_DiJet( ev ), weight ); }
    if ( n >= nMin_ && n <= nMax_ && n < hMt2_.size() ) {
      if ( hMt2_[n] ) hMt2_[n]->Fill( BrynPlottingOps::MT2_DiJet( ev ), weight );
    }


    if ( !hMt2_vs_alphaT_.empty() && hMt2_vs_alphaT_[0] ) { hMt2_vs_alphaT_[0]->Fill( BrynPlottingOps::MT2_DiJet( ev ), alpha_t, weight ); }
    if ( n >= nMin_ && n <= nMax_ && n < hMt2_vs_alphaT_.size() ) {
      if ( hMt2_vs_alphaT_[n] ) hMt2_vs_alphaT_[n]->Fill( BrynPlottingOps::MT2_DiJet( ev ), alpha_t, weight );
    }


    if ( !hMHT_over_MT2_.empty() && hMHT_over_MT2_[0] ) { hMHT_over_MT2_[0]->Fill( (ev.CommonMHT().Mt())/BrynPlottingOps::MT2_DiJet( ev ), weight ); }
    if ( n >= nMin_ && n <= nMax_ && n < hMt2_vs_alphaT_.size() ) {
      if ( hMHT_over_MT2_[n] ) hMHT_over_MT2_[n]->Fill( (ev.CommonMHT().Mt())/BrynPlottingOps::MT2_DiJet( ev ), weight );
    }

    if ( !hMT2_over_MHT_.empty() && hMT2_over_MHT_[0] ) { hMT2_over_MHT_[0]->Fill( BrynPlottingOps::MT2_DiJet( ev )/(ev.CommonMHT().Mt()), weight ); }
    if ( n >= nMin_ && n <= nMax_ && n < hMT2_over_MHT_.size() ) {
      if ( hMT2_over_MHT_[n] ) hMT2_over_MHT_[n]->Fill( BrynPlottingOps::MT2_DiJet( ev )/(ev.CommonMHT().Mt()), weight );
    }

  }
  return true;
}

// -----------------------------------------------------------------------------
//
bool BrynPlottingOps::mt2_Multi_Jet( Event::Data& ev ) {

      // Event weight
  Double_t weight = ev.GetEventWeight();

  std::vector<Event::Jet const *> jets = ev.JD_CommonJets().accepted;
  UInt_t n = jets.size();

      // Alpha_t variable
  std::vector<bool> pseudo;
  double alpha_t = AlphaT()( jets, pseudo, false );
  if ( pseudo.size() != jets.size() ) { abort(); }


  if ( mt2_Multi_jet_ ){


    if ( !hMt2_Multi_Jet_.empty() && hMt2_Multi_Jet_[0] ) { hMt2_Multi_Jet_[0]->Fill( BrynPlottingOps::MT2_NJet( ev ), weight);}
    if ( n >= nMin_ && n <= nMax_ && n < hMt2_Multi_Jet_.size() ) {
      if ( hMt2_Multi_Jet_[n] ) hMt2_Multi_Jet_[n]->Fill( BrynPlottingOps::MT2_NJet( ev ), weight );
    }


    if ( !hMt2_vs_alphaT_Multi_.empty() && hMt2_vs_alphaT_Multi_[0] ) { hMt2_vs_alphaT_Multi_[0]->Fill( BrynPlottingOps::MT2_NJet( ev ), alpha_t, weight ); }
    if ( n >= nMin_ && n <= nMax_ && n < hMt2_vs_alphaT_.size() ) {
      if ( hMt2_vs_alphaT_Multi_[n] ) hMt2_vs_alphaT_Multi_[n]->Fill( BrynPlottingOps::MT2_NJet( ev ), alpha_t, weight );
    }


    if ( !hMHT_over_MT2_Multi_.empty() && hMHT_over_MT2_Multi_[0] ) { hMHT_over_MT2_Multi_[0]->Fill( (ev.CommonMHT().Mt())/BrynPlottingOps::MT2_NJet( ev ), weight ); }
    if ( n >= nMin_ && n <= nMax_ && n < hMt2_vs_alphaT_Multi_.size() ) {
      if ( hMHT_over_MT2_Multi_[n] ) hMHT_over_MT2_Multi_[n]->Fill( (ev.CommonMHT().Mt())/BrynPlottingOps::MT2_NJet( ev ), weight );
    }

    if ( !hMT2_over_MHT_Multi_.empty() && hMT2_over_MHT_[0] ) { hMT2_over_MHT_[0]->Fill( BrynPlottingOps::MT2_NJet( ev )/(ev.CommonMHT().Mt()), weight ); }
    if ( n >= nMin_ && n <= nMax_ && n < hMT2_over_MHT_Multi_.size() ) {
      if ( hMT2_over_MHT_Multi_[n] ) hMT2_over_MHT_Multi_[n]->Fill( BrynPlottingOps::MT2_NJet( ev )/(ev.CommonMHT().Mt()), weight );
    }
  }


  return true;
}


// -----------------------------------------------------------------------------
//
bool BrynPlottingOps::mt2_Comparison( Event::Data& ev ) {

    // Event weight
  Double_t weight = ev.GetEventWeight();


  std::vector<Event::Jet const *> jets = ev.JD_CommonJets().accepted;
  UInt_t n = jets.size();

  if ( mt2_comparison_ ){

    if ( n >= nMin_ && n <= nMax_ && n < hMT2Val_.size() && n <= Event::KS_MinDEt_MaxN() ) {
      hMT2Val_[0]->Fill( BrynPlottingOps::MT2_DiJet( ev ), BrynPlottingOps::MT2_NJet( ev ), weight );
      hMT2Val_[n]->Fill( BrynPlottingOps::MT2_DiJet( ev ), BrynPlottingOps::MT2_NJet( ev ), weight );
    }

  }
  return true;

}


bool BrynPlottingOps::MHTPlots( Event::Data& ev){



  Double_t ht;
  LorentzV jet(0.,0.,0.,0.);
  std::vector<Event::Jet const *> jets = ev.JD_CommonJets().accepted;
  UInt_t n = jets.size();
  for ( int i = 0 ; i < n ; i++ ) { jet -= *jets[i]; ht+=jets[i]->Et();}



  if( Mht_plots_ ){
    //Compete event MET 4 vec PT taken as scalar sum of missing transvers energy is \slashed{H}_{T}
    if ( n >= nMin_ && n <= nMax_ && n < hMht_recoil_.size() && n <= Event::KS_MinDEt_MaxN() ) {
      //Histograms
      hMht_recoil_[0]->Fill( jet.Pt() );
      hMht_recoil_[n]->Fill( jet.Pt() );
    }//end full event MET

    // if ( n >= nMin_ && n <= nMax_ && n < hMht_framework_.size() && n <= Event::KS_MinDEt_MaxN() ){
    //
    //  hMht_framework_[0]->Fill( ev.CommonMHT() );
    //  hMht_framework_[n]->Fill( ev.CommonMHT() );
    //
    //
    // }




  }
  return true;
}

// -----------------------------------------------------------------------------
//
bool BrynPlottingOps::DalitzMT2( Event::Data& ev){
  // Event weight
  Double_t weight = ev.GetEventWeight();
  // Common objects
  UInt_t n = ev.CommonObjects().size();
  LorentzV mht = ev.CommonRecoilMET();
  // Alpha_t variable
  std::vector<bool> pseudo;
  AlphaT()( ev.CommonObjects(), pseudo, false );
  if ( pseudo.size() != ev.CommonObjects().size() ) { abort(); }
  // Variables for Dalitz plots
  LorentzV lv1(0.,0.,0.,0.);
  LorentzV lv2(0.,0.,0.,0.);
  if ( n == 2 ) {
    lv1 = ev.CommonObjects()[0];
    lv2 = ev.CommonObjects()[1];
  } else if ( n > 2 ) {
    for ( unsigned int i = 0; i < ev.CommonObjects().size(); ++i ) {
      if ( pseudo[i] ) { lv1 += ev.CommonObjects()[i]; }
      else             { lv2 += ev.CommonObjects()[i]; }
    }
    if ( lv2.Pt() > lv1.Pt() ) { LorentzV tmp = lv1; lv1 = lv2; lv2 = tmp; }
  }



  // DalitzMt plots
  double m_jj  = ( lv1 + lv2 ).M();
  double mt_jj  = ( lv1 + lv2 ).Mt();


  double mt_j1_mht = ( lv1 + mht ).Mt();


  double mt_j2_mht = ( lv2 + mht ).Mt();


  double m_jj_mt2 = BrynPlottingOps::MT2_NJet( ev );

  if ( DalitzMT2_ ){

  // M_{T2} vs M(j1,j2)
    if ( !hDalitzMT2Mjj_.empty() ) { hDalitzMT2Mjj_[0]->Fill( m_jj_mt2, m_jj, weight ); }
    if ( n >= nMin_ && n <= nMax_ && n < hDalitzMT2Mjj_.size() ) {
      hDalitzMT2Mjj_[n]->Fill( m_jj_mt2, m_jj, weight );
    }

  // M_{T2} vs M_{T}(j1,MHT)
    if ( !hDalitzMT2mt_j1_mht_.empty() ) { hDalitzMT2mt_j1_mht_[0]->Fill( m_jj_mt2, mt_j1_mht, weight ); }
    if ( n >= nMin_ && n <= nMax_ && n < hDalitzMT2mt_j1_mht_.size() ) {
      hDalitzMT2mt_j1_mht_[n]->Fill( m_jj_mt2, mt_j1_mht, weight );
    }

  // M_{T2} vs M_{T}(j2,MHT)
    if ( !hDalitzMT2mt_j2_mht_.empty() ) { hDalitzMT2mt_j2_mht_[0]->Fill( m_jj_mt2, mt_j2_mht, weight ); }
    if ( n >= nMin_ && n <= nMax_ && n < hDalitzMT2mt_j2_mht_.size() ) {
      hDalitzMT2mt_j2_mht_[n]->Fill( m_jj_mt2, mt_j2_mht, weight );
    }

  }
  return true;
}



// -----------------------------------------------------------------------------
//

bool BrynPlottingOps::DevPlots( Event::Data& ev ){

      // Event weight
  Double_t weight = ev.GetEventWeight();
  Double_t ht=0.;
  LorentzV mht(0.,0.,0.,0.);
  std::vector<Event::Jet const *> jets = ev.JD_CommonJets().accepted;
  // std::vector< Event::Jet const*>::iterator ijet = ev.JD_CommonJets().accepted.begin();
  // std::vector< Event::Jet const*>::iterator jjet = ev.JD_CommonJets().accepted.end();
  UInt_t n = jets.size();


//loop over jets and calculate HT amd MHT
  for ( int i = 0 ; i < n ; i++ ) {
    mht -= *jets[i];
    ht+=jets[i]->Et();
  }


  if( Dev_ ){

    if ( n >= nMin_ && n <= nMax_ && n < CALO_MET_.size() && n <= Event::KS_MinDEt_MaxN() ) {
       CALO_MET_[0]->Fill( ev.CaloMET().Pt(), weight );
       CALO_MET_[n]->Fill( ev.CaloMET().Pt(), weight );
     }


    if ( n >= nMin_ && n <= nMax_ && n < CaloMetvsSUMET_.size() && n <= Event::KS_MinDEt_MaxN() ) {
      CaloMetvsSUMET_[0]->Fill( ev.CaloMET().Pt(), ev.SumEt() , weight );
      CaloMetvsSUMET_[n]->Fill( ev.CaloMET().Pt(), ev.SumEt() , weight );
    }



  if ( n >= nMin_ && n <= nMax_ && n < SumETvsMHT_.size() && n <= Event::KS_MinDEt_MaxN() ) {
    SumETvsMHT_[0]->Fill( ev.SumEt(), mht.Pt() , weight );
    SumETvsMHT_[n]->Fill( ev.SumEt(), mht.Pt() , weight );
  }

    if ( n >= nMin_ && n <= nMax_ && n < SumETvsHT_.size() && n <= Event::KS_MinDEt_MaxN() ) {
      SumETvsHT_[0]->Fill( ev.SumEt(), ht , weight );
      SumETvsHT_[n]->Fill( ev.SumEt(), ht , weight );
    }



    if ( n >= nMin_ && n <= nMax_ && n < MassReco_.size() && n <= Event::KS_MinDEt_MaxN() ) {
      MassReco_[0]->Fill( BrynPlottingOps::MassReco( ev ), weight );
      MassReco_[n]->Fill( BrynPlottingOps::MassReco( ev ), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < HTvsMHT_.size() && n <= Event::KS_MinDEt_MaxN() ) {
      HTvsMHT_[0]->Fill( ht, mht.Pt() , weight );
      HTvsMHT_[n]->Fill( ht, mht.Pt() , weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < HTvsMHT_X_.size() && n <= Event::KS_MinDEt_MaxN() ) {
      HTvsMHT_X_[0]->Fill( ht, mht.Px() , weight );
      HTvsMHT_X_[n]->Fill( ht, mht.Px() , weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < HTvsMHT_Y_.size() && n <= Event::KS_MinDEt_MaxN() ) {
      HTvsMHT_Y_[0]->Fill( ht, mht.Py() , weight );
      HTvsMHT_Y_[n]->Fill( ht, mht.Py() , weight );
    }


    if ( n >= nMin_ && n <= nMax_ && n < MHT_X_.size() && n <= Event::KS_MinDEt_MaxN() ) {
      MHT_X_[0]->Fill( mht.Px() , weight );
      MHT_X_[n]->Fill( mht.Px() , weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < MHT_Y_.size() && n <= Event::KS_MinDEt_MaxN() ) {
      MHT_Y_[0]->Fill( mht.Py() , weight );
      MHT_Y_[n]->Fill( mht.Py() , weight );
    }


  }




  return true;

}




