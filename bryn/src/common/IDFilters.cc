/*! \file IDFilters.cc
 * \brief Implementation of the hadronic ID filters.
 */

#include "IDFilters.hh"

#include "EventData.hh"

namespace Hadronic {
	//_______________________________________________________________
	//
	// Muon::IDFilter
	//
	Muon::IDFilter::IDFilter( const Utils::ParameterSet& ps)
	{
		mModifies = true;
	}
	Muon::IDFilter::~IDFilter() {}

	bool Muon::IDFilter::Apply( Event::Lepton* ob) {
		//ob->SetLooseId(false);
		//ob->SetTightId(true);
		return true;
	}

	std::ostream & Muon::IDFilter::Description(std::ostream & ostrm) {
	  ostrm << "[Muon::IDFilter]: ";
	  return ostrm;
	}

	//________________________________________________________________
	//
	// Electron::IDFilter
	//
	Electron::IDFilter::IDFilter( const Utils::ParameterSet& ps ) {
		mModifies = true;
		verbose_ = ps.Get<bool>("Verbose");
		//
		//isolation
		loose_.trkIso.b        = ps.Get<double>("LooseCuts.TrkIso.B");
		loose_.trkIso.e        = ps.Get<double>("LooseCuts.TrkIso.E");
		loose_.eclIso.b        = ps.Get<double>("LooseCuts.EclIso.B");
		loose_.eclIso.e        = ps.Get<double>("LooseCuts.EclIso.E");
		loose_.hclIso.b        = ps.Get<double>("LooseCuts.HclIso.B");
		loose_.hclIso.e        = ps.Get<double>("LooseCuts.HclIso.E");
		//
		tight_.trkIso.b        = ps.Get<double>("TightCuts.TrkIso.B");
		tight_.trkIso.e        = ps.Get<double>("TightCuts.TrkIso.E");
		tight_.eclIso.b        = ps.Get<double>("TightCuts.EclIso.B");
		tight_.eclIso.e        = ps.Get<double>("TightCuts.EclIso.E");
		tight_.hclIso.b        = ps.Get<double>("TightCuts.HclIso.B");
		tight_.hclIso.e        = ps.Get<double>("TightCuts.HclIso.E");
		//
		//conversion rejection
		loose_.convNumHits.b   = ps.Get<int>("LooseCuts.ConversionNumHits.B");
		loose_.convNumHits.e   = ps.Get<int>("LooseCuts.ConversionNumHits.E");
		loose_.convDcot.b      = ps.Get<double>("LooseCuts.ConversionDcot.B");
		loose_.convDcot.e      = ps.Get<double>("LooseCuts.ConversionDcot.E");
		loose_.convDist.b      = ps.Get<double>("LooseCuts.ConversionDist.B");
		loose_.convDist.e      = ps.Get<double>("LooseCuts.ConversionDist.E");
		//
		tight_.convNumHits.b   = ps.Get<int>("TightCuts.ConversionNumHits.B");
		tight_.convNumHits.e   = ps.Get<int>("TightCuts.ConversionNumHits.E");
		tight_.convDcot.b      = ps.Get<double>("TightCuts.ConversionDcot.B");
		tight_.convDcot.e      = ps.Get<double>("TightCuts.ConversionDcot.E");
		tight_.convDist.b      = ps.Get<double>("TightCuts.ConversionDist.B");
		tight_.convDist.e      = ps.Get<double>("TightCuts.ConversionDist.E");
		//
		//id
	  loose_.sigmaIEtaIEta.b = ps.Get<double>("LooseCuts.SigmaIEtaIEtaCut.B");
		loose_.sigmaIEtaIEta.e = ps.Get<double>("LooseCuts.SigmaIEtaIEtaCut.E");
		loose_.deltaPhiAtVtx.b = ps.Get<double>("LooseCuts.DeltaPhiAtVertexCut.B");
		loose_.deltaPhiAtVtx.e = ps.Get<double>("LooseCuts.DeltaPhiAtVertexCut.E");
		loose_.deltaEtaAtVtx.b = ps.Get<double>("LooseCuts.DeltaEtaAtVertexCut.B");
		loose_.deltaEtaAtVtx.e = ps.Get<double>("LooseCuts.DeltaEtaAtVertexCut.E");
		loose_.hcalOverEcal.b  = ps.Get<double>("LooseCuts.HcalOverEcalCut.B");
		loose_.hcalOverEcal.e  = ps.Get<double>("LooseCuts.HcalOverEcalCut.E");
		//
	  tight_.sigmaIEtaIEta.b = ps.Get<double>("TightCuts.SigmaIEtaIEtaCut.B");
		tight_.sigmaIEtaIEta.e = ps.Get<double>("TightCuts.SigmaIEtaIEtaCut.E");
		tight_.deltaPhiAtVtx.b = ps.Get<double>("TightCuts.DeltaPhiAtVertexCut.B");
		tight_.deltaPhiAtVtx.e = ps.Get<double>("TightCuts.DeltaPhiAtVertexCut.E");
		tight_.deltaEtaAtVtx.b = ps.Get<double>("TightCuts.DeltaEtaAtVertexCut.B");
		tight_.deltaEtaAtVtx.e = ps.Get<double>("TightCuts.DeltaEtaAtVertexCut.E");
		tight_.hcalOverEcal.b  = ps.Get<double>("TightCuts.HcalOverEcalCut.B");
		tight_.hcalOverEcal.e  = ps.Get<double>("TightCuts.HcalOverEcalCut.E");
	}
	Electron::IDFilter::~IDFilter() {}

	bool Electron::IDFilter::Apply( Event::Lepton* ob) {
		Int_t idx = ob->GetIndex();
		//
		if (verbose_) std::cout<<"[Electron::IDFilter]: eta="<<ob->Eta()<<" ";
		//barrel/endcap transition electrons or outside tracker acceptance - not loose or tight
		if ((fabs(ob->Eta())>2.5) || ((1.4442 < fabs(ob->Eta()))&&(fabs(ob->Eta())<1.566))) {
			ob->SetLooseId(false);
			ob->SetTightId(false);
			if(verbose_)std::cout<<std::endl;
			return true;
		}
		//leaves only barrel or endcap electrons
		bool isB = (ob->Eta() < 1.4442);
		//
		if (//tight ID check - brace yourself...
				//isolation
			 ( isB ? (ob->GetTrkIsolation()  < tight_.trkIso.b) : (ob->GetTrkIsolation()  < tight_.trkIso.e) ) &&
			 ( isB ? (ob->GetEcalIsolation() < tight_.eclIso.b) : (ob->GetEcalIsolation() < tight_.eclIso.e) ) &&
			 ( isB ? (ob->GetHcalIsolation() < tight_.hclIso.b) : (ob->GetHcalIsolation() < tight_.hclIso.e) ) &&
				//conversion rejection
			 //( isB ? () : () ) && //for number of missing hits, when implemented...
			 ( isB ? (mEv->GetElectronDCot(idx) < tight_.convDcot.b) : (mEv->GetElectronDCot(idx) < tight_.convDcot.e) ) &&
			 ( isB ? (mEv->GetElectronDist(idx) < tight_.convDist.b) : (mEv->GetElectronDist(idx) < tight_.convDist.e) ) &&
				//id variables
			 ( isB ? (mEv->GetElectronSigmaIetaIeta(idx) < tight_.sigmaIEtaIEta.b) : (mEv->GetElectronSigmaIetaIeta(idx) < tight_.sigmaIEtaIEta.e) ) &&
			 ( isB ? (mEv->GetElectronDeltaPhiAtVtx(idx) < tight_.deltaPhiAtVtx.b) : (mEv->GetElectronDeltaPhiAtVtx(idx) < tight_.deltaPhiAtVtx.e) ) &&
			 ( isB ? (mEv->GetElectronDeltaEtaAtVtx(idx) < tight_.deltaEtaAtVtx.b) : (mEv->GetElectronDeltaEtaAtVtx(idx) < tight_.deltaEtaAtVtx.e) ) &&
			 ( isB ? (mEv->GetElectronHoE(idx) < tight_.hcalOverEcal.b) : (mEv->GetElectronHoE(idx) < tight_.hcalOverEcal.e) )                       
			 )
		{
			if(verbose_)std::cout<<" Tight electron! ";
      ob->SetLooseId(true); //cuts are all cumulative for loose/tight, so we save computing power...
			ob->SetTightId(true);
		}//end of tight ID check
		else if //loose ID check - brace yourself...
			(
				//isolation
			 ( isB ? (ob->GetTrkIsolation()  < loose_.trkIso.b) : (ob->GetTrkIsolation()  < loose_.trkIso.e) ) &&
			 ( isB ? (ob->GetEcalIsolation() < loose_.eclIso.b) : (ob->GetEcalIsolation() < loose_.eclIso.e) ) &&
			 ( isB ? (ob->GetHcalIsolation() < loose_.hclIso.b) : (ob->GetHcalIsolation() < loose_.hclIso.e) ) &&
				//conversion rejection
			 //( isB ? () : () ) && //for number of missing hits, when implemented...
			 ( isB ? (mEv->GetElectronDCot(idx) < loose_.convDcot.b) : (mEv->GetElectronDCot(idx) < loose_.convDcot.e) ) &&
			 ( isB ? (mEv->GetElectronDist(idx) < loose_.convDist.b) : (mEv->GetElectronDist(idx) < loose_.convDist.e) ) &&
				//id variables
			 ( isB ? (mEv->GetElectronSigmaIetaIeta(idx) < loose_.sigmaIEtaIEta.b) : (mEv->GetElectronSigmaIetaIeta(idx) < loose_.sigmaIEtaIEta.e) ) &&
			 ( isB ? (mEv->GetElectronDeltaPhiAtVtx(idx) < loose_.deltaPhiAtVtx.b) : (mEv->GetElectronDeltaPhiAtVtx(idx) < loose_.deltaPhiAtVtx.e) ) &&
			 ( isB ? (mEv->GetElectronDeltaEtaAtVtx(idx) < loose_.deltaEtaAtVtx.b) : (mEv->GetElectronDeltaEtaAtVtx(idx) < loose_.deltaEtaAtVtx.e) ) &&
			 ( isB ? (mEv->GetElectronHoE(idx)           < loose_.hcalOverEcal.b)  : (mEv->GetElectronHoE(idx)           < loose_.hcalOverEcal.e)  )
			)
		{
			if(verbose_)std::cout<<" Loose electron! ";
      ob->SetLooseId(true);
		}//end of loose ID check

		if(verbose_)std::cout<<std::endl;
		return true;
	}//end of IDFilter Apply method.

	std::ostream & Electron::IDFilter::Description(std::ostream & ostrm) {
	  ostrm << "[Electron::IDFilter]: ";
	  return ostrm;
	}
}//end of namespace Hadronic
