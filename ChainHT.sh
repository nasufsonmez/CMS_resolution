#!/bin/bash

echo "====================================="	
echo "Start time   : `date`"
echo "====================================="

#definitions
mg5=~/MG5_aMC_v2_3_3
myfilename="100-250 250-500 500-1000 1000-2500 2500-4000 4000-6000 6000-Inf"
ht=(100 250 500 1000 2500 4000 6000)
htt=(250 500 1000 2500 4000 6000 100000)
counter=0
for say in $myfilename
do

echo "====================================="	
echo "$say feyn basladı   : `date`"
echo "====================================="


cd ${mg5}

sed -i '/output [a-z]*/c\output '"$say"'' ${mg5}/proc_card.dat

cat ${mg5}/proc_card.dat | grep output

./bin/mg5 proc_card.dat

echo "====================================="	
echo "$say feyn cızıldı   : `date`"
echo "====================================="


cd ${mg5}/$say/Cards

rm run_card_default.dat run_card.dat

scp -r ${mg5}/RunCard/run_card.dat .



#sed  -i 's/ 1.0   = htjmin ! minimum jet HT=Sum(jet pt)/ '${ht[$counter]}'   = htjmin ! minimum jet HT=Sum(jet pt)/1' run_card.dat

#sed  -i 's/ -1.0  = htjmax ! maximum jet HT=Sum(jet pt)/ '${htt[$counter]}'  = htjmax ! maximum jet HT=Sum(jet pt)/1' run_card.dat

sed -i '/[a-z]*   = htjmin ! minimum jet HT=Sum(jet pt)/c\ '${ht[$counter]}'   = htjmin ! minimum jet HT=Sum(jet pt)' ${mg5}/$say/Cards/run_card.dat

sed -i '/ -1.0   = htjmax ! maximum jet HT=Sum(jet pt)/c\ '${htt[$counter]}'   = htjmax ! maximum jet HT=Sum(jet pt)' ${mg5}/$say/Cards/run_card.dat

counter=$((counter+1))

cd ${mg5}/$say

echo "====================================="	
echo "$say madevent start time  : `date`"
echo "====================================="

./bin/madevent multi_run 2 -f --laststep=delphes

echo "====================================="
echo "$say madevent end time   : `date`"
echo "====================================="

done

echo "====================================="	
echo "BITIS ZAMANI   : `date`"
echo "====================================="



exit 0
