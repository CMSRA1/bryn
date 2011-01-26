#include <boost/python.hpp>
#include "WeeklyUpdatePlots.hh"
#include "Trigger.hh"
#include "Ops.hh"
using namespace boost::python;

BOOST_PYTHON_MODULE(libbryn) {

  class_<Operation::WeeklyUpdatePlots, bases<Operation::_Base> >( "WeeklyUpdatePlots",
                    init<const Utils::ParameterSet&>());


  class_<Operation::AlphatTriggerCut, bases<Operation::_Base> >( "AlphatTriggerCut",  init<float,float,float>() );

  class_<Operation::Trigger, bases<Operation::_Base> >( "PL_TriggerPlots",
                    init<const Utils::ParameterSet&>());

}
