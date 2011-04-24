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
resultsDir = sys.argv(1)
flist = glob.glob(resultsDir)
print flist





