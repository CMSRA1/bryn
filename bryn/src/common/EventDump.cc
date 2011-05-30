//
//  EventDump.cc
//
//  Created by Bryn Mathias on 2011-05-30.
//

#import "EventDump.hh"
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

eventDump::eventDump() {}

eventDump::~eventDump(){}


eventDump::Process(Event::Data & ev){
    std::stringstream ss;
    ss << " --------------------------------------------------------" << std::endl
       << "[eventDump::eventDump]" << std::endl
       << " Info for this event is: " << std::endl
       << " --------------------------------------------------------" << std::endl
       << " | HT = " << std::setw(4) << std::setprecision(3) << ev.CommonHT() << std::endl
       << " | MHT" << std::setw(4) << std::setprecision(3) << ev.CommonMHT().Pt() << std::endl
       << " | AlphaT (common) " << std::setw(4) << std::setprecision(5) << ev.CommonAlphaT() << std::endl
       << " | AlphaT (hadronic) " << std::setw(4) << std::setprecision(5) << ev.HadAlphaT() << std::endl
       << " | run:lumi:ev " << ev.RunNumber() << ":"<< ev.LumiSection() << ":"<<  ev.EventNumber() << std::endl
       << " --------------------------------------------------------" << std::endl;
      evInfo_ = ss.str();
  return true;
}


void eventDump::End(Event::Data & ev){
  std::string name = static_cast<std::string> ( ev.OutputFile()->GetName() ); // need to convert TString to string
  name.erase(name.size()-5, 5);
  name.append("_eventDumpInfo");
  name.append(".txt");
  ofstream file;
  file.open(name.c_str(), ios::out);
  file << evInfo_.Print();
  file.close();
}