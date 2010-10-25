#!/usr/bin/env python

import setupSUSY
from libFrameworkSUSY import *
from libbryn import *
from icf.core import PSet,Analysis

from batchGolden import *

def addCutFlowData(a) :
  a.AddJetFilter("PreCC",JetCorrections)
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

ensure_dir("../results/")

TenDataFiles = PSet(
Name="UpdatedMultiJet",
Weight=1.,
Format=("ICF",2),
File=[
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_0_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_10_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_11_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_12_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_13_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_14_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_15_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_16_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_17_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_18_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_19_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_1_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_2_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_3_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_4_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_5_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_6_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_7_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_8_skim.root",
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_9_skim.root",

#    "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_0_skim.root",
#    "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_10_skim.root",
#    "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_11_skim.root",
#    "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_12_skim.root",
#    "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_13_skim.root",
#    "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_14_skim.root",
#    "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_15_skim.root",
#    "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_16_skim.root",
#    "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_17_skim.root",
#    "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_18_skim.root",
 #   "/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_19_skim.root",
]
)

anal_ak5_caloData.Run("../results/",conf_ak5_caloData,[TenDataFiles])
# anal_ak5_caloData.Run("../results/",conf_ak5_caloData,[bryn1])
#anal_ak5_caloData.Run("../results/",conf_ak5_caloData,[bryn2])
#anal_ak5_caloData.Run("../results/",conf_ak5_caloData,data38)
# anal_ak5_caloData.Run("../results/",conf_ak5_caloData,[LatestSkim101010])


#
#anal_ak5_pfData.Run("../results/",conf_ak5_pfData,data38)
# anal_ak5_jptData.Run("../results/",conf_ak5_jptData,data)
# anal_ak7_caloData.Run("../results/",conf_ak7_caloData,data)
