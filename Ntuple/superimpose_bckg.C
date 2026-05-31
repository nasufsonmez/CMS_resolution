{
	//gROOT->ProcessLine(".L /Users/nsonmez/root/macros/tdrStyle.C");
	#include "superimpose_new.h"
	//#include "tdrstyle.h"
	//#include "CMSTDRStyle.h"

	gStyle->SetOptStat("n");

	//setTDRStyle();
	char h_name[1000];
  char p_name[1000];
  char c_name[1000];
  char h_title[1000];

	char *bckg_name[] =
	{
		"analyze_sm_diphoton_bckg_aa",
		"analyze_sm_diphoton_bckg_aaa",
		"analyze_sm_diphoton_bckg_aaj",
		"analyze_sm_diphoton_bckg_aj",
		"analyze_sm_diphoton_bckg_ajj",
		"analyze_sm_diphoton_bckg_az",
		"analyze_sm_diphoton_bckg_ll"
	};

	int number_of_bckg = 7;

	// number of dataset

	//Matched cross section
	double cross_sections[] =
	{
		148.9/1000000,	 		// bckg_aa
		0.1021/1000000,	 		// bckg_aaa
		99.157/1000000,	 		// bckg_aaj
		83250.0/10000000, 		// bckg_aj
		79825.0/10000000, 		//bckg_ajj
		69.49/1000000,	 		//bckg_az
		1686.0/1000000	 		//bckg_ll
	};


	double signal_cross = 0.7*6/(1000000*100000);

  //______________________________________________________________
	// read the root files

  TFile *rootfile_bckg[number_of_bckg];
  TH1F *bckg_histPhotonInvMass_cut1[number_of_bckg];
  TCanvas *canvas_PhotonInvMass[number_of_bckg];

  TFile *rootfile_signal = new TFile("/home/fozturk/Desktop/Analysis-master/analyze_output_new_tfd/cut1/analyze_signal_diphoton_cut1.root", "READ" );
  TH1F *signal_histPhotonInvMass_cut1 = (TH1F*)rootfile_signal->Get("Photon/photon_invmass");

  for (int a=0; a<number_of_bckg; a++)
	{

    //if(a==3 || a==4) continue;

    sprintf(h_name,"/home/fozturk/Desktop/Analysis-master/analyze_output_new_tfd/cut1/%s_cut1.root", bckg_name[a]);
		rootfile_bckg[a] = new TFile( h_name, "READ" );
		bckg_histPhotonInvMass_cut1[a] = (TH1F*)rootfile_bckg[a]->Get("Photon/photon_invmass");
    cout << h_name << endl;

    signal_histPhotonInvMass_cut1->Scale(signal_cross);
		signal_histPhotonInvMass_cut1->Scale(1/signal_histPhotonInvMass_cut1->Integral());

    bckg_histPhotonInvMass_cut1[a]->Scale(cross_sections[a]);
    bckg_histPhotonInvMass_cut1[a]->Scale(1/bckg_histPhotonInvMass_cut1[a]->Integral());

    sprintf(c_name,"canvas_%s", bckg_name[a]);
		canvas_PhotonInvMass[a] = new TCanvas(c_name,"title",2500,0,600,500);

		hist_same (canvas_PhotonInvMass[a], bckg_histPhotonInvMass_cut1[a], signal_histPhotonInvMass_cut1 , "Cut 1 Photon 1 and Photon 2 Inv Mass_cut1", "InvMass_cut1 (GeV)", "Events", 0, 0);

    sprintf(h_title,"Photon InvMass %s cut1", bckg_name[a]);
    bckg_histPhotonInvMass_cut1[a]->SetTitle(h_title);

    sprintf(p_name,"plots_background/cut1/PhotonInvMass_%s_1.eps", bckg_name[a]);
		canvas_PhotonInvMass[a]->Print(p_name);

    //delete rootfile_signal;
    //delete signal_histPhotonInvMass_cut1;
    //delete bckg_histPhotonInvMass_cut1[a];
    //delete rootfile_bckg[a];
    //delete canvas_PhotonInvMass[a];

  }








  }
