#!/usr/bin/env python
import setupSUSY
from libFrameworkSUSY import *
from libHadronic import *
from libbryn import *
from icf.core import PSet,Analysis
from ra1objectid.vbtfElectronId_cff import *
from ra1objectid.vbtfMuonId_cff import *
from ra1objectid.ra3PhotonId_cff import *
from batchGolden import *

# JESUncert(0.1,false)    means +10%, independent of eta
# JESUncert(-0.1,false)   means -10%, independent of eta
# JESUncert(0.02,true)    means +2% per unit eta
# JESUncert(-0.02,true)   means -2% per unit eta

vbtfElectronIdFilter = Electron_IDFilter( vbtfelectronidWP95ps.ps() )
ra3PhotonIdFilter    = Photon_IDFilter( ra3photonidps.ps() )
JESUncert = JESUncert(-1.,False,True)
def addCutFlowMC(b) :
  b.AddPhotonFilter("PreCC",ra3PhotonIdFilter)
  b.AddElectronFilter("PreCC",vbtfElectronIdFilter)
  b.AddJetFilter("PreCC",JESUncert)
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

ensure_dir("../results/JESminus/")
#MC=[WJets_Madgraph_NNLO,TTBarTauola_NNLO,Zinvisible_jets_pset_NNLO,Zjets_madgraph_NNLO]
from montecarlo.QCD_Pythia6_384patch3_V14_00_02.QCD_Pt_1000to1400_TuneZ2_7TeV_pythia6_Fall10_START38_V12_v1 import *
anal_ak5_caloMC.Run("../results/Smear",conf_ak5_caloMC,[QCD_Pt_1000to1400_TuneZ2_7TeV_pythia6_Fall10_START38_V12_v1])
# anal_ak5_caloMC.Run("../results/JESminus/",conf_ak5_caloMC,[QCD_AllPtBins_7TeV_Pythia])
# anal_ak5_caloMC.Run("../results/JESminus/",conf_ak5_caloMC,AllMC)#MC+[QCD_AllPtBins_7TeV_Pythia,LM0,LM1,LM5])
# anal_ak5_pfMC.Run("../results/JESminus/",conf_ak5_pfMC,MC)
# anal_ak5_pfMC.Run("../results/JESminus/",conf_ak5_pfMC,[QCD_AllPtBins_7TeV_Pythia])
# anal_ak5_jptMC.Run("../results/JESminus/",conf_ak5_jptMC,MC)
# anal_ak5_jptMC.Run("../results/JESminus/",conf_ak5_jptMC,[QCD_AllPtBins_7TeV_Pythia])
# anal_ak7_caloMC.Run("../results/JESminus/",conf_ak7_caloMC,MC)
# anal_ak7_caloMC.Run("../results/JESminus/",conf_ak7_caloMC,[QCD_AllPtBins_7TeV_Pythia])

