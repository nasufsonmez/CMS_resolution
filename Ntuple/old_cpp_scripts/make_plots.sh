#!/bin/bash

analyze_files=/home/fozturk/Desktop/Analysis-master

cd $analyze_files

  for (( ncut = 0; ncut < 8; ncut++ ));
  do
      root -l -b
      .L hadd_cut${ncut}_new_tfd.C
      hadd()
      #'.q'
      root -l -b superimpose_new_cut${ncut}_tfd.C
  done

		date

		echo "============================================================================"
                echo " All plots generated. "
		echo "============================================================================"

exit
