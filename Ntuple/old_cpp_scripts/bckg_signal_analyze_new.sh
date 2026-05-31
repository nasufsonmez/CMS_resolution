#!/bin/bash

#samplefiles=/home/fozturk/Desktop/HEPrograms/MG5_aMC_v2_4_3
analyze_files=/home/fozturk/Desktop/Analysis-master

input_files=/home/fozturk/Desktop/Analysis-master/ntuple_data/cut0
output_files=/home/fozturk/Desktop/Analysis-master/analyze_output_new

data_files=("sm_diphoton_bckg_aa" "sm_diphoton_bckg_aj" "sm_diphoton_bckg_aaa" "sm_diphoton_bckg_aaj"
            "sm_diphoton_bckg_ajj" "sm_diphoton_bckg_az" "sm_diphoton_bckg_ll" "signal_diphoton")

cd $analyze_files
make

rm  $output_files/cut*/*_new_out

for((i=0; i < ${#data_files[@]}; i++))
do
  for (( ncut = 0; ncut < 5; ncut++ ));
  do
	    sed -i 's#InputFileName = "'.*'"#InputFileName = "'$input_files/'ntuple_'${data_files[$i]}'_cut0"#g' $analyze_files/input_parameters_analyze_new.par
	    sed -i 's#OutputFileName = "'.*'"#OutputFileName = "'$output_files/'cut'$ncut/'analyze_'${data_files[$i]}'_cut'$ncut'"#g' $analyze_files/input_parameters_analyze_new.par

      sed -i '/CUT0 = [a-z]*/c\CUT0 = cut'$ncut'' $analyze_files/input_parameters_analyze_new.par
      sed -i '/CUT1 = [a-z]*/c\CUT1 = cut'$ncut'' $analyze_files/input_parameters_analyze_new.par
      sed -i '/CUT2 = [a-z]*/c\CUT2 = cut'$ncut'' $analyze_files/input_parameters_analyze_new.par
      sed -i '/CUT3 = [a-z]*/c\CUT3 = cut'$ncut'' $analyze_files/input_parameters_analyze_new.par
      sed -i '/CUT4 = [a-z]*/c\CUT4 = cut'$ncut'' $analyze_files/input_parameters_analyze_new.par

      ./analyze_events_new $analyze_files/input_parameters_analyze_new.par >> $output_files/cut$ncut/analyze_${data_files[$i]}_cut${ncut}_new_out
      echo "${data_files[$i]}_cut${ncut}_new"

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
