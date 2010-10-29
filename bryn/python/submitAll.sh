#!/usr/bin/bash
source /vols/cms/grid/setup.sh
voms-proxy-init -voms cms -hours 130
source ../../setup.sh


./Data.py -b -n100
./McJESminus.py -b -n100
./McJESplus.py -b -n100
./McNoSmear.py -b -n100
./McSmeared.py -b -n100


# ./Data.py -l
# ./McJESetaPlus.py -l
# ./McJESetaMinus.py -l
# ./McJESminus.py -l
# ./McJESplus.py -l
# ./McNoSmear.py -l
# ./McSmeared.py -l
