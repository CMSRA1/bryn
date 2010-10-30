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
#vbtfElectronIdFilter = Electron_IDFilter( vbtfelectronidWP90ps.ps() )
#vbtMuonIdFilter      = Muon_IDFilter( vbtfmuonidps.ps() )
ra3PhotonIdFilter    = Photon_IDFilter( ra3photonidps.ps() )

def addCutFlowData(a) :
  a.AddJetFilter("PreCC",JetCorrections)
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

ensure_dir("../results/")
AllData38WithTP = PSet(
Name="AllRunsWithTP_Jet",
Weight=1.,
Format=("ICF",2),
File=[
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_0_skim.root"           ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_10_skim.root"          ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_11_skim.root"          ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_12_skim.root"          ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_13_skim.root"          ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_14_skim.root"          ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_15_skim.root"          ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_16_skim.root"          ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_17_skim.root"          ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_18_skim.root"          ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_19_skim.root"          ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_1_skim.root"           ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_2_skim.root"           ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_3_skim.root"           ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_4_skim.root"           ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_5_skim.root"           ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_6_skim.root"           ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_7_skim.root"           ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_8_skim.root"           ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_9_skim.root"           ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_0_skim.root"             ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_10_skim.root"            ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_11_skim.root"            ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_12_skim.root"            ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_13_skim.root"            ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_14_skim.root"            ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_15_skim.root"            ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_16_skim.root"            ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_17_skim.root"            ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_18_skim.root"            ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_19_skim.root"            ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_1_skim.root"             ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_2_skim.root"             ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_3_skim.root"             ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_4_skim.root"             ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_5_skim.root"             ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_6_skim.root"             ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_7_skim.root"             ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_8_skim.root"             ,
"/vols/cms02/elaird1/14_skims/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt/MultiJet.Run2010B-PromptReco-v2.RECO.RAW.Burt_9_skim.root"             ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_0_skim.root"                     ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_10_skim.root"                    ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_11_skim.root"                    ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_12_skim.root"                    ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_13_skim.root"                    ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_14_skim.root"                    ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_15_skim.root"                    ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_16_skim.root"                    ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_17_skim.root"                    ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_18_skim.root"                    ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_19_skim.root"                    ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_1_skim.root"                     ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_2_skim.root"                     ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_3_skim.root"                     ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_4_skim.root"                     ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_5_skim.root"                     ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_6_skim.root"                     ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_7_skim.root"                     ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_8_skim.root"                     ,
"/vols/cms02/elaird1/14_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt2_9_skim.root"                     ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_0_skim.root"                       ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_10_skim.root"                      ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_11_skim.root"                      ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_12_skim.root"                      ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_13_skim.root"                      ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_14_skim.root"                      ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_15_skim.root"                      ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_16_skim.root"                      ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_17_skim.root"                      ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_18_skim.root"                      ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_19_skim.root"                      ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_1_skim.root"                       ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_2_skim.root"                       ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_3_skim.root"                       ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_4_skim.root"                       ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_5_skim.root"                       ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_6_skim.root"                       ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_7_skim.root"                       ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_8_skim.root"                       ,
"/vols/cms02/elaird1/12_skims/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt/Jet.Run2010B-PromptReco-v2.RECO.RAW.Burt_9_skim.root"                       ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_0_skim.root"               ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_10_skim.root"              ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_11_skim.root"              ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_12_skim.root"              ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_13_skim.root"              ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_14_skim.root"              ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_15_skim.root"              ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_16_skim.root"              ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_17_skim.root"              ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_18_skim.root"              ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_19_skim.root"              ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_1_skim.root"               ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_2_skim.root"               ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_3_skim.root"               ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_4_skim.root"               ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_5_skim.root"               ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_6_skim.root"               ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_7_skim.root"               ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_8_skim.root"               ,
"/vols/cms02/elaird1/12_skims/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt/JetMET.Run2010A-Sep17ReReco_v2.RECO.RAW.Burt_9_skim.root"               ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_0_skim.root"   ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_10_skim.root"  ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_11_skim.root"  ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_12_skim.root"  ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_13_skim.root"  ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_14_skim.root"  ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_15_skim.root"  ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_16_skim.root"  ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_17_skim.root"  ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_18_skim.root"  ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_19_skim.root"  ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_1_skim.root"   ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_2_skim.root"   ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_3_skim.root"   ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_4_skim.root"   ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_5_skim.root"   ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_6_skim.root"   ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_7_skim.root"   ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_8_skim.root"   ,
"/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_9_skim.root"   ,
]
)
TestMet=PSet(
Name="testMe",
Weight=1.0,
Format=("ICF",2),
File="/vols/cms02/elaird1/12_skims/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning/JetMETTau.Run2010A-Sep17ReReco_v2.RECO.RAW.Henning_10_skim.root"
)
anal_ak5_caloData.Run("../results/",conf_ak5_caloData,[Jet_15pb_WithTP_json221010])



#
#anal_ak5_pfData.Run("../results/",conf_ak5_pfData,data38)
# anal_ak5_jptData.Run("../results/",conf_ak5_jptData,data)
# anal_ak7_caloData.Run("../results/",conf_ak7_caloData,data)
