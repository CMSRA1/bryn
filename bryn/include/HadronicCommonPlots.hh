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
    void BookHistos();

    std::ostream& Description( std::ostream& );

  private:

    //  void BookHistos();
    Double_t MT2( Event::Data& );
    Double_t MT2_Leading( Event::Data& );
    std::string dirName_;
    UInt_t nMin_;
    UInt_t nMax_;

    bool StandardPlots_;
    bool DeadECALPlots_;
    bool CleaningControlPlots_;
    bool MECPlots_;

    std::string deadECALFile_;
    
   
   
    //Standard Plots
    std::vector<TH1D*>  MHTOvHT_;
    std::vector<TH1D*>  Meff_;
    std::vector<TH1D*>  AlphaT_;
    std::vector<TH1D*>  AlphaT_Zoomed_;
    std::vector<TH1D*>  MHT_;
    std::vector<TH1D*>  Mt2_;
    std::vector<TH1D*>  HT_;
  
    std::vector<TH1D*>  AlphaT_Hadronic_;
    std::vector<TH1D*>  Mt2_LeadingJets_;
    
    std::vector<TH1D*>  fem_;
    std::vector<TH1D*>  JetPt_;
    std::vector<TH1D*>  JetEta_;


    //DeadECAL Plots
    std::vector<TH1D*>  BiasedDphi_;
    std::vector<TH1D*> BadJetECALDR_;
    std::vector<TH1D*> allMinECALDR_;
    std::vector<TH1D*> TPMHT_;
    std::vector<TH1D*> TPHT_;
    std::vector<TH1D*> TPMHTRatio_;
    

    //Cleaning Control Plots
    std::vector<TH1D*> NoisyMHT_;
    std::vector<TH1D*> NoisyHT_;
    

    //MEC Plots
    std::vector<TH1D*> MHTPFMETDiffOvMeff_;
    std::vector<TH1D*> MHTCaloMETDiffOvMeff_;
    std::vector<TH1D*> MHTOvPFMET_;
    std::vector<TH1D*> BabyJetMHT_10_50_;
    std::vector<TH1D*> BabyJetMHT_10_30_;
    std::vector<TH1D*>  MissedMHT_;
    
    std::vector<TH2D*> PFMET_vs_MHTPFMETDiffOvMeff_;
    std::vector<TH2D*> MHT_vs_PFMET_;

    

   
  
    void StandardPlots();
    bool StandardPlots( Event::Data& );
    void DeadECALPlots();
    bool DeadECALPlots( Event::Data& );
    void CleaningControlPlots();
    bool CleaningControlPlots( Event::Data& );
    void MECPlots();
    bool MECPlots( Event::Data& );

    };


 
  }

 double  DeadECALDR_File(TString deadECALfile,float jetphi,float jeteta, int nBad);
  double  DeadECALDR( Event::Data& ev,float jetphi,float jeteta, int nBad);


#endif // hadronic_include_HadronicCommonPlots_hh
