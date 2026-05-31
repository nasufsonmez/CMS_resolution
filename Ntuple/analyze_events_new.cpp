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

    string CutName0	= c1.getValue<string>	("CUT0");
  	string CutName1	= c1.getValue<string>	("CUT1");
  	string CutName2	= c1.getValue<string>	("CUT2");
  	string CutName3	= c1.getValue<string>	("CUT3");
  	string CutName4	= c1.getValue<string>	("CUT4");

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
    TH1F  *histJet_size_cut   = new TH1F("jet_size_cut"	 ,   "JET SIZE CUT",      15,      0.0,   15.0);
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

    TH1F *histPhoton_1_pt     	= new TH1F("photon_1_pt"        , "Photon PT" ,   		  100.0,   0.0,   2000.0);
    TH1F *histPhoton_1_eta    	= new TH1F("photon_1_eta"       , "Photon Eta",         100.0,  -10.0,  10.0);
    TH1F *histPhoton_1_phi    	= new TH1F("photon_1_phi"       , "Photon Phi",         100.0,  -3.5,   3.5);

    TH1F *histPhoton_2_pt     	  = new TH1F("photon_2_pt"          , "Photon(2) PT" ,   		   100.0,   0.0,   2000.0);
    TH1F *histPhoton_2_pt_1       = new TH1F("photon_2_pt_1"        , "Photon(2) PT Leading",  100.0,   0.0,   2000.0);
    TH1F *histPhoton_2_pt_2       = new TH1F("photon_2_pt_2"        , "Photon(2) PT Second" ,  100.0,   0.0,   2000.0);
    TH1F *histPhoton_2_eta_1    	= new TH1F("photon_2_eta_1"       , "Photon(2) Eta 1",       100.0,  -10.0,  10.0);
    TH1F *histPhoton_2_phi_1    	= new TH1F("photon_2_phi_1"       , "Photon(2) Phi 1",       100.0,  -3.5,   3.5);
    TH1F *histPhoton_2_eta_2    	= new TH1F("photon_2_eta_2"       , "Photon(2) Eta 2",       100.0,  -10.0,  10.0);
    TH1F *histPhoton_2_phi_2    	= new TH1F("photon_2_phi_2"       , "Photon(2) Phi 2",       100.0,  -3.5,   3.5);
    TH1F *histPhoton_2_deltaphi   = new TH1F("photon_2_delta_phi"   , "Photon(2) Delta Phi",   100.0,  -7.0,   7.0);
    TH1F *histPhoton_2_deltaeta   = new TH1F("photon_2_delta_eta"   , "Photon(2) Delta Eta",   100.0,  -20.0,  20.0);
    TH1F *histPhoton_2_deltar     = new TH1F("photon_2_deltar"      , "Photon(2) DeltaR",   	 100.0,   0.,    15.);
    TH1F *histPhoton_2_invmass	  = new TH1F("photon_2_invmass"     , "Photon(2) Inv Mass",    100.0,   0.,    1200.);


    TH1F *histPhoton_3_pt     	  = new TH1F("photon_3_pt"          , "Photon(3) PT" ,   		   100.0,   0.0,   2000.0);
    TH1F *histPhoton_3_pt_1       = new TH1F("photon_3_pt_1"        , "Photon(3) PT Leading",  100.0,   0.0,   2000.0);
    TH1F *histPhoton_3_pt_2       = new TH1F("photon_3_pt_2"        , "Photon(3) PT Second" ,  100.0,   0.0,   2000.0);
    TH1F *histPhoton_3_eta_1    	= new TH1F("photon_3_eta_1"       , "Photon(3) Eta 1",       100.0,  -10.0,  10.0);
    TH1F *histPhoton_3_phi_1    	= new TH1F("photon_3_phi_1"       , "Photon(3) Phi 1",       100.0,  -3.5,   3.5);
    TH1F *histPhoton_3_eta_2    	= new TH1F("photon_3_eta_2"       , "Photon(3) Eta 2",       100.0,  -10.0,  10.0);
    TH1F *histPhoton_3_phi_2    	= new TH1F("photon_3_phi_2"       , "Photon(3) Phi 2",       100.0,  -3.5,   3.5);
    TH1F *histPhoton_3_deltaphi   = new TH1F("photon_3_delta_phi"   , "Photon(3) Delta Phi",   100.0,  -7.0,   7.0);
    TH1F *histPhoton_3_deltaeta   = new TH1F("photon_3_delta_eta"   , "Photon(3) Delta Eta",   100.0,  -20.0,  20.0);
    TH1F *histPhoton_3_deltar     = new TH1F("photon_3_deltar"      , "Photon(3) DeltaR",   	 100.0,   0.,    15.);
    TH1F *histPhoton_3_invmass	  = new TH1F("photon_3_invmass"     , "Photon(3) Inv Mass",    100.0,   0.,    1200.);

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

    int counter_pre_event=0;
    int counter_pre_photon = 0;
    int counter_pre_photon_0 = 0;
    int counter_pre_photon_1 = 0;
    int counter_pre_photon_2 = 0;
    int counter_pre_photon_3 = 0;
    int counter_pre_photon_4 = 0;
    int counter_pre_muon = 0;
    int counter_pre_electron = 0;
    int counter_pre_lepton = 0;

    int counter_cut1_event=0;
    int counter_cut1_photon = 0;
    int counter_cut1_photon_0 = 0;
    int counter_cut1_photon_1 = 0;
    int counter_cut1_photon_2 = 0;
    int counter_cut1_photon_3 = 0;
    int counter_cut1_photon_4 = 0;
    int counter_cut1_muon = 0;
    int counter_cut1_electron = 0;
    int counter_cut1_lepton = 0;

    int counter_cut2_event=0;
    int counter_cut2_photon = 0;
    int counter_cut2_photon_0 = 0;
    int counter_cut2_photon_1 = 0;
    int counter_cut2_photon_2 = 0;
    int counter_cut2_photon_3 = 0;
    int counter_cut2_photon_4 = 0;
    int counter_cut2_muon = 0;
    int counter_cut2_electron = 0;
    int counter_cut2_lepton = 0;

    int counter_cut3_event=0;
    int counter_cut3_photon = 0;
    int counter_cut3_photon_0 = 0;
    int counter_cut3_photon_1 = 0;
    int counter_cut3_photon_2 = 0;
    int counter_cut3_photon_3 = 0;
    int counter_cut3_photon_4 = 0;
    int counter_cut3_muon = 0;
    int counter_cut3_electron = 0;
    int counter_cut3_lepton = 0;

    int counter_cut4_event=0;
    int counter_cut4_photon = 0;
    int counter_cut4_photon_0 = 0;
    int counter_cut4_photon_1 = 0;
    int counter_cut4_photon_2 = 0;
    int counter_cut4_photon_3 = 0;
    int counter_cut4_photon_4 = 0;
    int counter_cut4_muon = 0;
    int counter_cut4_electron = 0;
    int counter_cut4_lepton = 0;

    int counter_cutall_event=0;
    int counter_cutall_photon = 0;
    int counter_cutall_photon_0 = 0;
    int counter_cutall_photon_1 = 0;
    int counter_cutall_photon_2 = 0;
    int counter_cutall_photon_3 = 0;
    int counter_cutall_photon_4 = 0;
    int counter_cutall_muon = 0;
    int counter_cutall_electron = 0;
    int counter_cutall_lepton = 0;

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
    for ( int a =0; a<NPHOTON_MAX; a++ )    b_photon[a]->GetEvent(entry);
    for ( int a =0; a<NMUON_MAX; a++ )	    b_muon[a]->GetEvent(entry);
    for ( int a =0; a<NELECTRON_MAX; a++ )	b_electron[a]->GetEvent(entry);

    int photon_counter_cut=0;
    int jet_counter_cut=0;
    int muon_counter_cut=0;
    int electron_counter_cut=0;

    for (int i=0; i< NPHOTON_MAX; i++)
    {
                if(photon[i].PT  == -999) continue;
                photon_counter_cut++;
    }


    for (int i=0; i< NJET_MAX; i++)
    {
                if(jet[i].PT  == -999) continue;
                jet_counter_cut++;
    }


    for (int i=0; i< NMUON_MAX; i++)
    {
                if(muon[i].PT  == -999) continue;
                muon_counter_cut++;
    }

    for (int i=0; i< NELECTRON_MAX; i++)
    {
                if(electron[i].PT  == -999) continue;
                electron_counter_cut++;
    }



	  ///////////////////////////////////////////////////////////////////////////
	  /////////AT LEAST TWO PHOTON CANDİDATES////////////////////////////////////
	  //////////////////////////////////////////////////////////////////////////

    if(CutName1 == "cut1") if(photon_counter_cut < 2) continue;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if(CutName2 == "cut2"){

			if(photon_counter_cut < 2 ) continue;
			if(photon[0].PT < 60 && photon[1].PT < 60) continue;
		}

		if(CutName3 == "cut3"){

			if( photon_counter_cut < 2 ) continue;

			if( abs(photon[0].Eta) > 2.5  && abs(photon[1].Eta) > 2.5 ) continue;
			if( abs(photon[0].Eta) < 1.57 && abs(photon[0].Eta) > 1.44 &&	abs(photon[1].Eta) < 1.57 && abs(photon[1].Eta) > 1.44) continue;
			if( abs(photon[0].Eta) > 1.44 || abs(photon[1].Eta) > 1.44) continue;
		}

		if(CutName4 == "cut4"){

			if( photon_counter_cut < 2 ) continue;
			if( photon_invariant_mass(photon[0], photon[1]) < 300) continue;
   	}




    ///////////////////////////////////////////////////////////////////////////
	  ///////// HİSTOGRAMS //////////////////////////////////////////////////////
	  //////////////////////////////////////////////////////////////////////////

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

    delta_Phi = TMath::Abs(photon[0].Phi - photon[1].Phi);
    delta_Eta = photon[0].Eta - photon[1].Eta;
    if(delta_Phi > TMath::Pi()) delta_Phi = TMath::TwoPi() - delta_Phi;
    delta_R=TMath::Sqrt(delta_Eta*delta_Eta + delta_Phi*delta_Phi);

    //delta_Eta = photon[1].Eta - photon[0].Eta;
    //delta_Phi = photon[1].Phi - photon[0].Phi;
    //delta_R = sqrt( pow(abs(delta_Phi),2) + pow(abs(delta_Eta),2));

    //if(delta_Phi >  M_PI) delta_Phi = delta_Phi - M_PI;
    //if(delta_Phi < -M_PI) delta_Phi = delta_Phi + M_PI;

    histPhoton_deltaeta->Fill(delta_Eta);
    histPhoton_deltaphi->Fill(delta_Phi);
    histPhoton_deltar->Fill(delta_R);
    histPhoton_invmass->Fill(photon_invariant_mass(photon[0], photon[1]));
    }

    histPhoton_ht->Fill(photon_ht_value);

    if(photon_counter > 0){

      histPhoton_pt_1->Fill(photon[0].PT);
      histPhoton_eta_1->Fill(photon[0].Eta);
      histPhoton_phi_1->Fill(photon[0].Phi);
    }

    if(photon_counter > 1){

      histPhoton_pt_2->Fill(photon[1].PT);
      histPhoton_eta_2->Fill(photon[1].Eta);
      histPhoton_phi_2->Fill(photon[1].Phi);
    }

    if(photon_counter == 1){

      histPhoton_1_pt_1->Fill(photon[0].PT);
      histPhoton_1_eta_1->Fill(photon[0].Eta);
      histPhoton_1_phi_1->Fill(photon[0].Phi);
    }

    if(photon_counter == 2){

      histPhoton_2_pt_1->Fill(photon[0].PT);
      histPhoton_2_pt_2->Fill(photon[1].PT);

      histPhoton_2_eta_1->Fill(photon[0].Eta);
      histPhoton_2_eta_2->Fill(photon[1].Eta);

      histPhoton_2_phi_1->Fill(photon[0].Phi);
      histPhoton_2_phi_2->Fill(photon[1].Phi);

      delta_Phi = TMath::Abs(photon[0].Phi - photon[1].Phi);
      delta_Eta = photon[0].Eta - photon[1].Eta;
      if(delta_Phi > TMath::Pi()) delta_Phi = TMath::TwoPi() - delta_Phi;
      delta_R=TMath::Sqrt(delta_Eta*delta_Eta + delta_Phi*delta_Phi);

      histPhoton_2_deltaeta->Fill(delta_Eta);
      histPhoton_2_deltaphi->Fill(delta_Phi);
      histPhoton_2_deltar->Fill(delta_R);
      histPhoton_2_invmass->Fill(photon_invariant_mass(photon[0], photon[1]));

    }

    if(photon_counter > 2){

      histPhoton_3_pt_1->Fill(photon[0].PT);
      histPhoton_3_pt_2->Fill(photon[1].PT);

      histPhoton_3_eta_1->Fill(photon[0].Eta);
      histPhoton_3_eta_2->Fill(photon[1].Eta);

      histPhoton_3_phi_1->Fill(photon[0].Phi);
      histPhoton_3_phi_2->Fill(photon[1].Phi);

      delta_Phi = TMath::Abs(photon[0].Phi - photon[1].Phi);
      delta_Eta = photon[0].Eta - photon[1].Eta;
      if(delta_Phi > TMath::Pi()) delta_Phi = TMath::TwoPi() - delta_Phi;
      delta_R=TMath::Sqrt(delta_Eta*delta_Eta + delta_Phi*delta_Phi);

      histPhoton_3_deltaeta->Fill(delta_Eta);
      histPhoton_3_deltaphi->Fill(delta_Phi);
      histPhoton_3_deltar->Fill(delta_R);
      histPhoton_3_invmass->Fill(photon_invariant_mass(photon[0], photon[1]));

    }

    if(photon_counter == 0) photon_counter_0++;
    if(photon_counter == 1) photon_counter_1++;
    if(photon_counter == 2) photon_counter_2++;
    if(photon_counter == 3) photon_counter_3++;
    if(photon_counter == 4) photon_counter_4++;


    //------------------------------------------------------------
    //------------------------------------------------------------

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
            histJet_mass->Fill(jet[i].Mass);
            histJet_deltaeta->Fill(jet[i].DeltaEta);
            histJet_deltaphi->Fill(jet[i].DeltaPhi);
            histJet_deltar->Fill(sqrt( pow(abs(jet[i].DeltaEta),2) + pow(abs(jet[i].DeltaPhi),2)));
            histJet_charge->Fill(jet[i].Charge);
            histJet_btag->Fill(jet[i].BTag);
            histJet_tautag->Fill(jet[i].TauTag);

    }
    histJet_size->Fill(jet_counter);
    histJet_size_cut->Fill(jet_eta_counter);

    if(jet_counter > 1){

      delta_Phi = TMath::Abs(photon[0].Phi - photon[1].Phi);
      delta_Eta = photon[0].Eta - photon[1].Eta;
      if(delta_Phi > TMath::Pi()) delta_Phi = TMath::TwoPi() - delta_Phi;
      delta_R=TMath::Sqrt(delta_Eta*delta_Eta + delta_Phi*delta_Phi);

      //delta_Eta = jet[1].Eta - jet[0].Eta;
      //delta_Phi = jet[1].Phi - jet[0].Phi;
      //delta_R = sqrt( pow(abs(delta_Phi),2) + pow(abs(delta_Eta),2));

      //if(delta_Phi >  M_PI) delta_Phi = delta_Phi - M_PI;
      //if(delta_Phi < -M_PI) delta_Phi = delta_Phi + M_PI;

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


    ///////////////////////////////////////////////////////////////////////////
	  ///////// CUT COUNTER  ////////////////////////////////////////////////////
	  //////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////
	  /////////NO CUT PROCESS////////////////////////////////////////////////////
	  //////////////////////////////////////////////////////////////////////////

		if(CutName0 == "cut0"){

			counter_pre_event++;

    	if(photon_counter > 0)  counter_pre_photon = counter_pre_photon + photon_counter;
			if(photon_counter == 0) counter_pre_photon_0++;
    	if(photon_counter == 1) counter_pre_photon_1++;
    	if(photon_counter == 2) counter_pre_photon_2++;
    	if(photon_counter == 3) counter_pre_photon_3++;
			if(photon_counter == 4) counter_pre_photon_4++;


    	if(muon_counter  > 0)  	  counter_pre_muon = counter_pre_muon + muon_counter ;
    	if(electron_counter > 0)  counter_pre_electron = counter_pre_electron + electron_counter;
    	if(muon_counter  > 0 || electron_counter > 0)  counter_pre_lepton = counter_pre_lepton +
																			muon_counter + electron_counter;
		}

    ///////////////////////////////////////////////////////////////////////////
	  /////////NO CUT PROCESS////////////////////////////////////////////////////
	  //////////////////////////////////////////////////////////////////////////

		if(CutName1 == "cut1") {

			counter_cut1_event++;

      if(photon_counter > 0)  counter_cut1_photon = counter_cut1_photon + photon_counter;
			if(photon_counter == 0) counter_cut1_photon_0++;
    	if(photon_counter == 1) counter_cut1_photon_1++;
    	if(photon_counter == 2) counter_cut1_photon_2++;
    	if(photon_counter == 3) counter_cut1_photon_3++;
			if(photon_counter == 4) counter_cut1_photon_4++;

    	if(muon_counter  > 0) counter_cut1_muon = counter_cut1_muon + muon_counter;
    	if(electron_counter_cut > 0)  counter_cut1_electron = counter_cut1_electron + electron_counter;
    	if(muon_counter  > 0 || electron_counter > 0)  counter_cut1_lepton = counter_cut1_lepton + muon_counter + electron_counter;

    }

    ///////////////////////////////////////////////////////////////////////////
	  /////////NO CUT PROCESS////////////////////////////////////////////////////
	  //////////////////////////////////////////////////////////////////////////

    if(CutName2 == "cut2") {

      counter_cut2_event++;

      if(photon_counter > 0)  counter_cut2_photon = counter_cut2_photon + photon_counter;
			if(photon_counter == 0) counter_cut2_photon_0++;
    	if(photon_counter == 1) counter_cut2_photon_1++;
    	if(photon_counter == 2) counter_cut2_photon_2++;
    	if(photon_counter == 3) counter_cut2_photon_3++;
			if(photon_counter == 4) counter_cut2_photon_4++;

    	if(muon_counter  > 0) counter_cut2_muon = counter_cut2_muon + muon_counter;
    	if(electron_counter_cut > 0)  counter_cut2_electron = counter_cut2_electron + electron_counter;
    	if(muon_counter  > 0 || electron_counter > 0)  counter_cut2_lepton = counter_cut2_lepton + muon_counter + electron_counter;

		}

    ///////////////////////////////////////////////////////////////////////////
	  /////////NO CUT PROCESS////////////////////////////////////////////////////
	  //////////////////////////////////////////////////////////////////////////

    if(CutName3 == "cut3") {

      counter_cut3_event++;

      if(photon_counter > 0)  counter_cut3_photon = counter_cut3_photon + photon_counter;
			if(photon_counter == 0) counter_cut3_photon_0++;
    	if(photon_counter == 1) counter_cut3_photon_1++;
    	if(photon_counter == 2) counter_cut3_photon_2++;
    	if(photon_counter == 3) counter_cut3_photon_3++;
			if(photon_counter == 4) counter_cut3_photon_4++;

    	if(muon_counter  > 0) counter_cut3_muon = counter_cut3_muon + muon_counter;
    	if(electron_counter_cut > 0)  counter_cut3_electron = counter_cut3_electron + electron_counter;
    	if(muon_counter  > 0 || electron_counter > 0)  counter_cut3_lepton = counter_cut3_lepton + muon_counter + electron_counter;

		}

    ///////////////////////////////////////////////////////////////////////////
	  /////////NO CUT PROCESS////////////////////////////////////////////////////
	  //////////////////////////////////////////////////////////////////////////

    if(CutName4 == "cut4") {

      counter_cut4_event++;

      if(photon_counter > 0)  counter_cut4_photon = counter_cut4_photon + photon_counter;
			if(photon_counter == 0) counter_cut4_photon_0++;
    	if(photon_counter == 1) counter_cut4_photon_1++;
    	if(photon_counter == 2) counter_cut4_photon_2++;
    	if(photon_counter == 3) counter_cut4_photon_3++;
			if(photon_counter == 4) counter_cut4_photon_4++;

    	if(muon_counter  > 0) counter_cut4_muon = counter_cut4_muon + muon_counter;
    	if(electron_counter_cut > 0)  counter_cut4_electron = counter_cut4_electron + electron_counter;
    	if(muon_counter  > 0 || electron_counter > 0)  counter_cut4_lepton = counter_cut4_lepton + muon_counter + electron_counter;

		}

    ///////////////////////////////////////////////////////////////////////////
	  /////////NO CUT PROCESS////////////////////////////////////////////////////
	  //////////////////////////////////////////////////////////////////////////

    if( CutName0 == "cut0" && CutName1 == "cut1" && CutName2 == "cut2" && CutName3 == "cut3" && CutName4 == "cut4") {

      counter_cutall_event++;

      if(photon_counter > 0)  counter_cutall_photon = counter_cutall_photon + photon_counter;
			if(photon_counter == 0) counter_cutall_photon_0++;
    	if(photon_counter == 1) counter_cutall_photon_1++;
    	if(photon_counter == 2) counter_cutall_photon_2++;
    	if(photon_counter == 3) counter_cutall_photon_3++;
			if(photon_counter == 4) counter_cutall_photon_4++;

    	if(muon_counter  > 0) counter_cutall_muon = counter_cutall_muon + muon_counter;
    	if(electron_counter_cut > 0)  counter_cutall_electron = counter_cutall_electron + electron_counter;
    	if(muon_counter  > 0 || electron_counter > 0)  counter_cutall_lepton = counter_cutall_lepton + muon_counter + electron_counter;

		}



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

    //---------------------------------------------------------------------------------------------------------
  	////////////////////////////////  Saving the histograms into output  //////////////////////////////////////////
  	//---------------------------------------------------------------------------------------------------------
  	if(CutName0 == "cut0"){

  	cout << "----------------------------------------------------------------------------" << endl;
  	cout << "___________________NO CUT EVENTS____________________________________________" << endl;
  	cout << "----------------------------------------------------------------------------" << endl;
  	cout << "No cut Event number:  " 	    << counter_pre_event    << endl;
  	cout << "No cut Photon All number:  " << counter_pre_photon   << endl;
  	cout << "No cut Photon 0 number:  "	  << counter_pre_photon_0 << endl;
  	cout << "No cut Photon 1 number:  "	  << counter_pre_photon_1 << endl;
  	cout << "No cut Photon 2 number:  "   << counter_pre_photon_2 << endl;
  	cout << "No cut Photon 3 number:  "   << counter_pre_photon_3 << endl;
  	cout << "No cut Photon 4 number:  "	  << counter_pre_photon_4 << endl;
  	cout << "No cut Muon number:  "       << counter_pre_muon     << endl;
  	cout << "No cut Electron number:  "   << counter_pre_electron << endl;
  	cout << "No cut Lepton number:  " 	  << counter_pre_lepton   << endl;

  }
  	if(CutName1 == "cut1"){

  	cout << "---------------------------------------------------------------------------------------------" << endl;
  	cout << "___________________AT LEAST TWO PHOTON CANDİDATES____________________________________________" << endl;
  	cout << "---------------------------------------------------------------------------------------------" << endl;
  	cout << "Cut 1 Event number:  " 	   << counter_cut1_event    << endl;
  	cout << "Cut 1 Photon All number:  " << counter_cut1_photon   << endl;
  	cout << "Cut 1 Photon 0 number:  "	 << counter_cut1_photon_0 << endl;
  	cout << "Cut 1 Photon 1 number:  "	 << counter_cut1_photon_1 << endl;
  	cout << "Cut 1 Photon 2 number:  "   << counter_cut1_photon_2 << endl;
  	cout << "Cut 1 Photon 3 number:  "   << counter_cut1_photon_3 << endl;
  	cout << "Cut 1 Photon 4 number:  "	 << counter_cut1_photon_4 << endl;
  	cout << "Cut 1 Muon number:  "       << counter_cut1_muon 	  << endl;
  	cout << "Cut 1 Electron number:  "   << counter_cut1_electron << endl;
  	cout << "Cut 1 Lepton number:  " 	   << counter_cut1_lepton   << endl;
  	}

  	if(CutName2 == "cut2") {

  	cout << "---------------------------------------------------------------------------------------------" << endl;
  	cout << "___________________LEADİNG AND SECOND PHOTON PT > 60_________________________________________" << endl;
  	cout << "---------------------------------------------------------------------------------------------" << endl;
  	cout << "Cut 2 Event number:  " 	   << counter_cut2_event    << endl;
  	cout << "Cut 2 Photon All number:  " << counter_cut2_photon   << endl;
  	cout << "Cut 2 Photon 0 number:  "	 << counter_cut2_photon_0 << endl;
  	cout << "Cut 2 Photon 1 number:  "	 << counter_cut2_photon_1 << endl;
  	cout << "Cut 2 Photon 2 number:  "   << counter_cut2_photon_2 << endl;
  	cout << "Cut 2 Photon 3 number:  "   << counter_cut2_photon_3 << endl;
  	cout << "Cut 2 Photon 4 number:  "	 << counter_cut2_photon_4 << endl;
  	cout << "Cut 2 Muon number:  "       << counter_cut2_muon 	  << endl;
  	cout << "Cut 2 Electron number:  "   << counter_cut2_electron << endl;
  	cout << "Cut 2 Lepton number:  " 	   << counter_cut2_lepton   << endl;
  	}

  	if(CutName3 == "cut3") {

  	cout << "---------------------------------------------------------------------------------------------" << endl;
  	cout << "____________PHOTON |ETA| < 2.5  EXCEPT  1.44 < |ETA| < 1.57__________________________________" << endl;
  	cout << "---------------------------------------------------------------------------------------------" << endl;
  	cout << "Cut 3 Event number:  " 	   << counter_cut3_event    << endl;
  	cout << "Cut 3 Photon All number:  " << counter_cut3_photon   << endl;
  	cout << "Cut 3 Photon 0 number:  "	 << counter_cut3_photon_0 << endl;
  	cout << "Cut 3 Photon 1 number:  "	 << counter_cut3_photon_1 << endl;
  	cout << "Cut 3 Photon 2 number:  "   << counter_cut3_photon_2 << endl;
  	cout << "Cut 3 Photon 3 number:  "   << counter_cut3_photon_3 << endl;
  	cout << "Cut 3 Photon 4 number:  "	 << counter_cut3_photon_4 << endl;
  	cout << "Cut 3 Muon number:  "       << counter_cut3_muon 	  << endl;
  	cout << "Cut 3 Electron number:  "   << counter_cut3_electron << endl;
  	cout << "Cut 3 Lepton number:  " 	   << counter_cut3_lepton   << endl;
  	}

  	if(CutName4 == "cut4") {

  	cout << "---------------------------------------------------------------------------------------------" << endl;
  	cout << "____________PHOTON (1,2) INV MASS > 320______________________________________________________" << endl;
  	cout << "---------------------------------------------------------------------------------------------" << endl;
  	cout << "Cut 4 Event number:  " 	   << counter_cut4_event    << endl;
  	cout << "Cut 4 Photon All number:  " << counter_cut4_photon   << endl;
  	cout << "Cut 4 Photon 0 number:  "	 << counter_cut4_photon_0 << endl;
  	cout << "Cut 4 Photon 1 number:  "	 << counter_cut4_photon_1 << endl;
  	cout << "Cut 4 Photon 2 number:  "   << counter_cut4_photon_2 << endl;
  	cout << "Cut 4 Photon 3 number:  "   << counter_cut4_photon_3 << endl;
  	cout << "Cut 4 Photon 4 number:  "	 << counter_cut4_photon_4 << endl;
  	cout << "Cut 4 Muon number:  "       << counter_cut4_muon 	  << endl;
  	cout << "Cut 4 Electron number:  "   << counter_cut4_electron << endl;
  	cout << "Cut 4 Lepton number:  " 	   << counter_cut4_lepton   << endl;
  	}

  	if(CutName0 == "cut0" && CutName1 == "cut1" && CutName2 == "cut2" && CutName3 == "cut3" && CutName4 == "cut4") {

   	cout << "---------------------------------------------------------------------------------------------" << endl;
   	cout << "____________PHOTON (1,2) INV MASS > 320______________________________________________________" << endl;
   	cout << "---------------------------------------------------------------------------------------------" << endl;
   	cout << "Cut all Event number:  " 	   << counter_cutall_event    << endl;
   	cout << "Cut all Photon All number:  " << counter_cutall_photon   << endl;
   	cout << "Cut all Photon 0 number:  "	 << counter_cutall_photon_0 << endl;
   	cout << "Cut all Photon 1 number:  "	 << counter_cutall_photon_1 << endl;
   	cout << "Cut all Photon 2 number:  "   << counter_cutall_photon_2 << endl;
   	cout << "Cut all Photon 3 number:  "   << counter_cutall_photon_3 << endl;
   	cout << "Cut all Photon all number:  " << counter_cutall_photon_4 << endl;
   	cout << "Cut all Muon number:  "       << counter_cutall_muon 	  << endl;
   	cout << "Cut all Electron number:  "   << counter_cutall_electron << endl;
   	cout << "Cut all Lepton number:  " 	   << counter_cutall_lepton   << endl;

  }
    cout << "\t" << InputFileName.c_str() << endl;
  std::cout << "Pi number:  " <<  M_PI << std::endl;

    //myfile.close();
    outf->Write();
    outf->Close();

    //end of main loop
}
