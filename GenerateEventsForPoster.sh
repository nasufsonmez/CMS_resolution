#!/bin/bash


#definitions

mg5=/home//MG5_aMC_v2_3_3

adamDelphes=/home//delphes

#htIntervals="100-250 250-500"
htIntervals="100-250 250-500 500-1000 1000-2500 2500-4000 4000-6000 6000-Inf"

#htMin=(100 250)
htMin=(100 250 500 1000 2500 4000 6000)

#htMax=(250 500)
htMax=(250 500 1000 2500 4000 6000 -1.0)

#xqCut=(7.0 20.0)
xqCut=(20.0 20.0 20.0 20.0 20.0 20.0 20.0)

multiRunNo=10
nEvents=100000


   echo "+====================================="
   echo "+======  Start time   : `date`"
   echo "+====================================="

   counter=0

   for htInt in $htIntervals

   do

      echo "!!!====================================="
      echo "!!!======  MadGraph started for $htInt   : `date`"
      echo "!!!====================================="

      cd ${mg5}

      sed -i '/output [a-z]*/c\output '"Poster_Events/${htInt}"'' ${mg5}/proc_card.dat

      cat ${mg5}/proc_card.dat | grep output

      ./bin/mg5_aMC proc_card.dat

      echo "!!!====================================="
      echo "!!!======  MadGraph finished for $htInt   : `date`"
      echo "!!!====================================="

      cd ${mg5}/Poster_Events/${htInt}/Cards

      sed -i '/ 0.0   = htjmin ! minimum jet HT=Sum(jet pt)/c\ '${htMin[$counter]}'   = htjmin ! minimum jet HT=Sum(jet pt)' ${mg5}/Poster_Events/${htInt}/Cards/run_card.dat
      sed -i '/ -1.0  = htjmax ! maximum jet HT=Sum(jet pt)/c\ '${htMax[$counter]}'   = htjmax ! maximum jet HT=Sum(jet pt)' ${mg5}/Poster_Events/${htInt}/Cards/run_card.dat
      sed -i '/  10000 = nevents ! Number of unweighted events requested/c\ '${nEvents}' = nevents ! Number of unweighted events requested' ${mg5}/Poster_Events/${htInt}/Cards/run_card.dat
      sed -i '/ 30.0   = xqcut   ! minimum kt jet measure between partons/c\ '${xqCut[$counter]}'   = xqcut   ! minimum kt jet measure between partons' ${mg5}/Poster_Events/${htInt}/Cards/run_card.dat
      echo "!!!+=================================================================================================="
      echo "!!!+======`cat ${mg5}/Poster_Events/${htInt}/Cards/run_card.dat | grep "= xqcut" ; date`"
      echo "!!!+=================================================================================================="
      echo "!!!+======`cat ${mg5}/Poster_Events/${htInt}/Cards/run_card.dat | grep htj ; date`"



      sed -i '/ 0.0   = htjmin ! minimum jet HT=Sum(jet pt)/c\ '${htMin[$counter]}'   = htjmin ! minimum jet HT=Sum(jet pt)' ${mg5}/Poster_Events/${htInt}/Cards/run_card_default.dat
      sed -i '/ -1.0  = htjmax ! maximum jet HT=Sum(jet pt)/c\ '${htMax[$counter]}'   = htjmax ! maximum jet HT=Sum(jet pt)' ${mg5}/Poster_Events/${htInt}/Cards/run_card_default.dat
      sed -i '/  10000 = nevents ! Number of unweighted events requested/c\ '${nEvents}' = nevents ! Number of unweighted events requested' ${mg5}/Poster_Events/${htInt}/Cards/run_card_default.dat
      sed -i '/ 30.0   = xqcut   ! minimum kt jet measure between partons/c\ '${xqCut[$counter]}'   = xqcut   ! minimum kt jet measure between partons' ${mg5}/Poster_Events/${htInt}/Cards/run_card_default.dat


      counter=$((counter+1))

      cd ${mg5}/Poster_Events/${htInt}

      echo "!!!====================================="
      echo "!!!======  Madevent started for ${htInt}  : `date`"
      echo "!!!====================================="

      ./bin/madevent multi_run ${multiRunNo} -f --laststep=pythia

      echo "!!!====================================="
      echo "!!!======  MadEvent finished for ${htInt}   : `date`"
      echo "!!!====================================="

      cd ${mg5}/Poster_Events/${htInt}/Events

      echo "!!!+======================================="
      echo "!!!+======  Unzipping pythia hep files for ${htInt}...  `date`"

		for (( i=0; i < ${multiRunNo}; ++i));

		do

			cd run_01_$i

	        	gunzip tag_1_pythia_events.hep.gz

			cd ..

		done

      echo "!!!+======================================="
      echo "!!!+======  Unzipped pythia hep files  `date`"

   done

   echo "+====================================="
   echo "+======  End time   : `date`"
   echo "+====================================="

exit 0

