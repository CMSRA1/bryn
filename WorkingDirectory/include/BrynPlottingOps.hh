#ifndef hadronic_include_BrynPlottingOps_hh
#define hadronic_include_BrynPlottingOps_hh

#include "PlottingBase.hh"
#include "Utils.hh"
#include "Types.hh"

class TH1D;
class TH2D;

namespace Operation {

  class BrynPlottingOps : public PlottingBase {

  public:

    BrynPlottingOps( const Utils::ParameterSet& );
    ~BrynPlottingOps();

    void Start( Event::Data& );
    bool Process( Event::Data& );

    std::ostream& Description( std::ostream& );

  private:

    void BookHistos();

    LorentzV RecoilMET( Event::Data& );
    Double_t MassReco( Event::Data& );
    Double_t MT2_DiJet( Event::Data& );
    Double_t MT2_NJet( Event::Data& );
    std::string dirName_;
    UInt_t nMin_;
    UInt_t nMax_;

    // MT2
    bool mt2_;
    void mt2();
    bool mt2( Event::Data& );
    std::vector<TH1D*> hMt2_;
    std::vector<TH1D*> hMT2_over_MHT_;
    std::vector<TH1D*> hMHT_over_MT2_;
    std::vector<TH2D*> hMt2_vs_alphaT_;
    //MT2 using psudo jets from alpha_T
    bool mt2_Multi_jet_;
    std::vector<TH1D*> hMt2_Multi_Jet_;
    std::vector<TH1D*> hMT2_over_MHT_Multi_;
    std::vector<TH1D*> hMHT_over_MT2_Multi_;
    std::vector<TH2D*> hMt2_vs_alphaT_Multi_;
    void mt2_Multi_Jet();
    bool mt2_Multi_Jet( Event::Data& );
    //Comparison of MT2 to MT2 using psudo jets
    bool mt2_comparison_;
    std::vector<TH2D*> hMT2Val_;
    void mt2_Comparison();
    bool mt2_Comparison( Event::Data& );
    //MHT Plots
    bool Mht_plots_;
    std::vector<TH1D*> hMht_recoil_;
    void MHTPlots();
    bool MHTPlots( Event::Data& );
    //DalitzMT2 Plots
    bool DalitzMT2_;
    std::vector<TH2D*>  hDalitzMT2Mjj_;
    std::vector<TH2D*>  hDalitzMT2mt_j1_mht_;
    std::vector<TH2D*>  hDalitzMT2mt_j2_mht_;
    void DalitzMT2();
    bool DalitzMT2( Event::Data& );
    //Development Plots
    bool Dev_;
    std::vector<TH1D*> MassReco_;
    std::vector<TH2D*> HTvsMHT_;
    std::vector<TH2D*> HTvsMHT_X_;
    std::vector<TH2D*> HTvsMHT_Y_;
    std::vector<TH2D*> CaloMetvsSUMET_;
    std::vector<TH1D*> CALO_MET_;
    std::vector<TH1D*> MET_Pt_;
    std::vector<TH1D*> MHT_X_;
    std::vector<TH1D*> MHT_Y_;
    std::vector<TH2D*> SumETvsHT_;
    std::vector<TH2D*> SumETvsMHT_;
    void DevPlots();
    bool DevPlots( Event::Data& );

  };

}

#endif // hadronic_include_BrynPlottingOps_hh
