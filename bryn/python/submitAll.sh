#!/usr/bin/bash
source /vols/cms/grid/setup.sh
voms-proxy-init -voms cms -hours 130
source ../../setup.sh


./Data.py -b -n1
./McJESetaPlus.py -b
./McJESetaMinus.py -b
./McJESminus.py -b
./McJESplus.py -b
./McNoSmear.py -b
./McSmeared.py -b


# ./Data.py -l
# ./McJESetaPlus.py -l
# ./McJESetaMinus.py -l
# ./McJESminus.py -l
# ./McJESplus.py -l
# ./McNoSmear.py -l
# ./McSmeared.py -l
