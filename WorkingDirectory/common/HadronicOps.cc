#include "HadronicOps.hh"
#include "AlphaT.hh"
#include <iostream>
#include <string>

#include "Types.hh"

using namespace Operation;

// -----------------------------------------------------------------------------
//
HadronicAlphaT::HadronicAlphaT( float cut )
  : cut_(cut)
{;}

// -----------------------------------------------------------------------------
//
bool HadronicAlphaT::Process( Event::Data& ev ) {
  if ( ev.CommonObjects().size() < 2 ||
       ev.CommonObjects().size() > 50 ) { return false; }
  if ( AlphaT()( ev.CommonObjects() ) > cut_ ) { return true; }
  return false;
}

// -----------------------------------------------------------------------------
//
std::ostream& HadronicAlphaT::Description( std::ostream &ostrm ) {
  ostrm << "HadronicAlphaT " << cut_ << " " ;
  return ostrm;
}

// -----------------------------------------------------------------------------
//
HadronicCut::HadronicCut( float cut )
  : cut_(cut)
{;}

// -----------------------------------------------------------------------------
//
bool HadronicCut::Process( Event::Data& ev ) {

  double cut = 0.;

  if (1) {

  UInt_t n = ev.CommonObjects().size();
  LorentzV mht = ev.CommonRecoilMET();

  std::vector<bool> pseudo;
  AlphaT()( ev.CommonObjects(), pseudo, false );
  if ( pseudo.size() != ev.CommonObjects().size() ) { abort(); }

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

//     double rho_a = lv2.Pt() / ( lv1.Pt() + lv2.Pt() + mht.Pt() );
//     double rho_b = lv1.Pt() / ( lv1.Pt() + lv2.Pt() + mht.Pt() );

    double m_jj  = ( lv1 + lv2 ).M();
//     double m2_jj  = ( lv1 + lv2 ).M2();
//     double mt_jj  = ( lv1 + lv2 ).Mt();
//     double mt2_jj  = ( lv1 + lv2 ).Mt2();

//     double mt_j1_mht = ( lv1 + mht ).Mt();
//     double mt2_j1_mht = ( lv1 + mht ).Mt2();

//     double mt_j2_mht = ( lv2 + mht ).Mt();
//     double mt2_j2_mht = ( lv2 + mht ).Mt2();

    cut = m_jj;
  }

  return cut < cut_;

}

// -----------------------------------------------------------------------------
//
std::ostream& HadronicCut::Description( std::ostream &ostrm ) {
  ostrm << "HadronicCut " << cut_ << " " ;
  return ostrm;
}
