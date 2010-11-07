#!/usr/bin/env python

'''Created by Bryn Mathias
bryn.mathias@cern.ch
'''
import errno

import ROOT as Root
import math
from time import strftime
import os, commands
from PlottingFunctions import *
Root.gROOT.SetBatch(True) # suppress the creation of canvases on the screen.. much much faster if over a remote connection
Root.gROOT.SetStyle("Plain") #To set plain bkgds for slides
Root.gStyle.SetTitleBorderSize(0)
Root.gStyle.SetCanvasBorderMode(0)
Root.gStyle.SetCanvasColor(0)#Sets canvas colour white
Root.gStyle.SetOptStat(1110)#set no title on Stat box
Root.gStyle.SetLabelOffset(0.001)
Root.gStyle.SetLabelSize(0.05)
Root.gStyle.SetLabelSize(0.05,"Y")#Y axis
Root.gStyle.SetTitleSize(0.06)
Root.gStyle.SetTitleW(0.7)
Root.gStyle.SetTitleH(0.07)
Root.gStyle.SetOptTitle(1)
Root.gStyle.SetOptStat(0)
Root.gStyle.SetAxisColor(1, "XYZ");
Root.gStyle.SetStripDecimals(Root.kTRUE);
Root.gStyle.SetTickLength(0.03, "XYZ");
Root.gStyle.SetNdivisions(510, "XYZ");
Root.gStyle.SetPadTickX(1);
Root.gStyle.SetPadTickY(1);
Root.gStyle.SetLabelColor(1, "XYZ");
Root.gStyle.SetLabelFont(42, "XYZ");
Root.gStyle.SetLabelOffset(0.007, "XYZ");
Root.gStyle.SetLabelSize(0.05, "XYZ");
Root.gStyle.SetHatchesLineWidth(3)
# Root.gStyle.SetPaperSize(20,20)

def ensure_dir(path):
    try:
      os.makedirs(path)
    except OSError as exc: # Python >2.5
      if exc.errno == errno.EEXIST:
        pass
      else: raise

#Please enter the integrated lumi for the plots here:
algo = "Calo"
intlumi =35.0 #4.433 #inv pico barns
# intlumi = 2.947
#intlumi = 7.0
print "The Integrated Luminosity your plots are being scaled to is: ", intlumi , "pb^{-1}"
#Set your output file here
# outputfile = "../pdfs/PlotsForPO38WithTPs/"

# outputfile = "../pdfs/JESFixedTest/"

outputfile = "../pdfs/21pbTestPlots/"

ensure_dir(outputfile)


print "you are outputting to: " ,outputfile
#SetWhere your results from your analysis are
resultsDir = "~/results/" #"/vols/cms02/bm409/SUSYv2/hadronic/results/"+algo

print "you are using the " , algo , " Jet collection"
#close list is a global variable that has the file name appended to it so at the end of each hist loop the open files are closed. It is cleared each time a new hist is called.

def GetHist(DataSetName,col,norm,Legend):
    a = Root.TFile.Open(DataSetName) #open the file
    closeList.append(a) # append the file to the close list
    b = a.Get(DirKeys[dir].GetTitle()) #open the directory in the root file
    Hist = b.Get(hist) # get your histogram by name
    if Hist == None : Hist = Root.TH1D()
    if Legend != 0:
      leg.AddEntry(Hist,Legend,"LP") # add a legend entry
    Hist.SetLineWidth(3)
    Hist.SetLineColor(col) #set colour
    Hist.SetBinContent(Hist.GetNbinsX() ,Hist.GetBinContent(Hist.GetNbinsX())+Hist.GetBinContent(Hist.GetNbinsX()+1))
    Hist.SetBinError(Hist.GetNbinsX() ,math.sqrt((Hist.GetBinError(Hist.GetNbinsX()))**2 + (Hist.GetBinError(Hist.GetNbinsX()+1))**2))
    Hist.SetBinContent(Hist.GetNbinsX()+1,0)
    if norm != 0:
       Hist.Scale(intlumi/100.) #if not data normilse to the data by lumi, MC is by default weighted to 100pb-1, if you have changed this change here!
    return Hist


def GetHistFromFolder(DataSetName,folder,col,norm,Legend):
    a = Root.TFile.Open(DataSetName) #open the file
    closeList.append(a) # append the file to the close list
    b = a.Get(folder) #open the directory in the root file
    Hist = b.Get(hist) # get your histogram by name
    if Hist == None : Hist = Root.TH1D()
    if Legend != 0:
      leg.AddEntry(Hist,Legend,"LP") # add a legend entry
    Hist.SetLineWidth(3)
    Hist.SetLineColor(col) #set colour
    Hist.SetBinContent(Hist.GetNbinsX() ,Hist.GetBinContent(Hist.GetNbinsX())+Hist.GetBinContent(Hist.GetNbinsX()+1))
    Hist.SetBinError(Hist.GetNbinsX() ,math.sqrt((Hist.GetBinError(Hist.GetNbinsX()))**2 + (Hist.GetBinError(Hist.GetNbinsX()+1))**2))
    Hist.SetBinContent(Hist.GetNbinsX()+1,0)
    if norm != 0:
       Hist.Scale(intlumi/100.) #if not data normilse to the data by lumi, MC is by default weighted to 100pb-1, if you have changed this change here!
    return Hist


#   /MinBias_TuneD6T_7TeV-pythia6/Spring10-START3X_V26B-v1/GEN-SIM-RECO
#   /MinBias_TuneD6T_7TeV-pythia6/Fall10-START38_V9_preproduction-v1/GEN-SIM-RECODEBUG


def RatioPlot(Data,BackGround):
  """docstring for RatioPlot"""
  bottom = BackGround.Clone()
  top = Data.Clone()
  top.GetYaxis().SetTitle("data / sim")
  top.Divide(bottom)

  top.SetTitleSize(0.1, "XYZ");
  top.SetTitleOffset(0.55, "X");
  top.SetTitleOffset(0.3, "Y");
  top.SetLabelSize(0.06,"XY")

  # top.SetTitleXOffset(0.9);
  # top.SetTitleYOffset(0.9);
  top.GetXaxis().SetRangeUser(MinX,MaxX+0.1)
  top.GetYaxis().SetRangeUser(0.,2.0)
  return top

def UnityLine (Data):
  """docstring for RatioPlot"""
  # top = Data.Clone()  #Draw a line though the perfectly matching point
  # unity = Root.TBox(top.GetXaxis().GetBinUpEdge(top.GetXaxis().GetFirst()), 0.89,top.GetXaxis().GetBinUpEdge(top.GetNbinsX()), 1.11);

  unity = Root.TBox(Data.GetBinLowEdge(Data.GetXaxis().GetFirst()), 0.89,Data.GetBinLowEdge(Data.GetXaxis().GetLast())+Data.GetBinWidth(Data.GetXaxis().GetLast()), 1.11)
  unity.SetLineWidth(2);
  unity.SetLineColor(2);
  unity.SetFillColor(2);
  unity.SetFillStyle(3002)
  # unity.Draw();
  return unity
  pass


def PassingCutNumbers(Hist, name ,lowerBound):
  lowbin = Hist.FindBin(lowerBound)
  errorVal = Root.Double(0)
  passingCut = Hist.IntegralAndError(lowbin, Hist.GetNbinsX(), errorVal)
  textLine = "Sample = " + DirKeys[dir].GetTitle()  + "   " + str(Hist.GetName()) + "     " + name +  " , Number passing cut of   " + str(lowerBound) + " is " + "       " + str(passingCut)+ " +/- " + str(errorVal) + "\n"
  CutNumbers.write(textLine)


time = strftime("%Y_%m_%d")
print time

#A file to open and scan for histograms inside directories
RootFileList = [resultsDir+"/AK5"+algo+"_Jets.root"]
# RootFileList = [resultsDir+"/AK5Calo_ExtraJets.root"]

CutNumbers = open(outputfile+"CutTable.txt",'w')

Webpage = open(outputfile+"StandardPlots"+time+".html",'w')

AllPlots = ""
ControlRegonPlots1 = ""
ControlRegonPlots2 = ""
SignalRegonPlots = ""
ControlRegonPlotsAfterAT1 = ""
ControlRegonPlotsAfterAT2 = ""
SignalRegonPlotsAfterAT = ""
SignalRegonPlotsAfterATandDeadEcal = ""
SignalRegonPlotsAfterDeadEcal = ""
SignalRegonPlotsAfterAllCuts = ""
SignalRegonPlotsAfterAtAllCuts = ""
temp = Root.TFile.Open(RootFileList[0])
DirKeys = temp.GetListOfKeys()

HistKeys = [ (dir.ReadObj()).GetListOfKeys() for dir in DirKeys]
HistNames = [ [k.GetName() for k in D] for D in HistKeys]
#Loops though all the histograms that have been read from the first input file, this is done by histogram name
# print HistNames
closeList = []
for dir in range(0,len(DirKeys)):
  # print DirKeys[dir].GetTitle()
  for hist in HistNames[dir]:
    Draw = False
    if "CaloMET_after_alphaT_all" in hist: Draw = True
    if "EffectiveMass_after_alphaT_55_all" in hist: Draw = True
    if "HT_after_alphaT_all" in hist: Draw = True
    if "BiasedDeltaPhi_after_alphaT_55_all" in hist: Draw = True
    if "CosDetlaPhi_MHT_MHTBaby__all" in hist: Draw = True
    if "DPhi_MHT_MHTbaby_AfterAlphaT__all" in hist: Draw = True
    if "BabyJetMHT_all" in hist: Draw = True
    if "BabyJetMHTafterMetCut_all" in hist: Draw = True
    if "CaloMET_all" in hist: Draw = True
    if "MHTovMET_all" in hist: Draw = True
    if "MHTovMET_afterAlphaT_all" in hist: Draw = True
    if "Mt2_LeadingJets_all" in hist: Draw = True
    if "Mt2_all" in hist: Draw = True
    if "AlphaT_all" in hist: Draw = True
    if "AlphaT_Zoomed_all" in hist: Draw = True
    if "HT_all" in hist: Draw = True
    if "EffectiveMass_all" in hist: Draw = True
    if "BiasedDeltaPhi_all" in hist: Draw = True
    if "MHToverHT_all" in hist: Draw = True
    if "MHT_all" in hist: Draw = True
    if "JetMultiplicityAfterAlphaT_all" in hist: Draw = True
    if "JetMultiplicity_all" in hist: Draw = True
    if "JetEta_" in hist: Draw = True
    if "JetPt_" in hist: Draw = True
    if "fem__all" in hist: Draw = True
    # if DirKeys[dir].GetTitle()[0] != "n" and "_2" in hist: Draw = True
    # if "__1" in hist: Draw = True
    # if "__2" in hist: Draw = True
    # if "__3" in hist: Draw = True
    # if "__15" in hist: Draw = True
    if not Draw : continue
    if "/" in hist : continue
    leg = Root.TLegend(0.55, 0.4, 0.95, 0.85)
    leg.SetShadowColor(0)
    leg.SetBorderSize(0)
    leg.SetFillStyle(4100)
    leg.SetFillColor(0)
    leg.SetLineColor(0)
    if "PFMetVsMHT" in hist: continue #This is the 2d Histogram in the file, dont want to plot this!
    col=2
    fileno = 1
    MaxY = 1.0#These three are the low terms for the axis and are reset for each histogram see below
    MaxX = 1.0# to see the numbers set by the functions that are defined in the beginning of the program
    MinX = 1000.#
    c1 = Root.TCanvas("canvas"+hist,"canname"+hist,1200,1200)
    #Make two pads, one small for the ratio plot and one large for the plot its self
    mainPad = Root.TPad("","",0.01,0.25,0.99,0.99);
    mainPad.SetNumber(1);
    mainPad.Draw();
    ratioPad = Root.TPad("","",0.01,0.05,0.99,0.26);
    ratioPad.SetBottomMargin(0.32);
    ratioPad.SetNumber(2);

    ratioPad.Draw();
    c1.cd(1)
    #make your histograms form each file, read in the files you want below
    # GetHist("RootFile",Colour, scale to lumi 0=false anything else = true, Legend entry)
    #NB the order in which you book the histos is the order in which they appear in the legend

    Data = GetHist(resultsDir+"/AK5"+algo+"_Jets.root",1,0,"Data")
    # Data.Add(GetHistFromFolder(resultsDir+"/AK5"+algo+"_Jets.root","300_350Gevcombined",1,0,0))
    # Data.Add(GetHist(resultsDir+"/AK5Calo_ExtraJets.root",1,0,"Data"))
    if str(type(Data)) != "<class '__main__.TH1D'>" : continue
    QCD = GetHist(resultsDir+"/NoSmear/AK5"+algo+"_QCD_AllPtBins_7TeV_Pythia.root",Root.kRed-7,1,"QCD")
    # QCD.Add(GetHistFromFolder(resultsDir+"/AK5"+algo+"_QCD_AllPtBins_7TeV_Pythia.root","300_350Gevcombined",1,1,0))
    Data.SetMarkerStyle(20)
    Data.SetLineWidth(3)
    Data.SetLineColor(1)
    Data.SetFillColor(1)
    ZJets  = GetHist(resultsDir+"/NoSmear/AK5"+algo+"_zjets_madgraph_5.root",Root.kTeal-7,1,0)
    # ZJets.Add(GetHistFromFolder(resultsDir+"/AK5"+algo+"_zjets_madgraph_4.root","300_350Gevcombined",Root.kTeal-7,1,0))
    Zinv = GetHist(resultsDir+"/NoSmear/AK5"+algo+"_Zinvisible_jets.root",91,1,0)
    # Zinv.Add(GetHistFromFolder(resultsDir+"/AK5"+algo+"_Zinvisible_jets_3.root","300_350Gevcombined",Root.kTeal-7,1,0))
    Ztotal = ZJets.Clone()
    Ztotal.Add(Zinv)
    Ztotal.SetLineColor(Root.kTeal-7)
    leg.AddEntry(Ztotal,"Z + Jets","L")

    WJets = GetHist(resultsDir+"/NoSmear/AK5"+algo+"_wjets_madgraph_vols_1.root",Root.kPink+7,1,"W + Jets")
    # WJets.Add(GetHistFromFolder(resultsDir+"/AK5"+algo+"_wjets_madgraph_vols_1.root","300_350Gevcombined",Root.kTeal-7,1,0))
    ttbar = GetHist(resultsDir+"/NoSmear/AK5"+algo+"_ttbarTauola_2.root",Root.kBlue+1,1,"TTBar")
    # ttbar.Add(GetHistFromFolder(resultsDir+"/AK5"+algo+"_ttbarTauola_2.root","300_350Gevcombined",Root.kTeal-7,1,0))
    LM0 = GetHist(resultsDir+"/NoSmear/AK5"+algo+"_LM0_6.root",2,1,"LM0")
    # LM0.Add(GetHistFromFolder(resultsDir+"/AK5"+algo+"_LM0_5.root","300_350Gevcombined",Root.kTeal-7,1,0))
    LM1 = GetHist(resultsDir+"/NoSmear/AK5"+algo+"_LM1_7.root",Root.kRed+3,1,"LM1")
    # LM1.Add(GetHistFromFolder(resultsDir+"/AK5"+algo+"_LM1_6.root","300_350Gevcombined",Root.kTeal-7,1,0))

    QCD.SetLineWidth(3)

    if "EffectiveMass_all" == hist or "EffectiveMass_after_alphaT_55_all" == hist:
          leg.RecursiveRemove(Ztotal)
          leg.RecursiveRemove(WJets)
          leg.RecursiveRemove(ttbar)
          # LM2 = GetHist(resultsDir+"/AK5"+algo+"_LM2_10.root",3,1,"LM2")
          # LM3 = GetHist(resultsDir+"/AK5"+algo+"_LM3_11.root",4,1,"LM3")
          # LM4 = GetHist(resultsDir+"/AK5"+algo+"_LM4_12.root",5,1,"LM4")
          # LM5 = GetHist(resultsDir+"/AK5"+algo+"_LM5_13.root",6,1,"LM5")
          DrawSM = True

    if "BiasedDeltaPhi_all" == hist or "BiasedDeltaPhi_after_alphaT_all" == hist:
      Data.Rebin(2)
      QCD.Rebin(2)
      QCD.SetFillColor(Root.kRed-7)
      ZJets.Rebin(2)
      Zinv.Rebin(2)
      ttbar.Rebin(2)
      LM0.Rebin(2)
      LM1.Rebin(2)



    #Make a histogram of the sum of all the SM backgrounds
    Total = QCD.Clone()
    Total.Add(Zinv)
    Total.Add(ZJets)
    Total.Add(WJets)
    Total.Add(ttbar)


    Pythia8 = False

    if hist == "MHTovMET_afterAlphaT_all" or hist == "BabyJetMHT_all" or hist == "BiasedDeltaPhi_after_alphaT_55_all" or hist == "BiasedDeltaPhi_all" :
      Pythia8=GetHist(resultsDir+"/NoSmear/AK5"+algo+"_QCD_Pythia8.root",3,1,"QCD Pythia 8")
      # Pythia8.Add(GetHistFromFolder(resultsDir+"/AK5"+algo+"_QCD_Pythia8.root","300_350Gevcombined",Root.kTeal-7,1,0))


    # Systematics
    ScaledUpQCD = GetHist(resultsDir+"/JESplus/AK5"+algo+"_QCD_AllPtBins_7TeV_Pythia.root",Root.kTeal-7,1,0)
    ScaledUpW = GetHist(resultsDir+"/JESplus/AK5"+algo+"_wjets_madgraph_vols_1.root",Root.kTeal-7,1,0)
    ScaledUpZj = GetHist(resultsDir+"/JESplus/AK5"+algo+"_Zinvisible_jets.root",Root.kTeal-7,1,0)
    ScaledUpJi = GetHist(resultsDir+"/JESplus/AK5"+algo+"_zjets_madgraph_5.root",Root.kTeal-7,1,0)
    ScaledUptt = GetHist(resultsDir+"/JESplus/AK5"+algo+"_ttbarTauola_2.root",Root.kTeal-7,1,0)

    ScaledUp = ScaledUpQCD.Clone()
    ScaledUp.Add(ScaledUpW)
    ScaledUp.Add(ScaledUpZj)
    ScaledUp.Add(ScaledUpJi)
    ScaledUp.Add(ScaledUptt)
    ScaledDownQCD =GetHist(resultsDir+"/JESminus/AK5"+algo+"_QCD_AllPtBins_7TeV_Pythia.root",Root.kTeal-7,1,0)
    ScaledDownW =  GetHist(resultsDir+"/JESminus/AK5"+algo+"_wjets_madgraph_vols_1.root",Root.kTeal-7,1,0)
    ScaledDownZj = GetHist(resultsDir+"/JESminus/AK5"+algo+"_Zinvisible_jets.root",Root.kTeal-7,1,0)
    ScaledDownJi = GetHist(resultsDir+"/JESminus/AK5"+algo+"_zjets_madgraph_5.root",Root.kTeal-7,1,0)
    ScaledDowntt = GetHist(resultsDir+"/JESminus/AK5"+algo+"_ttbarTauola_2.root",Root.kTeal-7,1,0)
    ScaledDown =   ScaledDownQCD.Clone()
    ScaledDown.Add(ScaledDownW)
    ScaledDown.Add(ScaledDownZj)
    ScaledDown.Add(ScaledDownJi)
    ScaledDown.Add(ScaledDowntt)

    SmearedQCD =GetHist(resultsDir+"/Smear/AK5"+algo+"_QCD_AllPtBins_7TeV_Pythia.root",Root.kTeal-7,1,0)
    SmearedW =  GetHist(resultsDir+"/Smear/AK5"+algo+"_wjets_madgraph_vols_1.root",Root.kTeal-7,1,0)
    SmearedZj = GetHist(resultsDir+"/Smear/AK5"+algo+"_Zinvisible_jets.root",Root.kTeal-7,1,0)
    SmearedJi = GetHist(resultsDir+"/Smear/AK5"+algo+"_zjets_madgraph_5.root",Root.kTeal-7,1,0)
    Smearedtt = GetHist(resultsDir+"/Smear/AK5"+algo+"_ttbarTauola_2.root",Root.kTeal-7,1,0)
    Smeared =   SmearedQCD.Clone()
    Smeared.Add(SmearedW)
    Smeared.Add(SmearedZj)
    Smeared.Add(SmearedJi)
    Smeared.Add(Smearedtt)

    blank1 = Root.TH1D()
    blank2 = Root.TH2D()

    # AsymErrors = Systematics(Total,Total,Total,Smeared ,"TGraph")
    AsymErrors = Systematics(Total,ScaledUp,ScaledDown,Smeared ,"TGraph")
    AsymErrors.SetLineColor(Root.kAzure+2)#kTeal+3)
    AsymErrors.SetFillColor(Root.kAzure+2)#kTeal+3)
    AsymErrors.SetLineWidth(5)

    AsymErrors.SetFillStyle(3245)#(3245)

    SMBackGrounds = Systematics(Total,ScaledUp,ScaledDown,Smeared,"TH1")
    if SMBackGrounds.Integral(0,SMBackGrounds.GetNbinsX()) == 0 : Draw = False


    # if "AlphaT_all" == hist :
    #   PassingCutNumbers(Data, "Data"            ,0.55)
    #   # PassingCutNumbers(SmearedJets, "Data_SMEARED!!!"  ,0.55)
    #   PassingCutNumbers(Total, "Total Background Stat" ,0.55)
    #   PassingCutNumbers(SMBackGrounds, "Total Background Systematic" ,0.55)
    #   PassingCutNumbers(ttbar, "TTBbar"         ,0.55)
    #   PassingCutNumbers(ZJets, "ZJets"          ,0.55)
    #   PassingCutNumbers(WJets, "WJETS"          ,0.55)
    #   PassingCutNumbers(QCD, "QCD"              ,0.55)
    #   PassingCutNumbers(Zinv, "Zinv"            ,0.55)
    #   PassingCutNumbers(LM0, "LM0"              ,0.55)
    #   PassingCutNumbers(LM1, "LM1"              ,0.55)
    #
    #
    # if "HT_all" == hist :
    #   PassingCutNumbers(Data, "Data"    ,250.)
    #   PassingCutNumbers(Total, "Total Background Stat" ,250.)
    #   PassingCutNumbers(SMBackGrounds, "Total Background Systematic" ,250.)
    #   PassingCutNumbers(LM0, "LM0"      ,250.)
    #   PassingCutNumbers(LM1, "LM1"      ,250.)
    #   PassingCutNumbers(Data, "JetMET"  ,250.)
    #   PassingCutNumbers(ttbar, "TTBbar" ,250.)
    #   PassingCutNumbers(ZJets, "ZJets"  ,250.)
    #   PassingCutNumbers(WJets, "WJETS"  ,250.)
    #   PassingCutNumbers(QCD, "QCD"      ,250.)
    #   PassingCutNumbers(Zinv, "Zinv"    ,250.)
    #
    # if "MHT_all" == hist :
    #   PassingCutNumbers(Data, "Data"                                 ,140.)
    #   PassingCutNumbers(Total, "Total Background Stat"               ,140.)
    #   PassingCutNumbers(SMBackGrounds, "Total Background Systematic" ,140.)
    #   PassingCutNumbers(LM0, "LM0"                                   ,140.)
    #   PassingCutNumbers(LM1, "LM1"                                   ,140.)
    #   PassingCutNumbers(Data, "JetMET"                               ,140.)
    #   PassingCutNumbers(ttbar, "TTBbar"                              ,140.)
    #   PassingCutNumbers(ZJets, "ZJets"                               ,140.)
    #   PassingCutNumbers(WJets, "WJETS"                               ,140.)
    #   PassingCutNumbers(QCD, "QCD"                                   ,140.)
    #   PassingCutNumbers(Zinv, "Zinv"                                 ,140.)



    hcen=Total.Clone()
    herr=Total.Clone()
    herr.SetLineColor(Root.kTeal+3)
    herr.SetMarkerColor(Root.kAzure+6)
    herr.SetFillColor(Root.kAzure+6)
    Total.SetFillColor(Root.kAzure+6)
    herr.SetLineWidth(3)
    Total.SetLineWidth(3)

    # Total.SetFillColor(Root.kAzure+2)
    Total.SetLineColor(Root.kBlue+2)
    # Total.SetFillStyle(3245)
    hcen.SetFillColor(0)
    hcen.SetMarkerColor(Root.kTeal+3)
    hcen.SetLineColor(Root.kTeal+3)
    hcen.SetLineWidth(3)


    DrawSM = True
    #Defind the ranges of the histogram for the two highest histograms ie the data and the total

    MinY = 0.05
    if "AlphaT" in hist: MaxXOrig = Data.GetNbinsX()*Data.GetBinWidth(1)
    if HistogramMinX(Total) < MinX :
       MinX = HistogramMinX(Total)
    if HistogramMaxX(Total) > MaxX :
       MaxX = HistogramMaxX(Total)
    if HistogramMaxY(Total) > MaxY :
       MaxY = HistogramMaxY(Total)

    if HistogramMinX(Data) < MinX :
       MinX = HistogramMinX(Data)
    if HistogramMaxX(Data) > MaxX :
       MaxX = HistogramMaxX(Data)
    if HistogramMaxY(Data) > MaxY :
       MaxY = HistogramMaxY(Data)
    if "Mt2" in hist: MaxX = 500.
    if "AlphaT" in hist: MaxX = MaxXOrig
    if "Multiplicity" in hist:
      MaxX = 12.
      MinX = 1.
    if hist == "BiasedDeltaPhi_after_alphaT_55_all" or hist == "BiasedDeltaPhi_all":
      MinX = 0.
      MaxX = 3.2
      DrawSM = False
      leg2 = Root.TLegend(0.55, 0.4, 0.95, 0.85)
      leg2.SetShadowColor(0)
      leg2.SetBorderSize(0)
      leg2.SetFillStyle(4100)
      leg2.SetFillColor(0)
      leg2.SetLineColor(0)
      leg2.AddEntry(Data, "Data", "lp")
      leg2.AddEntry(QCD, "QCD Pythia 6", "lp")
      QCD.SetFillStyle(1001)
      QCD.SetFillColor(Root.kRed-7)
      Pythia8.SetFillStyle(1001)
      Pythia8.SetFillColor(3)
      leg2.AddEntry(Pythia8 , "QCD Pythia 8","lp")
      leg2.AddEntry(Ztotal, "Z + Jets", "lp")
      leg2.AddEntry(WJets, "W + Jets", "lp")
      leg2.AddEntry(ttbar, "TTBar", "lp")
      leg2.AddEntry(LM0, "LM0", "lp")
      leg2.AddEntry(LM1, "LM1", "lp")
    if  "EffectiveMass" in hist:
      MinX = 400.
      MaxX = 1800.
      MinY = 0.01
      DrawSM = False


      drawBackgrounds = False

    if "MHTovMET_afterAlphaT_all" in hist:
      MaxX = 5.
      MinX = 0.0
      DrawSM = False
      MaxY = 50.
      leg2 = Root.TLegend(0.55, 0.4, 0.95, 0.85)
      Data.Rebin(2)
      QCD.Rebin(2)
      Pythia8.Rebin(2)
      ZJets.Rebin(2)
      Zinv.Rebin(2)
      ttbar.Rebin(2)
      LM0.Rebin(2)
      LM1.Rebin(2)
      QCD.SetFillStyle(1001)
      QCD.SetFillColor(Root.kRed-7)
      Pythia8.SetFillStyle(1001)
      Pythia8.SetFillColor(3)
      leg2.SetShadowColor(0)
      leg2.SetBorderSize(0)
      leg2.SetFillStyle(4100)
      leg2.SetFillColor(0)
      leg2.SetLineColor(0)
      leg2.AddEntry(Data, "Data", "lp")
      leg2.AddEntry(QCD, "QCD Pythia 6", "lp")
      leg2.AddEntry(Pythia8 , "QCD Pythia 8","lp")
      leg2.AddEntry(Ztotal, "Z + Jets", "lp")
      leg2.AddEntry(WJets, "W + Jets", "lp")
      leg2.AddEntry(ttbar, "TTBar", "lp")
      leg2.AddEntry(LM0, "LM0", "lp")
      leg2.AddEntry(LM1, "LM1", "lp")



    if "BabyJetMHT_all" in hist:
      DrawSM = False
      MaxX= 240.
      MinX = 0.
      leg2 = Root.TLegend(0.55, 0.4, 0.95, 0.85)
      leg2.SetShadowColor(0)
      leg2.SetBorderSize(0)
      leg2.SetFillStyle(4100)
      leg2.SetFillColor(0)
      leg2.SetLineColor(0)
      leg2.AddEntry(Data, "Data", "lp")
      leg2.AddEntry(QCD, "QCD Pythia 6", "lp")
      leg2.AddEntry(Pythia8 , "QCD Pythia 8","lp")
      leg2.AddEntry(Ztotal, "Z + Jets", "lp")
      leg2.AddEntry(WJets, "W + Jets", "lp")
      leg2.AddEntry(ttbar, "TTBar", "lp")
      leg2.AddEntry(LM0, "LM0", "lp")
      leg2.AddEntry(LM1, "LM1", "lp")
      QCD.GetXaxis().SetTitle("MHT (GeV) [10 < p_{T}< 50 GeV]")
      Total.GetXaxis().SetTitle("MHT (GeV) [10 < p_{T}< 50 GeV]")
      Data.GetXaxis().SetTitle("MHT (GeV) [10 < p_{T}< 50 GeV]")

    Total.GetXaxis().SetRangeUser(MinX,MaxX)
    # print "Range of Total" , MinX , MaxX
    AsymErrors.GetYaxis().SetRangeUser(MinY,MaxY*5.)
    Total.GetYaxis().SetRangeUser(MinY,MaxY*5.)
    if Pythia8: Pythia8.GetXaxis().SetRangeUser(MinX,MaxX)
    if Pythia8: Pythia8.GetYaxis().SetRangeUser(MinY,MaxY*5.)
    QCD.GetYaxis().SetRangeUser(MinY,MaxY*5.)
    QCD.GetXaxis().SetRangeUser(MinX,MaxX)

    #Draw order is important!


    if DrawSM:
      leg.AddEntry(Total,"Standard Model","Lf")
      Total.Draw("9hist")
      AsymErrors.Draw("2same")
      QCD.Draw("9SAMEhist")
    # Total.Draw("9histsame")

    if DrawSM == False:
      if Pythia8:
        Pythia8.Draw("9hist")
        QCD.Draw("9histsame")
      else:
        Total.Draw("9hist")

    drawBackgrounds = True
    if hist == "MHTovMET_afterAlphaT_all"  or hist == "BabyJetMHT_all" or hist =="BiasedDeltaPhi_after_alphaT_55_all":
      Pythia8.Draw("9hist")
      QCD.Draw("9histsame")
    if "EffectiveMass" in hist:
      # LM2.Draw("9SAMEh")
      # LM3.Draw("9SAMEh")
      # LM4.Draw("9SAMEh")
      # LM5.Draw("9SAMEh")
      drawBackgrounds = False
    if drawBackgrounds:

      Ztotal.Draw("9Sameh")
      # Zinv.Draw("9SAMEh")
      WJets.Draw("9SAMEh")
      ttbar.Draw("9SAMEh")
      if "EffectiveMass" in hist:
          leg.RecursiveRemove(Ztotal)
          leg.RecursiveRemove(WJets)
          leg.RecursiveRemove(ttbar)
    LM0.Draw("9SAMEh")
    LM1.Draw("9SAMEh")
    #Draw Data last to get the points above everything else
    Data.Draw("9SAMEP")

    #Draw Text for histogram titile and for lumi
    prelim = Root.TLatex(0.4,0.75,"#scale[0.8]{CMS preliminary 2010}");
    lumi = Root.TLatex(0.4,.9,"#scale[0.8]{#int L dt = " + str(intlumi) + "pb^{-1}, #sqrt{s} = 7 TeV}");
    prelim.SetNDC()
    lumi.SetNDC()

    # prelim.Draw()
    lumi.Draw()
    title = Root.TLatex(0.05,0.95,(DirKeys[dir].GetTitle())+"_"+hist[0:-4])
    title.SetNDC()
    # title.Draw()
    lumi.Draw("Same")

    c1.cd(1).Update()

    if "EffectiveMass" not in hist and "MHTovMET_afterAlphaT_all" not in hist and "BiasedDeltaPhi_after_alphaT_55_all" not in hist and "BabyJetMHT_all" not in hist and "BiasedDeltaPhi_all" not in hist: leg.Draw()
    if "EffectiveMass" in hist:
      leg2 = Root.TLegend(0.55, 0.4, 0.95, 0.85)
      leg2.SetShadowColor(0)
      leg2.SetBorderSize(0)
      leg2.SetFillStyle(4100)
      leg2.SetFillColor(0)
      leg2.SetLineColor(0)
      leg2.AddEntry(Data, "Data", "lp")
      # leg2.AddEntry(QCD, "QCD", "lp")
      leg2.AddEntry(Total , "Standard Model")
      # leg2.AddEntry(LM0, "LM0", "lp")
      # leg2.AddEntry(LM1, "LM1", "lp")
      # leg2.AddEntry(LM2, "LM2", "lp")
      # leg2.AddEntry(LM3, "LM3", "lp")
      # leg2.AddEntry(LM4, "LM4", "lp")
      # leg2.AddEntry(LM5, "LM5", "lp")
      leg2.Draw()

    if "MHTovMET_afterAlphaT_all" in hist or "BiasedDeltaPhi_after_alphaT_55_all" in hist or "BabyJetMHT_all" in hist or "BiasedDeltaPhi_all" in hist:
      leg2.Draw()


    c1.cd(2)
    line = UnityLine(Total)
    ratio = RatioPlot(Data,SMBackGrounds)
    ratio.SetLabelSize(0.15, "XYZ")
    ratio.SetTitleSize(0.15, "XYZ")
    ratio.SetTitleOffset(1.05, "X")
    ratio.SetNdivisions(4, "Y");

    ratio.Draw()
    line.Draw()
    ratio.Draw("same")
    c1.cd(1).SetLogy()
    c1.Update()
    # print "saving hist:", hist, "from dir:",DirKeys[dir].GetTitle()
    # c1.SaveAs(outputfile+(DirKeys[dir].GetTitle())+hist+".png")
    if Total.GetEntries() == 0: Draw = False
    if Draw :
      c1.cd(1).SetLogy()
      c1.Update()
      c1.Print(outputfile+(DirKeys[dir].GetTitle())+hist+".png")
      c1.Print(outputfile+(DirKeys[dir].GetTitle())+hist+".pdf")
      if "All" == (DirKeys[dir].GetTitle()):
        AllPlots += PlotRow("All"+hist,"nAll"+hist,"Allcombined"+hist)

      if "250_300Gev" == (DirKeys[dir].GetTitle()):
        if "_after_alphaT" in hist : ControlRegonPlotsAfterAT1 += PlotRow("250_300Gev"+hist,"n250_300Gev"+hist,"250_300Gevcombined"+hist)
        else: ControlRegonPlots1 += PlotRow("250_300Gev"+hist,"n250_300Gev"+hist,"250_300Gevcombined"+hist)

      if "300_350Gev" == (DirKeys[dir].GetTitle()):
        if "_after_alphaT" in hist : ControlRegonPlotsAfterAT2 += PlotRow("300_350Gev"+hist,"n300_350Gev"+hist, "300_350Gevcombined"+hist)
        else: ControlRegonPlots2 += PlotRow("300_350Gev"+hist,"n300_350Gev"+hist,"300_350Gevcombined"+hist)

      if "350Gev" == (DirKeys[dir].GetTitle()):
        if "_after_alphaT" in hist : SignalRegonPlotsAfterAT += PlotRow("350Gev"+hist,"n350Gev"+hist,"350Gevcombined"+hist)
        else: SignalRegonPlots += PlotRow("350Gev"+hist,"n350Gev"+hist,"350Gevcombined"+hist)

      if "350Gev_afterDeadEcal" == (DirKeys[dir].GetTitle()):
        if "_after_alphaT" in hist : SignalRegonPlotsAfterATandDeadEcal += PlotRow("350Gev_afterDeadEcal"+hist,"n350Gev_afterDeadEcal"+hist,"350Gev_afterDeadEcalcombined"+hist)
        else: SignalRegonPlotsAfterDeadEcal += PlotRow("350Gev_afterDeadEcal"+hist,"n350Gev_afterDeadEcal"+hist,"350Gev_afterDeadEcalcombined"+hist)

      if "AllCuts" == (DirKeys[dir].GetTitle()):
        if "_after_alphaT" in hist : SignalRegonPlotsAfterAllCuts += PlotRow("AllCuts"+hist,"nAllCuts"+hist,"AllCutscombined"+hist)
        else: SignalRegonPlotsAfterAtAllCuts += PlotRow("AllCuts"+hist,"nAllCuts"+hist,"AllCutscombined"+hist)


    for a in closeList :
      a.Close()
    closeList = []
site = Header(intlumi)+BegSec("Signal Region after all cuts")+ SignalRegonPlotsAfterAllCuts+ EndSec() + BegSec("Signal Region after all cuts && at > 0.55")+ SignalRegonPlotsAfterAtAllCuts +EndSec() + BegSec("All Plots") + AllPlots + EndSec() + BegSec("Controll Region Plots 250-300GeV") + ControlRegonPlots1 + EndSec()  + BegSec("Controll Region 250-300GeV After AlphaT = 0.55 cut") +ControlRegonPlotsAfterAT1 + EndSec() + BegSec("Controll Region Plots 300-350GeV") + ControlRegonPlots2 + EndSec() + BegSec("Controll Region  300-350GeV After AlphaT = 0.55 cut") +ControlRegonPlotsAfterAT2 + EndSec() +  BegSec("Signal Region Plots") + SignalRegonPlots + EndSec() + BegSec("Signal Region After AlphaT = 0.55 cut") + SignalRegonPlotsAfterAT + EndSec() + BegSec("Signal Region Plots After Dead Ecal Cut") + SignalRegonPlotsAfterDeadEcal + EndSec() + BegSec("Signal Region After AlphaT = 0.55 cut && DeadEcal Cut") + SignalRegonPlotsAfterATandDeadEcal + EndSec() + Footer()
#


Webpage.write(site)
