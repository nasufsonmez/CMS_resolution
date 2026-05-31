#!/bin/bash

#samplefiles=/home/fozturk/Desktop/HEPrograms/MG5_aMC_v2_4_3
analyze_files=/home/fozturk/Desktop/Analysis-master

input_files=/home/fozturk/Desktop/Analysis-master/ntuple_inputs/list_files
output_files=/home/fozturk/Desktop/Analysis-master/ntuple_data

data_files=("signal_diphoton")


            #data_files=("sm_diphoton_bckg_aa" "sm_diphoton_bckg_aj" "sm_diphoton_bckg_aaa" "sm_diphoton_bckg_aaj"
            #            "sm_diphoton_bckg_ajj" "sm_diphoton_bckg_az" "sm_diphoton_bckg_ll" "signal_diphoton")

cd $analyze_files
make

rm  $output_files/cut01234/*_out

for((i=0; i < ${#data_files[@]}; i++))
do

	    sed -i 's#InputFileName = "'.*'"#InputFileName = "'$input_files/'list_'${data_files[$i]}'"#g' $analyze_files/input_parameters.par
	    sed -i 's#OutputFileName = "'.*'"#OutputFileName = "'$output_files/'cut01234/ntuple_'${data_files[$i]}'_cut01234"#g' $analyze_files/input_parameters.par

	    sed -i '/CUT0 = [a-z]*/c\CUT0 = cut0' $analyze_files/input_parameters.par
      sed -i '/CUT1 = [a-z]*/c\CUT1 = cut1' $analyze_files/input_parameters.par
      sed -i '/CUT2 = [a-z]*/c\CUT2 = cut2' $analyze_files/input_parameters.par
      sed -i '/CUT3 = [a-z]*/c\CUT3 = cut3' $analyze_files/input_parameters.par
      sed -i '/CUT4 = [a-z]*/c\CUT4 = cut4' $analyze_files/input_parameters.par

      ./create_ntuple_new $analyze_files/input_parameters.par >> $output_files/cut01234/ntuple_${data_files[$i]}_cut01234_out
      echo "${data_files[$i]}_cut01234"

done



		date

		echo "============================================================================"
                echo " All events generated. "
		echo "============================================================================"

exit
