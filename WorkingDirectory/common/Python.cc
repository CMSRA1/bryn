#include <boost/python.hpp>
#include "HadronicOps.hh"
#include "HadronicPlottingOps.hh"
#include "BrynPlottingOps.hh"
#include "TanjaCCControlPlots.hh"
#include "BkgdEstPlottingOps.hh"

#include "BkgdManager.hh"

using namespace boost::python;

BOOST_PYTHON_MODULE(libHadronic) {

  class_<Operation::HadronicAlphaT, bases<Operation::_Base> >( "HadronicAlphaT",
                     init<float>() );

  class_<Operation::HadronicCut, bases<Operation::_Base> >( "HadronicCut",
                  init<float>() );


  class_<Operation::HadronicCut, bases<Operation::_Base> >( "HadronicCut",
                  init<float>() );
  //init<const Utils::ParameterSet&>() );



  class_<Operation::HadronicAlphaT, bases<Operation::_Base> >( "HadronicAlphaT",  init<float>() );

  class_<Operation::HadronicCut, bases<Operation::_Base> >( "HadronicCut",  init<float>() );

  class_<Operation::HadronicPlottingOps, bases<Operation::_Base> >( "HadronicPlottingOps",
                    init<const Utils::ParameterSet&>() );

  class_<Operation::BrynPlottingOps, bases<Operation::_Base> >( "BrynPlottingOps",
                init<const Utils::ParameterSet&>() );

  class_<Operation::TanjaCCControlPlots, bases<Operation::_Base> >( "OP_TanjaCCControlPlots",
                    init<const Utils::ParameterSet&>() );

  class_<Operation::BkgdEstPlottingOps, bases<Operation::_Base> >( "OP_BkgdEstPlottingOps",
                    init<const Utils::ParameterSet&>() );

  class_<Operation::mSuGraPlottingOps, bases<Operation::_Base> >( "OP_mSuGraPlottingOps",
                    init<const Utils::ParameterSet&>() );

  class_<Operation::BkgdManager>("BkgdManager")
      .def("Run",&Operation::BkgdManager::Run);

}
