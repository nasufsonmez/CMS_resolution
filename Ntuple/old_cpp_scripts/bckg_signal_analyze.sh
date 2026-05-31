#!/bin/bash

#samplefiles=/home/fozturk/Desktop/HEPrograms/MG5_aMC_v2_4_3
analyze_files=/home/fozturk/Desktop/Analysis-master

input_files=/home/fozturk/Desktop/Analysis-master/ntuple_data
output_files=/home/fozturk/Desktop/Analysis-master/analyze_output

data_files=("sm_diphoton_bckg_aa" "sm_diphoton_bckg_aj" "sm_diphoton_bckg_aaa" "sm_diphoton_bckg_aaj"
            "sm_diphoton_bckg_ajj" "sm_diphoton_bckg_az" "sm_diphoton_bckg_ll" "signal_diphoton")

cd $analyze_files
make

rm  $output_files/cut*/*_out

for((i=0; i < ${#data_files[@]}; i++))
do
  for (( ncut = 0; ncut < 5; ncut++ ));
  do
	    sed -i 's#InputFileName = "'.*'"#InputFileName = "'$input_files/'cut'$ncut/'ntuple_'${data_files[$i]}'_cut'$ncut'"#g' $analyze_files/input_parameters_analyze.par
	    sed -i 's#OutputFileName = "'.*'"#OutputFileName = "'$output_files/'cut'$ncut/'analyze_'${data_files[$i]}'_cut'$ncut'"#g' $analyze_files/input_parameters_analyze.par
      sed -i 's/cut[0-9]/cut'${ncut}'/g'  $analyze_files/input_parameters.par

      ./analyze_events $analyze_files/input_parameters_analyze.par >> $output_files/cut$ncut/analyze_${data_files[$i]}_cut${ncut}_out
      echo "${data_files[$i]}_cut$ncut"

  done
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
