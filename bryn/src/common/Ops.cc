#include "Ops.hh"
#include "AlphaT.hh"
#include <iostream>
#include <string>
#include <fstream>

#include "Types.hh"

using namespace Operation;

// ----------------------------------------------------------------
AlphatTriggerCut::AlphatTriggerCut( float cut, float setScale )
  : cut_(cut),
    setScale_(setScale)
    {;}
// ----------------------------------------------------------------
bool AlphatTriggerCut::Process( Event::Data& ev){
  int nJets = 0;
  for(unsigned int i = 0; i <  ev.JD_Jets().size(); i++){
    if(ev.JD_Jets()[i].Et() > setScale_){
      nJets++;
    }
  }
  if( nJets == 2){
    double   HT = ev.JD_Jets()[0].Et() + ev.JD_Jets()[1].Et();
    LorentzV  MHTv(0.,0.,0.,0.);
    for(int i = 0 ; i < 2; i++){
      MHTv -= ev.JD_Jets()[i];
    }
    double  MHT = fabs(MHTv.Et());
    double  DHT = fabs(ev.JD_Jets()[0].Et() - ev.JD_Jets()[1].Et());
      cout <<"This event has on the fly alphaT of: " << (HT-DHT)/(2.*sqrt(HT*HT - (MHT*MHT)))  << " and alphaT of " << ev.CommonAlphaT() << endl;
    if((HT-DHT)/(2.*sqrt(HT*HT - (MHT*MHT))) > cut_ ){
      // cout <<"This event has on the fly alphaT of: " << (HT-DHT)/(2.*sqrt(HT*HT - (MHT*MHT)))  << " and alphaT of " << ev.CommonAlphaT() << endl;
      return true;}
    else return false;
  }
  if( nJets > 2){
    double  HT =0.;
    LorentzV  MHT(0.,0.,0.,0.);
    for(int j = 0; j < ev.JD_Jets().size(); j++){
      if(ev.JD_Jets()[j].Et() >= setScale_){ HT += ev.JD_Jets()[j].Et();}
      if(ev.JD_Jets()[j].Et() >= 20.){MHT -= ev.JD_Jets()[j];}
    }
      cout <<"This event has on the fly MHT/HT of: " << fabs(MHT.Et())/HT << " Event MHT/HT of: " << fabs(ev.CommonMHT().Et())/ev.CommonHT() <<" and alphaT of " << ev.CommonAlphaT() << endl;
    if(fabs(MHT.Et())/HT > sqrt(1. - 1./(4.*cut_*cut_))){
      // cout <<"This event has MHT/HT of: " << fabs(MHT.Et())/HT << " and alphaT of " << ev.CommonAlphaT() << endl;
      return true;}
    else return false;
  }
  return false;
}

std::ostream& AlphatTriggerCut::Description( std::ostream &ostrm ) {
  ostrm << "AlphatTriggerCut " << cut_ << " " << " Jet Scale: " <<setScale_ ;
  return ostrm;
}
