#!/usr/bin/env python

'''Created by Bryn Mathias
bryn.mathias@cern.ch
'''
import errno

import ROOT as Root
import math
from time import strftime
import os, commands
# from PlottingFunctions import *
# Root.gROOT.SetBatch(True) # suppress the creation of canvases on the screen.. much much faster if over a remote connection
Root.gROOT.SetStyle("Plain") #To set plain bkgds for slides
Root.gROOT.ProcessLine(".L ./tdrstyle.C+")

intlumi =35.0 #4.433 #inv pico barns
resultsDir = "./"

def GetHist(DataSetName,folder,hist,col,norm,Legend):
    a = Root.TFile.Open(DataSetName) #open the file
    # closeList.append(a) # append the file to the close list
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

leg = Root.TLegend(0.6, 0.55, 0.9, 0.8)
leg.SetShadowColor(0)
leg.SetBorderSize(0)
leg.SetFillStyle(4100)
leg.SetFillColor(0)
leg.SetLineColor(0)

prelim = Root.TLatex(0.37,0.82,"#scale[0.8]{CMS}")
prelim.SetNDC()
lumi = Root.TLatex(0.45,.82,"#scale[0.8]{#int L dt = 35 pb^{-1}, #sqrt{s} = 7 TeV}")
lumi.SetNDC()

c1 = Root.TCanvas("canvas","canname",1200,1200)



noCutsNoTrigger = GetHist("AK5Calo_Jets.root", "AllNoTrigger", "AlphaT_Zoomed_all",1,0,0)
noCutsTrigger = GetHist("AK5Calo_Jets.root", "AllWithTrigger", "AlphaT_Zoomed_all",1,0,0)
noCutsTriggerFail = GetHist("AK5Calo_Jets.root", "AllTriggerFail", "AlphaT_Zoomed_all",1,0,0)
AllCutsNoTrigger = GetHist("AK5Calo_Jets.root", "AllCutsNoTrigger", "AlphaT_Zoomed_all",1,0,0)
AllCutsTrigger = GetHist("AK5Calo_Jets.root", "AllCutsWithTrigger", "AlphaT_Zoomed_all",1,0,0)
AllCutsTriggerFail = GetHist("AK5Calo_Jets.root", "AllCutsTriggerFail", "AlphaT_Zoomed_all",1,0,0)


noCutsFail= Root.TGraphAsymmErrors()
CutsFail= Root.TGraphAsymmErrors()

noCutsEff = Root.TGraphAsymmErrors()
CutsEff = Root.TGraphAsymmErrors()
noCutsEff.BayesDivide(noCutsTrigger,noCutsNoTrigger)
noCutsFail.BayesDivide(noCutsTriggerFail,noCutsNoTrigger)


CutsFail.BayesDivide(AllCutsTriggerFail,AllCutsNoTrigger)
CutsEff.BayesDivide(AllCutsTrigger,AllCutsNoTrigger)
c1.cd()
noCutsEff.Draw("apl")
c1.SaveAs("./NoCutsEff.pdf")
c1.Clear()
c1.cd()
CutsEff.Draw("apl")
c1.SaveAs("./CutsEff.pdf")
c1.Clear()
c1.cd()
noCutsFail.Draw("apl")
c1.SaveAs("./noFailEff.pdf")
c1.Clear()
c1.cd()
CutsFail.Draw("apl")
c1.SaveAs("./CutsFailEff.pdf")