#!/bin/bash

samplefiles=/home/fozturk/Desktop/HEPrograms/MG5_aMC_v2_4_3
ntuple_list_files=/home/fozturk/Desktop/Analysis-master/ntuple_inputs/list_files
bckg_files=("sm_diphoton_bckg_aa" "sm_diphoton_bckg_aj" "sm_diphoton_bckg_aaa" "sm_diphoton_bckg_aaj"
            "sm_diphoton_bckg_ajj" "sm_diphoton_bckg_az" "sm_diphoton_bckg_ll")

rm $ntuple_list_files/list_*

for((i=0; i < ${#bckg_files[@]}; i++))
do
  if [[ -d "${samplefiles}/${bckg_files[$i]}" && ! -L "${samplefiles}/${bckg_files[$i]}" ]];
  then
      for bckg_run_files in ${samplefiles}/${bckg_files[$i]}/Events/run_01_*;
      do
          if [[ -d "$bckg_run_files" && ! -L "$bckg_run_files" ]];
          then
             echo "${samplefiles}/${bckg_files[$i]}"
          	 echo "$bckg_run_files/tag_1_delphes_events.root" >> $ntuple_list_files/list_${bckg_files[$i]}
         fi
      done
  fi
done

exit 0
