#!/usr/bin/env python
import setupSUSY
from libFrameworkSUSY import *
from libbryn import *
from libHadronic import *
from icf.core import PSet,Analysis
import icf.utils as Utils
from batchGolden import *


JetSmear = JetSmear(0.1,30)
vbtfElectronIdFilter = Electron_IDFilter( vbtfelectronidWP95ps.ps() )
ra3PhotonIdFilter    = Photon_IDFilter( ra3photonidps.ps() )
def addCutFlowMC(b) :
  b.AddPhotonFilter("PreCC",ra3PhotonIdFilter)
  b.AddElectronFilter("PreCC",vbtfElectronIdFilter)
  b+=cutTreeMC

#AK5 Calo
conf_ak5_caloMC = deepcopy(defaultConfig)
conf_ak5_caloMC.Ntuple = deepcopy(ak5_calo)
conf_ak5_caloMC.XCleaning = deepcopy(default_cc)
conf_ak5_caloMC.Common = deepcopy(default_common)
conf_ak5_caloMC.Common.print_out()
anal_ak5_caloMC=Analysis("AK5Calo")
addCutFlowMC(anal_ak5_caloMC)

# AK5 PF

conf_ak5_pfMC = deepcopy(defaultConfig)
conf_ak5_pfMC.Ntuple = deepcopy(ak5_pf)
conf_ak5_pfMC.XCleaning = deepcopy(default_cc)
conf_ak5_pfMC.Common = deepcopy(default_common)
anal_ak5_pfMC=Analysis("AK5PF")
addCutFlowMC(anal_ak5_pfMC)

# AK5 JPT

conf_ak5_jptMC = deepcopy(defaultConfig)
conf_ak5_jptMC.Ntuple = deepcopy(ak5_jpt)
conf_ak5_jptMC.XCleaning = deepcopy(default_cc)
conf_ak5_jptMC.Common = deepcopy(default_common)
# conf_ak5_jMCpt.Common.print_out()
anal_ak5_jptMC=Analysis("AK5JPT")
addCutFlowMC(anal_ak5_jptMC)


# AK7 Calo

conf_ak7_caloMC = deepcopy(defaultConfig)
conf_ak7_caloMC.Ntuple = deepcopy(ak7_calo)
conf_ak7_caloMC.XCleaning = deepcopy(default_cc)
conf_ak7_caloMC.Common = deepcopy(default_common)
# conf_ak5_calo.Common.print_out()
anal_ak7_caloMC=Analysis("AK7Calo")
addCutFlowMC(anal_ak7_caloMC)

ensure_dir("../results/NoSmear/")

QCD470=PSet(
Name="QCD470",
Format=("ICF",2),
File=(
"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_10_1_wU8.root",
#"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_11_1_o9t.root",
#"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_1_1_9gm.root",
#"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_12_1_Uuy.root",
#"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_13_1_A6P.root",
#"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_14_1_qnz.root",
#"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_15_1_CvP.root",
#"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_16_1_R0M.root",
#"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_17_1_lPJ.root",
#"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_18_1_Hw6.root",
#"/vols/cms02/gouskos/QCD_Pythia_Pt470_Jun2010/SusyCAF_Tree_19_1_SK4.root",
),
Weights = PSet(
    CrossSection = [8.762e+08,6.041e+07,9.238e+05,2.547e+04,1.256e+03,8.798e+01,2.186,0.01122],
    Events=[6095857,5069664,2065792,3171950,2976108,2159497,2181700,1185024],
    PtBin = [15.,30.,80.,170.,300., 470.,800.,1400.],
    ),
)
Utils.reweight([QCD470],10.9)
#anal_ak5_caloMC.Run("../results/NoSmear/",conf_ak5_caloMC,MC)
anal_ak5_caloMC.Run("../results/NoSmear",conf_ak5_caloMC,[QCD_AllPtBins_7TeV_Pythia])
# anal_ak5_pfMC.Run("../results/NoSmear",conf_ak5_pfMC,MC)
# anal_ak5_pfMC.Run("../results/NoSmear",conf_ak5_pfMC,[QCD_AllPtBins_7TeV_Pythia])
# anal_ak5_jptMC.Run("../results/NoSmear",conf_ak5_jptMC,MC)
# anal_ak5_jptMC.Run("../results/NoSmear",conf_ak5_jptMC,[QCD_AllPtBins_7TeV_Pythia])
# anal_ak7_caloMC.Run("../results/NoSmear",conf_ak7_caloMC,MC)
# anal_ak7_caloMC.Run("../results/NoSmear",conf_ak7_caloMC,[QCD_AllPtBins_7TeV_Pythia])

