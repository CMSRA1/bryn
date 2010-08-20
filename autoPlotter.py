#!/usr/bin/env python

'''Created by Bryn Mathias
bryn.mathias@cern.ch
'''

import ROOT as Root
import math
from time import strftime
import os, commands
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


#Please enter the integrated lumi for the plots here:
intlumi = 0.838 #inv pico barns
print "The Integrated Luminosity your plots are being scaled to is: ", intlumi , "pb^{-1}"
#Set your output file here
outputfile = "../pdfs/Calo/"
print "you are outputting to: " ,outputfile
#SetWhere your results from your analysis are
resultsDir = " ../results/"

#close list is a global variable that has the file name appended to it so at the end of each hist loop the open files are closed. It is cleared each time a new hist is called.

def GetHist(DataSetName,col,norm,Legend):
    a = Root.TFile.Open(DataSetName) #open the file
    closeList.append(a) # append the file to the close list
    b = a.Get(DirKeys[dir].GetTitle()) #open the directory in the root file
    Hist = b.Get(hist) # get your histogram by name
    if Legend != 0:
      leg.AddEntry(Hist,Legend,"LP") # add a legend entry
    Hist.SetLineWidth(3)
    Hist.SetLineColor(col) #set colour
    if norm != 0:
       Hist.Scale(intlumi/100.) #if not data normilse to the data by lumi, MC is by default weighted to 100pb-1, if you have changed this change here!
    return Hist


def HistogramMaxY(H):
   Nbins = H.GetNbinsX()
   Entries = [H.GetBinContent(i) for i in range(1,Nbins+1)]
   return max(Entries)

def HistogramMinX(H):
  Nbins = H.GetNbinsX()
  for x in range(0,Nbins):
    if H.GetBinContent(x) != 0:
      return H.GetBinLowEdge(x-2)
  return 0

def HistogramMaxX(H):
  Nbins = H.GetNbinsX()
  BackItr = range(0,Nbins)
  BackItr.reverse()
  for x in BackItr :
    if H.GetBinContent(x) != 0:
      return H.GetBinLowEdge(x+1)



def Systematics(H1,H2,H3):
  Standard = H1.Clone()
  UpperError = H2.Clone()
  LowerError = H3.Clone()
  for bin in range(1,Standard.GetNbinsX()):
    StandardUpper = math.sqrt((Standard.GetBinError(bin))**2 + ((UpperError.GetBinContent(bin) - LowerError.GetBinContent(bin))/2)**2)
    Standard.SetBinError(bin, StandardUpper)
  return Standard


def PassingCutNumbers(Hist, lowerBound):
  lowbin = Hist.FindBin(lowerBound)
  errorVal = Root.Double(0)
  passingCut = Hist.IntegralAndError(lowbin, Hist.GetNbinsX(), errorVal)
  print passingCut, errorVal
  textLine = "Sample =" + DirKeys[dir].GetTitle() + hist +  " , Number passing cut of" + "" + " is "
  CutNumbers.write(textLine)
#+ str(passingCut) + " pm "


time = strftime("%Y_%m_%d")
print time
mergedPlots = Root.TFile("StandardPlots.root", "RECREATE")


#A file to open and scan for histograms inside directories
RootFileList = ["../results/AK5Calo_JetMET_Compleate.root"]

CutNumbers = open(outputfile+"CutTable.txt",'w')

Webpage = open(outputfile+"StandardPlots"+time+".html",'w')
#put your name in the contact email field
header = '''
<body>
<CENTER>
<h1>Comparison of Basic quantities for N=2 and N>=3 Jets</h1>
<P>Data = JetMetTau 268nb, contact email bryn.mathias AT cern DOT ch</P>
<table border="1" bordercolor="#FFCC00" style="background-color:#FFFFCC" width="1200" cellpadding="3" cellspacing="3">
  <tr>
    <td>DiJet</td>
    <td>=3 Jet</td>
    <td>>=4 Jet</td>
    <td>>=2 Jet</td>

  </tr>'''
footer = '''  </table>
  </CENTER>
  </body>'''
Webpage.write(header)



temp = Root.TFile.Open(RootFileList[0])
DirKeys = temp.GetListOfKeys()

HistKeys = [ (dir.ReadObj()).GetListOfKeys() for dir in DirKeys]
HistNames = [ [k.GetName() for k in D] for D in HistKeys]
#Loops though all the histograms that have been read from the first input file, this is done by histogram name

closeList = []
for dir in range(0,len(DirKeys)):
  for hist in HistNames[dir]:
    if "/" in hist : continue
    leg = Root.TLegend(0.7, 0.6, 0.89, 0.85)
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
    ratioPad = Root.TPad("","",0.01,0.01,0.99,0.25);
    ratioPad.SetNumber(2);
    ratioPad.Draw();

    c1.cd(1)
    #make your histograms form each file, read in the files you want below
    # GetHist("RootFile",Colour, scale to lumi 0=false anything else = true, Legend entry)
    #NB the order in which you book the histos is the order in which they appear in the legend
    Data = GetHist("../results/AK5Calo_JetMET_Compleate.root",1,0,"Data")
    QCD = GetHist("../results/AK5Calo_QCD_AllPtBins_7TeV_Pythia6.root",Root.kPink+4,1,"QCD")
    Data.SetMarkerStyle(20)
    Data.SetLineWidth(3)
    Data.SetLineColor(1)
    Data.SetFillColor(1)
    ZJets  = GetHist("../results/AK5Calo_ZJets-madgraph.root",Root.kTeal-7,1,"Z+Jets (Madgraph)")
    Zinv = GetHist("../results/AK5Calo_Zinvisible_jets.root",91,1,"Z->#nu#nu + Jets")
    WJets = GetHist("../results/AK5Calo_WJets-madgraph.root",Root.kPink+7,1,"W+Jets")
    ttbar = GetHist("../results/AK5Calo_ttbarTauola.root",Root.kBlue+1,1,"TTBar")
    LM0 = GetHist("../results/AK5Calo_LM0.root",2,1,"LM0")


    # ScaledUp = GetHist("../results/AK5Calo_Scale1.1_QCD_Pythia6.root",Root.kTeal-7,1,0)
    # ScaledDown = GetHist("../results/AK5Calo_Scale0.9_QCD_Pythia6.root",Root.kTeal-7,1,0)
    #Make a histogram of the sum of all the SM backgrounds
    Total = QCD.Clone()
    Total.Add(Zinv)
    Total.Add(ZJets)
    Total.Add(WJets)
    Total.Add(ttbar)
    if "AlphaT_all" in hist : PassingCutNumbers(LM0, 0.55)
    #Some funkey stuff from Henning for drawing the total background with some interesting lines around it
    hcen=Total.Clone()
    herr=Total.Clone()
    # Total = Systematics(Total,ScaledUp,ScaledDown)
    herr.SetLineColor(Root.kTeal+3)
    herr.SetMarkerColor(Root.kAzure+6)
    herr.SetFillColor(Root.kAzure+6)

    herr.SetLineWidth(3)
    Total.SetLineWidth(3)

    Total.SetFillColor(Root.kAzure+2)
    Total.SetLineColor(Root.kAzure+2)
    Total.SetFillStyle(3245)
    hcen.SetFillColor(0)
    hcen.SetMarkerColor(Root.kTeal+3)
    hcen.SetLineColor(Root.kTeal+3)
    hcen.SetLineWidth(3)

    leg.AddEntry(Total,"Standard Model","LPf")

    #Defind the ranges of the histogram for the two highest histograms ie the data and the total
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


    herr.GetXaxis().SetRangeUser(MinX,MaxX)
    herr.GetYaxis().SetRangeUser(0.00001,MaxY*5.)
    #Draw order is important!
    herr.Draw("hist")
    hcen.Draw("histsame")
    Total.Draw("9E2same")
    ZJets.Draw("9Sameh")
    Zinv.Draw("9SAMEh")
    WJets.Draw("9SAMEh")
    ttbar.Draw("9SAMEh")
    QCD.Draw("9SAMEh")
    LM0.Draw("9SAMEh")
    #Draw Data last to get the points above everything else
    Data.Draw("9SAMEP")

    #Draw Text for histogram titile and for lumi
    prelim = Root.TLatex(0.5,0.75,"CMS preliminary 2010");
    lumi = Root.TLatex(0.4,.85,"#scale[0.8]{#int L dt = " + str(intlumi) + "pb^{-1}, #sqrt{s} = 7 TeV}");
    prelim.SetNDC()
    lumi.SetNDC()
    # prelim.Draw()
    lumi.Draw()
    title = Root.TLatex(0.05,0.95,(DirKeys[dir].GetTitle())+"_"+hist[0:-4])
    title.SetNDC()
    title.Draw()
    lumi.Draw("Same")


    #Ratio plot is between the sum of the background and the data - clone the two relevant histograms
    RatioBottom = Total.Clone()
    RatioTop = Data.Clone()
    RatioTop.GetYaxis().SetTitle("data / sim")
    RatioTop.Divide(RatioBottom)
    c1.cd(1).Update()
    # c1.cd(1).SetLogy()
    leg.Draw()
    # c1.cd(1).Update()
    c1.cd(2)

    RatioTop.SetTitleSize(0.1, "XYZ");
    RatioTop.SetTitleOffset(0.55, "X");
    RatioTop.SetTitleOffset(0.3, "Y");
    RatioTop.SetLabelSize(0.06,"XY")

    # RatioTop.SetTitleXOffset(0.9);
    # RatioTop.SetTitleYOffset(0.9);
    RatioTop.GetXaxis().SetRangeUser(MinX,MaxX)
    RatioTop.GetYaxis().SetRangeUser(0.,2.0)
    RatioTop.Draw()
    #Draw a line though the perfectly matching point
    unity = Root.TLine();
    unity.SetLineWidth(2);
    # unity.SetLineStyle(Root.kDashed);
    unity.SetLineColor(2);
    unity.DrawLine(MinX, 1,MaxX, 1);



    #Do not save all of the histograms produced by the analysis framework, only the ones containing all objects in your selection, if this is not what you want to do then remove the if "all in hist" line
    if "all" in hist :

      # c1.SaveAs(outputfile+(DirKeys[dir].GetTitle())+"_"+hist+".png")
      if (DirKeys[dir].GetTitle())[0] != "n":

        Images ='''<tr>
          <td><a href="'''+(DirKeys[dir].GetTitle())+"_Log_"+hist+'.png\"><img src=\"'+(DirKeys[dir].GetTitle())+"_Log_"+hist+'.png\" width =\"286\" height=\"286\" /></a></td>\n'+  "<td><a href=\""+"n"+(DirKeys[dir].GetTitle())+"_Log_"+hist+'.png\"><img src=\"'+"n"+(DirKeys[dir].GetTitle())+"_Log_"+hist+'.png\" width =\"286\" height=\"286\" /></a></td>\n'
        Webpage.write(Images)

      # mergedPlots.writeTObject(c1)
      # c1.cd(1)
      c1.cd(1).SetLogy(1)
      c1.Update()
      # c1.cd(2)
      # RatioTop.Draw()

      c1.SaveAs(outputfile+(DirKeys[dir].GetTitle())+"_Log_"+hist+".png")
      c1.SaveAs(outputfile+(DirKeys[dir].GetTitle())+"_Log_"+hist+".pdf")

    if "AlphaT_0" in hist :
      # c1.cd(2)
      # RatioTop.Draw()
      # c1.SaveAs(outputfile+(DirKeys[dir].GetTitle())+"_"+hist+".png")
      if (DirKeys[dir].GetTitle())[0] != "n":

        Images ='''<tr>
          <td><a href="'''+(DirKeys[dir].GetTitle())+"_Log_"+hist+'.png\"><img src=\"'+(DirKeys[dir].GetTitle())+"_Log_"+hist+'.png\" width =\"286\" height=\"286\" /></a></td>'"<td><a href=\""+"n"+(DirKeys[dir].GetTitle())+"_Log_"+hist+'.png\"><img src=\"'+"n"+(DirKeys[dir].GetTitle())+"_Log_"+hist+'.png\" width =\"286\" height=\"286\" /></a></td>'
        Webpage.write(Images)
      # mergedPlots.writeTObject(c1)
      c1.cd(1).SetLogy()
      # c1.cd(2)
      # RatioTop.Draw()

      c1.Update()
      c1.SaveAs(outputfile+(DirKeys[dir].GetTitle())+"_Log_"+hist+".png")
      c1.SaveAs(outputfile+(DirKeys[dir].GetTitle())+"_Log_"+hist+".pdf")

      c1.cd(1).SetLogy(0)

    for a in closeList :
      a.Close()
    closeList = []
Webpage.write(footer)

