#!/usr/bin/env python

#!/usr/bin/env python
"""
Created by Bryn Mathias on 2010-05-07.
"""

# -----------------------------------------------------------------------------
# Necessary includes
import errno
import os
import setupSUSY
from libFrameworkSUSY import *
from libHadronic import *
from libbryn import *
from icf.core import PSet,Analysis
from icf.config import defaultConfig
from copy import deepcopy
from icf.JetCorrections import *
from samples_cff import *

# -----------------------------------------------------------------------------
# Samples
#import yours in your running script
def ensure_dir(path):
    try:
      os.makedirs(path)
    except OSError as exc: # Python >2.5
      if exc.errno == errno.EEXIST:
        pass
      else: raise

# -----------------------------------------------------------------------------
# Reading the collections from the ntuple

default_ntuple = deepcopy(defaultConfig.Ntuple)
default_ntuple.Electrons=PSet(
Prefix="electron",
Suffix="Pat",
LooseID="EIDLoose",
TightID="EIDTight",
)
default_ntuple.Muons=PSet(
Prefix="muon",
Suffix="Pat",
LooseID="IsGlobalMuon",
TightID="IDGlobalMuonPromptTight",
)
default_ntuple.SecMuons=PSet(
    Prefix="muon",
    Suffix="PF")
default_ntuple.Taus=PSet(
Prefix="tau",
Suffix="Pat",
LooseID="TauIdbyTaNCfrOnePercent",
TightID="TauIdbyTaNCfrTenthPercent"
)
default_ntuple.Jets=PSet(
Prefix="ic5Jet",
Suffix="Pat",
Uncorrected=False,
)
default_ntuple.Photons=PSet(
Prefix="photon",
Suffix="Pat",
)

ic5_calo = deepcopy(default_ntuple)
ic5_calo.Jets.Prefix="ic5Jet"

ak5_calo = deepcopy(default_ntuple)
ak5_calo.Jets.Prefix="ak5Jet"

ak5_jpt = deepcopy(default_ntuple)
ak5_jpt.Jets.Prefix="ak5JetJPT"

ak5_pf = deepcopy(default_ntuple)
ak5_pf.Jets.Prefix="ak5JetPF"
ak5_pf.TerJets.Prefix="ak5Jet"

ak7_calo = deepcopy(default_ntuple)
ak7_calo.Jets.Prefix="ak7Jet"


# -----------------------------------------------------------------------------
# Cross-cleaning settings

default_cc = deepcopy(defaultConfig.XCleaning)
default_cc.Verbose=False
default_cc.MuonJet=True
default_cc.ElectronJet=True
default_cc.PhotonJet=True
default_cc.ResolveConflicts=True
default_cc.Jets.PtCut=10.0
default_cc.Jets.EtaCut=10.0
default_cc.Muons.ModifyJetEnergy=True
default_cc.Muons.PtCut=10.0
default_cc.Muons.EtaCut=2.5
default_cc.Muons.TrkIsoCut=-1.
default_cc.Muons.CombIsoCut=0.15
default_cc.Muons.MuonJetDeltaR=0.5
default_cc.Muons.MuonIsoTypePtCutoff=0.
default_cc.Muons.RequireLooseIdForInitialFilter=False
default_cc.Electrons.PtCut=10.0
default_cc.Electrons.EtaCut=2.5
default_cc.Electrons.TrkIsoCut=-1.0
default_cc.Electrons.CombIsoCut=0.15
default_cc.Electrons.ElectronJetDeltaR=0.5
default_cc.Electrons.ElectronIsoTypePtCutoff=0.
default_cc.Electrons.ElectronLooseIdRequired=True
default_cc.Electrons.ElectronTightIdRequired=False
default_cc.Electrons.RequireLooseIdForInitialFilter=False
default_cc.Photons.EtCut=25.0
default_cc.Photons.EtaCut=2.5
default_cc.Photons.TrkIsoCut=2.0
default_cc.Photons.CaloIsoCut=0.2
default_cc.Photons.IDReq=3
default_cc.Photons.PhotonJetDeltaR=0.5
default_cc.Photons.PhotonIsoTypePtCutoff=30.
# -----------------------------------------------------------------------------
# Definition of common objects
default_common = deepcopy(defaultConfig.Common)

default_common.ApplyXCleaning=True
default_common.Jets.PtCut=50.0
default_common.Jets.EtaCut=3.0
default_common.Jets.ApplyID=True
default_common.Jets.TightID=False
default_common.Electrons.PtCut=10.0
default_common.Electrons.EtaCut=2.5
default_common.Electrons.TrkIsoCut=-1.
default_common.Electrons.CombIsoCut=0.15
default_common.Electrons.ApplyID = True
default_common.Electrons.TightID = False
default_common.Electrons.RequireLooseForOdd = True
default_common.Muons.PtCut=10.0
default_common.Muons.EtaCut=2.5
default_common.Muons.TrkIsoCut=-1.
default_common.Muons.CombIsoCut=0.15
default_common.Muons.ApplyID = True
default_common.Muons.TightID = True
default_common.Muons.RequireLooseForOdd = True
default_common.Photons.EtCut=25.0
default_common.Photons.EtaCut=2.5
# the photon cuts are NOT read anyway
# default_common.Photons.TrkIsoRel=0.
# default_common.Photons.TrkIsoCut=99999.
# default_common.Photons.EcalIsoRel=0.
# default_common.Photons.EcalIsoCut=99999.
# default_common.Photons.HcalIsoRel=0.
# default_common.Photons.HcalIsoCut=99999.
# default_common.Photons.HadOverEmCut=0.5
# default_common.Photons.SigmaIetaIetaCut=0.5
##default_common.Photons.CaloIsoCut=99999.
default_common.Photons.IDReq = 3
default_common.Photons.RequireLooseForOdd = True
MC=[wjets_madgraph_vols,ttbarTauola,Zinvisible_jets,zjets_madgraph,LM0,LM1,LM2,LM3,LM4,LM5,LM6,LM9,LM12,LM13]
Pythia8=[QCD_Pt_0to15_7TeV_pythia8_Summer10_START36_V10_S09_v1,QCD_Pt_15to20_7TeV_pythia8_Summer10_START36_V10_S09_v1,QCD_Pt_20to30_7TeV_pythia8_Summer10_START36_V10_S09_v1,QCD_Pt_30to50_7TeV_pythia8_Summer10_START36_V10_S09_v2,QCD_Pt_50to80_7TeV_pythia8_Summer10_START36_V10_S09_v1,QCD_Pt_80to120_7TeV_pythia8_Summer10_START36_V10_S09_v1,QCD_Pt_120to170_7TeV_pythia8_Summer10_START36_V10_S09_v1,QCD_Pt_170to230_7TeV_pythia8_Summer10_START36_V10_S09_v2,QCD_Pt_230to300_7TeV_pythia8_Summer10_START36_V10_S09_v2,QCD_Pt_300to380_7TeV_pythia8_Summer10_START36_V10_S09_v1,QCD_Pt_380to470_7TeV_pythia8_Summer10_START36_V10_S09_v1,QCD_Pt_470to600_7TeV_pythia8_Summer10_START36_V10_S09_v1,QCD_Pt_600to800_7TeV_pythia8_Summer10_START36_V10_S09_v1,QCD_Pt_800to1000_7TeV_pythia8_Summer10_START36_V10_S09_v2,QCD_Pt_1000to1400_7TeV_pythia8_Summer10_START36_V10_S09_v2,QCD_Pt_1400to1800_7TeV_pythia8_Summer10_START36_V10_S09_v2,QCD_Pt_1800to2200_7TeV_pythia8_Summer10_START36_V10_S09_v2,QCD_Pt_2200to2600_7TeV_pythia8_Summer10_START36_V10_S09_v2,QCD_Pt_3000to3500_7TeV_pythia8_Summer10_START36_V10_S09_v2]
# CMSSW_3_8_4_patch3 V14-00-02 samples
from montecarlo.QCD_Pythia6_384patch3_V14_00_02_ALL import *
from montecarlo.QCD_Pythia8_384patch3_V14_00_02_ALL import *
from data.Jet_15pb_WithTP_json221010 import *
#AllMC = QCD_Pythia6_384patch3_V14_00_02_ALL+QCD_Pythia8_384patch3_V14_00_02_ALL+
AllMC =  MC+QCD_Pythia6_384patch3_V14_00_02_ALL+QCD_Pythia8_384patch3_V14_00_02_ALL
#+Pythia8



# -----------------------------------------------------------------------------


#Plot the common plots!
pset1 = PSet(
DirName      = "250_300Gev",
MinObjects   = 1,
MaxObjects   = 2,
StandardPlots     = True,
)

Npset1 = PSet(
DirName      = "n250_300Gev",
MinObjects   = 3,
MaxObjects   = 15,
StandardPlots     = True,
)

pset2 = PSet(
DirName      = "300Gev",
MinObjects   = 2,
MaxObjects   = 2,
StandardPlots     = True,
)

Npset2 = PSet(
DirName      = "n300Gev",
MinObjects   = 3,
MaxObjects   = 15,
StandardPlots     = True,
)

pset3 = PSet(
DirName      = "350Gev",
MinObjects   = 2,
MaxObjects   = 2,
StandardPlots     = True,
)

Npset3 = PSet(
DirName      = "n350Gev",
MinObjects   = 3,
MaxObjects   = 15,
StandardPlots     = True,
)


pset5 = PSet(
DirName      = "350Gev_afterDeadEcal",
MinObjects   = 2,
MaxObjects   = 2,
StandardPlots     = True,
)

Npset5 = PSet(
DirName      = "n350Gev_afterDeadEcal",
MinObjects   = 3,
MaxObjects   = 15,
StandardPlots     = True,
)

pset4 = PSet(
DirName      = "All",
MinObjects   = 2,
MaxObjects   = 2,
StandardPlots     = True,
)

Npset4 = PSet(
DirName      = "nAll",
MinObjects   = 3,
MaxObjects   = 15,
StandardPlots     = True,
)

Npset6 = PSet(
DirName      = "nAllCuts",
MinObjects   = 3,
MaxObjects   = 15,
StandardPlots     = True,
)

pset6 = PSet(
DirName      = "AllCuts",
MinObjects   = 2,
MaxObjects   = 2,
StandardPlots     = True,
)

dalitz_plots_Inclusive = HadronicPlottingOps( PSet(
DirName    = "Dalitz_Inclusive",
MinObjects = 2,
MaxObjects = 10,
Verbose    = False,
Summary    = False,
CC         = False,
Dalitz     = True,
AlphaT     = False,
PtHat      = False,
MET        = False,
Kine       = False,
Response   = False,
).ps()
)

dalitz_plots_250_300 = HadronicPlottingOps( PSet(
DirName    = "Dalitz_250_300",
MinObjects = 2,
MaxObjects = 10,
Verbose    = False,
Summary    = False,
CC         = False,
Dalitz     = True,
AlphaT     = False,
PtHat      = False,
MET        = False,
Kine       = False,
Response   = False,
).ps()
)

dalitz_plots_300_350 = HadronicPlottingOps( PSet(
DirName    = "Dalitz_300_350",
MinObjects = 2,
MaxObjects = 10,
Verbose    = False,
Summary    = False,
CC         = False,
Dalitz     = True,
AlphaT     = False,
PtHat      = False,
MET        = False,
Kine       = False,
Response   = False,
).ps()
)

dalitz_plots_350 = HadronicPlottingOps( PSet(
DirName    = "Dalitz_350",
MinObjects = 2,
MaxObjects = 10,
Verbose    = False,
Summary    = False,
CC         = False,
Dalitz     = True,
AlphaT     = False,
PtHat      = False,
MET        = False,
Kine       = False,
Response   = False,
).ps()
)




HadStandard250_350 = WeeklyUpdatePlots(pset1.ps())
HadStandard300 = WeeklyUpdatePlots(pset2.ps())
HadStandard350 = WeeklyUpdatePlots(pset3.ps())
HadStandard350_after_DeadEcal = WeeklyUpdatePlots(pset5.ps())
HadStandardAll = WeeklyUpdatePlots(pset4.ps())
nHadStandard250_350 = WeeklyUpdatePlots(Npset1.ps())
nHadStandard300 = WeeklyUpdatePlots(Npset2.ps())
nHadStandard350 = WeeklyUpdatePlots(Npset3.ps())
nHadStandardAll = WeeklyUpdatePlots(Npset4.ps())
nHadStandard350_after_DeadEcal = WeeklyUpdatePlots(Npset5.ps())
# Common cut definitions
#Avaiable criteria for MC and for Data are at current slightly different Hence the making of two trees
#DataOnly!

from icf.JetCorrections import *
corPset =  CorrectionPset("ResidualJetEnergyCorrections.txt")
# corPset =  CorrectionPset("Spring10DataV2_L2L3Residual_AK5PF.txt")
JetCorrections = JESCorrections( corPset.ps(),True )
NoiseFilt= OP_HadronicHBHEnoiseFilter()
selection = OP_GoodEventSelection()


JetTrigger = OP_TwoTriggerCut("HLT_HT100U","HLT_HT140U")
#Standard Event Selection
LeadingJetEta = OP_FirstJetEta(2.5)
unCorLeadJetCut = OP_UnCorLeadJetCut(30.)
LeadingJetCut = OP_FirstJetPtCut(100.)
oddMuon = OP_OddMuon()
oddElectron = OP_OddElectron()
oddPhoton = OP_OddPhoton()
oddJet = OP_OddJet()
secondJetET = OP_SecondJetEtCut(100.)
badMuonInJet = OP_BadMuonInJet()
numComLeptons = OP_NumComLeptons("<=",0)
numComPhotons = OP_NumComPhotons("<=",0)

DiJet0 = OP_NumComJets("==",2)
DiJet1 = OP_NumComJets("==",2)
DiJet2 = OP_NumComJets("==",2)
DiJet3 = OP_NumComJets("==",2)
DiJet4 = OP_NumComJets("==",2)
NJet0 = OP_NumComJets(">=",3)
NJet1 = OP_NumComJets(">=",3)
NJet2 = OP_NumComJets(">=",3)
NJet3 = OP_NumComJets(">=",3)
NJet4 = OP_NumComJets(">=",3)
DiVertexJets = OP_NumComJets("==",2)
NVertexJets = OP_NumComJets(">=",3)

LessThan350 = RECO_CommonHTLessThanCut(350.)
htCut250 = RECO_CommonHTCut(250.)
htCut300 = RECO_CommonHTCut(300.)
htCut350 = RECO_CommonHTCut(350.)
htCut350GeV = RECO_CommonHTCut(350.)
alphaT0 = OP_CommonAlphaTCut(0.55)
alphaT1 = OP_CommonAlphaTCut(0.55)
alphaT2 = OP_CommonAlphaTCut(0.55)
spikecleaner = OP_EcalSpikeCleaner()
event_display = OP_EventDisplay("EventDisplays", "common") #to draw all/common objects
alphat = OP_CommonAlphaTCut(0.55)
DeadEcalCutData = OP_DeadECALCut(0.3,0.5,30.,10,0,"./deadRegionList_GR10_P_V10.txt")
DeadEcalCutMC =   OP_DeadECALCut(0.3,0.5,30.,10,1,"./deadRegionList_START38_V12.txt")

MHT_METCut = OP_MHToverMET(1.25)
NJet5 = OP_NumComJets(">=",3)
DiJet5 = OP_NumComJets("==",2)
nHadStandardAllCuts=  WeeklyUpdatePlots(Npset6.ps())
HadStandardAllCuts=  WeeklyUpdatePlots(pset6.ps())


# Cross check with the allhadronic analysis
t1 = PSet(
    DirName      = "HadronicCommon_1",
    MinObjects   = 2,
    MaxObjects   = 15,
    StandardPlots     = False,
    DeadECALPlots = True,
    CleaningControlPlots = False,
    MECPlots = False,
    DeadECALFile = "./deadRegionList_START36_V9.txt",
    DeadECAL_MinJetPtCut = 30.,
    DeadECAL_MinBiasCut = 0.5,
    DeadECAL_NBadCellsCut = 10
)

t2 = deepcopy(t1)
t2.DirName = "HadronicCommon_2"

pset = PSet(
DirName      = "250_infGev",
MinObjects   = 1,
MaxObjects   = 2,
StandardPlots     = True,
)

Npset = PSet(
DirName      = "n250_infGev",
MinObjects   = 3,
MaxObjects   = 15,
StandardPlots     = True,
)

pset2 = deepcopy(pset)
pset2.DirName = "250_350Gev"

Npset2 = deepcopy(Npset)
Npset2.DirName = "n250_350Gev"

pset3 = deepcopy(pset)
pset3.DirName = "350GeVafterDeadEcal"
Npset3 = deepcopy(Npset)
Npset3.DirName = "n350GeVafterDeadEcal"

pset4 = deepcopy(pset)
pset4.DirName = "allCuts"
Npset4 = deepcopy(Npset)
Npset4.DirName = "nAllCuts"

HTplot = WeeklyUpdatePlots(pset.ps())
nHTplot = WeeklyUpdatePlots(Npset.ps())
controlRegion = WeeklyUpdatePlots(pset2.ps())
ncontrolRegion = WeeklyUpdatePlots(Npset2.ps())
afterDeadEcal = WeeklyUpdatePlots(pset3.ps())
nafterDeadEcal = WeeklyUpdatePlots(Npset3.ps())
afterAllCuts = WeeklyUpdatePlots(pset4.ps())
nafterAllCuts = WeeklyUpdatePlots(Npset4.ps())


pset2 = deepcopy(pset1)
pset2.DirName = "HadronicCommon_2"

t3 = deepcopy(t1)
t3.DirName = "HadronicCommon_3"

t4 = deepcopy(t1)
t4.DirName = "HadronicCommon_4"
#
HadStandard_1 = HadronicCommonPlots(t1.ps())
HadStandard_2 = HadronicCommonPlots(t2.ps())
HadStandard_3 = HadronicCommonPlots(t3.ps())
HadStandard_4 = HadronicCommonPlots(t4.ps())
VertexPtOverHT = OP_SumVertexPtOverHT(0.1)
eventDump = OP_EventNoDump("mydump","mydump")

datatriggerps = PSet(
    Verbose = False,
    Triggers = [
        "HLT_HT100U",
        "HLT_HT120U",
        "HLT_HT140U",
        "HLT_HT150U_v3",
        "HLT_HT160U_v1",
        "HLT_HT160U_v3",
        ]
    )
DataTrigger = OP_HadronicDataTrigger( datatriggerps.ps() )
# AlphatTriggerCut(0.52414,50)#


cutTreeData = Tree("Data")
cutTreeData.Attach(DataTrigger)
cutTreeData.TAttach(DataTrigger,NoiseFilt)
cutTreeData.TAttach(NoiseFilt,selection)
cutTreeData.TAttach(selection,oddMuon)
cutTreeData.TAttach(oddMuon,oddElectron)
cutTreeData.TAttach(oddElectron,oddPhoton)
cutTreeData.TAttach(oddPhoton,numComLeptons)
cutTreeData.TAttach(numComLeptons,numComPhotons)
cutTreeData.TAttach(numComPhotons,LeadingJetEta)
cutTreeData.TAttach(LeadingJetEta,badMuonInJet)
cutTreeData.TAttach(badMuonInJet,oddJet)
cutTreeData.TAttach(oddJet,LeadingJetCut)
cutTreeData.TAttach(LeadingJetCut,secondJetET)
cutTreeData.TAttach(secondJetET,VertexPtOverHT)
cutTreeData.TAttach(VertexPtOverHT,htCut250)

#FOR HT > 250Gev Plot
cutTreeData.TAttach(htCut250,DiJet3)
cutTreeData.TAttach(htCut250,NJet3)
cutTreeData.TAttach(DiJet3,HadStandardAll)
cutTreeData.TAttach(NJet3,nHadStandardAll)
#END HT 250GEV Plot
#Begin MHT/MET plot inthe low region.
cutTreeData.TAttach(htCut250,DeadEcalCutData)
cutTreeData.TAttach(DeadEcalCutData,LessThan350)
cutTreeData.TAttach(LessThan350,DiJet0)
cutTreeData.TAttach(LessThan350,NJet0)
cutTreeData.TAttach(DiJet0,HadStandard250_350)
cutTreeData.TAttach(NJet0,nHadStandard250_350)

#for Vertext multiplicity plot at 300geV
# cutTreeData.TAttach(htCut250,htCut300)
# cutTreeData.TAttach(htCut300,NVertexJets)
# cutTreeData.TAttach(htCut300,DiVertexJets)
# cutTreeData.TAttach(DiVertexJets,HadStandard300)
#cutTreeData.TAttach(NVertexJets,nHadStandard300)


cutTreeData.TAttach(DeadEcalCutData,htCut350)
# cutTreeData.TAttach(htCut350,dalitz_plots_350)
cutTreeData.TAttach(htCut250,htCut350GeV)
cutTreeData.TAttach(htCut350GeV,DiJet2)
cutTreeData.TAttach(htCut350GeV,NJet2)
#cutTreeData.TAttach(htCut350,alphaT0)
cutTreeData.TAttach(DiJet2,HadStandard350)
cutTreeData.TAttach(NJet2,nHadStandard350)

#Here be plots for baby jet MHT and MHT/MET in the signal region after dead ecal cuts
cutTreeData.TAttach(htCut350,DiJet4)
cutTreeData.TAttach(DiJet4,HadStandard350_after_DeadEcal)
cutTreeData.TAttach(htCut350,NJet4)
cutTreeData.TAttach(htCut350,alphaT1)
# cutTreeData.TAttach(alphaT1,HadStandard_2)
cutTreeData.TAttach(NJet4,nHadStandard350_after_DeadEcal)


#Here be plots after all the cuts!!
cutTreeData.TAttach(htCut350,MHT_METCut)
#cutTreeData.TAttach(htCut350GeV,alphaT2)
#cutTreeData.TAttach(alphaT2,HadStandard_3)
cutTreeData.TAttach(MHT_METCut,NJet5)
cutTreeData.TAttach(MHT_METCut,DiJet5)
cutTreeData.TAttach(MHT_METCut, alphat)
cutTreeData.TAttach(alphat,eventDump)
cutTreeData.TAttach(NJet5,nHadStandardAllCuts)
cutTreeData.TAttach(DiJet5,HadStandardAllCuts)


#Second MC!


cutTreeMC = Tree("MC")
cutTreeMC.Attach(selection)
cutTreeMC.TAttach(selection,oddMuon)
cutTreeMC.TAttach(oddMuon,oddElectron)
cutTreeMC.TAttach(oddElectron,oddPhoton)
cutTreeMC.TAttach(oddPhoton,numComLeptons)
cutTreeMC.TAttach(numComLeptons,numComPhotons)
cutTreeMC.TAttach(numComPhotons,LeadingJetEta)
cutTreeMC.TAttach(LeadingJetEta,badMuonInJet)
cutTreeMC.TAttach(badMuonInJet,oddJet)
cutTreeMC.TAttach(oddJet,LeadingJetCut)
cutTreeMC.TAttach(LeadingJetCut,secondJetET)
##########DiJet Studies
cutTreeMC.TAttach(secondJetET,VertexPtOverHT)
cutTreeMC.TAttach(VertexPtOverHT,htCut250)

#FOR HT > 250Gev Plot
cutTreeMC.TAttach(htCut250,DiJet3)
cutTreeMC.TAttach(htCut250,NJet3)
cutTreeMC.TAttach(DiJet3,HadStandardAll)
cutTreeMC.TAttach(NJet3,nHadStandardAll)
#END HT 250GEV Plot
#Begin MHT/MET plot inthe low region.
cutTreeMC.TAttach(htCut250,DeadEcalCutMC)
cutTreeMC.TAttach(DeadEcalCutMC,LessThan350)
cutTreeMC.TAttach(LessThan350,DiJet0)
cutTreeMC.TAttach(LessThan350,NJet0)
cutTreeMC.TAttach(DiJet0,HadStandard250_350)
cutTreeMC.TAttach(NJet0,nHadStandard250_350)

#for Vertext multiplicity plot at 300geV
# cutTreeMC.TAttach(htCut250,htCut300)
# cutTreeMC.TAttach(htCut300,NVertexJets)
# cutTreeMC.TAttach(htCut300,DiVertexJets)
# cutTreeMC.TAttach(DiVertexJets,HadStandard300)
# cutTreeMC.TAttach(NVertexJets,nHadStandard300)


cutTreeMC.TAttach(DeadEcalCutMC,htCut350)
# cutTreeMC.TAttach(htCut350,dalitz_plots_350)
cutTreeMC.TAttach(htCut250,htCut350GeV)
cutTreeMC.TAttach(htCut350GeV,DiJet2)
cutTreeMC.TAttach(htCut350GeV,NJet2)
# cutTreeMC.TAttach(htCut350,alphaT0)
cutTreeMC.TAttach(DiJet2,HadStandard350)
cutTreeMC.TAttach(NJet2,nHadStandard350)

#Here be plots for baby jet MHT and MHT/MET in the signal region after dead ecal cuts
cutTreeMC.TAttach(htCut350,DiJet4)
cutTreeMC.TAttach(DiJet4,HadStandard350_after_DeadEcal)
cutTreeMC.TAttach(htCut350,NJet4)
cutTreeMC.TAttach(htCut350,alphaT1)
# cutTreeMC.TAttach(alphaT1,HadStandard_2)
cutTreeMC.TAttach(NJet4,nHadStandard350_after_DeadEcal)


#Here be plots after all the cuts!!
cutTreeMC.TAttach(htCut350,MHT_METCut)
cutTreeMC.TAttach(htCut350GeV,alphaT2)
# cutTreeMC.TAttach(alphaT2,HadStandard_3)
cutTreeMC.TAttach(MHT_METCut,NJet5)
cutTreeMC.TAttach(MHT_METCut,DiJet5)
cutTreeMC.TAttach(NJet5,nHadStandardAllCuts)
cutTreeMC.TAttach(DiJet5,HadStandardAllCuts)

