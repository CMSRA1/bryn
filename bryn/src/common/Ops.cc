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
    if(ev.JD_Jets()[i].Pt() > setScale_){
      nJets++;
    }
  }
  if( nJets == 2){
    double   HT = ev.JD_Jets()[0].Et() + ev.JD_Jets()[1].Et();
    double  MHT = fabs((ev.JD_Jets()[0] + ev.JD_Jets()[1]).Et());
    double  DHT = ev.JD_Jets()[0].Et() - ev.JD_Jets()[1].Et();
    if( ((HT-DHT)/(2.*sqrt(HT*HT - (MHT*MHT)))) > ev.CommonAlphaT() ){cout << "Something went wrong here! Common alphaT is: " << ev.CommonAlphaT() << " on the fly alphaT is " <<  (HT-DHT)/(2.*sqrt(HT*HT - (MHT*MHT))) << endl;}
    if((HT-DHT)/(2.*sqrt(HT*HT - (MHT*MHT))) > cut_ ){
      cout <<"This event has on the fly alphaT of: " << (HT-DHT)/(2.*sqrt(HT*HT - (MHT*MHT)))  << " and alphaT of " << ev.CommonAlphaT() << endl;
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
    if(fabs(MHT.Et())/HT > fabs(ev.CommonMHT().Et())/ev.CommonHT() ) {cout << "Something went wrong here! Common alphaT is: " << ev.CommonAlphaT() << " on the fly MHT/HT is " <<  fabs(MHT.Et())/HT << " event MHT/HT is "<< fabs(ev.CommonMHT().Et())/ev.CommonHT() << endl;}
    if(fabs(MHT.Et())/HT > sqrt(1 - 1/(4*cut_*cut_))){
      cout <<"This event has MHT/HT of: " << fabs(MHT.Et())/HT << " and alphaT of " << ev.CommonAlphaT() << endl;
      return true;}
    else return false;
  }
  return false;
}

std::ostream& AlphatTriggerCut::Description( std::ostream &ostrm ) {
  ostrm << "AlphatTriggerCut " << cut_ << " " << " Jet Scale: " <<setScale_ ;
  return ostrm;
}
