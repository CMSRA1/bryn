#!/usr/bin/env python
import os
import sys  
import subprocess

def copyf(src,dest):
    cmd=["srmcp", "-2", "-streams_num=1" ,src,dest]
    print cmd
    subprocess.call(cmd)

if len(sys.argv)<2:
    print "Error: too few arguments"
    print "Usage: srmcopy.py [path]"
    print "e.g. srmcopy.py $DCACHE_SRM_ROOT/store/user/.../.../ /vols/cms01/susy/data/.../.../"
    print "will copy all files '$DCACHE_SRM_ROOT/store/user/.../.../*' to /vols/cms01/susy/data/.../.../"
    sys.exit(0)

if len(sys.argv)==2:
    outdir="./"
else:
    outdir=sys.argv[2]

path=sys.argv[1]

storage_element='srm://gfe02.grid.hep.ph.ic.ac.uk:8443/srm/managerv2?SFN='
#storage_element='srm://cmssrm.fnal.gov:8443/srm/managerv2?SFN='
p=os.popen("srmls %s" % path,'r')

for line in p.read().split("\n")[3:len(p.read().split("\n"))-3]:
    fields=line.split()
    filename=fields[1]
    fileout = filename.rpartition("/")[2]
    file = storage_element+filename
    copyf(file, outdir+"/"+fileout)


