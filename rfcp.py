#!/usr/bin/env python
import os
import sys
import subprocess


nCores = 10
def copyf(src,dest):
  """docstring for copyf"""
  cmd=["rfcp",src,dest]
#  print cmd
  subprocess.call(cmd)
  pass

if len(sys.argv)<2:
    print "Error: too few arguments"
    print "Usage: rfcp.py [path]"
    print "e.g. rfcp.py /castor/blah path"
    sys.exit(0)

if len(sys.argv)==2:
    outdir="./"
else:
    outdir= sys.argv[2]

path=sys.argv[1]
cmd2=["ls",outdir]
outdirFiles = os.popen("ls %s" % outdir,"r").read()
p=os.popen("rfdir %s" % path,'r')
listofP = []
outfileList = []





for line in p.read().split("\n")[3:len(p.read().split("\n"))-3]:
    fields=line.split()
    # print fields
    filename=fields[8]
    file = path+filename
 #   print file
#    if filename  in outdirFiles.split("\n"):
    print "starting", file, outdir
    copyf(file,outdir)

print "Done!!"
