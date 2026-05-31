#!/bin/bash

analyze_files=/home/fozturk/Desktop/Analysis-master

input_files=/home/fozturk/Desktop/Analysis-master/ntuple_inputs/list_files
output_files=/home/fozturk/Desktop/Analysis-master/ntuple_data

data_files=("100-250" "sm_diphoton_bckg_aj" "sm_diphoton_bckg_aaa" "sm_diphoton_bckg_aaj"
            "sm_diphoton_bckg_ajj" "sm_diphoton_bckg_az" "sm_diphoton_bckg_ll" "signal_diphoton")

cd $analyze_files
make

rm  $output_files/cut*/*_out

for((i=0; i < ${#data_files[@]}; i++))
do

	    sed -i 's#InputFileName = "'.*'"#InputFileName = "'$input_files/'list_'${data_files[$i]}'"#g' $analyze_files/input_parameters.par
	    sed -i 's#OutputFileName = "'.*'"#OutputFileName = "'$output_files/cut$ncut/'ntuple_'${data_files[$i]}'_cut'$ncut'"#g' $analyze_files/input_parameters.par


      ./create_ntuple_new $analyze_files/input_parameters.par >> $output_files/cut$ncut/ntuple_${data_files[$i]}_cut${ncut}_out

done




		#root -l << EOF
		#.L hadd_root.C
	    #hadd()
		#.q
		#EOF

		date

		echo "============================================================================"
                echo " All events generated. "
		echo "============================================================================"

exit
