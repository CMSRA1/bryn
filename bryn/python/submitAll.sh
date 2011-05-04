#!/usr/bin/bash
voms-proxy-init -voms cms -hours 130
source ../../setup.sh


./Data.py -b -n20
./McJESminus.py -b -n50
./McJESplus.py -b -n50
./McNoSmear.py -b -n50
./McSmeared.py -b -n50

# ./Data.py -l
# ./McJESetaPlus.py -l
# ./McJESetaMinus.py -l
# ./McJESminus.py -l
# ./McJESplus.py -l
# ./McNoSmear.py -l
# ./McSmeared.py -l
