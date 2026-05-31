{
	//gROOT->ProcessLine(".L /Users/nsonmez/root/macros/tdrStyle.C");
	#include "superimpose_new.h"
//	gStyle->SetOptStat("n");

	//setTDRStyle();
	char h_name[1000];


	char* bckg_name[] =
	{
		"analyze_sm_diphoton_bckg_aa",
		"analyze_sm_diphoton_bckg_aaa",
		"analyze_sm_diphoton_bckg_aaj",
		"analyze_sm_diphoton_bckg_aj",
		"analyze_sm_diphoton_bckg_ajj",
		"analyze_sm_diphoton_bckg_az",
		"analyze_sm_diphoton_bckg_ll",
	};

	int number_of_bckg = 7;

	// number of dataset

	//Matched cross section
	double cross_sections[] =
	{
		148.9,	 		// bckg_aa
		0.1021,	 		// bckg_aaa
		99.157,	 		// bckg_aaj
		83250.0, 		// bckg_aj
		79825.0, 		//bckg_ajj
		69.49,	 		//bckg_az
		1686.0,	 		//bckg_ll

	};

	double total_cross_b = 165078.6491;
	double total_cross_s = 0.006;

	//______________________________________________________________
	// read the root files

	TFile * rootfile_bckg[number_of_bckg];
	for (int a=0;a<number_of_bckg;a++)
	{
		sprintf(h_name,"/home/fozturk/Desktop/Analysis-master/analyze_output/cut0/%s_cut0.root", bckg_name[a]);
		cout << h_name << endl;
		rootfile_bckg[a] = new TFile( h_name, "READ" );
	}

	rootfile_signal = new TFile( "/home/fozturk/Desktop/Analysis-master/analyze_output/cut0/analyze_signal_diphoton_cut0.root", "READ" );

	//______________________________________________________________
	// read the root files
/*
	TFile * rootfile_bckg[number_of_bckg];
	for (int a=0;a<number_of_bckg;a++)
	{
		sprintf(h_name,"/home/fozturk/Desktop/Analysis-master/analyze_output/cut0/%s_cut0123.root", bckg_name[a]);
		cout << h_name << endl;
		rootfile_bckg[a] = new TFile( h_name, "READ" );
	}

	rootfile_signal = new TFile( "/home/fozturk/Desktop/Analysis-master/analyze_output/cut0/analyze_signal_diphoton_cut0.root", "READ" );
*/
	//______________________________________________________________
	// get the histograms

	TH1F * bckg_histHt[number_of_bckg];
	TH1F * bckg_histMet[number_of_bckg];
	TH1F * bckg_histMetEta[number_of_bckg];
	TH1F * bckg_histMetPhi[number_of_bckg];

	TH1F * bckg_histJetPT[number_of_bckg];
	TH1F * bckg_histJetMass[number_of_bckg];

	TH1F * bckg_histPhotonPT[number_of_bckg];
	TH1F * bckg_histPhotonHT[number_of_bckg];
	TH1F * bckg_histPhotonE[number_of_bckg];
	TH1F * bckg_histPhotonInvMass[number_of_bckg];



	for (int a=0;a<number_of_bckg;a++)
	{
		bckg_histHt[a] =  					 (TH1F*)rootfile_bckg[a]->Get("eventVar/ht");
		bckg_histMet[a] =  	  			 (TH1F*)rootfile_bckg[a]->Get("eventVar/met");
		bckg_histMetEta[a] =  			 (TH1F*)rootfile_bckg[a]->Get("eventVar/met_eta");
		bckg_histMetPhi[a] =  			 (TH1F*)rootfile_bckg[a]->Get("eventVar/met_phi");

		bckg_histJetPT[a] =   			 (TH1F*)rootfile_bckg[a]->Get("Jet/jet_pt");
		bckg_histJetMass[a] = 			 (TH1F*)rootfile_bckg[a]->Get("Jet/jet_mass");

		bckg_histPhotonHT[a] =  		 (TH1F*)rootfile_bckg[a]->Get("Photon/photon_ht");
		bckg_histPhotonPT[a] =       (TH1F*)rootfile_bckg[a]->Get("Photon/photon_pt");
		bckg_histPhotonE[a] =        (TH1F*)rootfile_bckg[a]->Get("Photon/photon_e");
		bckg_histPhotonInvMass[a] =  (TH1F*)rootfile_bckg[a]->Get("Photon/photon_invmass");

	}

	TH1F *signal_histHt =  		 				(TH1F*)rootfile_signal->Get("eventVar/ht");
	TH1F *signal_histMet =  	 				(TH1F*)rootfile_signal->Get("eventVar/met");
	TH1F *signal_histMetEta =  				(TH1F*)rootfile_signal->Get("eventVar/met_eta");
	TH1F *signal_histMetPhi =  				(TH1F*)rootfile_signal->Get("eventVar/met_phi");

	TH1F *signal_histJetPT =   				(TH1F*)rootfile_signal->Get("Jet/jet_pt");
	TH1F *signal_histJetMass = 				(TH1F*)rootfile_signal->Get("Jet/jet_mass");

	TH1F *signal_histPhotonHT =  			(TH1F*)rootfile_signal->Get("Photon/photon_ht");
	TH1F *signal_histPhotonPT =       (TH1F*)rootfile_signal->Get("Photon/photon_pt");
	TH1F *signal_histPhotonE =        (TH1F*)rootfile_signal->Get("Photon/photon_e");
	TH1F *signal_histPhotonInvMass =  (TH1F*)rootfile_signal->Get("Photon/photon_invmass");

		cout << "Histogramlar ayarlandı" << endl;


	//______________________________________________________________________
	// Photon PT SPECTRUM

	//TH1F * before_trigger_bckg_PhotonInvMass    = new TH1F("before_trigger_bckg_PhotonInvMass" ,  "before_trigger_bckg_PhotonInvMass",   100, 0.0, 1200);
	//TH1F * before_trigger_signal_PhotonInvMass  = new TH1F("before_trigger_signal_PhotonInvMass" ,"before_trigger_signal_PhotonInvMass", 100, 0.0, 1200);

	//for (int a=0;a<number_of_bckg;a++)
	//{
	//	double scale= ( 1.0 / (bckg_histPhotonInvMass[a]->GetEntries() ) )* (cross_sections[a] ) ;
	//	//cout <<"entries:  " <<  bckg_histPhotonInvMass[a]->GetEntries() << "  cross_sections:  " << cross_sections[a] << endl;
	//	bckg_histPhotonInvMass[a]->Scale( scale );
	//	before_trigger_bckg_PhotonInvMass->Add(bckg_histPhotonInvMass[a]);
	//}

	//	double scale= ( 1.0 / ( signal_histPhotonInvMass->GetEntries() ) )*total_cross_s;
	//	signal_histPhotonInvMass->Scale( scale );
	//	before_trigger_signal_PhotonInvMass->Add(signal_histPhotonInvMass);
	//	TCanvas *canvas_PT = new TCanvas("canvas_PT","title",2500,0,600,500);
	//	hist_same (canvas_PT, before_trigger_bckg_PhotonPT, before_trigger_signal_PhotonPT , "title", "InvMass (GeV)", "Events", 0, 2500, 0, 100000);
	//	canvas_PT->Print("plots/cut0/before_trigger_PhotonPT_hadd.eps");


		//______________________________________________________________________
		// Photon PT SPECTRUM

		TH1F * before_trigger_bckg_PhotonPT    = new TH1F("before_trigger_bckg_PhotonPT" ,  "before_trigger_bckg_PhotonPT",   100, 0.0, 2000);
		TH1F * before_trigger_signal_PhotonPT  = new TH1F("before_trigger_signal_PhotonPT" ,"before_trigger_signal_PhotonPT", 100, 0.0, 2000);

		for (int a=0;a<number_of_bckg;a++)
		{
			double scale= ( 1.0 / (bckg_histPhotonPT[a]->GetEntries() ) )* (cross_sections[a] ) ;
			//cout <<"entries:  " <<  bckg_histPhotonPT[a]->GetEntries() << "  cross_sections:  " << cross_sections[a] << endl;
			bckg_histPhotonPT[a]->Scale( scale );
			before_trigger_bckg_PhotonPT->Add(bckg_histPhotonPT[a]);
		}

			double scale= ( 1.0 / ( signal_histPhotonPT->GetEntries() ) )*total_cross_s;
			signal_histPhotonPT->Scale( scale );
			before_trigger_signal_PhotonPT->Add(signal_histPhotonPT);

			TCanvas *canvas_PhotonPT = new TCanvas("canvas_PhotonPT","title",2500,0,600,500);
			hist_same (canvas_PhotonPT, before_trigger_bckg_PhotonPT, before_trigger_signal_PhotonPT , "Before Trigger All Photon PT", "PT (GeV)", "Events", 0, 0);
			canvas_PhotonPT->Print("plots/cut0/before_trigger_PhotonPT_hadd.eps");

		//______________________________________________________________________
		// Photon HT SPECTRUM

		TH1F * before_trigger_bckg_PhotonHT    = new TH1F("before_trigger_bckg_PhotonHT" ,  "before_trigger_bckg_PhotonHT",   100, 0.0, 2500);
		TH1F * before_trigger_signal_PhotonHT  = new TH1F("before_trigger_signal_PhotonHT" ,"before_trigger_signal_PhotonHT", 100, 0.0, 2500);

		for (int a=0;a<number_of_bckg;a++)
		{
			double scale= ( 1.0 / (bckg_histPhotonHT[a]->GetEntries() ) )* (cross_sections[a] ) ;
			//cout <<"entries:  " <<  bckg_histPhotonHT[a]->GetEntries() << "  cross_sections:  " << cross_sections[a] << endl;
			bckg_histPhotonHT[a]->Scale( scale );
			before_trigger_bckg_PhotonHT->Add(bckg_histPhotonHT[a]);
		}

			double scale= ( 1.0 / ( signal_histPhotonHT->GetEntries() ) )*total_cross_s;
			signal_histPhotonHT->Scale( scale );
			before_trigger_signal_PhotonHT->Add(signal_histPhotonHT);

			TCanvas *canvas_PhotonHT = new TCanvas("canvas_PhotonHT","title",2500,0,600,500);
			hist_same (canvas_PhotonHT, before_trigger_bckg_PhotonHT, before_trigger_signal_PhotonHT , "Before Trigger All Photon HT", "HT (GeV)", "Events", 0, 0);
			canvas_PhotonHT->Print("plots/cut0/before_trigger_PhotonHT_hadd.eps");

		//______________________________________________________________________
		// Photon E SPECTRUM

		TH1F * before_trigger_bckg_PhotonE    = new TH1F("before_trigger_bckg_PhotonE" ,  "before_trigger_bckg_PhotonE",   100, 0.0, 4000);
		TH1F * before_trigger_signal_PhotonE  = new TH1F("before_trigger_signal_PhotonE" ,"before_trigger_signal_PhotonE", 100, 0.0, 4000);

		for (int a=0;a<number_of_bckg;a++)
		{
			double scale= ( 1.0 / (bckg_histPhotonE[a]->GetEntries() ) )* (cross_sections[a] ) ;
			//cout <<"entries:  " <<  bckg_histPhotonE[a]->GetEntries() << "  cross_sections:  " << cross_sections[a] << endl;
			bckg_histPhotonE[a]->Scale( scale );
			before_trigger_bckg_PhotonE->Add(bckg_histPhotonE[a]);
		}

			double scale= ( 1.0 / ( signal_histPhotonE->GetEntries() ) )*total_cross_s;
			signal_histPhotonE->Scale( scale );
			before_trigger_signal_PhotonE->Add(signal_histPhotonE);

			TCanvas *canvas_PhotonE = new TCanvas("canvas_PhotonE","title",2500,0,600,500);
			hist_same (canvas_PhotonE, before_trigger_bckg_PhotonE, before_trigger_signal_PhotonE , "Before Trigger All Photon E", "E (GeV)", "Events", 0, 0);
			canvas_PhotonE->Print("plots/cut0/before_trigger_PhotonE_hadd.eps");

		//______________________________________________________________________
		// Photon InvMass SPECTRUM

		TH1F * before_trigger_bckg_PhotonInvMass    = new TH1F("before_trigger_bckg_PhotonInvMass" ,  "before_trigger_bckg_PhotonInvMass",   100, 0.0, 1200);
		TH1F * before_trigger_signal_PhotonInvMass  = new TH1F("before_trigger_signal_PhotonInvMass" ,"before_trigger_signal_PhotonInvMass", 100, 0.0, 1200);

		for (int a=0;a<number_of_bckg;a++)
		{
			double scale= ( 1.0 / (bckg_histPhotonInvMass[a]->GetEntries() ) )* (cross_sections[a] ) ;
			//cout <<"entries:  " <<  bckg_histPhotonInvMass[a]->GetEntries() << "  cross_sections:  " << cross_sections[a] << endl;
			bckg_histPhotonInvMass[a]->Scale( scale );
			before_trigger_bckg_PhotonInvMass->Add(bckg_histPhotonInvMass[a]);
		}

			double scale= ( 1.0 / ( signal_histPhotonInvMass->GetEntries() ) )*total_cross_s;
			signal_histPhotonInvMass->Scale( scale );
			before_trigger_signal_PhotonInvMass->Add(signal_histPhotonInvMass);

			TCanvas *canvas_PhotonInvMass = new TCanvas("canvas_PhotonInvMass","title",2500,0,600,500);
			hist_same (canvas_PhotonInvMass, before_trigger_bckg_PhotonInvMass, before_trigger_signal_PhotonInvMass , "Before Trigger Photon 1 and Photon 2 Inv Mass", "InvMass (GeV)", "Events", 0, 0);
			canvas_PhotonInvMass->Print("plots/cut0/before_trigger_PhotonInvMass_hadd.eps");

		//______________________________________________________________________
		// JET PT SPECTRUM

		TH1F * before_trigger_bckg_JetPT    = new TH1F("before_trigger_bckg_JetPT" ,  "before_trigger_bckg_JetPT",   100, 0.0, 2000);
		TH1F * before_trigger_signal_JetPT  = new TH1F("before_trigger_signal_JetPT" ,"before_trigger_signal_JetPT", 100, 0.0, 2000);

		for (int a=0;a<number_of_bckg;a++)
		{
			double scale= ( 1.0 / (bckg_histJetPT[a]->GetEntries() ) )* (cross_sections[a] ) ;
			//cout <<"entries:  " <<  bckg_histJetPT[a]->GetEntries() << "  cross_sections:  " << cross_sections[a] << endl;
			bckg_histJetPT[a]->Scale( scale );
			before_trigger_bckg_JetPT->Add(bckg_histJetPT[a]);
		}

		double scale= ( 1.0 / ( signal_histJetPT->GetEntries() ) )*total_cross_s;
		signal_histJetPT->Scale( scale );
		before_trigger_signal_JetPT->Add(signal_histJetPT);

		TCanvas *canvas_JetPT = new TCanvas("canvas_JetPT","title",2500,0,600,500);
		hist_same (canvas_JetPT, before_trigger_bckg_JetPT, before_trigger_signal_JetPT , "Before Trigger All Jet PT", "PT (GeV)", "Events", 0, 0);
		canvas_JetPT->Print("plots/cut0/before_trigger_JetPT_hadd.eps");

		//______________________________________________________________________
		// JET MASS SPECTRUM

		TH1F * before_trigger_bckg_JetMass    = new TH1F("before_trigger_bckg_JetMass" ,  "before_trigger_bckg_JetMass",   100, 0.0, 500);
		TH1F * before_trigger_signal_JetMass  = new TH1F("before_trigger_signal_JetMass" ,"before_trigger_signal_JetMass", 100, 0.0, 500);

		for (int a=0;a<number_of_bckg;a++)
		{
			double scale= ( 1.0 / (bckg_histJetMass[a]->GetEntries() ) )* (cross_sections[a] ) ;
			//cout <<"entries:  " <<  bckg_histJetMass[a]->GetEntries() << "  cross_sections:  " << cross_sections[a] << endl;
			bckg_histJetMass[a]->Scale( scale );
			before_trigger_bckg_JetMass->Add(bckg_histJetMass[a]);
		}

		double scale= ( 1.0 / ( signal_histJetMass->GetEntries() ) )*total_cross_s;
		signal_histJetMass->Scale( scale );
		before_trigger_signal_JetMass->Add(signal_histJetMass);

		TCanvas *canvas_JetMass = new TCanvas("canvas_JetMass","title",2500,0,600,500);
		hist_same (canvas_JetMass, before_trigger_bckg_JetMass, before_trigger_signal_JetMass , "Before Trigger All Jet Mass", "Mass (GeV)", "Events", 0, 0.);
		canvas_JetMass->Print("plots/cut0/before_trigger_JetMass_hadd.eps");

		//______________________________________________________________________
		// Event HT

		TH1F * before_trigger_bckg_Ht    = new TH1F("before_trigger_bckg_Ht" ,  "before_trigger_bckg_Ht",   100, 0.0, 4500);
		TH1F * before_trigger_signal_Ht  = new TH1F("before_trigger_signal_Ht" ,"before_trigger_signal_Ht", 100, 0.0, 4500);

		for (int a=0;a<number_of_bckg;a++)
		{
			double scale= ( 1.0 / (bckg_histHt[a]->GetEntries() ) )* (cross_sections[a] ) ;
			//cout <<"entries:  " <<  bckg_histHt[a]->GetEntries() << "  cross_sections:  " << cross_sections[a] << endl;
			bckg_histHt[a]->Scale( scale );
			before_trigger_bckg_Ht->Add(bckg_histHt[a]);
		}

		double scale= ( 1.0 / ( signal_histHt->GetEntries() ) )*total_cross_s;
		signal_histHt->Scale( scale );
		before_trigger_signal_Ht->Add(signal_histHt);

		TCanvas *canvas_Ht = new TCanvas("canvas_Ht","title",2500,0,600,500);
		hist_same (canvas_Ht, before_trigger_bckg_Ht, before_trigger_signal_Ht , "Before Trigger Event HT", "HT (GeV)", "Events", 0, 0.);
		canvas_Ht->Print("plots/cut0/before_trigger_Ht_hadd.eps");

		//______________________________________________________________________
		// Event MET

		TH1F * before_trigger_bckg_Met    = new TH1F("before_trigger_bckg_Met" ,  "before_trigger_bckg_Met",   100, 0.0, 1200);
		TH1F * before_trigger_signal_Met  = new TH1F("before_trigger_signal_Met" ,"before_trigger_signal_Met", 100, 0.0, 1200);

		for (int a=0;a<number_of_bckg;a++)
		{
			double scale= ( 1.0 / (bckg_histMet[a]->GetEntries() ) )* (cross_sections[a] ) ;
			//cout <<"entries:  " <<  bckg_histMet[a]->GetEntries() << "  cross_sections:  " << cross_sections[a] << endl;
			bckg_histMet[a]->Scale( scale );
			before_trigger_bckg_Met->Add(bckg_histMet[a]);
		}

		double scale= ( 1.0 / ( signal_histMet->GetEntries() ) )*total_cross_s;
		signal_histMet->Scale( scale );
		before_trigger_signal_Met->Add(signal_histMet);

		TCanvas *canvas_Met = new TCanvas("canvas_Met","title",2500,0,600,500);
		hist_same (canvas_Met, before_trigger_bckg_Met, before_trigger_signal_Met , "Before Trigger Event MET", "MET (GeV)", "Events", 0, 0.);
		canvas_Met->Print("plots/cut0/before_trigger_Met_hadd.eps");

		//______________________________________________________________________
		// Event METEta

		TH1F * before_trigger_bckg_MetEta    = new TH1F("before_trigger_bckg_MetEta" ,  "before_trigger_bckg_MetEta",   100, -15.0, 15);
		TH1F * before_trigger_signal_MetEta  = new TH1F("before_trigger_signal_MetEta" ,"before_trigger_signal_MetEta", 100, -15.0, 15);

		for (int a=0;a<number_of_bckg;a++)
		{
			double scale= ( 1.0 / (bckg_histMetEta[a]->GetEntries() ) )* (cross_sections[a] ) ;
			//cout <<"entries:  " <<  bckg_histMetEta[a]->GetEntries() << "  cross_sections:  " << cross_sections[a] << endl;
			bckg_histMetEta[a]->Scale( scale );
			before_trigger_bckg_MetEta->Add(bckg_histMetEta[a]);
		}

		double scale= ( 1.0 / ( signal_histMetEta->GetEntries() ) )*total_cross_s;
		signal_histMetEta->Scale( scale );
		before_trigger_signal_MetEta->Add(signal_histMetEta);

		TCanvas *canvas_MetEta = new TCanvas("canvas_MetEta","title",2500,0,600,500);
		hist_same (canvas_MetEta, before_trigger_bckg_MetEta, before_trigger_signal_MetEta , "Before Trigger Event MET Eta", "Eta", "Events", 0, 0.);
		canvas_MetEta->Print("plots/cut0/before_trigger_MetEta_hadd.eps");

    //gPad->SetLogy();
    //before_trigger_bckg_PhotonInvMass->Draw();
	  //before_trigger_bckg_PhotonInvMass->SetLineColor(2);
	  //before_trigger_signal_PhotonInvMass->Draw("same");
	  //before_trigger_bckg_PhotonInvMass->SetLineWidth(2);
	  //before_trigger_signal_PhotonInvMass->SetLineWidth(2);
	  //canvas_PT->BuildLegend();
	  ////canvas_PT->SetLogy();
	  //before_trigger_bckg_PhotonInvMass->SetStats(0);
	  //before_trigger_signal_PhotonInvMass->SetStats(0);
	  //canvas_PT->SetLeftMargin(0.127517);
	  //canvas_PT->SetRightMargin(0.02013423);


}
