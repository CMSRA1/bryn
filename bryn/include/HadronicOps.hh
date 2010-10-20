#ifndef hadronic_include_HadronicOps_hh
#define hadronic_include_HadronicOps_hh

#include "EventData.hh"
#include "Math/VectorUtil.h"
#include "Operation.hh"
#include "TH1F.h"

namespace Operation {

  class HadronicAlphaT : public Operation::_Base {
  public:
    HadronicAlphaT( float );
    ~HadronicAlphaT() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
  };


  class UnCorrCut : public Operation::_Base {
  public:
    UnCorrCut( float );
    ~UnCorrCut() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
  };

  class DeadECALCut : public Operation::_Base {
  public:
    DeadECALCut( float,TString );
    ~DeadECALCut() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
    TString deadECALfile_;
   };


  class MHTPFMETDiffOvMeffCut: public Operation::_Base{
  public:
    MHTPFMETDiffOvMeffCut( float );
    ~MHTPFMETDiffOvMeffCut() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;

  };

  class ReversedPFMET : public Operation::_Base {
  public:
    ReversedPFMET( float );
    ~ReversedPFMET() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
   };

  class PFMET : public Operation::_Base {
  public:
    PFMET( float );
    ~PFMET() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
   };

  class BabyMHT : public Operation::_Base {
  public:
    BabyMHT( float );
    ~BabyMHT() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
   };

  class ReversedBabyMHT : public Operation::_Base {
  public:
    ReversedBabyMHT( float );
    ~ReversedBabyMHT() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
   };
  
   class BabyMHTovHT : public Operation::_Base {
  public:
    BabyMHTovHT( float );
    ~BabyMHTovHT() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
   };


  class MHTovHT : public Operation::_Base {
  public:
    MHTovHT( float );
    ~MHTovHT() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
   };

  class LowPtBiasedDphi : public Operation::_Base {
  public:
    LowPtBiasedDphi( float );
    ~LowPtBiasedDphi() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
   };
  




  class HadronicCut : public Operation::_Base {
  public:
    HadronicCut( float );
    ~HadronicCut() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
  };

}

#endif // hadronic_include_HadronicOps_hh





