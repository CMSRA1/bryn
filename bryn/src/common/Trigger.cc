#include "Trigger.hh"
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
Trigger::Trigger( const Utils::ParameterSet& ps ) :
// Misc
dirName_( ps.Get<std::string>("DirName") ),
  nMin_( ps.Get<int>("MinObjects") ),
  nMax_( ps.Get<int>("MaxObjects") ),
// MT2
  StandardPlots_( ps.Get<bool>("StandardPlots") )

  {}

// -----------------------------------------------------------------------------
//
Trigger::~Trigger() {}

// -----------------------------------------------------------------------------
//
void Trigger::Start( Event::Data& ev ) {
  initDir( ev.OutputFile(), dirName_.c_str() );
  BookHistos();
}

// -----------------------------------------------------------------------------
//
void Trigger::BookHistos() {
  if ( StandardPlots_ )           { StandardPlots(); }
}

// -----------------------------------------------------------------------------
//
bool Trigger::Process( Event::Data& ev ) {
  if ( StandardPlots_ )               { StandardPlots(ev); }
  return true;
}

// -----------------------------------------------------------------------------
//
std::ostream& Trigger::Description( std::ostream& ostrm ) {
  ostrm << "Hadronic Common Plots ";
  ostrm << "(bins " << nMin_ << " to " << nMax_ << ") ";
  return ostrm;
}

// -----------------------------------------------------------------------------
//
void Trigger::StandardPlots() {


  BookHistArray( MET70SecondJet70,
    "MET70SecondJet70",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Meffective350,
    "Meffective350",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Meffective375,
    "Meffective375",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Meffective400,
    "Meffective400",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Meffective425,
    "Meffective425",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Meffective450,
    "Meffective450",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht,
    "Ht",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht200,
    "Ht200",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht250,
    "Ht250",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht300,
    "Ht300",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht150Jet50,
    "Ht150Jet50",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht150SecondJet50,
    "Ht150SecondJet50",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht150Jet70,
    "Ht150Jet70",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht200Jet50,
    "Ht200Jet50",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht150SecondJet70,
    "Ht150SecondJet70",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht200SecondJet50,
    "Ht200SecondJet50",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht200SecondJet70,
    "Ht200SecondJet70",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( Ht200SecondJet70,
    "Ht200SecondJet70",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( MHT50SecondJet50,
    "MHT50SecondJet50",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( MHT50SecondJet70,
    "MHT50SecondJet70",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( MHT70SecondJet50,
    "MHT70SecondJet50",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( MHT70SecondJet70,
    "MHT70SecondJet70",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( MET50SecondJet50,
    "MET50SecondJet50",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( MET50SecondJet70,
    "MET50SecondJet70",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );



  BookHistArray( Ht200Jet70,
    "Ht200Jet70",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );

  BookHistArray( MET70SecondJet50,
    "MET70SecondJet50",
    ";H_{T};events/10GeV;",
    100, .0, 1000.,
    nMax_+1, 0, 1, true );
}
// -----------------------------------------------------------------------------
//
struct Trigger::EComp_sort
{

  bool operator() (const LorentzV & o1, const LorentzV & o2)  {
    return(o1.Et() > o2.Et());
  }
};
// -----------------------------------------------------------------------------
//

bool Trigger::StandardPlots( Event::Data& ev ) {

  double weight = ev.GetEventWeight();
  std::vector<LorentzV> ThresholdJets;

  std::vector<Event::Jet >::const_iterator ijet = ev.JD_Jets().begin();
  std::vector<Event::Jet >::const_iterator jjet = ev.JD_Jets().end();
  for ( ; ijet != jjet; ++ijet ) {

    LorentzV Jet = *ijet;

    Jet /= ev.jetCorrFactor()->at((*ijet).GetIndex());
    if( Jet.Pt() >= 20. ){ ThresholdJets.push_back(Jet); } // to enter collection jets must be above 20GeV uncorrected
  } // makes a collection of jets that are uncorrected, stores them in a vector
  std::sort(ThresholdJets.begin(),ThresholdJets.end(), EComp_sort() ); // sorth the uncorrected jet collection in Et order (as the trigger uses them)

  LorentzV mhtAllJets;
  double  htAllJets = 0.;
  for(unsigned int i =0; i < ThresholdJets.size(); i++){
    htAllJets += ThresholdJets[i].Et();
    mhtAllJets -= ThresholdJets[i];
  }

  // LorentzV mhtEtaThree;
  // double  htEtaThree = 0.;
  // for(unsigned int i =0; i < ThresholdJets.size(); i++){
  //   if(fabs(ThresholdJets[i].Eta) < 3. ){
  //     htEtaThree += ThresholdJets[i].Et();
  //     mhtEtaThree -= ThresholdJets[i];
  //   }
  // }

  unsigned int n = ThresholdJets.size();
//start Meffective trigger studies
//first reference collection:

  double Meff_allJets = htAllJets + mhtAllJets.Et();

  if(Meff_allJets > 350.){
    if ( n >= nMin_ && n <= nMax_ && n < Meffective350.size() ) {
      Meffective350[0]->Fill(ev.CommonHT(), weight);
      Meffective350[n]->Fill(ev.CommonHT(), weight);
    }
  }

  if(Meff_allJets > 375.){
    if ( n >= nMin_ && n <= nMax_ && n < Meffective375.size() ) {
      Meffective375[0]->Fill(ev.CommonHT(), weight);
      Meffective375[n]->Fill(ev.CommonHT(), weight);
    }
  }


  if(Meff_allJets > 400.){
    if ( n >= nMin_ && n <= nMax_ && n < Meffective400.size() ) {
      Meffective400[0]->Fill(ev.CommonHT(), weight);
      Meffective400[n]->Fill(ev.CommonHT(), weight);
    }
  }

  if(Meff_allJets > 425.){
    if ( n >= nMin_ && n <= nMax_ && n < Meffective425.size() ) {
      Meffective425[0]->Fill(ev.CommonHT(), weight);
      Meffective425[n]->Fill(ev.CommonHT(), weight);
    }
  }
  if(Meff_allJets > 450.){
    if ( n >= nMin_ && n <= nMax_ && n < Meffective450.size() ) {
      Meffective450[0]->Fill(ev.CommonHT(), weight);
      Meffective450[n]->Fill(ev.CommonHT(), weight);
    }
  }



  if ( n >= nMin_ && n <= nMax_ && n < Ht.size() ) {
    Ht[0]->Fill(ev.CommonHT(), weight);
    Ht[n]->Fill(ev.CommonHT(), weight);
  }


  if( htAllJets > 200. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht200.size() ) {
      Ht200[0]->Fill(ev.CommonHT(), weight);
      Ht200[n]->Fill(ev.CommonHT(), weight);
    }
  }

  if( htAllJets > 250. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht250.size() ) {
      Ht250[0]->Fill(ev.CommonHT(), weight);
      Ht250[n]->Fill(ev.CommonHT(), weight);
    }
  }

  if( htAllJets > 300. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht300.size() ) {
      Ht300[0]->Fill(ev.CommonHT(), weight);
      Ht300[n]->Fill(ev.CommonHT(), weight);
    }
  }


  if( htAllJets > 150. && ThresholdJets[0].Et() > 50. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht150Jet50.size() ) {
      Ht150Jet50[0]->Fill(ev.CommonHT(), weight);
      Ht150Jet50[n]->Fill(ev.CommonHT(), weight);
    }
  }

  if( htAllJets > 150. && ThresholdJets[1].Et() > 50. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht150SecondJet50.size() ) {
      Ht150SecondJet50[0]->Fill(ev.CommonHT(), weight);
      Ht150SecondJet50[n]->Fill(ev.CommonHT(), weight);
    }
  }


  if( htAllJets > 150. && ThresholdJets[0].Et() > 70. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht150Jet70.size() ) {
      Ht150Jet70[0]->Fill(ev.CommonHT(), weight);
      Ht150Jet70[n]->Fill(ev.CommonHT(), weight);
    }
  }
  if( htAllJets > 150. && ThresholdJets[1].Et() > 70. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht150SecondJet70.size() ) {
      Ht150SecondJet70[0]->Fill(ev.CommonHT(), weight);
      Ht150SecondJet70[n]->Fill(ev.CommonHT(), weight);
    }
  }


  if( htAllJets > 200. && ThresholdJets[0].Et() > 50. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht200Jet50.size() ) {
      Ht200Jet50[0]->Fill(ev.CommonHT(), weight);
      Ht200Jet50[n]->Fill(ev.CommonHT(), weight);
    }
  }

  if( htAllJets > 200. && ThresholdJets[1].Et() > 50. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht200SecondJet50.size() ) {
      Ht200SecondJet50[0]->Fill(ev.CommonHT(), weight);
      Ht200SecondJet50[n]->Fill(ev.CommonHT(), weight);
    }
  }


  if( htAllJets > 200. && ThresholdJets[0].Et() > 70. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht200Jet70.size() ) {
      Ht200Jet70[0]->Fill(ev.CommonHT(), weight);
      Ht200Jet70[n]->Fill(ev.CommonHT(), weight);
    }
  }
  if( htAllJets > 200. && ThresholdJets[1].Et() > 70. ){
    if ( n >= nMin_ && n <= nMax_ && n < Ht200SecondJet70.size() ) {
      Ht200SecondJet70[0]->Fill(ev.CommonHT(), weight);
      Ht200SecondJet70[n]->Fill(ev.CommonHT(), weight);
    }
  }



  if( mhtAllJets.Et() > 50. && ThresholdJets[1].Et() > 50. ){
    if ( n >= nMin_ && n <= nMax_ && n < MHT50SecondJet50.size() ) {
      MHT50SecondJet50[0]->Fill(ev.CommonHT(), weight);
      MHT50SecondJet50[n]->Fill(ev.CommonHT(), weight);
    }
  }

  if( mhtAllJets.Et() > 50. && ThresholdJets[1].Et() > 70. ){
    if ( n >= nMin_ && n <= nMax_ && n < MHT50SecondJet70.size() ) {
      MHT50SecondJet70[0]->Fill(ev.CommonHT(), weight);
      MHT50SecondJet70[n]->Fill(ev.CommonHT(), weight);
    }
  }


  if( mhtAllJets.Et() > 70. && ThresholdJets[1].Et() > 50. ){
    if ( n >= nMin_ && n <= nMax_ && n < MHT70SecondJet50.size() ) {
      MHT70SecondJet50[0]->Fill(ev.CommonHT(), weight);
      MHT70SecondJet50[n]->Fill(ev.CommonHT(), weight);
    }
  }

  if( mhtAllJets.Et() > 70. && ThresholdJets[1].Et() > 70. ){
    if ( n >= nMin_ && n <= nMax_ && n < MHT70SecondJet70.size() ) {
      MHT70SecondJet70[0]->Fill(ev.CommonHT(), weight);
      MHT70SecondJet70[n]->Fill(ev.CommonHT(), weight);
    }
  }



  if( ev.CaloMET().Et() > 50. && ThresholdJets[1].Et() > 50. ){
    if ( n >= nMin_ && n <= nMax_ && n < MET50SecondJet50.size() ) {
      MET50SecondJet50[0]->Fill(ev.CommonHT(), weight);
      MET50SecondJet50[n]->Fill(ev.CommonHT(), weight);
    }
  }

  if( ev.CaloMET().Et() > 50. && ThresholdJets[1].Et() > 70. ){
    if ( n >= nMin_ && n <= nMax_ && n < MET50SecondJet70.size() ) {
      MET50SecondJet70[0]->Fill(ev.CommonHT(), weight);
      MET50SecondJet70[n]->Fill(ev.CommonHT(), weight);
    }
  }


  if( ev.CaloMET().Et() > 70. && ThresholdJets[1].Et() > 50. ){
    if ( n >= nMin_ && n <= nMax_ && n < MET70SecondJet50.size() ) {
      MET70SecondJet50[0]->Fill(ev.CommonHT(), weight);
      MET70SecondJet50[n]->Fill(ev.CommonHT(), weight);
    }
  }

  if( ev.CaloMET().Et() > 70. && ThresholdJets[1].Et() > 70. ){
    if ( n >= nMin_ && n <= nMax_ && n < MET70SecondJet70.size() ) {
      MET70SecondJet70[0]->Fill(ev.CommonHT(), weight);
      MET70SecondJet70[n]->Fill(ev.CommonHT(), weight);
    }
  }





}
