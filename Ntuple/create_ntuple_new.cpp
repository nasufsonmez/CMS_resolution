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
#include <time.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include "TLatex.h"
#include "TLegend.h"
#include "Utilities.h"
#include "TVectorD.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
#include "DelphesClasses.h"
#include "Math/GenVector/VectorUtil.h"

#include "skimming_events_new.h"

using namespace std;

//----------------------------------------------------------------------------------------
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
	int NENTRIES			= c1.getValue<int>		("NEntries");


	if (!c1.check()) return 0;
	c1.print(); // Printing the options


	string outputfile = OutputFileName + ".root";

	TFile *outf = new TFile(outputfile.c_str(),"RECREATE");
	//TFile *outf = new TFile(OutputFileName.c_str(),"RECREATE");

	cout << "________________________________________________________________\n";
	cout << "\n";
	cout << "time start  " << endl;
	gSystem->Exec("date '+%H:%M:%S'");

	//----------------------------------------------------------------------------------------
	////////////////////////////////////////  My Data STructure  /////////////////////////////
	//----------------------------------------------------------------------------------------

	int MAX_NJETS =15;

	TTree *outputTree = new TTree("DATA","a tree of event info and jet info");
	//TTree::SetMaxTreeSize(100000000000LL);	//the maximum tree size
	outputTree->SetDirectory(outf);

	JET aux_jet[MAX_NJETS];
	JET aux_genjet[MAX_NJETS];
	JET aux_jet_CA[MAX_NJETS];
	JET aux_genjet_CA[MAX_NJETS];
	// JET aux_jet_KT[MAX_NJETS];
	// JET aux_genjet_KT[MAX_NJETS];


	char name[2000];


	for(int i=0;i<MAX_NJETS;i++)
	{
		sprintf(name,"jet%dVar",i+1);
		outputTree->Branch(name, &aux_jet[i],"PT/D:Eta:Phi");
	}
	for(int i=0;i<MAX_NJETS;i++)
	{
		sprintf(name,"genjet%dVar",i+1);
		outputTree->Branch(name, &aux_genjet[i],"PT/D:Eta:Phi");
	}
	for(int i=0;i<MAX_NJETS;i++)
	{
		sprintf(name,"jet_CA%dVar",i+1);
		outputTree->Branch(name, &aux_jet_CA[i],"PT/D:Eta:Phi");
	}
	for(int i=0;i<MAX_NJETS;i++)
	{
		sprintf(name,"genjet_CA%dVar",i+1);
		outputTree->Branch(name, &aux_genjet_CA[i],"PT/D:Eta:Phi");
	}
	// for(int i=0;i<MAX_NJETS;i++)
	// {
	// 	sprintf(name,"jet_KT%dVar",i+1);
	// 	outputTree->Branch(name, &aux_jet_KT[i],"PT/D:Eta:Phi");
	// }
	// for(int i=0;i<MAX_NJETS;i++)
	// {
	// 	// sprintf(name,"genjet_KT%dVar",i+1);
	// 	outputTree->Branch(name, &aux_genjet_KT[i],"PT/D:Eta:Phi");
	// }


	cout<<"event tree is booked"<<endl;

	gSystem->Load("libExRootAnalysis");
	gSystem->Load("libDelphes");

	// Create chain of root trees
	TChain chain("Delphes");
	//chain.Add(InputFileName.c_str());
	char filename[1000];
	FILE *input;
	input = fopen(InputFileName.c_str(),"r");
	if (input != NULL)
	{
		// lets read each line and get the filename from it
		while (fscanf(input,"%s\n",filename) != EOF)
		{
			printf("%s\n",filename);
			chain.Add(filename);
		}
	}
		// Create object of class ExRootTreeReader
	ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
	Long64_t numberOfEntries = treeReader->GetEntries();

	// Get pointers to branches used in this analysis
	TClonesArray *branchJet 	 = treeReader->UseBranch("Jet");
	TClonesArray *branchgenJet 	 = treeReader->UseBranch("GenJet");
	TClonesArray *branchJet_CA 	 = treeReader->UseBranch("Jet_CA");
	TClonesArray *branchgenJet_CA 	 = treeReader->UseBranch("GenJet_CA");
	// TClonesArray *branchJet_KT 	 = treeReader->UseBranch("Jet_KT");
	// TClonesArray *branchgenJet_KT 	 = treeReader->UseBranch("GenJet_KT");


	//----------------------------------------------------------------------------------------
	/////////////////////////////////////  LOOP  Over the EVENTS  ////////////////////////////
	//----------------------------------------------------------------------------------------

	cout << "Set Branch Addresses" << endl;

	int decade = 0;
	unsigned entries = 0;

	if (NENTRIES==-1) entries=numberOfEntries;
	else entries=NENTRIES;

	outf->cd();

	cout << "Reading TREE:  " << OutputFileName.c_str() << "   \t " << numberOfEntries << " events available, \n";
	cout << "\t\t" << NENTRIES << " of them will be analyzed." << endl;


	Jet *jet[15];
	Jet *genjet[15];
	Jet *jet_CA[15];
	Jet *genjet_CA[15];
	// Jet *jet_KT[15];
	// Jet *genjet_KT[15];


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Loop over all events
	for(Long64_t entry = 0; entry < entries; ++entry)
	{

		double progress = 10.0*entry/(1.0*entries);
		int k = TMath::FloorNint(progress);
		if (k > decade) {   cout << 10*k << "%\t"; gSystem->Exec("date '+%H:%M:%S'"); cout << endl;	}
		decade = k;

		// Load selected branches with data from specified event
		treeReader->ReadEntry(entry);

		//////////////////////////////////////////////////////////////
		//JET Properties/////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		vector<JET> all_jets;
		all_jets.clear();
		vector<JET> all_genjets;
		all_genjets.clear();
		// vector<JET> all_jets_KT;
		// all_jets_KT.clear();
		// vector<JET> all_genjets_KT;
		// all_genjets_KT.clear();
		vector<JET> all_jets_CA;
		all_jets_CA.clear();
		vector<JET> all_genjets_CA;
		all_genjets_CA.clear();


		for (int i=0; i < MAX_NJETS ; i++)
		{

			///////////////////// Anti-KT JET  ///////////////


			if(branchJet->GetEntries() > i ){

				jet[i] = (Jet*) branchJet->At(i);
			  JET jetvar;
				jetvar.PT=jet[i]->PT;
				jetvar.Eta=jet[i]->Eta;
				jetvar.Phi=jet[i]->Phi;
				all_jets.push_back(jetvar);

			}else{
				JET jetvar;
				jetvar.PT=-999;
				jetvar.Eta=-999;
				jetvar.Phi=-999;
				all_jets.push_back(jetvar);
			}

			////////////// Anti-KT Genjets

			if(branchgenJet->GetEntries() > i ){

				genjet[i] = (Jet*) branchgenJet->At(i);
			  JET genjetvar;
				genjetvar.PT=genjet[i]->PT;
				genjetvar.Eta=genjet[i]->Eta;
				genjetvar.Phi=genjet[i]->Phi;
				all_genjets.push_back(genjetvar);

			}else{
				JET genjetvar;
				genjetvar.PT=-999;
				genjetvar.Eta=-999;
				genjetvar.Phi=-999;
				all_genjets.push_back(genjetvar);
			}

				//////////////////////// Cambridge/Aachen jets ///////////////////////

			if(branchJet_CA->GetEntries() > i ){

				jet_CA[i] = (Jet*) branchJet_CA->At(i);
			  JET jetvar_CA;
				jetvar_CA.PT=jet_CA[i]->PT;
				jetvar_CA.Eta=jet_CA[i]->Eta;
				jetvar_CA.Phi=jet_CA[i]->Phi;
				all_jets_CA.push_back(jetvar_CA);

			}else{
				JET jetvar_CA;
				jetvar_CA.PT=-999;
				jetvar_CA.Eta=-999;
				jetvar_CA.Phi=-999;
				all_jets_CA.push_back(jetvar_CA);
			}

			///////////////////////// C/A genjets

			if(branchgenJet_CA->GetEntries() > i ){

				genjet_CA[i] = (Jet*) branchgenJet_CA->At(i);
			  JET genjetvar_CA;
				genjetvar_CA.PT=genjet_CA[i]->PT;
				genjetvar_CA.Eta=genjet_CA[i]->Eta;
				genjetvar_CA.Phi=genjet_CA[i]->Phi;
				all_genjets_CA.push_back(genjetvar_CA);

			}else{
				JET genjetvar_CA;
				genjetvar_CA.PT=-999;
				genjetvar_CA.Eta=-999;
				genjetvar_CA.Phi=-999;
				all_genjets_CA.push_back(genjetvar_CA);
			}

				///////////////////////////// KT jets /////////////////////////

			// // if(branchJet_KT->GetEntries() > i ){
			//
			// 	jet_KT[i] = (Jet*) branchJet_KT->At(i);
			// //   JET jetvar_KT;
			// 	jetvar_KT.PT=jet_KT[i]->PT;
			// 	jetvar_KT.Eta=jet_KT[i]->Eta;
			// 	jetvar_KT.Phi=jet_KT[i]->Phi;
			// 	all_jets_KT.push_back(jetvar_KT);
			//
			// }else{
			// 	// JET jetvar_KT;
			// 	// jetvar_KT.PT=-999;
			// 	// jetvar_KT.Eta=-999;
			// 	// jetvar_KT.Phi=-999;
			// 	all_jets_KT.push_back(jetvar_KT);
			// }
			//
			// 	////////////////////// KT genjets ///////////////////////////
			//
			// // if(branchgenJet_KT->GetEntries() > i ){
			//
			// 	genjet_KT[i] = (Jet*) branchgenJet_KT->At(i);
			// //   JET genjetvar_KT;
			// 	genjetvar_KT.PT=genjet_KT[i]->PT;
			// 	genjetvar_KT.Eta=genjet_KT[i]->Eta;
			// 	genjetvar_KT.Phi=genjet_KT[i]->Phi;
			// 	all_genjets_KT.push_back(genjetvar_KT);
			//
			// }else{
			// 	// JET genjetvar_KT;
			// 	// genjetvar_KT.PT=-999;
			// 	// genjetvar_KT.Eta=-999;
			// 	// genjetvar_KT.Phi=-999;
			// 	all_genjets_KT.push_back(genjetvar_KT);
			// }
		}




	///////////////////////////////////////////////////////////////////////////
	/////////SAVE BRANCHES ///////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

		//save jets
		for(int j=0; j < MAX_NJETS;j++) aux_jet[j] = all_jets[j];
		//save genjets
		for(int j=0; j < MAX_NJETS;j++) aux_genjet[j] = all_genjets[j];
		//save jets_CA
		for(int j=0; j < MAX_NJETS;j++) aux_jet_CA[j] = all_jets_CA[j];
		//save genjets_CA
		for(int j=0; j < MAX_NJETS;j++) aux_genjet_CA[j] = all_genjets_CA[j];
		// save jets_KT
		// for(int j=0; j < MAX_NJETS;j++) aux_jet_KT[j] = all_jets_KT[j];
		// save genjets_KT
		// for(int j=0; j < MAX_NJETS;j++) aux_genjet_KT[j] = all_genjets_KT[j];

		outputTree->Fill();


	}	//end of event loop

	outf->cd();
	outf = outputTree->GetCurrentFile(); //to get the pointer to the current file
	outf->Write();
	outf->Close();

}	//end of main loop
