#include <boost/python.hpp>
#include "HadronicOps.hh"
#include "HadronicPlottingOps.hh"
#include "BrynPlottingOps.hh"
#include "TanjaCCControlPlots.hh"
#include "BkgdEstPlottingOps.hh"
#include "EWKbkgClassesPlotOps.hh"
#include "JetMetPasPlottingOps.hh"
#include "HadronicCommonPlots.hh"

#include "IDFilters.hh"
#include "HadronicTools.hh"


using namespace boost::python;

BOOST_PYTHON_MODULE(libHadronic) {

  class_<Operation::HadronicAlphaT, bases<Operation::_Base> >( "HadronicAlphaT",  init<float>() );

  class_<Operation::HadronicCut, bases<Operation::_Base> >( "HadronicCut",  init<float>() );

  class_<Operation::HadronicPlottingOps, bases<Operation::_Base> >( "HadronicPlottingOps",
                    init<const Utils::ParameterSet&>() );

class_<Operation::EWKbkgClassesPlotOps, bases<Operation::_Base> >( "OP_EWKbkgClassesPlotOps",
                     init<const std::string &>() );
class_<Operation::PlotPhotons, bases<Operation::_Base> >( "OP_PlotPhotons",
                     init<const std::string &>() );

 class_<Operation::BrynPlottingOps, bases<Operation::_Base> >( "BrynPlottingOps",
                init<const Utils::ParameterSet&>() );

  class_<Operation::TanjaCCControlPlots, bases<Operation::_Base> >( "OP_TanjaCCControlPlots",
                    init<const Utils::ParameterSet&>() );

  class_<Operation::BkgdEstPlottingOps, bases<Operation::_Base> >( "OP_BkgdEstPlottingOps",
                    init<const Utils::ParameterSet&>() );

  class_<Operation::mSuGraPlottingOps, bases<Operation::_Base> >( "OP_mSuGraPlottingOps",
                    init<const Utils::ParameterSet&>() );


  class_<Operation::HadronicCommonPlots, bases<Operation::_Base> >( "HadronicCommonPlots",
                    init<const Utils::ParameterSet&>());


  class_<Operation::JetMetPasPlottingOps, bases<Operation::_Base> >( "JetMetPasPlottingOps",
                    init<const Utils::ParameterSet&>() );


  class_<Operation::UnCorrCut, bases<Operation::_Base> >("OP_UnCorLeadJetCut",init<float>() );



  class_<Operation::DeadECALCut, bases<Operation::_Base> >("OP_DeadECALCut",init<float,string>() );

  class_<Operation::ReversedPFMET, bases<Operation::_Base> >("OP_ReversedPFMET",init<float>() );

  class_<Operation::PFMET, bases<Operation::_Base> >("OP_PFMET",init<float>() );

  class_<Operation::MHTovHT, bases<Operation::_Base> >("OP_MHTovHT",init<float>() );

  class_<Operation::BabyMHT, bases<Operation::_Base> >("OP_BabyMHT",init<float>() );

  class_<Operation::ReversedBabyMHT, bases<Operation::_Base> >("OP_ReversedBabyMHT",init<float>() );

  class_<Operation::BabyMHTovHT, bases<Operation::_Base> >("OP_BabyMHTovHT",init<float>() );

  class_<Operation::LowPtBiasedDphi, bases<Operation::_Base> >("OP_LowPtBiasedDphi",init<float>() );

  class_<Operation::MHTPFMETDiffOvMeffCut,bases<Operation::_Base> >("OP_MHTPFMETDiffOvMeff",init<float>() );

	//TW custom ID filters
	//
  class_<Hadronic::Muon::IDFilter,     bases<Compute::ObjectFilter<Event::Lepton> > >("Muon_IDFilter",     init<const Utils::ParameterSet&>());
  class_<Hadronic::Electron::IDFilter, bases<Compute::ObjectFilter<Event::Lepton> > >("Electron_IDFilter", init<const Utils::ParameterSet&>());

	// Tools
	class_<Operation::CountOp, bases<Operation::_Base> >( "OP_Count", init<const std::string &>() );
	
}
