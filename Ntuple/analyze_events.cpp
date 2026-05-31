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
    TDirectory *jet_dir= outf->mkdir("Jet");
  	jet_dir->cd();

    TH1F  *histJet_size       = new TH1F("jet_size"	 ,       "JET SIZE",          15,      0.0,   15.0);
    TH1F  *histJet_pt    	    = new TH1F("jet_pt"     ,      "Jet PT All ",       100.0,   0.0,   2000.0);
    TH1F  *histJet_pt_1    	  = new TH1F("jet_pt_1"     ,    "Jet PT 1 ",         100.0,   0.0,   2000.0);
    TH1F  *histJet_pt_2    	  = new TH1F("jet_pt_2"     ,    "Jet PT 2 ",         100.0,   0.0,   2000.0);
    TH1F  *histJet_eta   	    = new TH1F("jet_eta"    ,      "Jet Eta All",       100.0,  -10.0,  10.0);
    TH1F  *histJet_phi   	    = new TH1F("jet_phi"    ,      "Jet Phi All ",      100.0,  -3.5,   3.5);
    TH1F  *histJet_mass  	  	= new TH1F("jet_mass"   ,      "Jet Mass All ",     100.0,   0.0,   450.0);
    TH1F  *histJet_phi_1  	  = new TH1F("jet_phi_1"   ,     "Jet Phi 1 ",        100.0,  -3.5,   3.5);
    TH1F  *histJet_eta_1  	  = new TH1F("jet_eta_1"   ,     "Jet Eta 1 ",        100.0,  -10.0,  10.0);
    TH1F  *histJet_phi_2  	  = new TH1F("jet_phi_2"   ,     "Jet Phi 2 ",        100.0,  -3.5,   3.5);
    TH1F  *histJet_eta_2  	  = new TH1F("jet_eta_2"   ,     "Jet Eta 2 ",        100.0,  -10.0,  10.0);
    TH1F  *histJet_deltaphi  	= new TH1F("jet_delta_phi"   , "Jet Delta Phi  ",   100.0,  -7.0,   7.0);
    TH1F  *histJet_deltaeta  	= new TH1F("jet_delta_eta"   , "Jet Delta Eta  ",   100.0,  -7.0,   7.0);
    TH1F  *histJet_deltar   	= new TH1F("jet_deltar"      , "Jet DeltaR ",       100.0,   0.,    15.);
    TH1F  *histJet_deltaphi_1 = new TH1F("jet_delta_phi_1" , "Jet Delta Phi 1 ",  100.0,  -7.0,   7.0);
    TH1F  *histJet_deltaeta_1 = new TH1F("jet_delta_eta_1" , "Jet Delta Eta 1 ",  100.0,  -20.0,  20.0);
    TH1F  *histJet_deltar_1  	= new TH1F("jet_deltar_1"    , "Jet DeltaR 1 ",     100.0,   0.,    15.);
    TH1F  *histJet_charge    	= new TH1F("jet_charge"      , "Jet Charge ",       4.0,    -2.0,   2.0);
    TH1F  *histJet_btag    	  = new TH1F("jet_btag"        , "Jet BTag "  ,       30.0,    0.0,   30.0);
    TH1F  *histJet_tautag   	= new TH1F("jet_tautag"      , "Jet TauTag ",       3.0,     0.0,   3.0);
    //histJet_invmass	  = new TH1F("jet_invmass"     , "Jet Inv Mass",      100.0,   0.,    1200.);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////

  	TDirectory *event_dir= outf->mkdir("eventVar");
  	event_dir->cd();
  	TH1F  *histHt    	   = new TH1F("ht"         , "HT" ,       100.0,   0.0,   4500.0);
  	TH1F  *histMet   	   = new TH1F("met"     	 , "MET",       100.0,   0.0,   1000.0);
  	TH1F  *histMet_phi   = new TH1F("met_phi"    , "MET Phi",   100.0,  -3.5,   3.5);
  	TH1F  *histMet_eta   = new TH1F("met_eta"    , "MET Eta",   100.0,  -10.5,  10.5);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////

    TDirectory *muon_dir= outf->mkdir("Muon");
    muon_dir->cd();
    TH1  *histMuon_pt      = new TH1F("muon_pt"     , "Muon PT" ,   	 100.0,    0.0,    1000.0);
    TH1  *histMuon_eta     = new TH1F("muon_eta"    , "Muon Eta",   	 100.0,   -10.0,   10.0);
    TH1  *histMuon_phi     = new TH1F("muon_phi"    , "Muon Phi",   	 100.0,   -3.5,    3.5);
    TH1  *histMuon_charge  = new TH1F("muon_charge" , "Muon Charge",   100.0,   -2.0,    2.0);
    TH1  *histMuon_size	   = new TH1F("muon_size"   , "Muon Size",  	 5.0,      0.,     5.);

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  	TDirectory *electron_dir= outf->mkdir("Electron");
  	electron_dir->cd();
  	TH1F  *histElectron_pt    	= new TH1F("electron_pt"     , "Electron PT" ,   	100.0,   0.0,    1000.0);
  	TH1F  *histElectron_eta     = new TH1F("electron_eta"    , "Electron Eta",   	100.0,  -10.0,   10.0);
  	TH1F  *histElectron_phi   	= new TH1F("electron_phi"    , "Electron Phi",   	100.0,  -3.5,    3.5);
  	TH1F  *histElectron_charge  = new TH1F("electron_charge" , "Electron Charge", 100.0,  -2.0,    2.0);
  	TH1F  *histElectron_size	  = new TH1F("electron_size"   , "Electron Size",  	5.0,     0.,     5.);

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  	TDirectory *photon_dir= outf->mkdir("Photon");
  	photon_dir->cd();

    TH1F *histPhoton_size       = new TH1F("photon_size"	      , "PHOTON SIZE",        5,       0.0,   5.0);
    TH1F *histPhoton_eta    	  = new TH1F("photon_eta"         , "Photon Eta",         100.0,  -10.0,  10.0);
    TH1F *histPhoton_phi    	  = new TH1F("photon_phi"         , "Photon Phi",         100.0,  -3.5,   3.5);
    TH1F *histPhoton_eta_1    	= new TH1F("photon_eta_1"       , "Photon Eta 1",       100.0,  -10.0,  10.0);
  	TH1F *histPhoton_phi_1    	= new TH1F("photon_phi_1"       , "Photon Phi 1",       100.0,  -3.5,   3.5);
    TH1F *histPhoton_eta_2    	= new TH1F("photon_eta_2"       , "Photon Eta 2",       100.0,  -10.0,  10.0);
    TH1F *histPhoton_phi_2    	= new TH1F("photon_phi_2"       , "Photon Phi 2",       100.0,  -3.5,   3.5);
    TH1F *histPhoton_e    	    = new TH1F("photon_e"           , "Photon E",           100.0,   0.0,   4000.);
    TH1F *histPhoton_ht     	  = new TH1F("photon_ht"          , "Photon HT" ,   		  100.0,   0.0,   4500.0);
  	TH1F *histPhoton_pt     	  = new TH1F("photon_pt"          , "Photon PT" ,   		  100.0,   0.0,   2000.0);
  	TH1F *histPhoton_pt_1       = new TH1F("photon_pt_1"        , "Photon PT Leading",  100.0,   0.0,   2000.0);
  	TH1F *histPhoton_pt_2       = new TH1F("photon_pt_2"        , "Photon PT Second" ,  100.0,   0.0,   2000.0);
  	TH1F *histPhoton_deltaphi   = new TH1F("photon_delta_phi"   , "Photon Delta Phi",   100.0,  -7.0,   7.0);
  	TH1F *histPhoton_deltaeta   = new TH1F("photon_delta_eta"   , "Photon Delta Eta",   100.0,  -20.0,  20.0);
  	TH1F *histPhoton_deltar     = new TH1F("photon_deltar"      , "Photon DeltaR",   	  100.0,   0.,    15.);
  	TH1F *histPhoton_invmass	  = new TH1F("photon_invmass"     , "Photon Inv Mass",    100.0,   0.,    1200.);

    TDirectory *lepton_dir= outf->mkdir("Lepton");
  	lepton_dir->cd();

    TH1F *histLepton_size       = new TH1F("lepton_size"	      , "LEPTON SIZE",        5,       0.0,   5.0);


    //---------------------------------------------------------------------------------------------------------
    //////////////////////////////////   BRANCHES AND CHAIN OVER INPUT FILES //////////////////////////////////
    //---------------------------------------------------------------------------------------------------------

	  string inputfile = InputFileName + ".root";

  	TFile *inf  = new TFile(inputfile.c_str());
    TTree *data = (TTree*)inf->Get("DATA");

    int NJET_MAX =12;
  	int NMUON_MAX=5;
  	int NELECTRON_MAX=5;
  	int NPHOTON_MAX=5;;

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

    TBranch *b_photon[5];
    PHOTON photon[5];

    for ( int a=0; a<NPHOTON_MAX; a++ )
    {
        sprintf(branch_name,"photon%iVar",a+1);
        b_photon[a]= (TBranch*)data->GetBranch(branch_name);
        b_photon[a]->SetAddress( &photon[a] );
    }

    TBranch *b_muon[5];
    MUON muon[5];

    for ( int a=0; a<NMUON_MAX; a++ )
    {
        sprintf(branch_name,"muon%iVar",a+1);
        b_muon[a]= (TBranch*)data->GetBranch(branch_name);
        b_muon[a]->SetAddress( &muon[a] );
    }

    TBranch *b_electron[5];
    ELECTRON electron[5];

    for ( int a=0; a<NELECTRON_MAX; a++ )
    {
        sprintf(branch_name,"electron%iVar",a+1);
        b_electron[a]= (TBranch*)data->GetBranch(branch_name);
        b_electron[a]->SetAddress( &electron[a] );
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
    int photon_counter_0=0;
    int photon_counter_1=0;
    int photon_counter_2=0;
    int photon_counter_3=0;
    int photon_counter_4=0;

    int photon_counter_new=0;

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
    for ( int a =0; a<NPHOTON_MAX; a++ )    b_photon[a]->GetEvent(entry);
    for ( int a =0; a<NMUON_MAX; a++ )	    b_muon[a]->GetEvent(entry);
    for ( int a =0; a<NELECTRON_MAX; a++ )	b_electron[a]->GetEvent(entry);

    double delta_Phi = 0.0;
  	double delta_Eta = 0.0;
  	double delta_R = 0.0;

    //------------------------------------------------------------
    //------------------------------------------------------------
    if(event.HT != -999) histHt->Fill(event.HT);
    if(event.MET != -999){
    histMet->Fill(event.MET);
    histMet_eta->Fill(event.METEta);
    histMet_phi->Fill(event.METPhi);
    }
    //------------------------------------------------------------
    //------------------------------------------------------------

    int photon_counter=0;
    double photon_ht_value=0;

    for (int i=0; i< NPHOTON_MAX; i++)
    {
                if(photon[i].PT  == -999) continue;
                photon_counter_new++;

                photon_counter++;
      		    	histPhoton_pt->Fill(photon[i].PT);
      		    	histPhoton_eta->Fill(photon[i].Eta);
      		    	histPhoton_phi->Fill(photon[i].Phi);
      		    	histPhoton_e->Fill(photon[i].E);
                photon_ht_value = photon_ht_value + photon[i].PT;


    }
    histPhoton_size->Fill(photon_counter);

    if(photon_counter > 1){
    delta_Eta = photon[1].Eta - photon[0].Eta;
    delta_Phi = photon[1].Phi - photon[0].Phi;
    delta_R = sqrt( pow(abs(delta_Phi),2) + pow(abs(delta_Eta),2));

    if(delta_Phi >  M_PI) delta_Phi = delta_Phi - M_PI;
    if(delta_Phi < -M_PI) delta_Phi = delta_Phi + M_PI;

    histPhoton_deltaeta->Fill(delta_Eta);
    histPhoton_deltaphi->Fill(delta_Phi);
    histPhoton_deltar->Fill(delta_R);
    histPhoton_invmass->Fill(photon_invariant_mass(photon[0], photon[1]));
    }

    if(photon_counter > 0) histPhoton_pt_1->Fill(photon[0].PT);
    if(photon_counter > 0) histPhoton_eta_1->Fill(photon[0].Eta);
    if(photon_counter > 0) histPhoton_phi_1->Fill(photon[0].Phi);

    if(photon_counter > 1) histPhoton_pt_2->Fill(photon[1].PT);
    if(photon_counter > 1) histPhoton_eta_2->Fill(photon[1].Eta);
    if(photon_counter > 1) histPhoton_phi_2->Fill(photon[1].Phi);

    histPhoton_ht->Fill(photon_ht_value);

    if(photon_counter == 0) photon_counter_0++;
    if(photon_counter == 1) photon_counter_1++;
    if(photon_counter == 2) photon_counter_2++;
    if(photon_counter == 3) photon_counter_3++;
    if(photon_counter == 4) photon_counter_4++;



    //------------------------------------------------------------
    //------------------------------------------------------------

    int jet_counter=0;

    for (int i=0; i< NJET_MAX; i++)
    {
            if(jet[i].PT == -999) continue;

            jet_counter++;

            histJet_pt->Fill(jet[i].PT);
            histJet_eta->Fill(jet[i].Eta);
            histJet_phi->Fill(jet[i].Phi);
            histJet_mass->Fill(jet[i].Mass);
            histJet_deltaeta->Fill(jet[i].DeltaEta);
            histJet_deltaphi->Fill(jet[i].DeltaPhi);
            histJet_deltar->Fill(sqrt( pow(abs(jet[i].DeltaEta),2) + pow(abs(jet[i].DeltaPhi),2)));
            histJet_charge->Fill(jet[i].Charge);
            histJet_btag->Fill(jet[i].BTag);
            histJet_tautag->Fill(jet[i].TauTag);

    }
    histJet_size->Fill(jet_counter);

    if(jet_counter > 1){

      delta_Eta = jet[1].Eta - jet[0].Eta;
      delta_Phi = jet[1].Phi - jet[0].Phi;
      delta_R = sqrt( pow(abs(delta_Phi),2) + pow(abs(delta_Eta),2));

      if(delta_Phi >  M_PI) delta_Phi = delta_Phi - M_PI;
      if(delta_Phi < -M_PI) delta_Phi = delta_Phi + M_PI;

      histJet_deltaeta_1->Fill(delta_Eta);
      histJet_deltaphi_1->Fill(delta_Phi);
      histJet_deltar_1->Fill(delta_R);

      //histJet_invmass->Fill(photon_invariant_mass(jet[0], jet[1]));
    }

     if(jet_counter > 0) histJet_pt_1->Fill(jet[0].PT);
     if(jet_counter > 0) histJet_eta_1->Fill(jet[0].Eta);
     if(jet_counter > 0) histJet_phi_1->Fill(jet[0].Phi);
     if(jet_counter > 1) histJet_pt_2->Fill(jet[1].PT);
     if(jet_counter > 1) histJet_eta_2->Fill(jet[1].Eta);
     if(jet_counter > 1) histJet_phi_2->Fill(jet[1].Phi);


    //------------------------------------------------------------
    //------------------------------------------------------------

    int muon_counter=0;

    for (int i=0; i< NMUON_MAX; i++)
    {
            if(muon[i].PT == -999) continue;
            muon_counter++;
      			histMuon_pt->Fill(muon[i].PT);
      			histMuon_eta->Fill(muon[i].Eta);
      			histMuon_phi->Fill(muon[i].Phi);
      			histMuon_charge->Fill(muon[i].Charge);
    }
    histMuon_size->Fill(muon_counter);

    //------------------------------------------------------------
    //------------------------------------------------------------
    int electron_counter=0;

    for (int i=0; i< NELECTRON_MAX; i++)
    {
            if(electron[i].PT == -999) continue;
            electron_counter++;
            histElectron_pt->Fill(electron[i].PT);
            histElectron_eta->Fill(electron[i].Eta);
            histElectron_phi->Fill(electron[i].Phi);
            histElectron_charge->Fill(electron[i].Charge);
    }
    histElectron_size->Fill(electron_counter);

    histLepton_size->Fill(electron_counter+muon_counter);


    }	//end of event loop

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //---------------------------------------------------------------------------------------------------------
    ////////////////////////////////  Saving the histograms into output  //////////////////////////////////////////
    //---------------------------------------------------------------------------------------------------------
    // end of event loop

    std::cout << "Photon New Numbers: " << photon_counter_new << std::endl;
    std::cout << "Photon 0 Numbers: " << photon_counter_0 << std::endl;
    std::cout << "Photon 1 Numbers: " << photon_counter_1 << std::endl;
    std::cout << "Photon 2 Numbers: " << photon_counter_2 << std::endl;
    std::cout << "Photon 3 Numbers: " << photon_counter_3 << std::endl;
    std::cout << "Photon 4 Numbers: " << photon_counter_4 << std::endl;
    cout << "\t" << InputFileName.c_str() << endl;


    //myfile.close();
    outf->Write();
    outf->Close();

    //end of main loop
}
