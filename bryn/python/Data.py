#!/usr/bin/env python

import setupSUSY
from libFrameworkSUSY import *
from libbryn import *
from libHadronic import *
from icf.core import PSet,Analysis

from batchGolden import *
from ra1objectid.vbtfElectronId_cff import *
from ra1objectid.vbtfMuonId_cff import *
from ra1objectid.ra3PhotonId_cff import *

vbtfElectronIdFilter = Electron_IDFilter( vbtfelectronidWP95ps.ps() )
ra3PhotonIdFilter    = Photon_IDFilter( ra3photonidps.ps() )
PreScaleWeights = PreScaleReweighting(datatriggerps.ps())
def addCutFlowData(a) :
  a.AddWeightFilter("Weight",PreScaleWeights)
  # a.AddJetFilter("PreCC",JetCorrections)
  a.AddPhotonFilter("PreCC",ra3PhotonIdFilter)
  a.AddElectronFilter("PreCC",vbtfElectronIdFilter)
  a+=cutTreeData

# AK5 Calo

conf_ak5_caloData = deepcopy(defaultConfig)
conf_ak5_caloData.Ntuple = deepcopy(ak5_calo)
conf_ak5_caloData.XCleaning = deepcopy(default_cc)
conf_ak5_caloData.Common = deepcopy(default_common)
# conf_ak5_calo.Common.print_out()
anal_ak5_caloData=Analysis("AK5Calo")
addCutFlowData(anal_ak5_caloData)

# AK5 PF

conf_ak5_pfData = deepcopy(defaultConfig)
conf_ak5_pfData.Ntuple = deepcopy(ak5_pf)
conf_ak5_pfData.XCleaning = deepcopy(default_cc)
conf_ak5_pfData.Common = deepcopy(default_common)
anal_ak5_pfData=Analysis("AK5PF")
addCutFlowData(anal_ak5_pfData)

# AK5 JPT

conf_ak5_jptData = deepcopy(defaultConfig)
conf_ak5_jptData.Ntuple = deepcopy(ak5_jpt)
conf_ak5_jptData.XCleaning = deepcopy(default_cc)
conf_ak5_jptData.Common = deepcopy(default_common)
# conf_ak5_jDatapt.Common.print_out()
anal_ak5_jptData=Analysis("AK5JPT")
addCutFlowData(anal_ak5_jptData)

# AK7 Calo

conf_ak7_caloData = deepcopy(defaultConfig)
conf_ak7_caloData.Ntuple = deepcopy(ak7_calo)
conf_ak7_caloData.XCleaning = deepcopy(default_cc)
conf_ak7_caloData.Common = deepcopy(default_common)
# conf_ak5_calo.Common.print_out()
anal_ak7_caloData=Analysis("AK7Calo")
addCutFlowData(anal_ak7_caloData)

from data.Run2011.HT_Run2011_promptReco import *
outDir = "../results/Data/"
ensure_dir(outDir)
anal_ak5_caloData.Run(outDir,conf_ak5_caloData,[HT_Run2011_promptReco])

# from data.MultiJet_Run2010B_Nov4ReReco_v1 import *

#
# anal_ak5_pfData.Run("../results/",conf_ak5_pfData,[AllData38WithTP])#[MultiJet_Run2010B_Nov4ReReco_v1])#
# anal_ak5_jptData.Run("../results/",conf_ak5_jptData,data)
# anal_ak7_caloData.Run("../results/",conf_ak7_caloData,data)
