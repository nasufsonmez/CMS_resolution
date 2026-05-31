#!/bin/bash

#samplefiles=/home/fozturk/Desktop/HEPrograms/MG5_aMC_v2_4_3
analyze_files=/home/fozturk/Desktop/Analysis-master

input_files=/home/fozturk/Desktop/Analysis-master/ntuple_data/cut0
output_files=/home/fozturk/Desktop/Analysis-master/analyze_output_new_tfd/cut0

data_files=("sm_diphoton_bckg_aa" "sm_diphoton_bckg_aj" "sm_diphoton_bckg_aaa" "sm_diphoton_bckg_aaj"
            "sm_diphoton_bckg_ajj" "sm_diphoton_bckg_az" "sm_diphoton_bckg_ll" "signal_diphoton")

cd $analyze_files
make

rm  $output_files/*_out

for((i=0; i < ${#data_files[@]}; i++))
do
      sed -i 's#InputFileName = "'.*'"#InputFileName = "'$input_files/'ntuple_'${data_files[$i]}'_cut0"#g' $analyze_files/input_parameters_analyze.par
	    sed -i 's#OutputFileName = "'.*'"#OutputFileName = "'$output_files/'analyze_'${data_files[$i]}'_cut0"#g' $analyze_files/input_parameters_analyze.par

      ./analyze_events_new_tfd_1 $analyze_files/input_parameters_analyze.par >> $output_files/analyze_${data_files[$i]}_cut0_new_tfd_1_out
      echo "${data_files[$i]}_cut0_new_tfd"

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
