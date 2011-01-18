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
  for(int i = 0; i <  ev.JD_Jets().size(); i++){
    if(ev.JD_Jets()[i].Et() > setScale_){
      nJets++;
    }
  }
  if( nJets == 2){
    double   HT = ev.JD_Jets()[0].Et() + ev.JD_Jets()[1].Et();
    double  MHT = fabs((ev.JD_Jets()[0] + ev.JD_Jets()[1]).Et());
    double  DHT = ev.JD_Jets()[0].Et() - ev.JD_Jets()[1].Et();
    if((HT-DHT)/2.*sqrt(HT*HT - (MHT*MHT)) > cut_ ){ return true;}
    else return false;
  }
  if( nJets > 2){
    double  HT =0.;
    LorentzV  MHT(0.,0.,0.,0.);
    for(int j = 0; j < nJets; j++){
      HT += ev.JD_Jets()[j].Et();
      MHT -= ev.JD_Jets()[j];
    }
    if(fabs(MHT.Et())/HT > sqrt(1 - 1/(4*cut_*cut_))){return true;}
    else return false;
  }
  return false;
}

std::ostream& AlphatTriggerCut::Description( std::ostream &ostrm ) {
  ostrm << "AlphatTriggerCut " << cut_ << " " << " Jet Scale: " <<setScale_ ;
  return ostrm;
}
