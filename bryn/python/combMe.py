#!/usr/bin/env python
import ROOT as r
import glob
import sys
from combiner import *
# class Combiner(object):
#   """Adds histograms in subdirectories of a root file outputting them to a new root file"""
#   def __init__(self, RootFile):
#     super(Combiner, self).__init__()
#     self.arg = arg
#     self.RootFile = RF
#

fileList = [
"AK5Calo_Jets.root",
"AK5Calo_QCD_All.root",
"AK5Calo_Zinv.root",
"AK5Calo_Wjets.root",
"AK5Calo_TTbar.root",
"AK5Calo_LM0.root",
"AK5Calo_LM1.root",
"AK5Calo_LM2.root",
"AK5Calo_LM3.root",
"AK5Calo_LM4.root",
"AK5Calo_LM5.root",
"AK5Calo_LM6.root",
"AK5Calo_LM7.root",
]

resultsDir = sys.argv[1]
a = glob.glob(resultsDir)
print a
for flist in a:
  for b in fileList:
  print b.rpartition("/")[2]
    if flist == b.rpartition("/")[2]:
      print flist





