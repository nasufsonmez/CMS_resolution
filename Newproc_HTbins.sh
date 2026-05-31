#!/bin/bash

echo "====================================="	
echo "Start time   : `date`"
echo "====================================="

#definitions
mg5=~/MG5_aMC_v2_3_3
myfilename="100-250 250-500 500-1000 1000-2500 2500-4000 4000-6000 6000-Inf"
ht=(100 250 500 1000 2500 4000 6000 100000)
for say in $myfilename
do

echo "====================================="	
echo "$say feyn basladı   : `date`"
echo "====================================="


cd ${mg5}
sed -i '/output [a-z]*/c\output '"$say"'' ${mg5}/proc_card.dat
cat ${mg5}/proc_card.dat | grep output
cd ${mg5}
./bin/mg5_aMC proc_card.dat

echo "====================================="	
echo "$say feyn cızıldı   : `date`"
echo "====================================="


cd ${mg5}/$say/Cards
rm -r run_card.dat
scp -r ${mg5}/QCD_Cards/run_card.dat ${mg5}/$say/Cards

cd ${mg5}/$say/Cards
sed -i '/ 100   = htjmin ! minimum jet HT=Sum(jet pt)/c\ `${ht[1]}`   = htjmin ! minimum jet HT=Sum(jet pt)' ${mg5}/$say/Cards/run_card.dat

cd ${mg5}/$say
./bin/madevent multi_run 10 -f --laststep=delphes
done

