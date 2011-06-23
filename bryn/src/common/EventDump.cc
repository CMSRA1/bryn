//
//  EventDump.cc
//
//  Created by Bryn Mathias on 2011-05-30.
//

#import "EventDump.hh"
#include "Trigger.hh"
#include "CommonOps.hh"
#include "JetData.hh"
#include "Compute_Helpers.hh"
#include "LeptonData.hh"
#include "PhotonData.hh"
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

  std::string jets;
  jets = "Jets \n";

  LorentzV test(0,0,0,0);
  double itHT = 0.;
  int nj = 0;
  double dht = 0.;
  double aT = 0.;
  double mhtx = 0.;
  double mhty = 0.;

  for (std::vector<Event::Jet const *>::const_iterator iph = ev.JD_CommonJets().accepted.begin();
  iph != ev.JD_CommonJets().accepted.end();
  ++iph) {
          mhtx -= (*iph)->Et()*cos((*iph)->Phi());
          mhty -= (*iph)->Et()*sin((*iph)->Phi());
          double mHT = sqrt(mhtx*mhtx + mhty*mhty);
        nj++;
        dht += ( nj < 2 ? (*iph)->Et() : -1.* (*iph)->Et() ); //@@ only use for njets < 4
        if ( nj == 2 || nj == 3 ) {
          aT = ( itHT - fabs(dht) ) / ( 2. * sqrt( ( itHT*itHT ) - ( mHT*mHT  ) ) );
        } else if ( nj > 3 ) {
          aT = itHT / ( 2.*sqrt( ( itHT*itHT ) - ( mHT*mHT  ) ) );
        }
    std::stringstream jet;
    itHT += (*iph)->Et();
    test+=(**iph);
    jet << "Pt: " << std::setw(4) << std::setprecision(6) << (*iph)->Pt()
      << " Phi: "<< std::setw(4) << std::setprecision(6) <<  (*iph)->Phi()
      << " Eta: "<< std::setw(4) << std::setprecision(6) <<  (*iph)->Eta()
      <<" fem: "<< std::setw(4) << std::setprecision(6) << (*iph)->GetEmFrac()
      << " Itterative HT " << std::setw(4) << std::setprecision(6) << itHT
      << " Itterative MHT " << std::setw(4) << std::setprecision(6) << test.Pt()
      << " Itterative MHT (from Et projection) " << std::setw(4) << std::setprecision(6) << mHT
      << " DeltaHT " << std::setw(4) << std::setprecision(6) << dht
      << " Trigger emu alphaT " << std::setw(4) << std::setprecision(6) << aT
      << endl;

    jets+=jet.str();
  }
 for (std::vector<Event::Jet const *>::const_iterator iph = ev.JD_CommonJets().baby.begin();
  iph != ev.JD_CommonJets().baby.end();
  ++iph) {
    std::stringstream jet;
    itHT += (*iph)->Et();
    nj++;
    test+=(**iph);
     mhtx -= (*iph)->Et()*cos((*iph)->Phi());
     mhty -= (*iph)->Et()*sin((*iph)->Phi());
      double mHT = sqrt(mhtx*mhtx + mhty*mhty);
        nj++;
        dht += ( nj < 2 ? (*iph)->Et() : -1.* (*iph)->Et() ); //@@ only use for njets < 4
        if ( nj == 2 || nj == 3 ) {
          aT = ( itHT - fabs(dht) ) / ( 2. * sqrt( ( itHT*itHT ) - ( mHT*mHT  ) ) );
        } else if ( nj > 3 ) {
          aT = itHT / ( 2.*sqrt( ( itHT*itHT ) - ( mHT*mHT  ) ) );
        }
    jet << "Pt: " << std::setw(4) << std::setprecision(6) << (*iph)->Pt()
      << " Et: " << std::setw(4) << std::setprecision(6) << (*iph)->Et()
      << " Phi: "<< std::setw(4) << std::setprecision(6) <<  (*iph)->Phi()
      << " Eta: "<< std::setw(4) << std::setprecision(6) <<  (*iph)->Eta()
      << " fem: "<< std::setw(4) << std::setprecision(6) << (*iph)->GetEmFrac()
      << " Itterative HT " << std::setw(4) << std::setprecision(6) << itHT
      << " Itterative MHT " << std::setw(4) << std::setprecision(6) << test.Pt()
      << " Itterative MHT (from Et projection) " << std::setw(4) << std::setprecision(6) << mHT
      << " DeltaHT " << std::setw(4) << std::setprecision(6) << dht
      << " Trigger emu alphaT " << std::setw(4) << std::setprecision(6) << aT
      << endl;



    jets+=jet.str();
}
  std::stringstream MHT;

  MHT << "MHT Pt: " << test.Pt() <<" phi " << (-test).Phi() << " "<< ev.CommonRecoilMET().Pt() << endl;

  std::string muons;
  muons = " Muons \n";
  for (std::vector<Event::Lepton const *>::const_iterator iph = ev.LD_CommonMuons().accepted.begin();
  iph != ev.LD_CommonMuons().accepted.end();
  ++iph) {
    std::stringstream muon;
    muon << "Pt: " << std::setw(4) << std::setprecision(6) << (*iph)->Pt()
      << " Phi: " << std::setw(4) << std::setprecision(6) << (*iph)->Phi()
      << " Eta: " << std::setw(4) << std::setprecision(6) << (*iph)->Eta()
      << endl;
    muons+=muon.str();
  }
  std::string electrons;
  electrons = " Electrons \n";
  for (std::vector<Event::Lepton const *>::const_iterator iph = ev.LD_CommonElectrons().accepted.begin();
  iph != ev.LD_CommonElectrons().accepted.end();
  ++iph) {
    std::stringstream electron;
    electron << "Pt: " << std::setw(4) << std::setprecision(6) << (*iph)->Pt()
      << " Phi: " << std::setw(4) << std::setprecision(6) << (*iph)->Phi()
      << " Eta: " << std::setw(4) << std::setprecision(6) << (*iph)->Eta()
      << endl;
    electrons+=electron.str();
  }

  std::string photons;
  photons = "Photons \n";
  for (std::vector<Event::Photon const *>::const_iterator iph = ev.PD_CommonPhotons().accepted.begin();
  iph != ev.PD_CommonPhotons().accepted.end();
  ++iph) {
    std::stringstream photon;
    photon << "Pt: " << std::setw(4) << std::setprecision(6) << (*iph)->Pt()
      << " Phi: " << std::setw(4) << std::setprecision(6) <<  (*iph)->Phi()
      << " Eta: " << std::setw(4) << std::setprecision(6) <<  (*iph)->Eta()
      << endl;
    photons+=photon.str();
  }

    // JJ - bug here - referenced taus not commontaus
  std::string taus;
  taus = "Taus \n";
  for (std::vector<Event::Lepton const *>::const_iterator iph = ev.LD_CommonTaus().accepted.begin();
  iph != ev.LD_CommonTaus().accepted.end();
  ++iph) {
    std::stringstream tau;
    tau << "Pt: " << std::setw(4) << std::setprecision(6) << (*iph)->Pt()
      << " Phi: " << std::setw(4) << std::setprecision(6) << (*iph)->Phi()
      << " Eta: " << std::setw(4) << std::setprecision(6) << (*iph)->Eta()
      <<endl;
    taus += tau.str();
  }

  std::string jetsNcc;
  jetsNcc = "Jets \n";
  nj = 0;
  aT = 0.;
  dht = 0.;
  itHT = 0.;
  LorentzV testNcc(0,0,0,0);
      for (std::vector<Event::Jet>::const_iterator iph = ev.JD_Jets().begin();
     iph != ev.JD_Jets().end();
     ++iph) {
      std::stringstream jetNcc;
         itHT += iph->Et();
    nj++;
      if( iph->Pt()>30) { testNcc+=(*iph); }
     mhtx -= iph->Et()*cos(iph->Phi());
     mhty -= iph->Et()*sin(iph->Phi());
      double mHT = sqrt(mhtx*mhtx + mhty*mhty);
        nj++;
        dht += ( nj < 2 ? iph->Et() : -1.* iph->Et() ); //@@ only use for njets < 4
        if ( nj == 2 || nj == 3 ) {
          aT = ( itHT - fabs(dht) ) / ( 2. * sqrt( ( itHT*itHT ) - ( mHT*mHT  ) ) );
        } else if ( nj > 3 ) {
          aT = itHT / ( 2.*sqrt( ( itHT*itHT ) - ( mHT*mHT  ) ) );
        }
    jetNcc << "Pt: " << std::setw(4) << std::setprecision(6) << iph->Pt()
      << " Et: " << std::setw(4) << std::setprecision(6) << iph->Et()
      << " Phi: "<< std::setw(4) << std::setprecision(6) << iph->Phi()
      << " Eta: "<< std::setw(4) << std::setprecision(6) << iph->Eta()
      << " fem: "<< std::setw(4) << std::setprecision(6) << iph->GetEmFrac()
      << " Itterative HT " << std::setw(4) << std::setprecision(6) << itHT
      << " Itterative MHT " << std::setw(4) << std::setprecision(6) << testNcc.Pt()
      << " Itterative MHT (from Et projection) " << std::setw(4) << std::setprecision(6) << mHT
      << " DeltaHT " << std::setw(4) << std::setprecision(6) << dht
      << " Trigger emu alphaT " << std::setw(4) << std::setprecision(6) << aT
      << endl;

      jetsNcc+=jetNcc.str();
  }
  std::stringstream MHTNcc;

  MHTNcc << "MHT Pt: " << testNcc.Pt() <<" phi " << (-testNcc).Phi() << " "<< ev.RecoilMET().Pt() << endl;

  std::string muonsNcc;
  muonsNcc = " Muons \n";
    for (std::vector<Event::Lepton>::const_iterator iph = ev.LD_Muons().begin(); iph != ev.LD_Muons().end(); ++iph) {
    std::stringstream muonNcc;
      muonNcc << "Pt: " << std::setw(4) << std::setprecision(6) << iph->Pt()<< " Phi: "<< std::setw(4) << std::setprecision(6) <<  iph->Phi()<< " Eta: "<< std::setw(4) << std::setprecision(6) <<  iph->Eta()<<" was cc "<<endl;
    muonsNcc+=muonNcc.str();
  }
  std::string electronsNcc;
  electronsNcc = " Electrons : \n";
  for (std::vector<Event::Lepton>::const_iterator iph = ev.LD_Electrons().begin(); iph != ev.LD_Electrons().end(); ++iph) {
    std::stringstream electronNcc;
    electronNcc << "Pt: " << std::setw(4) << std::setprecision(6) << iph->Pt()<< " Phi: " << std::setw(4) << std::setprecision(6) <<  iph->Phi()<< " Eta: " << std::setw(4) << std::setprecision(6) <<  iph->Eta()<<endl;
    electronsNcc+=electronNcc.str();
  }

  std::string photonsNcc;
  photonsNcc = "Photons : \n";
   for (std::vector<Event::Photon>::const_iterator iph = ev.PD_Photons().begin();
     iph != ev.PD_Photons().end();
     ++iph) {
    std::stringstream photonNcc;
    photonNcc << "Pt: " << std::setw(4) << std::setprecision(6) << iph->Pt()<< " Phi: " << std::setw(4) << std::setprecision(6) <<  iph->Phi()<< " Eta: " << std::setw(4) << std::setprecision(6) <<  iph->Eta()<< endl;
    photonsNcc+=photonNcc.str();
  }

    // JJ - bug here - referenced taus not taus
  std::string tausNcc;
  tausNcc = "Taus : \n";
     for (std::vector<Event::Lepton>::const_iterator iph = ev.LD_Taus().begin();
     iph != ev.LD_Taus().end();
     ++iph) {
      std::stringstream tauNcc;
      tauNcc << "Pt: " << std::setw(4) << std::setprecision(6) << iph->Pt() << " Phi: " << std::setw(4) << std::setprecision(6) << iph->Phi() << " Eta: " << std::setw(4) << std::setprecision(6) << iph->Eta() << endl;
    tausNcc += tauNcc.str();
  }


  std::stringstream ss;
 ss << " --------------------------------------------------------" << std::endl
    << "[eventDump::eventDump]" << std::endl
    << " Info for " << ev.RunNumber() << ":"<< ev.LumiSection() << ":"<<  ev.EventNumber() << std::endl
    << " --------------------------------------------------------" << std::endl
    << " | HT = " << std::setw(4) << std::setprecision(6) << ev.CommonHT() << std::endl
    << " | MHT = " << std::setw(4) << std::setprecision(6) << ev.CommonMHT().Pt() << std::endl
    << " | Meff = " << std::setw(4) << std::setprecision(6) << ev.CommonHT()+ev.CommonMHT().Pt() << std::endl
    << " | AlphaT (com) " << std::setw(4) << std::setprecision(5) << ev.CommonAlphaT() << std::endl
    << " | AlphaT (had) " << std::setw(4) << std::setprecision(5) << ev.HadronicAlphaT() << std::endl
    << " | HBHe Noise Result (had) " << std::setw(4) << (ev.GethbheNoiseFilterResult() ? "Passed" : "Failed") << std::endl
    << " --------------------------------------------------------" << std::endl;
  evInfo_ += ss.str();
  evInfo_ += "CrossCleaned Objects:";
  evInfo_ += jets;
  evInfo_ += MHT.str();
  evInfo_ += photons;
  evInfo_ += electrons;
  evInfo_ += muons;
  evInfo_ += "Not Cross Cleaned Objects";
  evInfo_ += jetsNcc;
  evInfo_ += MHTNcc.str();
  evInfo_ += electronsNcc;
  evInfo_ += photonsNcc;
  evInfo_ += muonsNcc;
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


