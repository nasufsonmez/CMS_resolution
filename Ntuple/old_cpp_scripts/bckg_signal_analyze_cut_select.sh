#!/bin/bash

#samplefiles=/home/fozturk/Desktop/HEPrograms/MG5_aMC_v2_4_3
analyze_files=/home/fozturk/Desktop/Analysis-master

input_files=/home/fozturk/Desktop/Analysis-master/ntuple_data
output_files=/home/fozturk/Desktop/Analysis-master/analyze_output

data_files=("sm_diphoton_bckg_aa" "sm_diphoton_bckg_aj" "sm_diphoton_bckg_aaa" "sm_diphoton_bckg_aaj"
            "sm_diphoton_bckg_ajj" "sm_diphoton_bckg_az" "sm_diphoton_bckg_ll" "signal_diphoton")

cd $analyze_files
make

rm  $output_files/cut01234/*_new_out

for((i=0; i < ${#data_files[@]}; i++))
do

	    sed -i 's#InputFileName = "'.*'"#InputFileName = "'$input_files/'cut01234/ntuple_'${data_files[$i]}'_cut01234"#g' $analyze_files/input_parameters_analyze.par
	    sed -i 's#OutputFileName = "'.*'"#OutputFileName = "'$output_files/'cut01234/analyze_'${data_files[$i]}'_cut01234"#g' $analyze_files/input_parameters_analyze.par

      sed -i '/CUT0 = [a-z]*/c\CUT0 = cut0' $analyze_files/input_parameters_analyze.par
      sed -i '/CUT1 = [a-z]*/c\CUT1 = cut1' $analyze_files/input_parameters_analyze.par
      sed -i '/CUT2 = [a-z]*/c\CUT2 = cut2' $analyze_files/input_parameters_analyze.par
      sed -i '/CUT3 = [a-z]*/c\CUT3 = cut3' $analyze_files/input_parameters_analyze.par
      sed -i '/CUT4 = [a-z]*/c\CUT4 = cut4' $analyze_files/input_parameters_analyze.par

      ./analyze_events $analyze_files/input_parameters_analyze.par >> $output_files/cut01234/analyze_${data_files[$i]}_cut01234_out
      echo "${data_files[$i]}_cut01234"

done



		date

		echo "============================================================================"
                echo " All events generated. "
		echo "============================================================================"

exit
