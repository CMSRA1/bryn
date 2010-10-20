#include "HadronicCommonPlots.hh"
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
#include "TMath.h"

using namespace Operation;

// -----------------------------------------------------------------------------
HadronicCommonPlots::HadronicCommonPlots( const Utils::ParameterSet& ps ) :
// Misc
dirName_( ps.Get<std::string>("DirName") ),
  nMin_( ps.Get<int>("MinObjects") ),
  nMax_( ps.Get<int>("MaxObjects") ),
// MT2
  StandardPlots_( ps.Get<bool>("StandardPlots") )

  {}

// -----------------------------------------------------------------------------
//
HadronicCommonPlots::~HadronicCommonPlots() {}

// -----------------------------------------------------------------------------
//
void HadronicCommonPlots::Start( Event::Data& ev ) {
  initDir( ev.OutputFile(), dirName_.c_str() );
  BookHistos();
}

// -----------------------------------------------------------------------------
//
void HadronicCommonPlots::BookHistos() {
  if ( StandardPlots_ )           { StandardPlots(); }
}

// -----------------------------------------------------------------------------
//
bool HadronicCommonPlots::Process( Event::Data& ev ) {
  if ( StandardPlots_ )               { StandardPlots(ev); }
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
void HadronicCommonPlots::StandardPlots() {





  BookHistArray( DPhi_MHT_MHTBaby_,
    "CosDetlaPhi_MHT_MHTBaby_",
    ";#Delta Cos#phi(MHT,MHTbaby); Events/0.65 rad;",
    40, -1., 1,
    nMax_+1, 0, 1, true );

  BookHistArray( DPhi_MET_MHTBaby_,
    "DetlaPhi_MET_MHTBaby_",
    ";#Delta #phi(MET,MHTbaby); Events/0.65 rad;",
    40, 0., TMath::Pi(),
    nMax_+1, 0, 1, true );


  BookHistArray( DPhi_MET_MHT_,
    "DetlaPhi_MET_MHT_",
    ";#Delta #phi(MET,MHTbaby); Events/0.65 rad;",
    40, 0., TMath::Pi(),
    nMax_+1, 0, 1, true );


  BookHistArray( BabyJetMHT_StandardAlphaT_,
    "BabyJetMHT_vs_AlphaT",
    "Cos(Dphi(MHT,MHTbaby));CommonAlphaT;",
    60,0.,1.5,
    20,-1.,1.,
    nMax_+1, 0, 1, true );


  BookHistArray( BabyJetMHT_StandardHT_,
    "BabyJetMHT_vs_HT",
    "CommonHT;BabyJetMHT;",
    200,0.,1000.,
    200,0.,1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( BabyJetMHT_StandardMHT_,
    "BabyJetMHT_vs_MHT",
    "CommonMHT;BabyJetMHT;",
    200,0.,1000.,
    200,0.,1000.,
    nMax_+1, 0, 1, true );


  BookHistArray( BabyJetMHT_,
    "BabyJetMHT",
    ";BabyJetMHT;Events/5GeV;",
    60, .0, 300.,
    nMax_+1, 0, 1, true );


  BookHistArray( MHT_PFMET_,
    "MHT_PFMET_",
    ";MHT_PFMET/PFMET;Events/0.2;",
    100, -2.0, 20.,
    nMax_+1, 0, 1, true );

  BookHistArray( MHT_PFMET_AfterCut_,
    "MHT_PFMET_After_AT_55_",
    ";MHT_PFMET/PFMET;Events/0.22;",
    100, -2.0, 20.,
    nMax_+1, 0, 1, true );


  BookHistArray( MissedHT_,
    "MHTRatio_after_alphaT_55",
    ";MHT30/MHT10;Events/0.1;",
    100, 0., 10,
    nMax_+1, 0, 1, true );

  BookHistArray( DetlaPhi_LeadingJets_,
    "DetlaPhi_LeadingJets_",
    ";#Delta #phi(j_{1},j_{i}); Events/0.65 rad;",
    40, 0., TMath::Pi(),
    nMax_+1, 0, 1, true );


  BookHistArray( DetlaPhi_NextToLeadingJets_,
    "DetlaPhi_NextToLeadingJets_",
    ";#Delta #phi(j_{2},j_{3}); Events/0.65 rad;",
    40, 0., TMath::Pi(),
    nMax_+1, 0, 1, true );

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

  BookHistArray( AlphaT_METCut_,
    "AlphaT_afterMht_pfmet",
    ";#alpha_{T};Events/0.025;",
    60,0.,1.5,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_Zoomed_METCut_,
    "AlphaT_Zoomed_afterMht_pfmet",
    ";#alpha_{T}; Events/0.0025;",
    60,0.45,0.6,
    nMax_+1, 0, 1, true );




  BookHistArray( AlphaT_Hadronic_,
    "AlphaT_Hadronic",
    ";#alpha_{T};Events/0.025;",
    60,0.,1.5,
    nMax_+1, 0, 1, true );


  BookHistArray( AlphatCut_Meff_,
    "EffectiveMass_after_alphaT_55",
    ";M_{eff} (GeV); Events/40 GeV;",
    75, 0., 3000.,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphatCut_HT_,
    "HT_after_alphaT",
    ";H_{T} (GeV); Events/25 (GeV);",
    80,0.,2000.,
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



  BookHistArray( AlphatCut_BiasedDphi_,
    "BiasedDeltaPhi_after_alphaT_55",
    ";#Delta #phi^{*} (rad); Events/0.05 rad;",
    60, 0., TMath::Pi(),
    nMax_+1, 0, 1, true );

  BookHistArray( BiasedDphi_,
    "BiasedDeltaPhi",
    ";#Delta #phi^{*} (rad); Events/0.05 rad;",
    60, 0., TMath::Pi(),
    nMax_+1, 0, 1, true );

  BookHistArray( MHToverHT_,
    "MHToverHT",
    ";#slash{H}_{T}/H_{T};Events/0.025;",
    40,0.,1.,
    nMax_+1, 0, 1, true );

  BookHistArray( MHT_,
    "MHT",
    ";#slash{H}_{T} (GeV); Events/10 GeV;",
    40,0.,400.,
    nMax_+1, 0, 1, true );



  BookHistArray( HT_forRatio_,
    "HT_forRatioPlots",
    ";H_{T} (GeV); Events/25 GeV;",
    80,0.,2000.,
    nMax_+1, 0, 1, true );


  BookHistArray( PFmetvsMHT_,
    "PFMetVsMHT",
    "",
    200,0.,1000.,
    200,0.,1000.,
    nMax_+1, 0, 1, true );


  BookHistArray( Multiplicity_,
    "JetMultiplicity",
    ";n",
    15,0.,15.,
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


    if((ev.CommonMHT().Pt()-ev.PFMET().Pt())/(ev.CommonHT()+ev.CommonMHT().Pt()) < 0.15){
      if ( n >= nMin_ && n <= nMax_ && n < AlphaT_METCut_.size()) {
        AlphaT_METCut_[0]->Fill(ev.CommonAlphaT(),weight);
        AlphaT_METCut_[n]->Fill(ev.CommonAlphaT(),weight);
        AlphaT_Zoomed_METCut_[0]->Fill(ev.CommonAlphaT(),weight);
        AlphaT_Zoomed_METCut_[n]->Fill(ev.CommonAlphaT(),weight);
      }

    }



    if ( n >= nMin_ && n <= nMax_ && n < DPhi_MHT_MHTBaby_.size()) {
      // DPhi_MHT_MHTBaby_[0]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().killedHT)),weight);
      // DPhi_MHT_MHTBaby_[n]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().killedHT)),weight);

    }

    if ( n >= nMin_ && n <= nMax_ && n < DPhi_MET_MHTBaby_.size()) {
      // DPhi_MET_MHTBaby_[0]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.JD_CommonJets().killedHT)),weight);
      // DPhi_MET_MHTBaby_[n]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.JD_CommonJets().killedHT)),weight);

    }

    if ( n >= nMin_ && n <= nMax_ && n < DPhi_MET_MHT_.size()) {
      DPhi_MET_MHT_[0]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.CommonMHT())),weight);
      DPhi_MET_MHT_[n]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.CommonMHT())),weight);

    }

    if ( n >= nMin_ && n <= nMax_ && n < MHT_PFMET_.size()) {
      MHT_PFMET_[0]->Fill((ev.CommonMHT().Pt()-ev.PFMET().Pt())/ev.PFMET().Pt(),weight);
      MHT_PFMET_[n]->Fill((ev.CommonMHT().Pt()-ev.PFMET().Pt())/ev.PFMET().Pt(),weight);

    }

    if ( n >= nMin_ && n <= nMax_ && n < BabyJetMHT_.size()) {
      // BabyJetMHT_[0]->Fill( ev.JD_CommonJets().killedHT.Pt(), weight );
      // BabyJetMHT_[n]->Fill( ev.JD_CommonJets().killedHT.Pt(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < BabyJetMHT_StandardMHT_.size()) {
      // BabyJetMHT_StandardMHT_[0]->Fill( ev.CommonMHT().Pt(),ev.JD_CommonJets().killedHT.Pt(), weight );
      // BabyJetMHT_StandardMHT_[n]->Fill( ev.CommonMHT().Pt(),ev.JD_CommonJets().killedHT.Pt(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < BabyJetMHT_StandardAlphaT_.size()) {
      // BabyJetMHT_StandardAlphaT_[0]->Fill( ev.CommonAlphaT(), cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().killedHT)), weight );
      // BabyJetMHT_StandardAlphaT_[n]->Fill( ev.CommonAlphaT(), cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().killedHT)), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < BabyJetMHT_StandardAlphaT_.size()) {
      // BabyJetMHT_StandardHT_[0]->Fill( ev.CommonHT(), ev.JD_CommonJets().killedHT.Pt(), weight );
      // BabyJetMHT_StandardHT_[n]->Fill( ev.CommonHT(), ev.JD_CommonJets().killedHT.Pt(), weight );
    }


    if ( n >= nMin_ && n <= nMax_ && n < Mt2_LeadingJets_.size()) {
      Mt2_LeadingJets_[0]->Fill( HadronicCommonPlots::MT2_Leading(ev), weight );
      Mt2_LeadingJets_[n]->Fill( HadronicCommonPlots::MT2_Leading(ev), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < Multiplicity_.size()) {
      Multiplicity_[0]->Fill( n, weight );
      Multiplicity_[n]->Fill( n, weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < MHT_.size()) {
      MHT_[0]->Fill( ev.CommonMHT().Pt(), weight );
      MHT_[n]->Fill( ev.CommonMHT().Pt(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < HT_.size() ) {
      HT_[0]->Fill( ev.CommonHT(), weight );
      HT_[n]->Fill( ev.CommonHT(), weight );
    }

    if(ev.CommonAlphaT() > 0.55){

      if ( n >= nMin_ && n <= nMax_ && n < HT_forRatio_.size() ) {
        HT_forRatio_[0]->Fill(  ev.CommonHT(), weight );
        HT_forRatio_[n]->Fill( ev.CommonHT(), weight );
      }

      if ( n >= nMin_ && n <= nMax_ && n < MissedHT_.size() ) {
        // MissedHT_[0]->Fill(  ev.CommonRecoilMET().Pt()/(ev.CommonRecoilMET()+ev.JD_CommonJets().killedHT).Pt(), weight );
        // MissedHT_[n]->Fill( ev.CommonRecoilMET().Pt()/(ev.CommonRecoilMET()+ev.JD_CommonJets().killedHT).Pt(), weight );
      }

    }

    if(ev.CommonAlphaT() > 0.55){

      if ( n >= nMin_ && n <= nMax_ && n < MHT_PFMET_AfterCut_.size()) {
        MHT_PFMET_AfterCut_[0]->Fill((ev.CommonMHT().Pt()-ev.PFMET().Pt())/ev.PFMET().Pt(),weight);
        MHT_PFMET_AfterCut_[n]->Fill((ev.CommonMHT().Pt()-ev.PFMET().Pt())/ev.PFMET().Pt(),weight);

      }

      if ( n >= nMin_ && n <= nMax_ && n < AlphatCut_HT_.size() ) {
        AlphatCut_HT_[0]->Fill( ev.CommonHT(), weight );
        AlphatCut_HT_[n]->Fill( ev.CommonHT(), weight );
      }

      if ( n >= nMin_ && n <= nMax_ && n < AlphatCut_Meff_.size()) {
        AlphatCut_Meff_[0]->Fill( ev.CommonMHT().Pt()+ev.CommonHT(), weight );
        AlphatCut_Meff_[n]->Fill( ev.CommonMHT().Pt()+ev.CommonHT(), weight );
      }

      if ( n >= nMin_ && n <= nMax_ && n < AlphatCut_BiasedDphi_.size()  ) {
        AlphatCut_BiasedDphi_[0]->Fill( ev.CommonMinBiasDPhi(), weight );
        AlphatCut_BiasedDphi_[n]->Fill( ev.CommonMinBiasDPhi(), weight );
      }
    }

    if ( n >= nMin_ && n <= nMax_ && n < MHToverHT_.size() ) {
      MHToverHT_[0]->Fill( ev.CommonMHT().Pt()/ev.CommonHT(), weight );
      MHToverHT_[n]->Fill( ev.CommonMHT().Pt()/ev.CommonHT(), weight );
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

    if ( n >= nMin_ && n <= nMax_ && n < Mt2_.size() ) {
      Mt2_[0]->Fill( HadronicCommonPlots::MT2(ev), weight );
      Mt2_[n]->Fill( HadronicCommonPlots::MT2(ev), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < BiasedDphi_.size()  ) {
      BiasedDphi_[0]->Fill( ev.CommonMinBiasDPhi(), weight );
      BiasedDphi_[n]->Fill( ev.CommonMinBiasDPhi(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < PFmetvsMHT_.size()  ) {
      PFmetvsMHT_[0]->Fill( ev.PFMET().Pt(),ev.CommonRecoilMET().Pt(), weight );
      PFmetvsMHT_[n]->Fill( ev.PFMET().Pt(),ev.CommonRecoilMET().Pt(), weight );
    }


    if( n >= nMin_ && n <= nMax_ && n < DetlaPhi_LeadingJets_.size() ){
      DetlaPhi_LeadingJets_[1]->Fill( fabs( ROOT::Math::VectorUtil::DeltaPhi(*ev.JD_CommonJets().accepted[0],*ev.JD_CommonJets().accepted[1])));
      if(n <2){
        DetlaPhi_NextToLeadingJets_[2]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(*ev.JD_CommonJets().accepted[1],*ev.JD_CommonJets().accepted[2])));

      }
    }


    for(unsigned int i = 0; i < ev.JD_CommonJets().accepted.size() && i < 3; i++){
      fem_[0]->Fill(ev.JD_CommonJets().accepted[i]->GetEmFrac(),weight);
      JetPt_[0]->Fill(ev.JD_CommonJets().accepted[i]->Pt(),weight);
      JetEta_[0]->Fill(ev.JD_CommonJets().accepted[i]->Eta(),weight);
      fem_[i+1]->Fill(ev.JD_CommonJets().accepted[i]->GetEmFrac(),weight);
      JetPt_[i+1]->Fill(ev.JD_CommonJets().accepted[i]->Pt(),weight);
      JetEta_[i+1]->Fill(ev.JD_CommonJets().accepted[i]->Eta(),weight);
    }


    if(!ev.pthat.enabled()){
      // if(ev.CommonAlphaT() > 0.55 || HadronicCommonPlots::MT2_Leading(ev) > 200. || HadronicCommonPlots::MT2(ev) > 200. || ev.CommonMHT().Pt() > 250.){
        if(ev.CommonAlphaT() > 0.55 && ev.CommonHT() > 350.){
          LorentzV lv1(0.,0.,0.,0.);
          lv1 += *(ev.JD_CommonJets().accepted[0]);
          lv1 += *(ev.JD_CommonJets().accepted[1]);
        cout << " This event passes offline cuts!!! " <<endl;
        cout << "Alpha T is " << ev.CommonAlphaT() << " HT is "<< ev.CommonHT() <<" MHT is  " << ev.CommonMHT().Pt() << " and MT2 is " << HadronicCommonPlots::MT2_Leading(ev) << " Bised delta phi is " << ev.CommonMinBiasDPhi()<< " Meff is " << ev.CommonMHT().Pt()+ev.CommonHT()<<endl;
        if(HadronicCommonPlots::MT2_Leading(ev) > 300.){ cout << "MT2 Variables are: px,py, Leading Jet " <<
          ev.JD_CommonJets().accepted[0]->Px() << "," << ev.JD_CommonJets().accepted[0]->Py() << "," <<" px,py, Second Jet " << ev.JD_CommonJets().accepted[1]->Px()  <<"," <<  ev.JD_CommonJets().accepted[1]->Py() << "," << endl;}
        cout << "run : " <<  ev.RunNumber() << "lumi Section "<< ev.LumiSection() <<  " event : "<<  ev.EventNumber() << " Alpha T is" << ev.CommonAlphaT() << " Effective mass is : " << ev.CommonMHT().Pt()+ev.CommonHT() << " Dijet Mass is " << (lv1).M() << endl;
        cout << "x-cleaned"<<endl;
        ev.PrintStableVisRec();
        cout << "all"<<endl;
        ev.PrintStableVisAllRec();

      }

    }

  }
  return true;

}
