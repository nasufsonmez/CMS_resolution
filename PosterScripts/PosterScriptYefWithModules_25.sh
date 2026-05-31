#!/bin/bash


#definitions

mg5=/home/csamaner/MG5_aMC_v2_3_3

pileUps="25"
#pileUps="0 5 10 15 25 50 100 200"

#htIntervals="100-250"
htIntervals="100-250 250-500 500-1000 1000-2500 2500-4000 4000-6000 6000-Inf"

multiRunNo=10

MadEventOutputFolder=Poster_Events # MUST BE SAME NAME WITH GenerateEven*.sh OutputFolderName

DelphesOutputFolder=Poster_DelphesSimWithModulesCard

delphesCardUsed=/home/csamaner/MG5_aMC_v2_3_3/PosterScripts/delphes_card_CMS_PileUp_25_JetAlgo_6-5-4.tcl

   echo "csamaner====================================="
   echo "csamaner======  Start time   : `date`"
   echo "csamaner====================================="

   mkdir ${mg5}/${DelphesOutputFolder}

   for pile_no in $pileUps

   do

      sed -i "s/MeanPileUp [0-9]*/MeanPileUp ${pile_no}/g" ${delphesCardUsed}

      echo "csamaner!!!+=================================================================================================="
      echo "csamaner!!!+======`cat ${delphesCardUsed} | grep MeanPileUp ; date`"



      for htInt in $htIntervals

      do

	 cd ${mg5}/Delphes

         echo "csamaner!!!++============================================================="
         echo "csamaner!!!++====== PileUp ${pile_no} ve HT ${htInt} için rootları oluşturuyor...     `date`==="
         echo "csamaner!!!++============================================================="


         for (( i=0; i < $multiRunNo; ++i));

         do

            echo "csamaner!!!++============================================================="
            echo "csamaner!!!++====== PileUp ${pile_no} ve HT ${htInt} için ${i}. root yazılıyor `date`==="
            echo "csamaner!!!++============================================================="


            ./DelphesSTDHEP	\
            ${delphesCardUsed} \
            ${mg5}/${DelphesOutputFolder}/PileUp-${pile_no}_Ht_${htInt}_jetAlgo_6-5-4_${i}.root \
            ${mg5}/${MadEventOutputFolder}/${htInt}/Events/run_01_${i}/tag_1_pythia_events.hep


            echo "csamaner!!!++============================================================="
            echo "csamaner!!!++====== PileUp ${pile_no} ve HT ${htInt} için ${i}. root bitti `date`==="
            echo "csamaner!!!++============================================================="

         done

         cd ${mg5}/${DelphesOutputFolder}

         echo "csamaner!!!++=============================================================="
         echo "csamaner!!!++====== Combining Root Files with Pile Up ...   `date`==============="
         echo "csamaner!!!++=============================================================="

         hadd Combined_Ht_${htInt}_PileUp_${pile_no}_6-5-4.root PileUp-${pile_no}_Ht_${htInt}_jetAlgo_6-5-4_*.root

         rm PileUp-${pile_no}_Ht_${htInt}_jetAlgo_6-5-4_*.root # birleştirdikten sonra eskileri kaldırıyor

         echo "csamaner!!!++=============================================================="
         echo "csamaner!!!++====== Root Files Combined   `date`==============="
         echo "csamaner!!!++=============================================================="

      done

   done

   echo "csamaner====================================="
   echo "csamaner======  End time   : `date`========="
   echo "csamaner====================================="

exit 0

