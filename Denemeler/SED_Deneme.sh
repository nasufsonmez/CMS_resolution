#!/bin/bash

echo "====================================="	
echo "Start time   : `date`"
echo "====================================="

#definitions
mg5=~/v2_3_0/MG5_aMC_v2_3_3
myfilename="100-250 250-500 500-1000 1000-2500 2500-4000 4000-6000 6000-Inf"
ht=(100 250 500 1000 2500 4000 6000)
htt=(250 500 1000 2500 4000 6000 100000)



counter=2


echo "====================================="	
echo "$say feyn basladı   : `date`"
echo "====================================="





sed  -i 's/ 1.0   = htjmin ! minimum jet HT=Sum(jet pt)/ '${ht[$counter]}'   = htjmin ! minimum jet HT=Sum(jet pt)/1' hocaya_uyarlanmıs_run_card.dat
sed  -i 's/ -1.0  = htjmax ! maximum jet HT=Sum(jet pt)/ '${htt[$counter]}'  = htjmax ! maximum jet HT=Sum(jet pt)/1' hocaya_uyarlanmıs_run_card.dat


exit 0




























