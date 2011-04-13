#!/usr/bin/env python
import setupSUSY
from libFrameworkSUSY import *
from libbryn import *
from libHadronic import *
from icf.core import PSet,Analysis
import icf.utils as Utils
from batchGolden import *
from samples_cff import *
from ra1objectid.vbtfElectronId_cff import *
from ra1objectid.vbtfMuonId_cff import *
from ra1objectid.ra3PhotonId_cff import *


#JetSmear = JetSmear(0.1,30)
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

ensure_dir("../results/EffTest")

#MC=[WJets_Madgraph_NNLO,TTBarTauola_NNLO,Zinvisible_jets_pset_NNLO,Zjets_madgraph_NNLO]
from montecarlo.QCD_Pythia6_384patch3_V14_00_02.QCD_Pt_1000to1400_TuneZ2_7TeV_pythia6_Fall10_START38_V12_v1 import *
# anal_ak5_caloMC.Run("../results/NoSmear",conf_ak5_caloMC,[QCD_AllPtBins_7TeV_Pythia])
QCD_Pt_470to600_7TeV_pythia8_Summer10_START36_V10_S09_v1=PSet(
 Name="QCD_Pt_470to600_7TeV_pythia8_Summer10_START36_V10_S09_v1",
 Format=("ICF",2),
 File=[
 "dcap://gfe02.grid.hep.ph.ic.ac.uk:22128//pnfs/hep.ph.ic.ac.uk/data/cms/store/user/bm409//ICF/automated/2010_07_26_10_23_33//QCD_Pt-470to600_7TeV-pythia8.Summer10-START36_V10_S09-v1.GEN-SIM-RECO//SusyCAF_Tree_1_1.root" ,
 "dcap://gfe02.grid.hep.ph.ic.ac.uk:22128//pnfs/hep.ph.ic.ac.uk/data/cms/store/user/bm409//ICF/automated/2010_07_26_10_23_33//QCD_Pt-470to600_7TeV-pythia8.Summer10-START36_V10_S09-v1.GEN-SIM-RECO//SusyCAF_Tree_2_1.root" ,
 "dcap://gfe02.grid.hep.ph.ic.ac.uk:22128//pnfs/hep.ph.ic.ac.uk/data/cms/store/user/bm409//ICF/automated/2010_07_26_10_23_33//QCD_Pt-470to600_7TeV-pythia8.Summer10-START36_V10_S09-v1.GEN-SIM-RECO//SusyCAF_Tree_3_1.root" ,
 ],
 CrossSection=7.410e+01,
# LastEntry = 1000,
)

#anal_ak5_caloMC.Run("../robtest/",conf_ak5_caloMC,[QCD_Pt_470to600_7TeV_pythia8_Summer10_START36_V10_S09_v1])
anal_ak5_caloMC.Run("../results/EffTest",conf_ak5_caloMC,[LM0,LM1])
# anal_ak5_pfMC.Run("../results/NoSmear",conf_ak5_pfMC,MC)
# anal_ak5_pfMC.Run("../results/NoSmear",conf_ak5_pfMC,[QCD_AllPtBins_7TeV_Pythia])
# anal_ak5_jptMC.Run("../results/NoSmear",conf_ak5_jptMC,MC)
# anal_ak5_jptMC.Run("../results/NoSmear",conf_ak5_jptMC,[QCD_AllPtBins_7TeV_Pythia])
# anal_ak7_caloMC.Run("../results/NoSmear",conf_ak7_caloMC,MC)
# anal_ak7_caloMC.Run("../results/NoSmear",conf_ak7_caloMC,[QCD_AllPtBins_7TeV_Pythia])

