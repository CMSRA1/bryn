#ifndef hadronic_include_HadronicCommonPlots_hh
#define hadronic_include_HadronicCommonPlots_hh

#include "PlottingBase.hh"
#include "Utils.hh"
#include "Types.hh"

class TH1D;
class TH2D;

namespace Operation {

  class HadronicCommonPlots : public PlottingBase {

  public:

    HadronicCommonPlots( const Utils::ParameterSet& );
    ~HadronicCommonPlots();

    void Start( Event::Data& );
    bool Process( Event::Data& );

    std::ostream& Description( std::ostream& );

  private:

    void BookHistos();
    Double_t MT2( Event::Data& );
    Double_t MT2_Leading( Event::Data& );
    std::string dirName_;
    UInt_t nMin_;
    UInt_t nMax_;

    bool StandardPlots_;
    std::vector<TH2D*>  BabyJetMHT_StandardAlphaT_;
    std::vector<TH2D*>  BabyJetMHT_StandardHT_;
    std::vector<TH2D*>  BabyJetMHT_StandardMHT_;
    std::vector<TH2D*>  PFmetvsMHT_;
    std::vector<TH1D*>  DPhi_MHT_MHTBaby_;
    std::vector<TH1D*>  DPhi_MET_MHTBaby_;
    std::vector<TH1D*>  DPhi_MET_MHT_;
    std::vector<TH1D*>  BabyJetMHT_;
    std::vector<TH1D*>  MHToverHT_;
    std::vector<TH1D*>  MissedHT_;
    std::vector<TH1D*>  MHT_PFMET_;
    std::vector<TH1D*>  HT_forRatio_;
    std::vector<TH1D*>  MHT_PFMET_AfterCut_;
    std::vector<TH1D*>  BiasedDphi_;
    std::vector<TH1D*>  AlphatCut_BiasedDphi_;
    std::vector<TH1D*>  DetlaPhi_LeadingJets_;
    std::vector<TH1D*>  DetlaPhi_NextToLeadingJets_;
    std::vector<TH1D*>  Meff_;
    std::vector<TH1D*>  AlphaT_;
    std::vector<TH1D*>  AlphaT_Zoomed_;
    std::vector<TH1D*>  MHT_;
    std::vector<TH1D*>  Mt2_;
    std::vector<TH1D*>  HT_;
    std::vector<TH1D*>  AlphatCut_Meff_;
    std::vector<TH1D*>  AlphatCut_HT_;
    std::vector<TH1D*>  AlphaT_Hadronic_;
    std::vector<TH1D*>  Mt2_LeadingJets_;
    std::vector<TH1D*>  Multiplicity_;
    std::vector<TH1D*>  fem_;
    std::vector<TH1D*>  JetPt_;
    std::vector<TH1D*>  JetEta_;
    std::vector<TH1D*>  AlphaT_Zoomed_METCut_;
    std::vector<TH1D*>  AlphaT_METCut_;
    void StandardPlots();
    bool StandardPlots( Event::Data& );

    };

  }

#endif // hadronic_include_HadronicCommonPlots_hh