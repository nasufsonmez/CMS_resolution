#!/bin/bash



#pileUps="0 50"
pileUps="0 5 10 15 25 50 100 200"


myfilename="100-250 250-500 500-1000 1000-2500 2500-4000 4000-6000 6000-Inf"

workingfolder=/home/nsonmez/MG5_aMC_v2_3_3


for pile_no in $pileUps

do

   cd $workingfolder


     rm AnalysisPosterOutputs/AnalysisOutput*${pile_no}.root
     rm Hadd_C_CombinedPileUp_${pile_no}.root
     rm outPut_${pile_no}.out

   	for say in $myfilename

   	do

   		./Poster Poster_DelphesSimWithModulesCard/Combined_Ht_${say}_PileUp_${pile_no}.root AnalysisPosterOutputs/AnalysisOutput-${say}-PileUp-${pile_no}.root >> outPut_${pile_no}.out


   	done

root -l -b -q .x haddPoster_${pile_no}.C

done




exit 0
