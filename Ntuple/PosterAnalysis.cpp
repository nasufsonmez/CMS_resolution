#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <time.h>

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
#include <TMath.h>
#include <TProfile.h>
#include <TString.h>
#include "TVectorD.h"
#include "TLorentzVector.h"

#include "Utilities.h"
#include "analyze_events.h"

using namespace std;


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

int main(int argc, char*argv[])
{
    //----------------------------------------------------------------------------------------
    /////////////////////////////////////////////  Read Input Parameters  ////////////////////
    //----------------------------------------------------------------------------------------
    if (argc < 2) {printf("******Error in input parameters\n");return 1;}

    CommandLine c1;
    c1.parse(argc,argv);
    gROOT->ProcessLine("#include >vector<");

    string InputFileName	= c1.getValue<string>	("InputFileName");
    string OutputFileName	= c1.getValue<string>	("OutputFileName");
    int NENTRIES			  = c1.getValue<int>		("NEntries");


    if ( !c1.check() ) return 0;
    c1.print();				// Printing the options

    string outputfile = OutputFileName  + ".root";
    TFile *outf = new TFile(outputfile.c_str(),"RECREATE");

    cout << "________________________________________________________________\n";
    cout << "\n";
    cout << "time start  " << endl;
    gSystem->Exec("date '+%H:%M:%S'");

    //----------------------------------------------------------------------------------------
    ///////////////////////////////////////////////  Histogram Output  ///////////////////////
    //----------------------------------------------------------------------------------------
    // Book histograms

    //char hist_name[100];
	  //char hist_title[100];

    //----------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------
    //////////////////////////////////   BRANCHES AND CHAIN OVER INPUT FILES //////////////////////////////////
    //---------------------------------------------------------------------------------------------------------

	  string inputfile = InputFileName + ".root";

  	TFile *inf  = new TFile(inputfile.c_str());
    TTree *data = (TTree*)inf->Get("DATA");

    int NJET_MAX =12;
    char branch_name[100];

    TBranch *b_event = data->GetBranch("eventVar");
    EVENT_VAR event;
    b_event->SetAddress(&event);

    TBranch *b_jet[NJET_MAX];
    JET jet[NJET_MAX];

    for ( int a=0; a<NJET_MAX; a++ )
    {
        sprintf(branch_name,"jet%iVar",a+1);
        b_jet[a]= (TBranch*)data->GetBranch(branch_name);
        b_jet[a]->SetAddress( &jet[a] );
    }


    Long64_t numberOfEntries = b_event->GetEntries();
    cout << "Set Branch Addresses" << endl;

    //----------------------------------------------------------------------------------------
    /////////////////////////////////////  LOOP  Over the EVENTS  ////////////////////////////
    //----------------------------------------------------------------------------------------

    unsigned entries = 0;

    if (NENTRIES==-1) entries=numberOfEntries;
    else entries=NENTRIES;

    cout << "Reading TREE: " << numberOfEntries << " events available, \n";
    cout << "\t\t" << NENTRIES << " of them will be analyzed." << endl;


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//___________________________________________________________________________________________________________
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int decade = 0;
    //std::cout << "/* message */ Before Loop" << std::endl;

    // Loop over all events
    for(Long64_t entry = 0; entry < entries; ++entry)
    {
        //nevents++;
		//progress( entries, entry );
		double progress = 10.0*entry/(1.0*entries);
		int k = TMath::FloorNint(progress);
		if (k > decade) {   cout << 10*k << "%\t"; gSystem->Exec("date '+%H:%M:%S'"); cout << endl;	}
		decade = k;

    // Load selected branches with data from specified event
    b_event->GetEvent(entry);
    for ( int a =0; a<NJET_MAX; a++ )	      b_jet[a]->GetEvent(entry);

    int jet_counter_cut=0;

    for (int i=0; i< NJET_MAX; i++)
    {
                if(jet[i].PT  == -999) continue;
                jet_counter_cut++;
    }


    int jet_counter=0;
    int jet_eta_counter=0;

    for (int i=0; i< NJET_MAX; i++)
    {
            if(jet[i].PT == -999) continue;

            jet_counter++;
            if(jet[i].PT > 50  && abs(jet[i].Eta) < 3.0) jet_eta_counter++;
            histJet_pt->Fill(jet[i].PT);
            histJet_eta->Fill(jet[i].Eta);
            histJet_phi->Fill(jet[i].Phi);

    }
    histJet_size->Fill(jet_counter);
    histJet_size_cut->Fill(jet_eta_counter);

    }	//end of event loop

    //---------------------------------------------------------------------------------------------------------
  	////////////////////////////////  Saving the histograms into output  //////////////////////////////////////////
  	//---------------------------------------------------------------------------------------------------------




    cout << "\t" << InputFileName.c_str() << endl;
    std::cout << "Pi number:  " <<  M_PI << std::endl;

    //myfile.close();
    outf->Write();
    outf->Close();

    //end of main loop
}
