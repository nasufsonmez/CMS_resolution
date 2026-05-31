#!/bin/bash
#
#
#
#




durmusmg5=/home/dyilmaz/v2_3_0/MG5_aMC_v2_3_3

delphes=/home//MG5_aMC_v2_3_3/Delphes


HTbins="100-250 250-500 500-1000 1000-2500 2500-4000 4000-6000 6000-Inf"

	echo "!!!=================================================================="
	echo "!!! Start   `date`========================================" 		
	echo "!!!=================================================================="

	for ht in $HTbins # loop over all HTbin directories

	do

		mkdir $delphes/roots_for_$ht

		cd $durmusmg5/$ht/Events 


		for (( i=0 ; i < 5 ; ++i)) ;

		do

			cd run_01_$i

			gunzip tag_1_pythia_events.hep.gz # unzipping the generated hep files

			echo "!!!======================================="
			echo "!!!  $i . hep file unzipped        `date`"	
			echo "!!!===================================="

			
			cd ..
	
		done

#==========================================================================================
#======================  Detector Simulation over hep files   =============================
#==========================================================================================


		cd $delphes


		echo "!!!============================================================="	
		echo "!!! $ht Detector simulation...     `date`======================="
		echo "!!!============================================================="

			
		for (( i=0 ; i < 5 ; ++i)) ;

		do

		echo "!!!============================================================="	
		echo "!!! Detector simulation over run_01_$i hep file  `date`========="
		echo "!!!============================================================="


 			./DelphesSTDHEP \
			$delphes/cards/delphes_card_CMS.tcl \
			$delphes/roots_for_$ht/run_01_$i.root \
			$durmusmg5/$ht/Events/run_01_$i/tag_1_pythia_events.hep 		

		done



		cd $delphes/roots_for_$ht

		hadd combined_$ht.root run_01_*.root

	done

	echo "!!!=================================================================="
	echo "!!! End   `date`========================================" 		
	echo "!!!=================================================================="

exit 0


		
			



































