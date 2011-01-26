#ifndef bryn_include_Ops_hh
#define bryn_include_Ops_hh

#include "EventData.hh"
#include "Math/VectorUtil.h"
#include "Operation.hh"
#include "TH1F.h"

namespace Operation {
  class AlphatTriggerCut : public Operation::_Base {
  public:
    AlphatTriggerCut( float ,float,float);
    ~AlphatTriggerCut() {;}
    bool Process( Event::Data& );
    std::ostream& Description( std::ostream& );
  private:
    float cut_;
    float setScale_;
    float mhtScale_;
  };

}

#endif // bryn_include_Ops_hh
