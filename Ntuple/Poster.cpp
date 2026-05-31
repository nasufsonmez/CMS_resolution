#include <TSystem.h>
#include <TChain.h>
#include <TROOT.h>
#include <TRint.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TEventList.h>
#include "TClonesArray.h"
#include <TH1D.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TF1.h>
#include "TLorentzVector.h"
#include "TCanvas.h"
#include <TMath.h>
#include <TProfile.h>
#include "TStyle.h"
#include <TString.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <time.h>

// #include "tdrstyle.h"


#include <algorithm>

#include "TLatex.h"
#include "TLegend.h"

#include "TVectorD.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
#include "DelphesClasses.h"
#include "Math/GenVector/VectorUtil.h"

#include <TProfile.h>

//#include "CMSTDRStyle.h"
using namespace std;

const double JETPTCUT = 20.00 ;
const double JETETACUT = 1.8 ;

const int ptIntervals[]={60,100,150,250,500,800,1100,1500,2000,2600,3300,4000,5000,6500};
const int ptIntervalsArraySize = sizeof(ptIntervals)/sizeof(int);
// int ptIntervalsFrom = 20;
// int ptIntervalsTo = 500;
// int ptIntervalValue = 10;

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

int main(int argc, char*argv[])
{

 // setTDRStyle();
 string inputFile=argv[1];
 string outputFile=argv[2];

 TFile *outf = new TFile(outputFile.c_str(),"RECREATE");

 /////////////////////// Book histograms ///////////////////////////////

    char hist_name[100];
    char hist_title[1000];

     // Jet Pt distribution ---------------------------------------------------------------------------------------

     TDirectory *ptDist = outf->mkdir("JetPtDistribution");
     ptDist->cd();

         TH1 *histcalojetPT          = new TH1F("calojetpt", "pT of calojets", 500, 0.0, 6000.0);
         TH1 *histcalojetPT_CA          = new TH1F("calojetpt_CA", "pT of calojets_CA", 500, 0.0, 6000.0);
         TH1 *histgenjetPT           = new TH1F("genjetpt", "pT of genjets", 500, 0.0, 6000.0);
         TH1 *histgenjetPT_CA           = new TH1F("genjetpt_CA", "pT of genjets_CA", 500, 0.0, 6000.0);

     // HT distributions---------------------------------------------------------------------------

     TDirectory *htDist = outf->mkdir("JetHtDistribution");
     htDist->cd();

        TH1 *hist_SHT                = new TH1F("hist_SHT", "ScalarHT.HT (Scaled)" , 500, 0.0, 11000.0);
        TH1 *hist_SHT_CA                = new TH1F("hist_SHT_CA", "ScalarHT.HT_CA (Scaled)" , 500, 0.0, 11000.0);

     // PT RESO ---------------------------------------------------------------------------------------

     TDirectory *ptResolutionsFull = outf->mkdir("JetPtResolutions");
     ptResolutionsFull->cd();

        TH2F *hist_PtResoFullNEW     = new TH2F("Jet Pt Resolution for Full scale","",500, 0.0, 3000.0, 100, -50, 50 );
        TH2F *hist_PtResoFullNEW_CA     = new TH2F("Jet Pt Resolution for Full scale_CA","",500, 0.0, 3000.0, 100, -50, 50 );

     // PT RESO NEW METHOD ------------------------------------------------------------

     TDirectory *ptResoNew = outf->mkdir("JetRelativePtResolutionPTBins");
     ptResoNew->cd();

        TH1 *histRelativePtResoPTBins[ptIntervalsArraySize-1];

        for ( int a=0; a < ptIntervalsArraySize-1; a++ )
        {
            sprintf(hist_name,"pt_Reso_PT%ito%i",ptIntervals[a],ptIntervals[a+1]);
            sprintf(hist_title,"%i < Pt < %i",ptIntervals[a],ptIntervals[a+1]);
            histRelativePtResoPTBins[a]          = new TH1F(hist_name,hist_title,100, 0.0, 2.0);
        }

     // PT RESO NEW METHOD Cambridge/Aachen  ------------------------------------------------------------

     TDirectory *ptResoNew_CA = outf->mkdir("JetRelativePtResolutionPTBins_CA");
     ptResoNew_CA->cd();

        TH1 *histRelativePtResoPTBins_CA[ptIntervalsArraySize-1];

        for ( int a=0; a < ptIntervalsArraySize-1; a++ )
        {
            sprintf(hist_name,"pt_Reso_PT%ito%i_CA",ptIntervals[a],ptIntervals[a+1]);
            sprintf(hist_title,"%i < Pt < %i _CA",ptIntervals[a],ptIntervals[a+1]);
            histRelativePtResoPTBins_CA[a]          = new TH1F(hist_name,hist_title,100, 0.0, 2.0);
        }

      //   Jet Size -----------------------------------------------------------------------------------------

      TDirectory *jetSize = outf->mkdir("JetSizePlots");
      jetSize->cd();

         TH1 *histJetSize            = new TH1F("Jet_Size", "jet Size" , 13, 0, 13);
         TH1 *histJetSize_CA         = new TH1F("Jet_Size_CA", "jet Size_CA" , 13, 0, 13);

     gSystem->Load("libDelphes");
	  gSystem->Load("libExRootAnalysis");

 // Create chain of root trees
 TChain chain("Delphes");
 chain.Add(inputFile.c_str());

 // Create object of class ExRootTreeReader
 ExRootTreeReader *treeReader   = new ExRootTreeReader(&chain);
 Long64_t numberOfEntries       = treeReader->GetEntries();

 // Get pointers to branches used in this analysis
 TClonesArray *branchJet    = treeReader->UseBranch("Jet");
 TClonesArray *branchJet_CA    = treeReader->UseBranch("Jet_CA");
 TClonesArray *branchGenJet = treeReader->UseBranch("GenJet");
 TClonesArray *branchGenJet_CA = treeReader->UseBranch("GenJet_CA");
 TClonesArray *branchSHT 	 = treeReader->UseBranch("ScalarHT");
 TClonesArray *branchSHT_CA 	 = treeReader->UseBranch("ScalarHT_CA");


// some definitions

 vector<Jet *> jetta;
 vector<Jet *> genjetta;
 vector<Jet *> jetta_CA;
 vector<Jet *> genjetta_CA;

 ScalarHT* sht = 0;
 ScalarHT* sht_CA = 0;

 Jet *jet;
 Jet *genjet;
 Jet *jet_CA;
 Jet *genjet_CA;

 int decade = 0;

 // Loop over all events

	for(int entry = 0; entry < numberOfEntries; ++entry)
 	{
//   		if(entry%1000 == 0) cout << "event number: " << entry << endl;

      double progress = 10.0*entry/(1.0*numberOfEntries);
      int k = TMath::FloorNint(progress);
      if (k > decade) {   cout << 10*k << "%\t"; gSystem->Exec("date '+%H:%M:%S'"); cout << endl;	}
      decade = k;

   	// Load selected branches with data from specified event
   	treeReader->ReadEntry(entry);

///////////////////////////// Jet Size /////////////////////////////////////////-------------------

      histJetSize->Fill( branchJet->GetEntriesFast() ) ;
      histJetSize_CA->Fill( branchJet_CA->GetEntriesFast() ) ;

///////////////////////////////CALO JET/////////////////////////////////--------------------------

      jetta.clear();

   	for(int i = 0; i < branchJet->GetEntriesFast(); ++i)
      {
			jet = (Jet*) branchJet->At(i);
			jetta.push_back(jet);
		}

		//PT distribution of CaloJets-------------------------------------------------

      if(jetta.size() > 0)
		{
			for(unsigned i = 0 ; i < jetta.size() ; ++i)
			{
				histcalojetPT->Fill(jetta[i]->PT);
			}
		}
///////////////////////////////CALO JET Cambrigde/Aachen  /////////////////////////////////--------------------------

      jetta_CA.clear();

   	for(int i = 0; i < branchJet_CA->GetEntriesFast(); ++i)
      {
			jet_CA = (Jet*) branchJet_CA->At(i);
			jetta_CA.push_back(jet_CA);
		}

		//PT distribution of CaloJets   CA   -------------------------------------------------

      if(jetta_CA.size() > 0)
		{
			for(unsigned i = 0 ; i < jetta_CA.size() ; ++i)
			{
				histcalojetPT_CA->Fill(jetta_CA[i]->PT);
			}
		}
///////////////////////////////GEN JET/////////////////////////////////--------------------------------------

		genjetta.clear();

		for(int i = 0; i < branchGenJet->GetEntriesFast(); ++i)
   	{
			genjet = (Jet*) branchGenJet->At(i);
			genjetta.push_back(genjet);
 		}

		//PT dist of GenJets------------------------------------------------------------------------------

      if(genjetta.size() > 0)
		{
			for(unsigned i = 0 ; i < genjetta.size() ; ++i)
			{
				histgenjetPT->Fill(genjetta[i]->PT);
			}
		}

///////////////////////////////GEN JET   Cambrigde/Aachen   /////////////////////////////////--------------------------------------

		genjetta_CA.clear();

		for(int i = 0; i < branchGenJet_CA->GetEntriesFast(); ++i)
   	{
			genjet_CA = (Jet*) branchGenJet_CA->At(i);
			genjetta_CA.push_back(genjet_CA);
 		}

		//PT dist of GenJets------------------------------------------------------------------------------

      if(genjetta_CA.size() > 0)
		{
			for(unsigned i = 0 ; i < genjetta_CA.size() ; ++i)
			{
				histgenjetPT_CA->Fill(genjetta_CA[i]->PT);
			}
		}

////////////////// PT RESOLUTION NEW METHOD---------------------------------------------------------------

        double PtResoNEW = 0;
        double delta_phi_for_Reso;

        if( genjetta.size() == jetta.size() )
        {
           for(unsigned i = 0 ; i < genjetta.size() ; ++i )
      	  {
              if ( ( abs( genjetta[i]->Eta ) <= JETETACUT ) && ( genjetta[i]->PT > JETPTCUT ) )
              {

                 if ( abs(jetta[i]->Phi - genjetta[i]->Phi) <= 3.141592 )
                 {
                     delta_phi_for_Reso = abs(jetta[i]->Phi - genjetta[i]->Phi) ;
                 }
                 else
                 {
                     delta_phi_for_Reso = ( (2 * 3.141592) - abs(jetta[i]->Phi - genjetta[i]->Phi) ) ;
                 }

                 std::cout << "delta_phi = " << delta_phi_for_Reso << std::endl;
                 double delta_eta_for_Reso = abs(jetta[i]->Eta - genjetta[i]->Eta) ;
                 double delta_r_for_Reso = sqrt( pow( delta_phi_for_Reso ,2 ) + pow( delta_eta_for_Reso ,2 ) );

                 if ( delta_r_for_Reso < 0.25 )
                 {
                    double PtResoFullNEW = ( (genjetta[i]->PT) - (jetta[i]->PT) );
                    hist_PtResoFullNEW->Fill(genjetta[i]->PT,PtResoFullNEW);

                    for (int a=0; a <ptIntervalsArraySize-1; a++)
                    {
                      if( ( ptIntervals[a] <= genjetta[i]->PT ) && ( genjetta[i]->PT < ptIntervals[a+1] ) )
                      {
                        PtResoNEW = jetta[i]->PT / genjetta[i]->PT ;
                        histRelativePtResoPTBins[a]->Fill(PtResoNEW);
                      }
                    }
                 }
              }
           }
        }

////////////////// PT RESOLUTION NEW METHOD Cambridge/Aachen   ---------------------------------------------------------------

        double PtResoNEW_CA = 0;
        double delta_phi_for_Reso_CA;

        if( genjetta_CA.size() == jetta_CA.size() )
        {
           for(unsigned i = 0 ; i < genjetta_CA.size() ; ++i )
      	  {
              if ( ( abs( genjetta_CA[i]->Eta ) <= JETETACUT ) && ( genjetta_CA[i]->PT > JETPTCUT ) )
              {
               //   std::cout << "jetta_CA phi = " << genjetta_CA[i]->Phi << std::endl;
               //   std::cout << "jetta_CA Eta = " << genjetta_CA[i]->Eta << std::endl;

                 if ( abs(jetta_CA[i]->Phi - genjetta_CA[i]->Phi) <= 3.141592 )
                 {
                     delta_phi_for_Reso_CA = abs(jetta_CA[i]->Phi - genjetta_CA[i]->Phi) ;
                 }
                 else
                 {
                     delta_phi_for_Reso_CA = ( (2 * 3.141592) - abs(jetta_CA[i]->Phi - genjetta_CA[i]->Phi) ) ;
                 }

                 std::cout << "delta_phi_CA = " << delta_phi_for_Reso_CA << std::endl;
                 double delta_eta_for_Reso_CA = abs(jetta_CA[i]->Eta - genjetta_CA[i]->Eta) ;
                 double delta_r_for_Reso_CA = sqrt( pow( delta_phi_for_Reso_CA ,2 ) + pow( delta_eta_for_Reso_CA ,2 ) );

                 if ( delta_r_for_Reso_CA < 0.25 )
                 {
                    double PtResoFullNEW_CA = ( (genjetta_CA[i]->PT) - (jetta_CA[i]->PT) );
                    hist_PtResoFullNEW_CA->Fill(genjetta_CA[i]->PT,PtResoFullNEW_CA);

                    for (int a=0; a <ptIntervalsArraySize-1; a++)
                    {
                      if( ( ptIntervals[a] <= genjetta_CA[i]->PT ) && ( genjetta_CA[i]->PT < ptIntervals[a+1] ) )
                      {
                        PtResoNEW_CA = jetta_CA[i]->PT / genjetta_CA[i]->PT ;
                        histRelativePtResoPTBins_CA[a]->Fill(PtResoNEW_CA);
                      }
                    }
                 }
              }
           }
        }
///////////////// SCALAR HT   --------------------------------------------------------

        if(jetta.size() > 0)
        {
            if(branchSHT->GetEntries() > 0)
            {
      			sht = (ScalarHT *) branchSHT->At(0);
   		      hist_SHT->Fill(sht->HT);

            }
        }


///////////////// SCALAR HT  Cambrigde/Aachen --------------------------------------------------------

        if(jetta_CA.size() > 0)
        {
            if(branchSHT_CA->GetEntries() > 0)
            {
      			sht_CA = (ScalarHT *) branchSHT_CA->At(0);
   		      hist_SHT_CA->Fill(sht_CA->HT);

            }
        }
	 }

    cout << "csamaner! For inputfile " << inputFile << "..." << endl;
    cout << "csamaner! number of total entries : "<< numberOfEntries << endl;
    cout << "csamaner! ----------------------------------------------------------------------\n" ;
   //  for (int i=0;i<ptIntervalsArraySize;i++)
   //  {
   //    cout << "\n" << ptIntervals[i] << endl;
   //  }

    outf->Write();
    outf->Close();
}
