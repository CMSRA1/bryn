#!/usr/bin/env python

'''Created by Bryn Mathias
bryn.mathias@cern.ch
'''
import errno

import ROOT as Root
import math
from time import strftime
import os, commands, sys
from PlottingFunctions import *
Root.gROOT.SetBatch(True) # suppress the creation of canvases on the screen... much much faster if over a remote connection

Root.gROOT.ProcessLine(".L ./tdrstyle.C+")
Root.gStyle.SetLineStyleString(11,"50 25")
def ensure_dir(path):
    try:
      os.makedirs(path)
    except OSError as exc: # Python >2.5
      if exc.errno == errno.EEXIST:
        pass
      else: raise


# Global Close List
closeList = []
intlumi = 189.

leg = Root.TLegend(0.65, 0.45, 0.97, 0.8)
leg.SetShadowColor(0)
leg.SetBorderSize(0)
leg.SetFillStyle(4100)
leg.SetFillColor(0)
leg.SetLineColor(0)

def GetAllhistos(inFile):
  temp = Root.TFile.Open(inFile)
  DirKeys = temp.GetListOfKeys()
  print DirKeys
  # histKeys =
  histList = [k.GetName() for k in (DirKeys[0].ReadObj()).GetListOfKeys()]
  return histList

def GetAllSubFiles(inFile):
  """docstring for GetAllSubFiles"""
  temp = Root.TFile.Open(inFile)
  DirKeys = temp.GetListOfKeys()
  DirList = []
  for d in DirKeys:
    DirList.append(d.GetName())
  return DirList

def GethistFromFolder(DataSetName,folder,hist,col,norm,Legend):
    a = Root.TFile.Open(DataSetName) #open the file
    closeList.append(a) # append the file to the close list
    b = a.Get(folder) #open the directory in the root file
    hist = b.Get(hist) # get your histogram b4y name
    if hist == None : hist = Root.TH1D()
    if Legend != 0:
      leg.AddEntry(hist,Legend,"LP") # add a legend entry
    hist.SetLineWidth(3)
    hist.SetLineColor(col) #set colour
    hist.SetBinContent(hist.GetNbinsX() ,hist.GetBinContent(hist.GetNbinsX())+hist.GetBinContent(hist.GetNbinsX()+1))
    hist.SetBinError(hist.GetNbinsX() ,math.sqrt((hist.GetBinError(hist.GetNbinsX()))**2 + (hist.GetBinError(hist.GetNbinsX()+1))**2))
    hist.SetBinContent(hist.GetNbinsX()+1,0)
    if norm != 0:
       hist.Scale(intlumi/100.) #if not data normilse to the data by lumi, MC is by default weighted to 100pb-1, if you have changed this change here!
    return hist


resultsDir = ["../resultsAllHTbins+0GeV","../resultsAllHTbins+10GeV","../resultsAllHTbins+5GeV"]
outdirTmp = "../Plots/"
histList = ["JetMultiplicityAfterAlphaT_all","HT_aftar_AlphaT_all"]
JetThreshList = ["","37","43"]
for num in JetThreshList:
  for dir in GetAllSubFiles("../resultsAllHTbins+0GeV/Data/AK5Calo_Jets.root"):
    if dir == "susyTree" : continue
    for hist in histList:
      outdir = outdirTmp
      print dir,num,hist
      Data =  GethistFromFolder(resultsDir[0]+ "/Data"+num+"/AK5Calo_Jets.root",dir,hist,1,0,"Data")
      MCCentral =    GethistFromFolder(resultsDir[0]+"/NoSmear"+num+"/AK5Calo_QCD_All.root",dir,hist,2,intlumi,"Central")
      MCCentral.Add( GethistFromFolder(resultsDir[0]+"/NoSmear"+num+"/AK5Calo_SingleTop.root",dir,hist,1,intlumi,0) )
      MCCentral.Add( GethistFromFolder(resultsDir[0]+"/NoSmear"+num+"/AK5Calo_TTbar.root",dir,hist,1,intlumi,0) )
      MCCentral.Add( GethistFromFolder(resultsDir[0]+"/NoSmear"+num+"/AK5Calo_WJets.root",dir,hist,1,intlumi,0) )
      MCCentral.Add( GethistFromFolder(resultsDir[0]+"/NoSmear"+num+"/AK5Calo_Zinv.root",dir,hist,1,intlumi,0) )
      MCplus5 =    GethistFromFolder(resultsDir[1]+"/NoSmear"+num+"/AK5Calo_QCD_All.root",dir,hist,3,intlumi,"+5GeV")
      MCplus5.Add( GethistFromFolder(resultsDir[1]+"/NoSmear"+num+"/AK5Calo_SingleTop.root",dir,hist,1,intlumi,0) )
      MCplus5.Add( GethistFromFolder(resultsDir[1]+"/NoSmear"+num+"/AK5Calo_TTbar.root",dir,hist,1,intlumi,0) )
      MCplus5.Add( GethistFromFolder(resultsDir[1]+"/NoSmear"+num+"/AK5Calo_WJets.root",dir,hist,1,intlumi,0) )
      MCplus5.Add( GethistFromFolder(resultsDir[1]+"/NoSmear"+num+"/AK5Calo_Zinv.root",dir,hist,1,intlumi,0) )
      MCplus10 =    GethistFromFolder(resultsDir[2]+"/NoSmear"+num+"/AK5Calo_QCD_All.root",dir,hist,4,intlumi,"+10GeV")
      MCplus10.Add( GethistFromFolder(resultsDir[2]+"/NoSmear"+num+"/AK5Calo_SingleTop.root",dir,hist,1,intlumi,0) )
      MCplus10.Add( GethistFromFolder(resultsDir[2]+"/NoSmear"+num+"/AK5Calo_TTbar.root",dir,hist,1,intlumi,0) )
      MCplus10.Add( GethistFromFolder(resultsDir[2]+"/NoSmear"+num+"/AK5Calo_WJets.root",dir,hist,1,intlumi,0) )
      MCplus10.Add( GethistFromFolder(resultsDir[2]+"/NoSmear"+num+"/AK5Calo_Zinv.root",dir,hist,1,intlumi,0) )
      c1 = Root.TCanvas("canvas"+hist,"canname"+hist,1200,1200)
      if False:
        #Make two pads, one small for the ratio plot and one large for the plot its self
        mainPad = Root.TPad("","",0.01,0.25,0.99,0.99)
        mainPad.SetNumber(1)
        mainPad.Draw()
        ratioPad = Root.TPad("","",0.01,0.05,0.99,0.26)
        ratioPad.SetBottomMargin(0.32)
        ratioPad.SetNumber(2)
        ratioPad.Draw()
        ratioPad.Clear()
      c1.cd(1)
      Data.Draw("p")
      MCCentral.Draw("histsame")
      MCplus5.Draw("histsame")
      MCplus10.Draw("histsame")
      leg.Draw("same")
      outdir = outdir+"/"+num+"/"
      ensure_dir(outdir)
      c1.SaveAs(outdir+"/"+hist+"_"+num+"_"+dir+".png")
      leg.Clear()
      for a in closeList:
        a.Close()


