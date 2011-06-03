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
#include "Photon.hh"
#include "Jet.hh"
#include "Lepton.hh"
#include "Math/VectorUtil.h"
#include "JetData.hh"
#include "TMath.h"

using namespace Operation;

eventDump::eventDump() {}

eventDump::~eventDump(){}


bool eventDump::Process(Event::Data & ev){

  std::stringstream jets;

  LorentzV test(0,0,0,0);
  for (std::vector<Event::Jet const *>::const_iterator iph = JD_CommonJets().accepted.begin();
  iph != JD_CommonJets().accepted.end();
  ++iph) {
    std::stringstream jet;

    jet << "Pt: " << (*iph)->Pt()
      << " Phi: "<<  (*iph)->Phi()
      << " Eta: "<<  (*iph)->Eta()
      <<" was cc: "<< (*iph)->WasItcc()
      <<" fem: "<< (*iph)->GetEmFrac()
      << endl;
    test+=(**iph);
    jets+=jet;
  }
  std::stringstream MHT;

  MHT << "MHT Pt: " << test.Pt() <<" phi " << (-test).Phi() << " "<< CommonRecoilMET().Pt() << endl;

  std::stringstream muons;
  for (std::vector<Event::Lepton const *>::const_iterator iph = LD_CommonMuons().accepted.begin();
  iph != LD_CommonMuons().accepted.end();
  ++iph) {
    std::stringstream muon;
    muon << "Pt: " << (*iph)->Pt()
      << " Phi: " << (*iph)->Phi()
      << " Eta: " << (*iph)->Eta()
      << " was cc: " << (*iph)->WasItcc()
      << endl;
    muons+=muon;
  }
  std::stringstream electrons;

  for (std::vector<Event::Lepton const *>::const_iterator iph = LD_CommonElectrons().accepted.begin();
  iph != LD_CommonElectrons().accepted.end();
  ++iph) {
    std::stringstream electron;
    electron << "Pt: " << (*iph)->Pt()
      << " Phi: " << (*iph)->Phi()
      << " Eta: " << (*iph)->Eta()
      << " was cc: " << (*iph)->WasItcc()
      << endl;
    electrons+=electron;
  }

  std::stringstream photons;

  for (std::vector<Event::Photon const *>::const_iterator iph = PD_CommonPhotons().accepted.begin();
  iph != PD_CommonPhotons().accepted.end();
  ++iph) {
    std::stringstream photon;
    photon << "Pt: " << (*iph)->Pt()
      << " Phi: " <<  (*iph)->Phi()
      << " Eta: " <<  (*iph)->Eta()
      << " was cc " << (*iph)->WasItcc()<<endl;
    photons+=photon;
  }

    // JJ - bug here - referenced taus not commontaus
  std::stringstream taus;

  for (std::vector<Event::Lepton const *>::const_iterator iph = LD_CommonTaus().accepted.begin();
  iph != LD_CommonTaus().accepted.end();
  ++iph) {
    std::stringstream tau;
    tau << "Pt: " << (*iph)->Pt()
      << " Phi: "<< (*iph)->Phi()
      << " Eta: "<< (*iph)->Eta()<<endl;
    taus += tau;
  }




  std::stringstream ss;
  ss << " --------------------------------------------------------" << std::endl
    << "[eventDump::eventDump]" << std::endl
    << " Info for " << ev.RunNumber() << ":"<< ev.LumiSection() << ":"<<  ev.EventNumber() << std::endl
    << " --------------------------------------------------------" << std::endl
    << " | HT =" << std::setw(4) << std::setprecision(3) << ev.CommonHT() << std::endl
    << " | MHT =" << std::setw(4) << std::setprecision(3) << ev.CommonMHT().Pt() << std::endl
    << " | AlphaT (com) " << std::setw(4) << std::setprecision(5) << ev.CommonAlphaT() << std::endl
    << " | AlphaT (had) " << std::setw(4) << std::setprecision(5) << ev.HadronicAlphaT() << std::endl
    << " --------------------------------------------------------" << std::endl;
  evInfo_ += ss.str();
  evInfo_ += jets.str();
  evInfo_ += MHT.str();
  evInfo_+= electrons.str();
  evInfo_+= muons.str();
  return true;
}


void eventDump::End(Event::Data & ev){
  std::string name = static_cast<std::string> ( ev.OutputFile()->GetName() ); // need to convert TString to string
  name.erase(name.size()-5, 5);
  name.append("_eventDumpInfo");
  name.append(".txt");
  ofstream file;
  file.open(name.c_str(), ios::out);
  file << evInfo_;

  file.close();
}
std::ostream& eventDump::Description( std::ostream &ostrm ) {
  ostrm << "Dumped event info " << " ";
  return ostrm;
}


