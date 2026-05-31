#!/bin/bash
# Nasuf Sönmez

#definitions

mg5=/home//MG5_aMC_v2_3_3

pileUps="0"
#pileUps="0 5 10 15 25 50 100 200"

#htIntervals="100-250"
htIntervals="100-250 250-500 500-1000 1000-2500 2500-4000 4000-6000 6000-Inf"

multiRunNo=1

MadEventOutputFolder=Poster_Events # MUST BE SAME NAME WITH GenerateEven*.sh OutputFolderName

DelphesOutputFolder=Poster_DelphesSimWithModulesCard

delphesCardUsed=/home//MG5_aMC_v2_3_3/PosterScripts/delphes_card_CMS_PileUp_JetAlgo_6-5.tcl

   echo "====================================="
   echo "======  Start time   : `date`"
   echo "====================================="

   mkdir ${mg5}/${DelphesOutputFolder}

   for pile_no in $pileUps

   do

      sed -i "s/MeanPileUp [0-9]*/MeanPileUp ${pile_no}/g" ${delphesCardUsed}

      echo "!!!+=================================================================================================="
      echo "!!!+======`cat ${delphesCardUsed} | grep MeanPileUp ; date`"

      cd ${mg5}/Delphes

      for htInt in $htIntervals

      do

         echo "!!!++============================================================="
         echo "!!!++====== PileUp ${pile_no} ve HT ${htInt} için rootları oluşturuyor...     `date`==="
         echo "!!!++============================================================="


         for (( i=0; i < $multiRunNo; ++i));

         do

            echo "!!!++============================================================="
            echo "!!!++====== PileUp ${pile_no} ve HT ${htInt} için ${i}. root yazılıyor `date`==="
            echo "!!!++============================================================="


            ./DelphesSTDHEP	\
            ${delphesCardUsed} \
            ${mg5}/${DelphesOutputFolder}/PileUp-${pile_no}_Ht_${htInt}_jetAlgo_6-5_${i}.root \
            ${mg5}/${MadEventOutputFolder}/${htInt}/Events/run_01_${i}/tag_1_pythia_events.hep


            echo "!!!++============================================================="
            echo "!!!++====== PileUp ${pile_no} ve HT ${htInt} için ${i}. root bitti `date`==="
            echo "!!!++============================================================="

         done

         cd ${mg5}/${DelphesOutputFolder}

         echo "!!!++=============================================================="
         echo "!!!++====== Combining Root Files with Pile Up ...   `date`==============="
         echo "!!!++=============================================================="

         hadd Combined_Ht_${htInt}_PileUp_${pile_no}.root PileUp-${pile_no}_Ht_${htInt}_jetAlgo_6-5_*.root

         rm PileUp-${pile_no}_Ht_${htInt}_jetAlgo_6-5_*.root # birleştirdikten sonra eskileri kaldırıyor

         echo "!!!++=============================================================="
         echo "!!!++====== Root Files Combined   `date`==============="
         echo "!!!++=============================================================="

      done

   done

   echo "====================================="
   echo "======  End time   : `date`========="
   echo "====================================="

exit 0

