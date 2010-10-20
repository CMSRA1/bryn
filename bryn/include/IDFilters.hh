/*! \file IDFilters.hh
 * \brief Header file for the 
 */
#ifndef Hadronic_IDFilters_hh
#define Hadronic_IDFilters_hh

#include "Lepton.hh"
#include "Utils.hh"

namespace Hadronic {
	  
	namespace Muon {
		class IDFilter : public Compute::ObjectFilter<Event::Lepton> {
		 public:
			 IDFilter(const Utils::ParameterSet& ps);
		  ~IDFilter();
		  bool Apply( Event::Lepton* );
		  std::ostream & Description( std::ostream& );
		 private:
		};//end of class Muon::IDFilter
	}//end of namespace Muon


	namespace Electron {
		template <class T>
		struct CutValue {
			T b; //!< Barrel value.
			T e; //!< Endcap value.
		};
		struct CutSet {
			//isolation
			CutValue<double> trkIso;
			CutValue<double> eclIso;
			CutValue<double> hclIso;
			//conversion rejection
			CutValue<int>    convNumHits;
			CutValue<double> convDcot;
			CutValue<double> convDist;
			//id variables
			CutValue<double> sigmaIEtaIEta; //!< Shower shape variable.
			CutValue<double> deltaPhiAtVtx; //!< Spatial matching between track and supercluster - Delta phi.
			CutValue<double> deltaEtaAtVtx; //!< Spatial matching between track and supercluster - Delta eta.
			CutValue<double> hcalOverEcal;  //!< Hadronic energy found within 0.15 of ECAL cluster over ECAL energy.
		};

		/*! \brief Allows the (RA1) user to set "Loose" and "Tight" ID according to custom variables.
		 *
		 * @author Tom Whyntie
		 * @date October 2010
		 * @version 1.0
		 *
		 * The idea is to implement a custom ID scheme (for example, the Vector Boson Task Force
		 * electron ID) quickly and without interfering with the rest of the framework.
		 * This filter class, when applied before cross-cleaning, changes the ID based
		 * on the cut variables defined above and the values supplied in the PSet
		 * provided in the constructor.
		 *
		 * To use, create an ElectronFilter like this:
		 * > from ra1objectid.vbtfElectronId_cff import * #default POG values
     * > electronIDfilter = Electron_IDFilter(vbtfelectronidps.ps())
		 * then add it to your analysis like so:
		 * > def addCutFlowData(a) :
     * > a.AddElectronFilter("PreCC",electronIDfilter)
     * > a+=cutTreeData #or whatever...
	 	 */
		class IDFilter : public Compute::ObjectFilter<Event::Lepton> {
	 	 public:
	  	IDFilter(const Utils::ParameterSet& ps);
	  	~IDFilter();
	  	bool Apply( Event::Lepton* );
	  	std::ostream & Description( std::ostream& );
	 	 private:
			bool verbose_; //!< cout statements

			CutSet loose_; //!< Loose cut set.
			CutSet tight_; //!< Tight cut set.
		};//end of class Electron::IDFilter
	}//end of namespace Electron
	  
}//end of namespace Hadronic

#endif
