#include "HadronicCommonPlots.hh"
#include "CommonOps.hh"
#include "EventData.hh"
#include "KinSuite.hh"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "Types.hh"
#include "mt2_bisect.hh"
#include "AlphaT.hh"
#include "Jet.hh"
#include "Math/VectorUtil.h"
#include "JetData.hh"
#include <fstream>

using namespace Operation;

// -----------------------------------------------------------------------------
HadronicCommonPlots::HadronicCommonPlots( const Utils::ParameterSet& ps ) :
  // Misc
  dirName_( ps.Get<std::string>("DirName") ),
  nMin_( ps.Get<int>("MinObjects") ),
  nMax_( ps.Get<int>("MaxObjects") ),
  //Plotting Categories
  StandardPlots_( ps.Get<bool>("StandardPlots") ),
  DeadECALPlots_( ps.Get<bool>("DeadECALPlots") ),
  CleaningControlPlots_( ps.Get<bool>("CleaningControlPlots") ),
  MECPlots_( ps.Get<bool>("MECPlots") ),
  deadECALFile_(ps.Get<std::string>("DeadECALFile") )
  {}

// -----------------------------------------------------------------------------
//
HadronicCommonPlots::~HadronicCommonPlots() {}

// -----------------------------------------------------------------------------
//
void HadronicCommonPlots::Start( Event::Data& ev ) {

  TDirectory* headDir = returnDir(ev.OutputFile(),dirName_.c_str());

 

  if(StandardPlots_){
    initDir(headDir,"StandardPlots");
    StandardPlots();
    
  }
  if(DeadECALPlots_){
    initDir(headDir,"DeadECALPlots");
    DeadECALPlots();
  }
  if(CleaningControlPlots_){
    initDir(headDir,"CleaningControlPlots");
    CleaningControlPlots();    
  }
  if(MECPlots_){
    initDir(headDir,"MECPlots");
    MECPlots();
  }

  BookHistos();
}

void HadronicCommonPlots::BookHistos() {

  
}

// -----------------------------------------------------------------------------
//
bool HadronicCommonPlots::Process( Event::Data& ev ) {
  if ( StandardPlots_ )               { StandardPlots(ev); }
  if ( DeadECALPlots_) {DeadECALPlots(ev); }
  if ( CleaningControlPlots_) {CleaningControlPlots(ev); }
  if ( MECPlots_) {MECPlots(ev); }
  return true;
}

// -----------------------------------------------------------------------------
//
std::ostream& HadronicCommonPlots::Description( std::ostream& ostrm ) {
  ostrm << "Hadronic Common Plots ";
  ostrm << "(bins " << nMin_ << " to " << nMax_ << ") ";
  return ostrm;
}

// -----------------------------------------------------------------------------
//

void HadronicCommonPlots::DeadECALPlots(){
  
  BookHistArray(BadJetECALDR_,
		"BadJetECALDR",
		";DR(jet,Death to the ECAL);"
		,200,0,10,
		nMax_+1,0,1,true);

  BookHistArray(allMinECALDR_,
		"allMinECALDR",
		";DR(jet,Death to the ECAL);",
		200,0,10,
		nMax_+1,0,1,true);

  BookHistArray(TPMHT_,
		"TPMHT",
		";TPMHT;",
		400,0,1000,
		nMax_+1,0,1,true);

  BookHistArray(TPMHTRatio_,
		"TPMHTRatio",
		";TPMHTRatio;",
		200,0,40,
		nMax_+1,0,1,true);

  BookHistArray(TPHT_,
		"TPHT",
		";TPHT;",
		400,0,2000,
		nMax_+1,0,1,true);

   
  BookHistArray( BiasedDphi_,
		 "BiasedDeltaPhi",
		 ";#Delta #phi^{*} (rad); Events/0.05 rad;",
		 60, 0., TMath::Pi(),
		 nMax_+1, 0, 1, true );

}

void HadronicCommonPlots::CleaningControlPlots(){

  BookHistArray(NoisyMHT_,
		"NoisyMHT",
		";NoisyMHT;",
		400,0,2000,
		nMax_+1,0,1,true);

  BookHistArray(NoisyHT_,
		"NoisyHT",
		";NoisyHT;",
		400,0,2000,
		nMax_+1,0,1,true);

}


void HadronicCommonPlots::MECPlots(){

  BookHistArray(MHTPFMETDiffOvMeff_,
		"MHTPFMETDiffOvMeff",
		"#frac{MHT-PFMET}{Meff}",
		300,-1.5,1.5,
		nMax_+1,0,1,true);

  BookHistArray(MHTCaloMETDiffOvMeff_,
		"MHTCaloMETDiffOvMeff",
		"#frac{MHT-CaloMET}{Meff}",
		300,-1.5,1.5,
		nMax_+1,0,1,true);

  BookHistArray(PFMET_vs_MHTPFMETDiffOvMeff_,
		"PFMET_vs_MHTPFMETDiffOvMeff",
		";PFMET;#frac{MHT-PFMET}{Meff}",
		200,0,5000,300,-1.5,1.5,
		nMax_+1,0,1,true);

  BookHistArray(MHTOvPFMET_,
		"MHTOvPFMET",
		";MHTOvPFMET",
		500,0,50,
		nMax_+1,0,1,true);

   BookHistArray(MHT_vs_PFMET_,
		"MHT_vs_PFMET",
		";MHT_vs_PFMET",
		500,0,5000,
		 500,0,5000,
		nMax_+1,0,1,true);

  BookHistArray( BabyJetMHT_10_50_,
		 "BabyJetMHT_10_50",
		 ";BabyJetMHT;Events/5GeV;",
		 60, .0, 300.,
		 nMax_+1, 0, 1, true );
  
  BookHistArray( BabyJetMHT_10_30_,
		 "BabyJetMHT_10_30",
		 ";BabyJetMHT;Events/5GeV;",
		 60, .0, 300.,
		 nMax_+1, 0, 1, true );
  
  
 
  
  BookHistArray( MissedMHT_,
		 "MHTRatio",
		 ";MHT50/MHT10;Events/0.1;",
		 100, 0., 10,
		 nMax_+1, 0, 1, true );
  
  
}




void HadronicCommonPlots::StandardPlots() {


  BookHistArray( Mt2_LeadingJets_,
    "Mt2_LeadingJets",
    ";M_{T2} (GeV); Events/20 GeV;",
    100, 0., 2000.,
    nMax_+1, 0, 1, true );


  BookHistArray( Mt2_,
    "Mt2",
    ";M_{T2} (GeV); Events/20 GeV;",
    100, 0., 2000.,
    nMax_+1, 0, 1, true );



  BookHistArray( AlphaT_,
    "AlphaT",
    ";#alpha_{T};Events/0.025;",
    60,0.,1.5,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_Zoomed_,
    "AlphaT_Zoomed",
    ";#alpha_{T}; Events/0.0025;",
    60,0.45,0.6,
    nMax_+1, 0, 1, true );


  BookHistArray( AlphaT_Hadronic_,
    "AlphaT_Hadronic",
    ";#alpha_{T};Events/0.025;",
    60,0.,1.5,
    nMax_+1, 0, 1, true );


 

  BookHistArray( HT_,
    "HT",
    ";H_{T} (GeV); Events/25 GeV;",
    80,0.,2000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Meff_,
    "EffectiveMass",
    ";M_{eff} (GeV); Events/40 GeV;",
    75, 0., 3000.,
    nMax_+1, 0, 1, true );

  BookHistArray( MHT_,
    "MHT",
    ";#slash{H}_{T} (GeV); Events/10 GeV;",
    40,0.,1000.,
    nMax_+1, 0, 1, true );


  BookHistArray( MHTOvHT_,
    "MHTOvHT",
    ";#slash{H}_{T}/H_{T};Events/0.025;",
    40,0.,1.,
    nMax_+1, 0, 1, true );

 
   BookHistArray( JetEta_,
    "JetEta_",
    ";#eta ; Events/1 eta;",
    60,-5.,5.,
    nMax_+1, 0, 1, true );

  BookHistArray( JetPt_,
    "JetPt_",
    ";GeV ; Events/1 eta ",
    75,0.,1500.,
    nMax_+1, 0, 1, true );

  BookHistArray( fem_,
    "fem_",
    ";fem ; Events/0.2 ",
    100,-1.,1.,
    nMax_+1, 0, 1, true );





 
 

}
// -----------------------------------------------------------------------------
//

Double_t HadronicCommonPlots::MT2_Leading( Event::Data& ev ){
  mt2_bisect::mt2 mt2_event;
  std::vector<Event::Jet const *> jet = ev.JD_CommonJets().accepted;

  LorentzV lv1 = *jet[0];
  LorentzV lv2 = *jet[1];

  double pa[3]; // px py m of object 1
  double pb[3]; // px py m of object 2
  double pm[3];       //jet1
  pa[1] = lv1.Px();
  pa[2] = lv1.Py();
  pa[0] = 0.;//KS_MT(objects[0]);
            //jet2
  pb[1] = lv2.Px();
  pb[2] = lv2.Py();
  pb[0] = 0.;//KS_MT(objects[1]);

  pm[1]= ev.CommonMHT().Px();
  pm[2]= ev.CommonMHT().Py();

  // set invisable mass
  double mn = 0.;
  mt2_event.set_momenta(pa,pb,pm);
  mt2_event.set_mn(mn);

  return mt2_event.get_mt2();

}


Double_t HadronicCommonPlots::MT2( Event::Data& ev){

  std::vector<Event::Jet const *> jet = ev.JD_CommonJets().accepted;
  UInt_t n = jet.size();

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

        }
        else             { lv2 += *jet[i];

        }
      }
    }
    if ( lv2.Pt() > lv1.Pt() ) { LorentzV tmp = lv1; lv1 = lv2; lv2 = tmp; }

  }

  double pa[3]; //m, px, py, of object 1
  double pb[3]; //m, px ,py, of object 2
  double pm[3];       //jet1
  pa[1] = lv1.Px();
  pa[2] = lv1.Py();
  pa[0] = 0.;//KS_MT(objects[0]);
            //jet2
  pb[1] = lv2.Px();
  pb[2] = lv2.Py();
  pb[0] = 0.;//KS_MT(objects[1]);

  pm[1]= ev.CommonMHT().Px();
  pm[2]= ev.CommonMHT().Py();

  // set invisable mass
  double mn = 0.;
  mt2_event.set_momenta(pa,pb,pm);
  mt2_event.set_mn(mn);
  // mt2_event.print();
  return mt2_event.get_mt2();
}



bool HadronicCommonPlots::StandardPlots( Event::Data& ev ) {

  UInt_t n = ev.CommonObjects().size();
  Double_t weight = ev.GetEventWeight();


  if ( StandardPlots_ ){


   if ( n >= nMin_ && n <= nMax_ && n < Mt2_.size() ) {
      Mt2_[0]->Fill( HadronicCommonPlots::MT2(ev), weight );
      Mt2_[n]->Fill( HadronicCommonPlots::MT2(ev), weight );
    }
   

    if ( n >= nMin_ && n <= nMax_ && n < Mt2_LeadingJets_.size()) {
      Mt2_LeadingJets_[0]->Fill( HadronicCommonPlots::MT2_Leading(ev), weight );
      Mt2_LeadingJets_[n]->Fill( HadronicCommonPlots::MT2_Leading(ev), weight );
    }

   

    if ( n >= nMin_ && n <= nMax_ && n < MHT_.size()) {
      MHT_[0]->Fill( ev.CommonMHT().Pt(), weight );
      MHT_[n]->Fill( ev.CommonMHT().Pt(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < HT_.size() ) {
      HT_[0]->Fill( ev.CommonHT(), weight );
      HT_[n]->Fill( ev.CommonHT(), weight );
    }

   

    if ( n >= nMin_ && n <= nMax_ && n < MHTOvHT_.size() ) {
      MHTOvHT_[0]->Fill( ev.CommonMHT().Pt()/ev.CommonHT(), weight );
      MHTOvHT_[n]->Fill( ev.CommonMHT().Pt()/ev.CommonHT(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < Meff_.size()) {
      Meff_[0]->Fill( ev.CommonMHT().Pt()+ev.CommonHT(), weight );
      Meff_[n]->Fill( ev.CommonMHT().Pt()+ev.CommonHT(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < AlphaT_Hadronic_.size()  ) {
      AlphaT_Hadronic_[0]->Fill( ev.hadAlpha_t(), weight );
      AlphaT_Hadronic_[n]->Fill( ev.hadAlpha_t(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < AlphaT_Zoomed_.size()  ) {
      AlphaT_Zoomed_[0]->Fill( ev.CommonAlphaT(), weight );
      AlphaT_Zoomed_[n]->Fill( ev.CommonAlphaT(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < AlphaT_.size()  ) {
      AlphaT_[0]->Fill( ev.CommonAlphaT(), weight );
      AlphaT_[n]->Fill( ev.CommonAlphaT(), weight );
    }

   

   

  

  

    for(unsigned int i = 0; i < ev.JD_CommonJets().accepted.size() && i < 3; i++){
      fem_[0]->Fill(ev.JD_CommonJets().accepted[i]->GetEmFrac(),weight);
      JetPt_[0]->Fill(ev.JD_CommonJets().accepted[i]->Pt(),weight);
      JetEta_[0]->Fill(ev.JD_CommonJets().accepted[i]->Eta(),weight);
      fem_[i+1]->Fill(ev.JD_CommonJets().accepted[i]->GetEmFrac(),weight);
      JetPt_[i+1]->Fill(ev.JD_CommonJets().accepted[i]->Pt(),weight);
      JetEta_[i+1]->Fill(ev.JD_CommonJets().accepted[i]->Eta(),weight);
    }


   

  }
  return true;

}

bool HadronicCommonPlots::DeadECALPlots( Event::Data& ev ) {

  UInt_t n = ev.CommonObjects().size();
  Double_t weight = ev.GetEventWeight();

  Double_t TPMHT = 0;
  Double_t TPHT = 0;

  int idx = 0;

  LorentzV mht;
  mht.SetPxPyPzE(0.,0.,0.,0.);

  //  cout << " size " << ev.ecalDeadTowerNBadXtals()->size() << endl;
  if(DeadECALPlots_){


    double biasedDPhi = 10;
    float deadECALDR = 100;
  
    for( std::vector<Event::Jet const *>::const_iterator i = ev.JD_CommonJets().accepted.begin();
	 i != ev.JD_CommonJets().accepted.end();
	 ++i ){

    float newBiasDPhi = fabs(ROOT::Math::VectorUtil::DeltaPhi(**i, ev.CommonMHT() + (**i) + ev.JD_CommonJets().babyHT_30_50)) ;
    if(newBiasDPhi < biasedDPhi){
      biasedDPhi = newBiasDPhi;
      if(deadECALFile_ != "")deadECALDR = DeadECALDR_File( deadECALFile_,(*i)->Phi(),(*i)->Eta(),0);
      else deadECALDR = DeadECALDR(ev,(*i)->Phi(),(*i)->Eta(),0);
    }
  }
  for( std::vector<Event::Jet const*>::const_iterator iI = ev.JD_CommonJets().baby_30_50.begin(); iI != ev.JD_CommonJets().baby_30_50.end();
	 ++iI) {
    float newBiasDPhi_2 = fabs(ROOT::Math::VectorUtil::DeltaPhi(**iI, ev.CommonMHT() + (**iI) + ev.JD_CommonJets().babyHT_30_50)) ;
    if(newBiasDPhi_2 < biasedDPhi){
      biasedDPhi = newBiasDPhi_2;
      if(deadECALFile_ != "")deadECALDR = DeadECALDR_File( deadECALFile_,(*iI)->Phi(),(*iI)->Eta(),0);
      else deadECALDR = DeadECALDR(ev,(*iI)->Phi(),(*iI)->Eta(),0);
    }
  }

  if( biasedDPhi <= ev.LowPtBiasedCommonRecoilMETJetDPhi() && ev.LowPtBiasedCommonRecoilMETJetDPhi() < 0.5){
    if( n >= nMin_ && n <= nMax_ && n < BadJetECALDR_.size() ){
      BadJetECALDR_[0]->Fill(deadECALDR,weight);
      BadJetECALDR_[n]->Fill(deadECALDR,weight);
    }
  }
  else {
     if( n >= nMin_ && n <= nMax_ && n < allMinECALDR_.size() ){
      allMinECALDR_[0]->Fill(deadECALDR,weight);
      allMinECALDR_[n]->Fill(deadECALDR,weight);
    }

  }

  try{
    // cout << " size " << ev.ecalDeadTowerTrigPrimP4()->size() << endl;
    for(std::vector<ICF_LorentzV>::const_iterator ii=ev.ecalDeadTowerTrigPrimP4()->begin();ii!=ev.ecalDeadTowerTrigPrimP4()->end();++ii,++idx){
      // cout << " pt " << (*ii).Pt() << endl;
      if((*ii).E() != 0){
	TPHT = TPHT+ (*ii).Et();
	mht-=(*ii);
      }
    }
    TPMHT = fabs(mht.Et());
    
  }
  catch(...){
    //cout << " dead trigger tower not in sample " << endl;
  }
    
 

    if ( n >= nMin_ && n <= nMax_ && n < TPMHT_.size()  ) {
      TPMHT_[0]->Fill( TPMHT, weight );
      TPMHT_[n]->Fill( TPMHT, weight );
      //cout << " TPMHT " << TPMHT << " TPHT " << TPHT << " dead ecaldr " << deadECALDR << endl;
    }
    if( n >= nMin_ && n <= nMax_ && n < TPHT_.size()  ) {
      TPHT_[0]->Fill( TPHT, weight );
      TPHT_[n]->Fill( TPHT, weight );
    }
    if( n >= nMin_ && n <= nMax_ && n < TPMHTRatio_.size()  ) {
      TPMHTRatio_[0]->Fill( ev.CommonMHT().Et()/(ev.CommonMHT()+mht).Et(),weight);
      TPMHTRatio_[n]->Fill( ev.CommonMHT().Et()/(ev.CommonMHT()+mht).Et(),weight);
    }
    if ( n >= nMin_ && n <= nMax_ && n < BiasedDphi_.size()  ) {
      BiasedDphi_[0]->Fill( ev.CommonMinBiasDPhi(), weight );
      BiasedDphi_[n]->Fill( ev.CommonMinBiasDPhi(), weight );
    }


  }


  return true;
}


bool HadronicCommonPlots::CleaningControlPlots(Event::Data& ev){

   UInt_t n = ev.CommonObjects().size();
   Double_t weight = ev.GetEventWeight();

   Double_t noisy_ECalo_HT = 0;
   

   LorentzV noisy_ECalo_MHT;
   noisy_ECalo_MHT.SetPxPyPzE(0.,0.,0.,0.);

   int idx = 0;

  if ( CleaningControlPlots_ ){

    try{
       for(std::vector<ICF_LorentzV>::const_iterator ii=ev.rechitCaloP4Eb()->begin();ii!=ev.rechitCaloP4Eb()->end();++ii,++idx){

	  noisy_ECalo_HT = noisy_ECalo_HT+ (*ii).Et();
	  noisy_ECalo_MHT -=(*ii);
	}
        for(std::vector<ICF_LorentzV>::const_iterator ii=ev.rechitCaloP4Ee()->begin();ii!=ev.rechitCaloP4Ee()->end();++ii,++idx){

	  noisy_ECalo_HT = noisy_ECalo_HT+ (*ii).Et();
	  noisy_ECalo_MHT -=(*ii);
	}
      }
    catch(...){}
    

    if ( n >= nMin_ && n <= nMax_ && n < NoisyMHT_.size()  ) {
      NoisyMHT_[0]->Fill(noisy_ECalo_MHT.Et(), weight );
      NoisyMHT_[n]->Fill(noisy_ECalo_MHT.Et(), weight );
    }
    if( n >= nMin_ && n <= nMax_ && n < NoisyHT_.size()  ) {
      NoisyHT_[0]->Fill(noisy_ECalo_HT, weight );
      NoisyHT_[n]->Fill(noisy_ECalo_HT, weight );
    }



  }

  return true;

}


bool HadronicCommonPlots::MECPlots(Event::Data& ev){

  UInt_t n = ev.CommonObjects().size();
  Double_t weight = ev.GetEventWeight();

  if ( MECPlots_ ){

    Double_t babyMHT_10_50 = (ev.JD_CommonJets().babyHT).Pt();
    Double_t babyMHT_10_30 = (ev.JD_CommonJets().babyHT_10_30).Pt();
    Double_t MHTratio_10_50 = ev.CommonMHT().Pt()/(ev.JD_CommonJets().babyHT+ev.CommonMHT()).Pt();
  
      
    Double_t MHTPFMETDiff = (ev.CommonMHT().Pt()-ev.PFMET().Pt());    
    Double_t MHTCaloMETDiff = (ev.CommonMHT().Pt()-ev.CaloMET().Pt());

    Double_t Meff = ev.CommonMHT().Pt()+ev.CommonHT();


 

    if ( n >= nMin_ && n <= nMax_ && n < MHTPFMETDiffOvMeff_.size()  ) {
      MHTPFMETDiffOvMeff_[0]->Fill( MHTPFMETDiff/Meff, weight );
      MHTPFMETDiffOvMeff_[n]->Fill( MHTPFMETDiff/Meff, weight );
    }
    if( n >= nMin_ && n <= nMax_ && n < MHTCaloMETDiffOvMeff_.size()  ) {
      MHTCaloMETDiffOvMeff_[0]->Fill( MHTCaloMETDiff/Meff, weight );
      MHTCaloMETDiffOvMeff_[n]->Fill( MHTCaloMETDiff/Meff, weight );
    }
    if( n >= nMin_ && n <= nMax_ && n < PFMET_vs_MHTPFMETDiffOvMeff_.size()  ) {
      PFMET_vs_MHTPFMETDiffOvMeff_[0]->Fill(ev.PFMET().Pt(), MHTPFMETDiff/Meff, weight );
      PFMET_vs_MHTPFMETDiffOvMeff_[n]->Fill(ev.PFMET().Pt(), MHTPFMETDiff/Meff, weight );
    }
    if( n >= nMin_ && n <= nMax_ && n < MHTOvPFMET_.size()  ) {
      MHTOvPFMET_[0]->Fill(ev.CommonMHT().Pt()/ev.PFMET().Pt(),weight);
      MHTOvPFMET_[n]->Fill(ev.CommonMHT().Pt()/ev.PFMET().Pt(),weight);
    }
    if( n >= nMin_ && n <= nMax_ && n < MHT_vs_PFMET_.size()  ) {
      MHT_vs_PFMET_[0]->Fill(ev.CommonMHT().Pt(),ev.PFMET().Pt(),weight);
      MHT_vs_PFMET_[n]->Fill(ev.CommonMHT().Pt(),ev.PFMET().Pt(),weight);
    }
    if( n >= nMin_ && n <= nMax_ && n < BabyJetMHT_10_50_.size()  ) {
      BabyJetMHT_10_50_[0]->Fill(babyMHT_10_50,weight);
      BabyJetMHT_10_50_[n]->Fill(babyMHT_10_50,weight);
    }
    if( n >= nMin_ && n <= nMax_ && n < BabyJetMHT_10_30_.size()  ) {
      BabyJetMHT_10_30_[0]->Fill(babyMHT_10_30,weight);
      BabyJetMHT_10_30_[n]->Fill(babyMHT_10_30,weight);
    }
    if( n >= nMin_ && n <= nMax_ && n < MissedMHT_.size()  ) {
      MissedMHT_[0]->Fill(MHTratio_10_50,weight);
      MissedMHT_[n]->Fill(MHTratio_10_50,weight);
    }
    
  }


   return true;


}


Double_t DeadECALDR( Event::Data& ev,float jetphi,float jeteta, int nBad){
  double DRmin = 100;
  TLorentzVector testjetVec(0,0,0,0);
  int idx = 0;
 
  testjetVec.SetPtEtaPhiE(100,jeteta,jetphi,100);
  try{
    for(std::vector<ICF_LorentzV>::const_iterator ii=ev.ecalDeadTowerTrigPrimP4()->begin();ii!=ev.ecalDeadTowerTrigPrimP4()->end();++ii,++idx){
      if((*ii).E() >0){
	float DR = fabs(ROOT::Math::VectorUtil::DeltaR(*ii,testjetVec));
	if(DR < DRmin) DRmin = DR;
      }
      
    }
  }
  catch(...){}

  return DRmin;
}
 
Double_t DeadECALDR_File(TString deadECALfile,float jetphi,float jeteta, int nBad){
  // cout << " hi ho " << deadECALfile << endl;
  TLorentzVector testjetVec(0,0,0,0);
  double DRmin = 100;
  testjetVec.SetPtEtaPhiE(100,jeteta,jetphi,100);

  //cout << " in dead ecal " << endl;
  ifstream myfile(deadECALfile);
  if(!myfile.good()) cout << "file is not there " << endl;
  if(myfile.is_open()){

    while(!myfile.eof()){

      float phi,eta;
      int iEta,iPhi,nBadCells;
      myfile>>eta;
      myfile>>phi;
      myfile>>iEta;
      myfile>>iPhi;
      myfile>>nBadCells;
      // cout <<eta<< " "<< phi<<endl;
      if(nBadCells > nBad){
	TLorentzVector testVec(0,0,0,0);
	testVec.SetPtEtaPhiE(100,eta,phi,100);
	float DR = fabs(ROOT::Math::VectorUtil::DeltaR(testVec,testjetVec));
	if(DR < DRmin) DRmin = DR;
      }
    }
   
    myfile.close();
  } 
  return DRmin;

} 
  
  
 
 
