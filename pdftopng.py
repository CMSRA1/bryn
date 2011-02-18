#!/opt/local/bin/python
# encoding: utf-8
"""
untitled.py

Created by Bryn Mathias on 2011-02-18.
Copyright (c) 2011 Imperial College. All rights reserved.
"""

import sys
import os
import subprocess
import commands

def pdf2png(inF, out):
  """docstring for pdf2png"""
  # cmd = ["sips -s format png",inF,"--out", out]
  # print "sips -s format png",inF,"--out", out
  os.system("sips -s format png " +inF +" --out "+ out)
  pass

if len(sys.argv)<1:
    print "Error: too few arguments"
    print "Usage: pdf2ps path to pdf files"
    sys.exit(0)

workDir = sys.argv[1]
p=os.popen("ls %s" % workDir,'r')
h = os.popen("pwd").read().split("\n")[0]
f = p.read().split("\n")

for fi in f:
  if fi.rpartition(".")[2] == "pdf":
    # print h+"/"+fi.rpartition(".")[0]+".png"
    # print h+"/"+fi, "GOES TO", str(h) +"/"+fi.rpartition(".")[0]+".png"
    pdf2png(".//"+fi, fi.rpartition(".")[0]+".png")