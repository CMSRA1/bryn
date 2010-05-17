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





