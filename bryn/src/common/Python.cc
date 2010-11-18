#include <boost/python.hpp>
#include "WeeklyUpdatePlots.hh"
#include "Trigger.hh"

using namespace boost::python;

BOOST_PYTHON_MODULE(libbryn) {

  class_<Operation::WeeklyUpdatePlots, bases<Operation::_Base> >( "WeeklyUpdatePlots",
                    init<const Utils::ParameterSet&>());


  class_<Operation::Trigger, bases<Operation::_Base> >( "TriggerPlots",
                    init<const Utils::ParameterSet&>());

}
