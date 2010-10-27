#include <boost/python.hpp>
#include "HadronicOps.hh"
#include "HadronicPlottingOps.hh"
#include "BrynPlottingOps.hh"
#include "TanjaCCControlPlots.hh"
#include "BkgdEstPlottingOps.hh"
#include "EWKbkgClassesPlotOps.hh"
#include "JetMetPasPlottingOps.hh"
#include "WeeklyUpdatePlots.hh"

#include "IDFilters.hh"
#include "HadronicTools.hh"


using namespace boost::python;

BOOST_PYTHON_MODULE(libbryn) {

  class_<Operation::WeeklyUpdatePlots, bases<Operation::_Base> >( "WeeklyUpdatePlots",
                    init<const Utils::ParameterSet&>());

}
