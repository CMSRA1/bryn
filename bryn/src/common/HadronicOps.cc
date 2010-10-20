#include "HadronicOps.hh"
#include "AlphaT.hh"
#include <iostream>
#include <string>
#include <fstream>

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


//
MHTovHT::MHTovHT(float cut)
  : cut_(cut)
{;}

bool MHTovHT::Process(Event::Data& ev){
  if(ev.CommonMHT().Pt()/ev.CommonHT() > cut_)return true;
  else return false;
}

//
std::ostream& MHTovHT::Description( std::ostream &ostrm ) {
  ostrm << " " << cut_ << " " ;
  return ostrm;
}

// -----------------------------------------------------------------------------
//
PFMET::PFMET(float cut)
  : cut_(cut)
{;}

bool PFMET::Process(Event::Data& ev){
  if(ev.PFMET().Pt() > cut_)return true;
  else return false;
}

//
std::ostream& PFMET::Description( std::ostream &ostrm ) {
  ostrm << " " << cut_ << " " ;
  return ostrm;
}

// -----------------------------------------------------------------------------
//
ReversedPFMET::ReversedPFMET(float cut)
  : cut_(cut)
{;}

bool ReversedPFMET::Process(Event::Data& ev){
  if(ev.PFMET().Pt() < cut_)return true;
  else return false;
}

//
std::ostream& ReversedPFMET::Description( std::ostream &ostrm ) {
  ostrm << " " << cut_ << " " ;
  return ostrm;
}
//-------------------------------------------------------------------

BabyMHT::BabyMHT(float cut)
  : cut_(cut)
{;}

bool BabyMHT::Process(Event::Data& ev){
  if( ev.JD_CommonJets().babyHT.Pt() > cut_)return true;
  else return false;
}

//
std::ostream& BabyMHT::Description( std::ostream &ostrm ) {
  ostrm << " " << cut_ << " " ;
  return ostrm;
}

//-------------------------------------------------------------------

ReversedBabyMHT::ReversedBabyMHT(float cut)
  : cut_(cut)
{;}

bool ReversedBabyMHT::Process(Event::Data& ev){
  if( ev.JD_CommonJets().babyHT.Pt() < cut_)return true;
  else return false;
}

//
std::ostream& ReversedBabyMHT::Description( std::ostream &ostrm ) {
  ostrm << " " << cut_ << " " ;
  return ostrm;
}

//-------------------------------------------------------------------

LowPtBiasedDphi::LowPtBiasedDphi(float cut)
  : cut_(cut)
{;}

bool LowPtBiasedDphi::Process(Event::Data& ev){
  if( ev.LowPtBiasedCommonRecoilMETJetDPhi() < cut_)return true;
  else return false;
}

//
std::ostream& LowPtBiasedDphi::Description( std::ostream &ostrm ) {
  ostrm << " " << cut_ << " " ;
  return ostrm;
}


//-------------------------------------------------------------------

BabyMHTovHT::BabyMHTovHT(float cut)
  : cut_(cut)
{;}

bool BabyMHTovHT::Process(Event::Data& ev){
  if( ev.JD_CommonJets().killedHT.Pt()/ev.CommonHT() > cut_)return true;
  else return false;
}

//
std::ostream& BabyMHTovHT::Description( std::ostream &ostrm ) {
  ostrm << " " << cut_ << " " ;
  return ostrm;
}

//---------------------------------------------------------

MHTPFMETDiffOvMeffCut::MHTPFMETDiffOvMeffCut(float cut)
  : cut_(cut)
{;}

bool MHTPFMETDiffOvMeffCut::Process(Event::Data& ev){

  /*
  TLorentzVector hadronicPFMET = ev.PFMET();

 if(ev.PD_CommonPhotons().accepted.size()==1)
   {
     hadronicPFMET = hadronicPFMET+(*(ev.PD_CommonPhotons().accepted[0]));
   }

 if(ev.LD_CommonMuons().accepted.size()==1)
    {
      hadronicPFMET = hadronicPFMET+(*(ev.LD_CommonMuons().accepted[0]));
    }
  */

  if(ev.PD_CommonPhotons().accepted.size()==0&& ev.LD_CommonMuons().accepted.size()==0)
    {
      if((ev.CommonMHT().Pt()-ev.PFMET().Pt())/(ev.CommonMHT().Pt()+ev.CommonHT()) < cut_) return true;
    }

  // if there is a "common" photon in (photon control sample)
  if(ev.PD_CommonPhotons().accepted.size()==1)
   {
     if((ev.CommonMHT().Pt()-(ev.PFMET()+(*(ev.PD_CommonPhotons().accepted[0]))).Pt())/(ev.CommonMHT().Pt()+ev.CommonHT()) < cut_) return true;
    }

  // if there is a "common" muon in (photon control sample)
  if(ev.LD_CommonMuons().accepted.size()==1)
    {
      if((ev.CommonMHT().Pt()-(ev.PFMET()+(*(ev.LD_CommonMuons().accepted[0]))).Pt())/(ev.CommonMHT().Pt()+ev.CommonHT()) < cut_) return true;
    }
  
  return false;

}

std::ostream& MHTPFMETDiffOvMeffCut::Description(std::ostream &ostrm){
  ostrm << " (MHT-PFMET)/Meff < " << cut_ << " " ;
  return ostrm;
}



Double_t DeadECALDR(TString deadECALfile,float jetphi,float jeteta, int nBad){
  // cout << " hi ho " << deadECALfile << endl;
  TLorentzVector testjetVec(0,0,0,0);
  double DRmin = 100;
  testjetVec.SetPtEtaPhiE(100,jeteta,jetphi,100);

  //cout << " in dead ecal " << endl;
  ifstream myfile(deadECALfile);
  if(!myfile.good()) cout << "file is not there " << endl;
  if(myfile.is_open()){

    while(!myfile.eof()){

      float phi,eta;
      int iEta,iPhi,nBadCells;
      myfile>>eta;
      myfile>>phi;
      myfile>>iEta;
      myfile>>iPhi;
      myfile>>nBadCells;
      // cout <<eta<< " "<< phi<<endl;
      if(nBadCells > nBad){
	TLorentzVector testVec(0,0,0,0);
	testVec.SetPtEtaPhiE(100,eta,phi,100);
	float DR = fabs(ROOT::Math::VectorUtil::DeltaR(testVec,testjetVec));
	if(DR < DRmin) DRmin = DR;
      }
    }
   
    myfile.close();
  } 
  return DRmin;

}

DeadECALCut::DeadECALCut(float cut,TString deadECALfile):cut_(cut),deadECALfile_(deadECALfile){;}

bool DeadECALCut::Process(Event::Data& ev) {

 double biasedDPhi = 10;
 // int indexBad =-10; 
  LorentzV gen_p4;
  float deadECALDR = 10;
  
  for( std::vector<Event::Jet const *>::const_iterator i = ev.JD_CommonJets().accepted.begin();
       i != ev.JD_CommonJets().accepted.end();
       ++i ){

    float newBiasDPhi = fabs(ROOT::Math::VectorUtil::DeltaPhi(**i, ev.CommonMHT() + (**i) + ev.JD_CommonJets().babyHT_30_50)) ;
    if(newBiasDPhi < biasedDPhi){
      biasedDPhi = newBiasDPhi;
      deadECALDR = DeadECALDR( deadECALfile_,(*i)->Phi(),(*i)->Eta(),0);
    }
  }
  for( std::vector<Event::Jet const*>::const_iterator iI = ev.JD_CommonJets().baby_30_50.begin(); iI != ev.JD_CommonJets().baby_30_50.end();
	 ++iI) {
    float newBiasDPhi_2 = fabs(ROOT::Math::VectorUtil::DeltaPhi(**iI, ev.CommonMHT() + (**iI) + ev.JD_CommonJets().babyHT_30_50)) ;
    if(newBiasDPhi_2 < biasedDPhi){
      biasedDPhi = newBiasDPhi_2;
      deadECALDR = DeadECALDR( deadECALfile_,(*iI)->Phi(),(*iI)->Eta(),0);
    }
  }


 
 if( biasedDPhi <= ev.LowPtBiasedCommonRecoilMETJetDPhi() && ev.LowPtBiasedCommonRecoilMETJetDPhi() < 0.5){
      
   if(deadECALDR < cut_)return false;
   
  }

  

  return true;


}

// -----------------------------------------------------------------------------
//
std::ostream& DeadECALCut::Description( std::ostream &ostrm ) {
  ostrm << "Dead ECAL cut " << cut_ << " " ;
  return ostrm;
}
// -----------------------------------------------------------------------------



UnCorrCut::UnCorrCut( float cut )
  : cut_(cut)
  {;}


bool UnCorrCut::Process( Event::Data& ev ) {


    int leadUnCorjet = -1;
    double LeadUnCorEn = 0.;
    for(unsigned int i = 0; i < ev.JD_CommonJets().accepted.size() && ev.JD_CommonJets().accepted[i]->GetIndex() >= 0; i++){

      if ( (ev.JD_CommonJets().accepted[i]->Pt()/ev.GetJetCorrFactor(ev.JD_CommonJets().accepted[i]->GetIndex())) > LeadUnCorEn){ // loop though all jets and calculate uncor energy, compare to some tmp value, if larger than tmp value set tmp value to uncor enegy
        LeadUnCorEn = ev.JD_CommonJets().accepted[i]->Pt()/ev.GetJetCorrFactor(ev.JD_CommonJets().accepted[i]->GetIndex());
        leadUnCorjet = i; // set the index of the leading uncor jet

      }
    }

    if( LeadUnCorEn > cut_ ) { return true; } // check the leading uncor jet has cor Pt > cut
    else{return false;}


  }

// -----------------------------------------------------------------------------
//
  std::ostream& UnCorrCut::Description( std::ostream &ostrm ) {
    ostrm << "Leading uncorrected jet has PT > " << cut_ << " " ;
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
