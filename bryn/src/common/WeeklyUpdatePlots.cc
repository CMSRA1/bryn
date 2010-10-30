#include "WeeklyUpdatePlots.hh"
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
WeeklyUpdatePlots::WeeklyUpdatePlots( const Utils::ParameterSet& ps ) :
// Misc
dirName_( ps.Get<std::string>("DirName") ),
  nMin_( ps.Get<int>("MinObjects") ),
  nMax_( ps.Get<int>("MaxObjects") ),
// MT2
  StandardPlots_( ps.Get<bool>("StandardPlots") )

  {}

// -----------------------------------------------------------------------------
//
WeeklyUpdatePlots::~WeeklyUpdatePlots() {}

// -----------------------------------------------------------------------------
//
void WeeklyUpdatePlots::Start( Event::Data& ev ) {
  initDir( ev.OutputFile(), dirName_.c_str() );
  BookHistos();
}

// -----------------------------------------------------------------------------
//
void WeeklyUpdatePlots::BookHistos() {
  if ( StandardPlots_ )           { StandardPlots(); }
}

// -----------------------------------------------------------------------------
//
bool WeeklyUpdatePlots::Process( Event::Data& ev ) {
  if ( StandardPlots_ )               { StandardPlots(ev); }
  return true;
}

// -----------------------------------------------------------------------------
//
std::ostream& WeeklyUpdatePlots::Description( std::ostream& ostrm ) {
  ostrm << "Hadronic Common Plots ";
  ostrm << "(bins " << nMin_ << " to " << nMax_ << ") ";
  return ostrm;
}

// -----------------------------------------------------------------------------
//
void WeeklyUpdatePlots::StandardPlots() {



  BookHistArray( AlphaT_components_,
    "AlphaT_Components",
    ";#slashed{H}_{T}/H_{T};#Delta)H_{T}/H_{T}",
    20, 0., 1.,
    20, 0., 1.,
    nMax_+1, 0, 1, true );


  BookHistArray( AlphaTafterPFMEC_,
    "AlphaT_after_PF_MEC",
    ";#alpha_{T};Events/0.025;",
    60,0.,1.5,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_Zoomed_afterPFMEC_,
    "AlphaT_Zoomed_after_PF_MEC",
    ";#alpha_{T}; Events/0.0025;",
    60,0.45,0.6,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphaTafterCaloMEC_,
    "AlphaT_after_Calo_MEC",
    ";#alpha_{T};Events/0.025;",
    60,0.,1.5,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_ZoomedafterCaloMEC_,
    "AlphaT_Zoomed_after_Calo_MEC",
    ";#alpha_{T}; Events/0.0025;",
    60,0.45,0.6,
    nMax_+1, 0, 1, true );

  BookHistArray( DPhi_MHT_MHTBaby_,
    "CosDetlaPhi_MHT_MHTBaby_",
    ";#Delta Cos#phi(MHT,MHTbaby); Events/0.65 rad;",
    40, -1., 1,
    nMax_+1, 0, 1, true );

  BookHistArray( DPhi_MHT_MHTbaby_AfterAlphaT_,
    "DPhi_MHT_MHTbaby_AfterAlphaT_",
    ";Cos #Delta #phi(MHT,MHTbaby); Events/0.65 rad;",
    40, -1., 1.,
    nMax_+1, 0, 1, true );


  BookHistArray( DPhi_MHT_MHTbaby_vsMHTbabyOverMHT_,
    "DPhi_MHT_MHTbaby_vsMHTbabyOverMHT_",
    ";Cos #Delta #phi(MHT,MHTbaby);MHTBaby Over MHT",
    40, -1., 1.,
    50, 0., 5.,
    nMax_+1, 0, 1, true );

  BookHistArray( DPhi_MHT_MHTbaby_vsMHTbabyOverMHT_AfterAlphaT_,
    "DPhi_MHT_MHTbaby_vsMHTbabyOverMHT_AfterAlphaT_",
    ";Cos #Delta #phi(MHT,MHTbaby);MHTBaby Over MHT",
    40, -1., 1.,
    50, 0., 5.,
    nMax_+1, 0, 1, true );

  BookHistArray( BabyJetMHT_StandardAlphaT_,
    "BabyJetMHT_vs_AlphaT",
    "Cos(Dphi(MHT,MHTbaby));CommonAlphaT;",
    60,0.,1.5,
    20,-1.,1.,
    nMax_+1, 0, 1, true );

  BookHistArray( BabyJetMHT_,
    "BabyJetMHT",
    ";BabyJetMHT;Events/5GeV;",
    60, .0, 300.,
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
    "AlphaT_after_MHTRatio",
    ";#alpha_{T};Events/0.025;",
    60,0.,1.5,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_Zoomed_METCut_,
    "AlphaT_Zoomed_after_MHTRatio",
    ";#alpha_{T}; Events/0.0025;",
    60,0.45,0.6,
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
    100,0.,2500.,
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
    60,0.,600.,
    nMax_+1, 0, 1, true );



  BookHistArray( HT_forRatio_,
    "HT_forRatioPlots",
    ";H_{T} (GeV); Events/25 GeV;",
    80,0.,2000.,
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

Double_t WeeklyUpdatePlots::MT2_Leading( Event::Data& ev ){
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


Double_t WeeklyUpdatePlots::DeltaHT( Event::Data& ev){
  std::vector<Event::Jet const *> jet = ev.JD_CommonJets().accepted;
  UInt_t n = jet.size();

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

  return lv1.Et()-lv2.Et();

}



Double_t WeeklyUpdatePlots::MT2( Event::Data& ev){

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



bool WeeklyUpdatePlots::StandardPlots( Event::Data& ev ) {

  UInt_t n = ev.CommonObjects().size();
  Double_t weight = ev.GetEventWeight();


  if ( StandardPlots_ ){


    if( (ev.CommonMHT().Pt()-ev.PFMET().Pt())/(ev.CommonMHT().Pt()+ev.CommonHT()) < 0.15){
      if( n >= nMin_ && n <= nMax_ && n < AlphaTafterPFMEC_.size() ) {
        AlphaTafterPFMEC_[0]->Fill(ev.CommonAlphaT(),weight);
        AlphaTafterPFMEC_[n]->Fill(ev.CommonAlphaT(),weight);
        AlphaT_Zoomed_afterPFMEC_[0]->Fill(ev.CommonAlphaT(),weight);
        AlphaT_Zoomed_afterPFMEC_[n]->Fill(ev.CommonAlphaT(),weight);
      }
    }

    if( (ev.CommonMHT().Pt()-LorentzV(*ev.metP4caloTypeII()).Pt())/(ev.CommonMHT().Pt()+ev.CommonHT()) < 0.15){
      if( n >= nMin_ && n <= nMax_ && n < AlphaTafterCaloMEC_.size() ) {
        AlphaTafterCaloMEC_[0]->Fill(ev.CommonAlphaT(),weight);
        AlphaTafterCaloMEC_[n]->Fill(ev.CommonAlphaT(),weight);
        AlphaT_ZoomedafterCaloMEC_[0]->Fill(ev.CommonAlphaT(),weight);
        AlphaT_ZoomedafterCaloMEC_[n]->Fill(ev.CommonAlphaT(),weight);
      }
    }


    if(ev.CommonMHT().Pt()/LorentzV(*ev.metP4caloTypeII()).Pt() < 1.25){
      if ( n >= nMin_ && n <= nMax_ && n < AlphaT_METCut_.size()) {
        AlphaT_METCut_[0]->Fill(ev.CommonAlphaT(),weight);
        AlphaT_METCut_[n]->Fill(ev.CommonAlphaT(),weight);
        AlphaT_Zoomed_METCut_[0]->Fill(ev.CommonAlphaT(),weight);
        AlphaT_Zoomed_METCut_[n]->Fill(ev.CommonAlphaT(),weight);
      }

    }



    if ( n >= nMin_ && n <= nMax_ && n < DPhi_MHT_MHTBaby_.size()) {
      DPhi_MHT_MHTBaby_[0]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),weight);
      DPhi_MHT_MHTBaby_[n]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),weight);

    }

    if ( n >= nMin_ && n <= nMax_ && n < DPhi_MET_MHTBaby_.size()) {
      DPhi_MET_MHTBaby_[0]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.JD_CommonJets().babyHT)),weight);
      DPhi_MET_MHTBaby_[n]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.JD_CommonJets().babyHT)),weight);

    }

    if ( n >= nMin_ && n <= nMax_ && n < DPhi_MET_MHT_.size()) {
      DPhi_MET_MHT_[0]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.CommonMHT())),weight);
      DPhi_MET_MHT_[n]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.CommonMHT())),weight);

    }



    if ( n >= nMin_ && n <= nMax_ && n < BabyJetMHT_.size()) {
      BabyJetMHT_[0]->Fill( ev.JD_CommonJets().babyHT.Pt(), weight );
      BabyJetMHT_[n]->Fill( ev.JD_CommonJets().babyHT.Pt(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < BabyJetMHT_StandardMHT_.size()) {
      BabyJetMHT_StandardMHT_[0]->Fill( ev.CommonMHT().Pt(),ev.JD_CommonJets().babyHT.Pt(), weight );
      BabyJetMHT_StandardMHT_[n]->Fill( ev.CommonMHT().Pt(),ev.JD_CommonJets().babyHT.Pt(), weight );
    }



    if ( n >= nMin_ && n <= nMax_ && n < DPhi_MHT_MHTbaby_vsMHTbabyOverMHT_.size()) {
      DPhi_MHT_MHTbaby_vsMHTbabyOverMHT_[0]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),
        (ev.JD_CommonJets().babyHT).Pt()/ev.CommonMHT().Pt(),weight);
      DPhi_MHT_MHTbaby_vsMHTbabyOverMHT_[n]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),
        (ev.JD_CommonJets().babyHT).Pt()/ev.CommonMHT().Pt(),weight);

    }




    if ( n >= nMin_ && n <= nMax_ && n < BabyJetMHT_StandardAlphaT_.size()) {
      BabyJetMHT_StandardAlphaT_[0]->Fill( ev.CommonAlphaT(), cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)), weight );
      BabyJetMHT_StandardAlphaT_[n]->Fill( ev.CommonAlphaT(), cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)), weight );
    }



    if ( n >= nMin_ && n <= nMax_ && n < Mt2_LeadingJets_.size()) {
      Mt2_LeadingJets_[0]->Fill( WeeklyUpdatePlots::MT2_Leading(ev), weight );
      Mt2_LeadingJets_[n]->Fill( WeeklyUpdatePlots::MT2_Leading(ev), weight );
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


    if ( n >= nMin_ && n <= nMax_ && n < MHToverHT_.size() ) {
      MHToverHT_[0]->Fill( ev.CommonMHT().Pt()/ev.CommonHT(), weight );
      MHToverHT_[n]->Fill( ev.CommonMHT().Pt()/ev.CommonHT(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < Meff_.size()) {
      Meff_[0]->Fill( ev.CommonMHT().Pt()+ev.CommonHT(), weight );
      Meff_[n]->Fill( ev.CommonMHT().Pt()+ev.CommonHT(), weight );
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
      Mt2_[0]->Fill( WeeklyUpdatePlots::MT2(ev), weight );
      Mt2_[n]->Fill( WeeklyUpdatePlots::MT2(ev), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < BiasedDphi_.size()  ) {
      BiasedDphi_[0]->Fill( ev.CommonMinBiasDPhi(), weight );
      BiasedDphi_[n]->Fill( ev.CommonMinBiasDPhi(), weight );
    }

    if( n >= nMin_ && n <= nMax_ && n < DetlaPhi_LeadingJets_.size() ){
      DetlaPhi_LeadingJets_[1]->Fill( fabs( ROOT::Math::VectorUtil::DeltaPhi(*ev.JD_CommonJets().accepted[0],*ev.JD_CommonJets().accepted[1])),weight);
      if(n <2){
        DetlaPhi_NextToLeadingJets_[2]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(*ev.JD_CommonJets().accepted[1],*ev.JD_CommonJets().accepted[2])),weight);

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



    if( n >= nMin_ && n <= nMax_ && n < AlphaT_components_.size() ){
      AlphaT_components_[0]->Fill(ev.CommonMHT().Pt()/ev.CommonHT(),WeeklyUpdatePlots::DeltaHT(ev)/ev.CommonHT(),weight);
      AlphaT_components_[n]->Fill(ev.CommonMHT().Pt()/ev.CommonHT(),WeeklyUpdatePlots::DeltaHT(ev)/ev.CommonHT(),weight);
    }





    if(ev.CommonAlphaT() > 0.55){

      if ( n >= nMin_ && n <= nMax_ && n < HT_forRatio_.size() ) {
        HT_forRatio_[0]->Fill(  ev.CommonHT(), weight );
        HT_forRatio_[n]->Fill( ev.CommonHT(), weight );
      }

      if ( n >= nMin_ && n <= nMax_ && n < MissedHT_.size() ) {
        MissedHT_[0]->Fill(  ev.CommonRecoilMET().Pt()/(ev.CommonRecoilMET()+ev.JD_CommonJets().babyHT).Pt(), weight );
        MissedHT_[n]->Fill( ev.CommonRecoilMET().Pt()/(ev.CommonRecoilMET()+ev.JD_CommonJets().babyHT).Pt(), weight );
      }

      if ( n >= nMin_ && n <= nMax_ && n < DPhi_MHT_MHTbaby_vsMHTbabyOverMHT_AfterAlphaT_.size()) {
        DPhi_MHT_MHTbaby_vsMHTbabyOverMHT_AfterAlphaT_[0]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),
          ev.JD_CommonJets().babyHT.Pt()/ev.CommonMHT().Pt(),weight);
        DPhi_MHT_MHTbaby_vsMHTbabyOverMHT_AfterAlphaT_[n]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),
          ev.JD_CommonJets().babyHT.Pt()/ev.CommonMHT().Pt(),weight);

      }



      if ( n >= nMin_ && n <= nMax_ && n < DPhi_MHT_MHTbaby_AfterAlphaT_.size()) {
        DPhi_MHT_MHTbaby_AfterAlphaT_[0]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),weight);
        DPhi_MHT_MHTbaby_AfterAlphaT_[n]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),weight);

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




    if(!ev.pthat.enabled()){
      // if(ev.CommonAlphaT() > 0.55 || WeeklyUpdatePlots::MT2_Leading(ev) > 200. || WeeklyUpdatePlots::MT2(ev) > 200. || ev.CommonMHT().Pt() > 250.){
      if(ev.CommonAlphaT() > 0.55 && ev.CommonHT() > 350.){
        LorentzV lv1(0.,0.,0.,0.);
        LorentzV lv2(0.,0.,0.,0.);
        lv1 += *(ev.JD_CommonJets().accepted[0]);
        lv2 += *(ev.JD_CommonJets().accepted[1]);
        cout << " This event passes offline cuts!!! " <<endl;
        cout << "Alpha T is " << ev.CommonAlphaT() << " HT is "<< ev.CommonHT() <<" MHT is  " << ev.CommonMHT().Pt() << " and MT2 is " << WeeklyUpdatePlots::MT2_Leading(ev) << " Bised delta phi is " << ev.CommonMinBiasDPhi()<< " Meff is " << ev.CommonMHT().Pt()+ev.CommonHT()<<endl;
        if(WeeklyUpdatePlots::MT2_Leading(ev) > 300.){ cout << "MT2 Variables are: px,py, Leading Jet " <<
          ev.JD_CommonJets().accepted[0]->Px() << "," << ev.JD_CommonJets().accepted[0]->Py() << "," <<" px,py, Second Jet " << ev.JD_CommonJets().accepted[1]->Px()  <<"," <<  ev.JD_CommonJets().accepted[1]->Py() << "," << endl;}
        cout << "run : " <<  ev.RunNumber() << "lumi Section "<< ev.LumiSection() <<  " event : "<<  ev.EventNumber() << " Alpha T is" << ev.CommonAlphaT() << " Effective mass is : " << ev.CommonMHT().Pt()+ev.CommonHT() << " Dijet Mass is " << (lv1+lv2).M() << endl;
        cout << "x-cleaned"<<endl;
        ev.PrintStableVisRec();
        cout << "all"<<endl;
        ev.PrintStableVisAllRec();

      }

    }

  }







  return true;

}
