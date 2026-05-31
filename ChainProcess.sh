#!/bin/bash



		echo "!!!=================================================================="
		echo "!!! Process started   `date`" 		
		echo "!!!================================================================="




  		cd ~/MG5_aMC_v2_3_3/QCD_HT-100To250

	        		./bin/madevent multi_run 10 -f --laststep=delphes --nb_core=2

		echo "!!!=================================================================="
		echo "!!! QCD_HT-100To250 tamamlandı   `date`" 		
		echo "!!!================================================================="


		cd ~/MG5_aMC_v2_3_3/QCD_jj_HT-100To250

				
		        	./bin/madevent multi_run 10 -f --laststep=delphes --nb_core=2

		echo "!!!=================================================================="
		echo "!!! QCD_jj_HT-100To250 tamamlandı   `date`" 		
		echo "!!!================================================================="


		cd ~/MG5_aMC_v2_3_3/QCD_jj_onlysm_HT-100To250

		        	./bin/madevent multi_run 10 -f --laststep=delphes --nb_core=2

		echo "!!!=================================================================="
		echo "!!! QCD_jj_onlysm_HT-100To250 tamamlandı   `date`" 		
		echo "!!!================================================================="


exit 0
























