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
  double MHTx = 0.;
  double MHTy = 0.;
  for(unsigned int i = 0; i <  ev.JD_Jets().size(); i++){
    if(ev.JD_Jets()[i].Pt() > setScale_){
      nJets++;
    }
  }
  if( nJets == 2){
    double   HT = ev.JD_Jets()[0].Et() + ev.JD_Jets()[1].Et();
    for(int i = 0 ; i < 2; i++){
      if(ev.JD_Jets()[i].Pt() > 30.){
        MHTx-=ev.JD_Jets()[i].Et()*cos(ev.JD_Jets()[i].Phi());
        MHTy-=ev.JD_Jets()[i].Et()*sin(ev.JD_Jets()[i].Phi());
      }
    }
    double  MHT = sqrt(MHTx*MHTx + MHTy*MHTy);
    double  DHT = fabs(ev.JD_Jets()[0].Et() - ev.JD_Jets()[1].Et());
    // cout <<"This event has on the fly alphaT of: " << (HT-DHT)/(2.*sqrt(HT*HT - (MHT*MHT)))  << " HT is: " << HT << " Delta HT is: " << DHT << " MHT is: " << MHT <<" and alphaT of " << ev.CommonAlphaT() << endl;
    if((HT-DHT)/(2.*sqrt((HT*HT) - (MHT*MHT))) > cut_ ){

      return true;}
      else{
      cout <<"This event has on the fly alphaT of: " << (HT-DHT)/(2.*sqrt(HT*HT - (MHT*MHT)))  << " and alphaT of " << ev.CommonAlphaT() << endl;
      cout << "The number of Jets in common jets is:" << ev.JD_CommonJets().accepted.size() << " Number of jets is " << nJets << endl;
      return false;}
    }
    if( nJets > 2){
      double  HT =0.;
      for(int j = 0; j < ev.JD_Jets().size(); j++){
        if(ev.JD_Jets()[j].Pt() >= setScale_){HT += ev.JD_Jets()[j].Et();}
        if(ev.JD_Jets()[j].Pt() >= 30.){
          MHTx-=ev.JD_Jets()[j].Et()*cos(ev.JD_Jets()[j].Phi());
          MHTy-=ev.JD_Jets()[j].Et()*sin(ev.JD_Jets()[j].Phi());
        }
      }
      double  MHT = sqrt(MHTx*MHTx + MHTy*MHTy);
      // cout <<"This event has on the fly MHT/HT of: " << fabs(MHT)/HT << " Event MHT/HT of: " << fabs(ev.CommonMHT().Et())/ev.CommonHT() <<" and alphaT of " << ev.CommonAlphaT() << endl;
      if(fabs(MHT)/HT > sqrt(1. - 1./(4.*cut_*cut_))){
        // cout <<"This event has MHT/HT of: " << MHT/HT << " and alphaT of " << ev.CommonAlphaT() << endl;
        return true;
        }
        else{
        cout <<"This event has MHT/HT of: " << MHT/HT << " and MHT of " << fabs(ev.CommonMHT().Pt())/ev.CommonHT() << endl;
        cout << "The number of Jets in common jets is:" << ev.JD_CommonJets().accepted.size() << " Number of jets is " << nJets << endl;
      return false;}
      }
      return false;
    }

    std::ostream& AlphatTriggerCut::Description( std::ostream &ostrm ) {
      ostrm << "AlphatTriggerCut " << cut_ << " " << " Jet Scale: " <<setScale_ ;
      return ostrm;
    }
