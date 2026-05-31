{
	//gROOT->ProcessLine(".L /Users/nsonmez/root/macros/tdrStyle.eps");
	#include "superimpose_new.h"
	//#include "tdrstyle.h"
	//#include "CMSTDRStyle.h"

	gStyle->SetOptStat("n");

	//setTDRStyle();

	//double total_cross_b = 165078.6491;
	double signal_cross = (1.3*0.6)/(1000000*100000);
	//int signal_entry=100000;

	//______________________________________________________________
	// read the root files

  TFile *rootfile_bckg = new TFile( "/home/fozturk/Desktop/Analysis-master/analyze_output_new_tfd/cut1/analyze_sm_diphoton_bckg_all_cut1.root", "READ" );
	TFile *rootfile_signal = new TFile( "/home/fozturk/Desktop/Analysis-master/analyze_output_new_tfd/cut1/analyze_signal_diphoton_cut1.root", "READ" );

	//______________________________________________________________
	// get the histograms

	//------------------------------------------------------------------------------------
	//------------------Background Histograms---------------------------------------------
	//------------------------------------------------------------------------------------

	TH1F *bckg_histHt 		=				 (TH1F*)rootfile_bckg->Get("eventVar/ht");
	TH1F *bckg_histMet    =  			 (TH1F*)rootfile_bckg->Get("eventVar/met");
	TH1F *bckg_histMetEta =  			 (TH1F*)rootfile_bckg->Get("eventVar/met_eta");
	TH1F *bckg_histMetPhi =  			 (TH1F*)rootfile_bckg->Get("eventVar/met_phi");

  //------------------------------------------------------------------------------------

	TH1F *bckg_histJetSize    		= (TH1F*)rootfile_bckg->Get("Jet/jet_size");
	TH1F *bckg_histJetSize_cut    = (TH1F*)rootfile_bckg->Get("Jet/jet_size_cut");
	//TH1F  *histJet_size_cut   = new TH1F("jet_size_cut"	 ,   "JET SIZE CUT",          15,      0.0,   15.0);


	TH1F *bckg_histJetPT    			= (TH1F*)rootfile_bckg->Get("Jet/jet_pt");
	TH1F *bckg_histJetEta   			= (TH1F*)rootfile_bckg->Get("Jet/jet_eta");
	TH1F *bckg_histJetPhi   			= (TH1F*)rootfile_bckg->Get("Jet/jet_phi");

	TH1F *bckg_histJetPT_1        = (TH1F*)rootfile_bckg->Get("Jet/jet_pt_1");
	TH1F *bckg_histJetEta_1       = (TH1F*)rootfile_bckg->Get("Jet/jet_eta_1");
	TH1F *bckg_histJetPhi_1       = (TH1F*)rootfile_bckg->Get("Jet/jet_phi_1");

	TH1F *bckg_histJetPT_2        = (TH1F*)rootfile_bckg->Get("Jet/jet_pt_2");
	TH1F *bckg_histJetEta_2       = (TH1F*)rootfile_bckg->Get("Jet/jet_eta_2");
	TH1F *bckg_histJetPhi_2       = (TH1F*)rootfile_bckg->Get("Jet/jet_phi_2");

	TH1F *bckg_histJetMass  			= (TH1F*)rootfile_bckg->Get("Jet/jet_mass");

	TH1F *bckg_histJetDeltaEta    = (TH1F*)rootfile_bckg->Get("Jet/jet_delta_eta");
	TH1F *bckg_histJetDeltaPhi    = (TH1F*)rootfile_bckg->Get("Jet/jet_delta_phi");
	TH1F *bckg_histJetDeltaR      = (TH1F*)rootfile_bckg->Get("Jet/jet_deltar");

	TH1F *bckg_histJetDeltaEta_1  = (TH1F*)rootfile_bckg->Get("Jet/jet_delta_eta_1");
	TH1F *bckg_histJetDeltaPhi_1  = (TH1F*)rootfile_bckg->Get("Jet/jet_delta_phi_1");
	TH1F *bckg_histJetDeltaR_1    = (TH1F*)rootfile_bckg->Get("Jet/jet_deltar_1");

	//------------------------------------------------------------------------------------

	TH1F *bckg_histPhotonSize    	  				= (TH1F*)rootfile_bckg->Get("Photon/photon_size");
	TH1F *bckg_histPhotonSize_barrel    	  = (TH1F*)rootfile_bckg->Get("Photon/photon_size_barrel");
	TH1F *bckg_histPhotonSize_endcap    	  = (TH1F*)rootfile_bckg->Get("Photon/photon_size_endcap");
	TH1F *bckg_histPhotonSize_endbar    	  = (TH1F*)rootfile_bckg->Get("Photon/photon_size_endbar");

	TH1F *bckg_histPhotonPT    		  = (TH1F*)rootfile_bckg->Get("Photon/photon_pt");
	TH1F *bckg_histPhotonEta   		  = (TH1F*)rootfile_bckg->Get("Photon/photon_eta");
	TH1F *bckg_histPhotonPhi   		  = (TH1F*)rootfile_bckg->Get("Photon/photon_phi");

	TH1F *bckg_histPhotonPT_1       = (TH1F*)rootfile_bckg->Get("Photon/photon_pt_1");
	TH1F *bckg_histPhotonEta_1      = (TH1F*)rootfile_bckg->Get("Photon/photon_eta_1");
	TH1F *bckg_histPhotonPhi_1      = (TH1F*)rootfile_bckg->Get("Photon/photon_phi_1");

	TH1F *bckg_histPhotonPT_2       = (TH1F*)rootfile_bckg->Get("Photon/photon_pt_2");
	TH1F *bckg_histPhotonEta_2      = (TH1F*)rootfile_bckg->Get("Photon/photon_eta_2");
	TH1F *bckg_histPhotonPhi_2      = (TH1F*)rootfile_bckg->Get("Photon/photon_phi_2");

	TH1F *bckg_histPhotonHT    		  = (TH1F*)rootfile_bckg->Get("Photon/photon_ht");
	TH1F *bckg_histPhotonE          = (TH1F*)rootfile_bckg->Get("Photon/photon_e");
	TH1F *bckg_histPhotonInvMass  	= (TH1F*)rootfile_bckg->Get("Photon/photon_invmass");
	TH1F *bckg_histPhotonInvMass_barrel  	= (TH1F*)rootfile_bckg->Get("Photon/photon_invmass_barrel");
	TH1F *bckg_histPhotonInvMass_endcap  	= (TH1F*)rootfile_bckg->Get("Photon/photon_invmass_endcap");
	TH1F *bckg_histPhotonInvMass_endbar  	= (TH1F*)rootfile_bckg->Get("Photon/photon_invmass_endbar");


	TH1F *bckg_histPhotonDeltaEta   = (TH1F*)rootfile_bckg->Get("Photon/photon_delta_eta");
	TH1F *bckg_histPhotonDeltaPhi   = (TH1F*)rootfile_bckg->Get("Photon/photon_delta_phi");
	TH1F *bckg_histPhotonDeltaR     = (TH1F*)rootfile_bckg->Get("Photon/photon_deltar");
	TH1F *bckg_histPhotonReso       = (TH1F*)rootfile_bckg->Get("Photon/photon_pt_reso");

	//------------------------------------------------------------------------------------

	TH1F *bckg_histPhotonJet_pt     	       = (TH1F*)rootfile_bckg->Get("photonjet_pt"         );
	TH1F *bckg_histPhotonJet_deltaphi        = (TH1F*)rootfile_bckg->Get("photonjet_delta_phi"  );
	TH1F *bckg_histPhotonJet_deltaeta        = (TH1F*)rootfile_bckg->Get("photonjet_delta_eta"  );
	TH1F *bckg_histPhotonJet_deltar          = (TH1F*)rootfile_bckg->Get("photonjet_deltar"     );

	TH1F *bckg_histPhotonJet_pt_1     	     = (TH1F*)rootfile_bckg->Get("photonjet_pt_1"       );
	TH1F *bckg_histPhotonJet_deltaphi_1      = (TH1F*)rootfile_bckg->Get("photonjet_delta_phi_1");
	TH1F *bckg_histPhotonJet_deltaeta_1      = (TH1F*)rootfile_bckg->Get("photonjet_delta_eta_1");
	TH1F *bckg_histPhotonJet_deltar_1        = (TH1F*)rootfile_bckg->Get("photonjet_deltar_1"   );


	//------------------------------------------------------------------------------------

	TH1F *bckg_histMuonSize    		  = (TH1F*)rootfile_bckg->Get("Muon/muon_size");
	TH1F *bckg_histElectronSize    	= (TH1F*)rootfile_bckg->Get("Electron/electron_size");
	TH1F *bckg_histLeptonSize    		= (TH1F*)rootfile_bckg->Get("Lepton/lepton_size");



	//------------------------------------------------------------------------------------
	//------------------Signal Histograms-------------------------------------------------
	//------------------------------------------------------------------------------------

	TH1F *signal_histHt =  					 (TH1F*)rootfile_signal->Get("eventVar/ht");
	TH1F *signal_histMet =  	  		 (TH1F*)rootfile_signal->Get("eventVar/met");
	TH1F *signal_histMetEta =  			 (TH1F*)rootfile_signal->Get("eventVar/met_eta");
	TH1F *signal_histMetPhi =  			 (TH1F*)rootfile_signal->Get("eventVar/met_phi");

	//------------------------------------------------------------------------------------

	TH1F *signal_histJetSize    		= (TH1F*)rootfile_signal->Get("Jet/jet_size");
	TH1F *signal_histJetSize_cut    = (TH1F*)rootfile_signal->Get("Jet/jet_size_cut");

	TH1F *signal_histJetPT    			= (TH1F*)rootfile_signal->Get("Jet/jet_pt");
	TH1F *signal_histJetEta   			= (TH1F*)rootfile_signal->Get("Jet/jet_eta");
	TH1F *signal_histJetPhi   			= (TH1F*)rootfile_signal->Get("Jet/jet_phi");

	TH1F *signal_histJetPT_1        = (TH1F*)rootfile_signal->Get("Jet/jet_pt_1");
	TH1F *signal_histJetEta_1       = (TH1F*)rootfile_signal->Get("Jet/jet_eta_1");
	TH1F *signal_histJetPhi_1       = (TH1F*)rootfile_signal->Get("Jet/jet_phi_1");

	TH1F *signal_histJetPT_2        = (TH1F*)rootfile_signal->Get("Jet/jet_pt_2");
	TH1F *signal_histJetEta_2       = (TH1F*)rootfile_signal->Get("Jet/jet_eta_2");
	TH1F *signal_histJetPhi_2       = (TH1F*)rootfile_signal->Get("Jet/jet_phi_2");

	TH1F *signal_histJetMass  			= (TH1F*)rootfile_signal->Get("Jet/jet_mass");

	TH1F *signal_histJetDeltaEta    = (TH1F*)rootfile_signal->Get("Jet/jet_delta_eta");
	TH1F *signal_histJetDeltaPhi    = (TH1F*)rootfile_signal->Get("Jet/jet_delta_phi");
	TH1F *signal_histJetDeltaR      = (TH1F*)rootfile_signal->Get("Jet/jet_deltar");

	TH1F *signal_histJetDeltaEta_1  = (TH1F*)rootfile_signal->Get("Jet/jet_delta_eta_1");
	TH1F *signal_histJetDeltaPhi_1  = (TH1F*)rootfile_signal->Get("Jet/jet_delta_phi_1");
	TH1F *signal_histJetDeltaR_1    = (TH1F*)rootfile_signal->Get("Jet/jet_deltar_1");


	//------------------------------------------------------------------------------------

	TH1F *signal_histPhotonSize    	  = (TH1F*)rootfile_signal->Get("Photon/photon_size");
	TH1F *signal_histPhotonSize_barrel    	  = (TH1F*)rootfile_signal->Get("Photon/photon_size_barrel");
	TH1F *signal_histPhotonSize_endcap    	  = (TH1F*)rootfile_signal->Get("Photon/photon_size_endcap");
	TH1F *signal_histPhotonSize_endbar    	  = (TH1F*)rootfile_signal->Get("Photon/photon_size_endbar");

	TH1F *signal_histPhotonPT    		  = (TH1F*)rootfile_signal->Get("Photon/photon_pt");
	TH1F *signal_histPhotonEta   		  = (TH1F*)rootfile_signal->Get("Photon/photon_eta");
	TH1F *signal_histPhotonPhi   		  = (TH1F*)rootfile_signal->Get("Photon/photon_phi");

	TH1F *signal_histPhotonPT_1       = (TH1F*)rootfile_signal->Get("Photon/photon_pt_1");
	TH1F *signal_histPhotonEta_1      = (TH1F*)rootfile_signal->Get("Photon/photon_eta_1");
	TH1F *signal_histPhotonPhi_1      = (TH1F*)rootfile_signal->Get("Photon/photon_phi_1");

	TH1F *signal_histPhotonPT_2       = (TH1F*)rootfile_signal->Get("Photon/photon_pt_2");
	TH1F *signal_histPhotonEta_2      = (TH1F*)rootfile_signal->Get("Photon/photon_eta_2");
	TH1F *signal_histPhotonPhi_2      = (TH1F*)rootfile_signal->Get("Photon/photon_phi_2");

	TH1F *signal_histPhotonHT   		  = (TH1F*)rootfile_signal->Get("Photon/photon_ht");
	TH1F *signal_histPhotonE          = (TH1F*)rootfile_signal->Get("Photon/photon_e");
	TH1F *signal_histPhotonInvMass    = (TH1F*)rootfile_signal->Get("Photon/photon_invmass");
	TH1F *signal_histPhotonInvMass_barrel  	= (TH1F*)rootfile_signal->Get("Photon/photon_invmass_barrel");
	TH1F *signal_histPhotonInvMass_endcap  	= (TH1F*)rootfile_signal->Get("Photon/photon_invmass_endcap");
	TH1F *signal_histPhotonInvMass_endbar  	= (TH1F*)rootfile_signal->Get("Photon/photon_invmass_endbar");


	TH1F *signal_histPhotonDeltaEta   = (TH1F*)rootfile_signal->Get("Photon/photon_delta_eta");
	TH1F *signal_histPhotonDeltaPhi   = (TH1F*)rootfile_signal->Get("Photon/photon_delta_phi");
	TH1F *signal_histPhotonDeltaR     = (TH1F*)rootfile_signal->Get("Photon/photon_deltar");
	TH1F *signal_histPhoton_reso       = (TH1F*)rootfile_signal->Get("Photon/photon_pt_reso");

	//------------------------------------------------------------------------------------

	TH1F *signal_histMuonSize    		  = (TH1F*)rootfile_signal->Get("Muon/muon_size");
	TH1F *signal_histElectronSize    	= (TH1F*)rootfile_signal->Get("Electron/electron_size");
	TH1F *signal_histLeptonSize    		= (TH1F*)rootfile_signal->Get("Lepton/lepton_size");

	//------------------------------------------------------------------------------------

	TH1F *signal_histPhotonJet_pt     	       = (TH1F*)rootfile_signal->Get("photonjet_pt"         );
	TH1F *signal_histPhotonJet_deltaphi        = (TH1F*)rootfile_signal->Get("photonjet_delta_phi"  );
	TH1F *signal_histPhotonJet_deltaeta        = (TH1F*)rootfile_signal->Get("photonjet_delta_eta"  );
	TH1F *signal_histPhotonJet_deltar          = (TH1F*)rootfile_signal->Get("photonjet_deltar"     );

	TH1F *signal_histPhotonJet_pt_1     	     = (TH1F*)rootfile_signal->Get("photonjet_pt_1"       );
	TH1F *signal_histPhotonJet_deltaphi_1      = (TH1F*)rootfile_signal->Get("photonjet_delta_phi_1");
	TH1F *signal_histPhotonJet_deltaeta_1      = (TH1F*)rootfile_signal->Get("photonjet_delta_eta_1");
	TH1F *signal_histPhotonJet_deltar_1        = (TH1F*)rootfile_signal->Get("photonjet_deltar_1"   );


	//------------------------------------------------------------------------------------
	 //------------------------------------------------------------------------------------
	 //------------------------------------------------------------------------------------
		cout << "Histogramlar ayarlandı" << endl;

		double scale=0.0;

		//______________________________________________________________________
		// PhotonJet SPECTRUM

		//bckg_histPhotonPhotonJet_pt->Scale(1/ bckg_histPhotonPhotonJet_pt->Integral() );

		signal_histPhotonPhotonJet_pt->Scale( signal_cross);
		//signal_histPhotonPhotonJet_pt->Scale(1/signal_histPhotonPhotonJet_pt->Integral());

		TCanvas *canvas_PhotonPhotonJet_pt = new TCanvas("canvas_PhotonPhotonJet_pt","title",2500,0,600,500);
		hist_same (canvas_PhotonPhotonJet_pt, bckg_histPhotonPhotonJet_pt, signal_histPhotonPhotonJet_pt , "Cut 1 Photon PhotonJet_pt", "PhotonJet_pt (GeV)", "Events", 0, 0);
		canvas_PhotonPhotonJet_pt->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonPhotonJet_pt.eps");

		//------------------------------------------------------------------------------------

		//bckg_histPhotonJet_deltaphi->Scale(1/ bckg_histPhotonJet_deltaphi->Integral() );

		signal_histPhotonJet_deltaphi->Scale( signal_cross);
		//signal_histPhotonJet_deltaphi->Scale(1/signal_histPhotonJet_deltaphi->Integral());

		TCanvas *canvas_PhotonJet_deltaphi = new TCanvas("canvas_PhotonJet_deltaphi","title",2500,0,600,500);
		hist_same (canvas_PhotonJet_deltaphi, bckg_histPhotonJet_deltaphi, signal_histPhotonJet_deltaphi , "Cut 1 Photon Jet_deltaphi", "Jet_deltaphi (GeV)", "Events", 0, 0);
		canvas_PhotonJet_deltaphi->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonJet_deltaphi.eps");

		//------------------------------------------------------------------------------------


		//bckg_histPhotonJet_deltaeta->Scale(1/ bckg_histPhotonJet_deltaeta->Integral() );

		signal_histPhotonJet_deltaeta->Scale( signal_cross);
		//signal_histPhotonJet_deltaeta->Scale(1/signal_histPhotonJet_deltaeta->Integral());

		TCanvas *canvas_PhotonJet_deltaeta = new TCanvas("canvas_PhotonJet_deltaeta","title",2500,0,600,500);
		hist_same (canvas_PhotonJet_deltaeta, bckg_histPhotonJet_deltaeta, signal_histPhotonJet_deltaeta , "Cut 1 Photon Jet_deltaeta", "Jet_deltaeta (GeV)", "Events", 0, 0);
		canvas_PhotonJet_deltaeta->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonJet_deltaeta.eps");


		//------------------------------------------------------------------------------------

		//bckg_histPhotonJet_deltar->Scale(1/ bckg_histPhotonJet_deltar->Integral() );

		signal_histPhotonJet_deltar->Scale( signal_cross);
		//signal_histPhotonJet_deltar->Scale(1/signal_histPhotonJet_deltar->Integral());

		TCanvas *canvas_PhotonJet_deltar = new TCanvas("canvas_PhotonJet_deltar","title",2500,0,600,500);
		hist_same (canvas_PhotonJet_deltar, bckg_histPhotonJet_deltar, signal_histPhotonJet_deltar , "Cut 1 Photon Jet_deltar", "Jet_deltar (GeV)", "Events", 0, 0);
		canvas_PhotonJet_deltar->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonJet_deltar.eps");

		//------------------------------------------------------------------------------------

		//bckg_histPhotonPhotonJet_pt_1->Scale(1/ bckg_histPhotonPhotonJet_pt_1->Integral() );

		signal_histPhotonPhotonJet_pt_1->Scale( signal_cross);
		//signal_histPhotonPhotonJet_pt_1->Scale(1/signal_histPhotonPhotonJet_pt_1->Integral());

		TCanvas *canvas_PhotonPhotonJet_pt_1 = new TCanvas("canvas_PhotonPhotonJet_pt_1","title",2500,0,600,500);
		hist_same (canvas_PhotonPhotonJet_pt_1, bckg_histPhotonPhotonJet_pt_1, signal_histPhotonPhotonJet_pt_1 , "Cut 1 Photon PhotonJet_pt_1", "PhotonJet_pt_1 (GeV)", "Events", 0, 0);
		canvas_PhotonPhotonJet_pt_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonPhotonJet_pt_1.eps");

		//------------------------------------------------------------------------------------

		//bckg_histPhotonJet_deltaphi_1->Scale(1/ bckg_histPhotonJet_deltaphi_1->Integral() );

		signal_histPhotonJet_deltaphi_1->Scale( signal_cross);
		//signal_histPhotonJet_deltaphi_1->Scale(1/signal_histPhotonJet_deltaphi_1->Integral());

		TCanvas *canvas_PhotonJet_deltaphi_1 = new TCanvas("canvas_PhotonJet_deltaphi_1","title",2500,0,600,500);
		hist_same (canvas_PhotonJet_deltaphi_1, bckg_histPhotonJet_deltaphi_1, signal_histPhotonJet_deltaphi_1 , "Cut 1 Photon Jet_deltaphi_1", "Jet_deltaphi_1 (GeV)", "Events", 0, 0);
		canvas_PhotonJet_deltaphi_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonJet_deltaphi_1.eps");

		//------------------------------------------------------------------------------------


		//bckg_histPhotonJet_deltaeta_1->Scale(1/ bckg_histPhotonJet_deltaeta_1->Integral() );

		signal_histPhotonJet_deltaeta_1->Scale( signal_cross);
		//signal_histPhotonJet_deltaeta_1->Scale(1/signal_histPhotonJet_deltaeta_1->Integral());

		TCanvas *canvas_PhotonJet_deltaeta_1 = new TCanvas("canvas_PhotonJet_deltaeta_1","title",2500,0,600,500);
		hist_same (canvas_PhotonJet_deltaeta_1, bckg_histPhotonJet_deltaeta_1, signal_histPhotonJet_deltaeta_1 , "Cut 1 Photon Jet_deltaeta_1", "Jet_deltaeta_1 (GeV)", "Events", 0, 0);
		canvas_PhotonJet_deltaeta_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonJet_deltaeta_1.eps");


		//------------------------------------------------------------------------------------

		//bckg_histPhotonJet_deltar_1->Scale(1/ bckg_histPhotonJet_deltar_1->Integral() );

		signal_histPhotonJet_deltar_1->Scale( signal_cross);
		//signal_histPhotonJet_deltar_1->Scale(1/signal_histPhotonJet_deltar_1->Integral());

		TCanvas *canvas_PhotonJet_deltar_1 = new TCanvas("canvas_PhotonJet_deltar_1","title",2500,0,600,500);
		hist_same (canvas_PhotonJet_deltar_1, bckg_histPhotonJet_deltar_1, signal_histPhotonJet_deltar_1 , "Cut 1 Photon Jet_deltar_1", "Jet_deltar_1 (GeV)", "Events", 0, 0);
		canvas_PhotonJet_deltar_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonJet_deltar_1.eps");

		//------------------------------------------------------------------------------------

		//bckg_histPhoton_reso->Scale(1/ bckg_histPhoton_reso->Integral() );

		signal_histPhoton_reso->Scale( signal_cross);
		//signal_histPhoton_reso->Scale(1/signal_histPhoton_reso->Integral());

		TCanvas *canvas_Photon_reso = new TCanvas("canvas_Photon_reso","title",2500,0,600,500);
		hist_same (canvas_Photon_reso, bckg_histPhoton_reso, signal_histPhoton_reso , "Cut 1 Photon _reso", "_reso (GeV)", "Events", 0, 0);
		canvas_Photon_reso->Print("plots_new_tfd/cut1_hadd/cut1_hadd_Photon_reso.eps");


		//______________________________________________________________________
		// Photon Size SPECTRUM

		//bckg_histPhotonSize->Scale(1/ bckg_histPhotonSize->Integral() );

		signal_histPhotonSize->Scale( signal_cross);
		//signal_histPhotonSize->Scale(1/signal_histPhotonSize->Integral());

		TCanvas *canvas_PhotonSize = new TCanvas("canvas_PhotonSize","title",2500,0,600,500);
		hist_same (canvas_PhotonSize, bckg_histPhotonSize, signal_histPhotonSize , "Cut 1 Photon Size", "Size (GeV)", "Events", 0, 0);
		canvas_PhotonSize->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonSize.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonSize_barrel->Scale(1/ bckg_histPhotonSize_barrel->Integral() );

		signal_histPhotonSize_barrel->Scale( signal_cross);
		//signal_histPhotonSize_barrel->Scale(1/signal_histPhotonSize_barrel->Integral());

		TCanvas *canvas_PhotonSize_barrel = new TCanvas("canvas_PhotonSize_barrel","title",2500,0,600,500);
		hist_same (canvas_PhotonSize_barrel, bckg_histPhotonSize_barrel, signal_histPhotonSize_barrel , "Cut 1 Photon Size_barrel", "Size_barrel (GeV)", "Events", 0, 0);
		canvas_PhotonSize_barrel->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonSize_barrel.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonSize_endcap->Scale(1/ bckg_histPhotonSize_endcap->Integral() );

		signal_histPhotonSize_endcap->Scale( signal_cross);
		//signal_histPhotonSize_endcap->Scale(1/signal_histPhotonSize_endcap->Integral());

		TCanvas *canvas_PhotonSize_endcap = new TCanvas("canvas_PhotonSize_endcap","title",2500,0,600,500);
		hist_same (canvas_PhotonSize_endcap, bckg_histPhotonSize_endcap, signal_histPhotonSize_endcap , "Cut 1 Photon Size_endcap", "Size_endcap (GeV)", "Events", 0, 0);
		canvas_PhotonSize_endcap->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonSize_endcap.eps");

//--------------------------------------------------------------------------------------------------------------------------------------
		//bckg_histPhotonSize_endbar->Scale(1/ bckg_histPhotonSize_endbar->Integral() );

		signal_histPhotonSize_endbar->Scale( signal_cross);
		//signal_histPhotonSize_endbar->Scale(1/signal_histPhotonSize_endbar->Integral());

		TCanvas *canvas_PhotonSize_endbar = new TCanvas("canvas_PhotonSize_endbar","title",2500,0,600,500);
		hist_same (canvas_PhotonSize_endbar, bckg_histPhotonSize_endbar, signal_histPhotonSize_endbar , "Cut 1 Photon Size_endbar", "Size_endbar (GeV)", "Events", 0, 0);
		canvas_PhotonSize_endbar->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonSize_endbar.eps");

		//______________________________________________________________________
		// Photon Size Eta Phi All SPECTRUM

		//bckg_histPhotonPT->Scale(1/bckg_histPhotonPT->Integral());

		signal_histPhotonPT->Scale( signal_cross);
		//signal_histPhotonPT->Scale(1/signal_histPhotonPT->Integral());

		TCanvas *canvas_PhotonPT = new TCanvas("canvas_PhotonPT","title",2500,0,600,500);
		hist_same (canvas_PhotonPT, bckg_histPhotonPT, signal_histPhotonPT , "Cut 1 All Photon PT", "PT (GeV)", "Events", 0, 0);
		canvas_PhotonPT->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonPT.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonEta->Scale(1/bckg_histPhotonEta->Integral());

		signal_histPhotonEta->Scale( signal_cross);
		//signal_histPhotonEta->Scale(1/signal_histPhotonEta->Integral());

		TCanvas *canvas_PhotonEta = new TCanvas("canvas_PhotonEta","title",2500,0,600,500);
		hist_same (canvas_PhotonEta, bckg_histPhotonEta, signal_histPhotonEta , "Cut 1 All Photon Eta", "Eta (GeV)", "Events", 0, 0);
		canvas_PhotonEta->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonEta.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonPhi->Scale(1/bckg_histPhotonPhi->Integral());

		signal_histPhotonPhi->Scale( signal_cross);
		//signal_histPhotonPhi->Scale(1/signal_histPhotonPhi->Integral());

		TCanvas *canvas_PhotonPhi = new TCanvas("canvas_PhotonPhi","title",2500,0,600,500);
		hist_same (canvas_PhotonPhi, bckg_histPhotonPhi, signal_histPhotonPhi , "Cut 1 All Photon Phi", "Phi (GeV)", "Events", 0, 0);
		canvas_PhotonPhi->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonPhi.eps");

		//______________________________________________________________________
		// Photon PT 1, Eta 1, and Phi 1  SPECTRUM

		//bckg_histPhotonPT_1->Scale(1/bckg_histPhotonPT_1->Integral());

		signal_histPhotonPT_1->Scale( signal_cross);
		//signal_histPhotonPT_1->Scale(1/signal_histPhotonPT_1->Integral());

		TCanvas *canvas_PhotonPT_1 = new TCanvas("canvas_PhotonPT_1","title",2500,0,600,500);
		hist_same (canvas_PhotonPT_1, bckg_histPhotonPT_1, signal_histPhotonPT_1 , "Cut 1 Photon PT_1", "PT_1 (GeV)", "Events", 0, 0);
		canvas_PhotonPT_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonPT_1.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonEta_1->Scale(1/bckg_histPhotonEta_1->Integral());

		signal_histPhotonEta_1->Scale( signal_cross);
		//signal_histPhotonEta_1->Scale(1/signal_histPhotonEta_1->Integral());

		TCanvas *canvas_PhotonEta_1 = new TCanvas("canvas_PhotonEta_1","title",2500,0,600,500);
		hist_same (canvas_PhotonEta_1, bckg_histPhotonEta_1, signal_histPhotonEta_1 , "Cut 1 Photon Eta_1", "Eta_1 (GeV)", "Events", 0, 0);
		canvas_PhotonEta_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonEta_1.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonPhi_1->Scale(1/bckg_histPhotonPhi_1->Integral());

		signal_histPhotonPhi_1->Scale( signal_cross);
		//signal_histPhotonPhi_1->Scale(1/signal_histPhotonPhi_1->Integral());

		TCanvas *canvas_PhotonPhi_1 = new TCanvas("canvas_PhotonPhi_1","title",2500,0,600,500);
		hist_same (canvas_PhotonPhi_1, bckg_histPhotonPhi_1, signal_histPhotonPhi_1 , "Cut 1 Photon Phi_1", "Phi_1 (GeV)", "Events", 0, 0);
		canvas_PhotonPhi_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonPhi_1.eps");


		//______________________________________________________________________
		// Photon PT 2, Eta 2 and Phi 2 SPECTRUM

		//bckg_histPhotonPT_2->Scale(1/bckg_histPhotonPT_2->Integral());

		signal_histPhotonPT_2->Scale( signal_cross);
		//signal_histPhotonPT_2->Scale(1/signal_histPhotonPT_2->Integral());

		TCanvas *canvas_PhotonPT_2 = new TCanvas("canvas_PhotonPT_2","title",2500,0,600,500);
		hist_same (canvas_PhotonPT_2, bckg_histPhotonPT_2, signal_histPhotonPT_2 , "Cut 1 Photon PT_2", "PT_2 (GeV)", "Events", 0, 0);
		canvas_PhotonPT_2->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonPT_2.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonEta_2->Scale(1/bckg_histPhotonEta_2->Integral());

		signal_histPhotonEta_2->Scale( signal_cross);
		//signal_histPhotonEta_2->Scale(1/signal_histPhotonEta_2->Integral());

		TCanvas *canvas_PhotonEta_2 = new TCanvas("canvas_PhotonEta_2","title",2500,0,600,500);
		hist_same (canvas_PhotonEta_2, bckg_histPhotonEta_2, signal_histPhotonEta_2 , "Cut 1 Photon Eta_2", "Eta_2 (GeV)", "Events", 0, 0);
		canvas_PhotonEta_2->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonEta_2.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonPhi_2->Scale(1/bckg_histPhotonPhi_2->Integral());

		signal_histPhotonPhi_2->Scale( signal_cross);
		//signal_histPhotonPhi_2->Scale(1/signal_histPhotonPhi_2->Integral());

		TCanvas *canvas_PhotonPhi_2 = new TCanvas("canvas_PhotonPhi_2","title",2500,0,600,500);
		hist_same (canvas_PhotonPhi_2, bckg_histPhotonPhi_2, signal_histPhotonPhi_2 , "Cut 1 Photon Phi_2", "Phi_2 (GeV)", "Events", 0, 0);
		canvas_PhotonPhi_2->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonPhi_2.eps");


		//______________________________________________________________________
		// Photon Delta Eta, Delta Phi, DeltaR

		//bckg_histPhotonDeltaEta->Scale(1/bckg_histPhotonDeltaEta->Integral());

		signal_histPhotonDeltaEta->Scale( signal_cross);
		//signal_histPhotonDeltaEta->Scale(1/signal_histPhotonDeltaEta->Integral());

		TCanvas *canvas_PhotonDeltaEta = new TCanvas("canvas_PhotonDeltaEta","title",2500,0,600,500);
		hist_same (canvas_PhotonDeltaEta, bckg_histPhotonDeltaEta, signal_histPhotonDeltaEta , "Cut 1 Photon Delta_Eta", "Delta_Eta (GeV)", "Events", 0, 0);
		canvas_PhotonDeltaEta->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonDeltaEta.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonDeltaPhi->Scale(1/bckg_histPhotonDeltaPhi->Integral());

		signal_histPhotonDeltaPhi->Scale( signal_cross);
		//signal_histPhotonDeltaPhi->Scale(1/signal_histPhotonDeltaPhi->Integral());

		TCanvas *canvas_PhotonDeltaPhi = new TCanvas("canvas_PhotonDeltaPhi","title",2500,0,600,500);
		hist_same (canvas_PhotonDeltaPhi, bckg_histPhotonDeltaPhi, signal_histPhotonDeltaPhi , "Cut 1 Photon Delta_Phi", "Delta_Phi (GeV)", "Events", 0, 0);
		canvas_PhotonDeltaPhi->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonDeltaPhi.eps");

		//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonDeltaR->Scale(1/bckg_histPhotonDeltaR->Integral());

		signal_histPhotonDeltaR->Scale( signal_cross);
		//signal_histPhotonDeltaR->Scale(1/signal_histPhotonDeltaR->Integral());

		TCanvas *canvas_PhotonDeltaR = new TCanvas("canvas_PhotonDeltaR","title",2500,0,600,500);
		hist_same (canvas_PhotonDeltaR, bckg_histPhotonDeltaR, signal_histPhotonDeltaR , "Cut 1 Photon DeltaR", "DeltaR (GeV)", "Events", 0, 0);
		canvas_PhotonDeltaR->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonDeltaR.eps");

		//______________________________________________________________________
		// Photon HT SPECTRUM

		//bckg_histPhotonHT->Scale(1/bckg_histPhotonHT->Integral());

		signal_histPhotonHT->Scale( signal_cross);
		//signal_histPhotonHT->Scale(1/signal_histPhotonHT->Integral());

		TCanvas *canvas_PhotonHT = new TCanvas("canvas_PhotonHT","title",2500,0,600,500);
		hist_same (canvas_PhotonHT, bckg_histPhotonHT, signal_histPhotonHT , "Cut 1 All Photon HT", "HT (GeV)", "Events", 0, 0);
		//bckg_histPhotonHT->GetXaxis()->SetRangeUser(0,1000);
		canvas_PhotonHT->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonHT.eps");

		//______________________________________________________________________
		// Photon E SPECTRUM

		//bckg_histPhotonE->Scale(1/bckg_histPhotonE->Integral());

		signal_histPhotonE->Scale( signal_cross);
		//signal_histPhotonE->Scale(1/signal_histPhotonE->Integral());

		TCanvas *canvas_PhotonE = new TCanvas("canvas_PhotonE","title",2500,0,600,500);
		hist_same (canvas_PhotonE, bckg_histPhotonE, signal_histPhotonE , "Cut 1 All Photon E", "E (GeV)", "Events", 0, 0);
		canvas_PhotonE->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonE.eps");

		//______________________________________________________________________
		// Photon InvMass SPECTRUM

		//bckg_histPhotonInvMass->Scale(1/bckg_histPhotonInvMass->Integral());

		signal_histPhotonInvMass->Scale( signal_cross);
		//signal_histPhotonInvMass->Scale(1/signal_histPhotonInvMass->Integral());

		TCanvas *canvas_PhotonInvMass = new TCanvas("canvas_PhotonInvMass","title",2500,0,600,500);
		hist_same (canvas_PhotonInvMass, bckg_histPhotonInvMass, signal_histPhotonInvMass , "Cut 1 Photon 1 and Photon 2 Inv Mass", "InvMass (GeV)", "Events", 0, 0);
		canvas_PhotonInvMass->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonInvMass.eps");

		//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonInvMass_barrel->Scale(1/bckg_histPhotonInvMass_barrel->Integral());

		signal_histPhotonInvMass_barrel->Scale( signal_cross);
		//signal_histPhotonInvMass_barrel->Scale(1/signal_histPhotonInvMass_barrel->Integral());

		TCanvas *canvas_PhotonInvMass_barrel = new TCanvas("canvas_PhotonInvMass_barrel","title",2500,0,600,500);
		hist_same (canvas_PhotonInvMass_barrel, bckg_histPhotonInvMass_barrel, signal_histPhotonInvMass_barrel , "Cut 1 Photon 1 and Photon 2 Inv Mass Barrel", "InvMass_barrel (GeV)", "Events", 0, 0);
		canvas_PhotonInvMass_barrel->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonInvMass_barrel.eps");

		//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonInvMass_endcap->Scale(1/bckg_histPhotonInvMass_endcap->Integral());

		signal_histPhotonInvMass_endcap->Scale( signal_cross);
		//signal_histPhotonInvMass_endcap->Scale(1/signal_histPhotonInvMass_endcap->Integral());

		TCanvas *canvas_PhotonInvMass_endcap = new TCanvas("canvas_PhotonInvMass_endcap","title",2500,0,600,500);
		hist_same (canvas_PhotonInvMass_endcap, bckg_histPhotonInvMass_endcap, signal_histPhotonInvMass_endcap , "Cut 1 Photon 1 and Photon 2 Inv Mass Endcap", "InvMass_endcap (GeV)", "Events", 0, 0);
		canvas_PhotonInvMass_endcap->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonInvMass_endcap.eps");

		//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histPhotonInvMass_endbar->Scale(1/bckg_histPhotonInvMass_endbar->Integral());

		signal_histPhotonInvMass_endbar->Scale( signal_cross);
		//signal_histPhotonInvMass_endbar->Scale(1/signal_histPhotonInvMass_endbar->Integral());

		TCanvas *canvas_PhotonInvMass_endbar = new TCanvas("canvas_PhotonInvMass_endbar","title",2500,0,600,500);
		hist_same (canvas_PhotonInvMass_endbar, bckg_histPhotonInvMass_endbar, signal_histPhotonInvMass_endbar , "Cut 1 Photon 1 and Photon 2 Inv Mass", "InvMass_endbar (GeV)", "Events", 0, 0);
		canvas_PhotonInvMass_endbar->Print("plots_new_tfd/cut1_hadd/cut1_hadd_PhotonInvMass_endbar.eps");

		//______________________________________________________________________
		// Jet Size SPECTRUM

		//bckg_histJetSize->Scale(1/bckg_histJetSize->Integral());

		signal_histJetSize->Scale( signal_cross);
		//signal_histJetSize->Scale(1/signal_histJetSize->Integral());

		TCanvas *canvas_JetSize = new TCanvas("canvas_JetSize","title",2500,0,600,500);
		hist_same (canvas_JetSize, bckg_histJetSize, signal_histJetSize , "Cut 1 Jet Size", "Size (GeV)", "Events", 0, 0);
		canvas_JetSize->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetSize.eps");

		//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetSize_cut->Scale(1/bckg_histJetSize_cut->Integral());

		signal_histJetSize_cut->Scale( signal_cross);
		//signal_histJetSize_cut->Scale(1/signal_histJetSize_cut->Integral());

		TCanvas *canvas_JetSize_cut = new TCanvas("canvas_JetSize_cut","title",2500,0,600,500);
		hist_same (canvas_JetSize_cut, bckg_histJetSize_cut, signal_histJetSize_cut , "Cut 1 Jet Size_cut", "Size_cut (GeV)", "Events", 0, 0);
		canvas_JetSize_cut->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetSize_cut.eps");

		//______________________________________________________________________
		// Jet Size Eta Phi All SPECTRUM

		//bckg_histJetPT->Scale(1/bckg_histJetPT->Integral());

		signal_histJetPT->Scale( signal_cross);
		//signal_histJetPT->Scale(1/signal_histJetPT->Integral());

		TCanvas *canvas_JetPT = new TCanvas("canvas_JetPT","title",2500,0,600,500);
		hist_same (canvas_JetPT, bckg_histJetPT, signal_histJetPT , "Cut 1 All Jet PT", "PT (GeV)", "Events", 0, 0);
		canvas_JetPT->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetPT.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetEta->Scale(1/bckg_histJetEta->Integral());

		signal_histJetEta->Scale( signal_cross);
		//signal_histJetEta->Scale(1/signal_histJetEta->Integral());

		TCanvas *canvas_JetEta = new TCanvas("canvas_JetEta","title",2500,0,600,500);
		hist_same (canvas_JetEta, bckg_histJetEta, signal_histJetEta , "Cut 1 All Jet Eta", "Eta (GeV)", "Events", 0, 0);
		canvas_JetEta->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetEta.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetPhi->Scale(1/bckg_histJetPhi->Integral());

		signal_histJetPhi->Scale( signal_cross);
		//signal_histJetPhi->Scale(1/signal_histJetPhi->Integral());

		TCanvas *canvas_JetPhi = new TCanvas("canvas_JetPhi","title",2500,0,600,500);
		hist_same (canvas_JetPhi, bckg_histJetPhi, signal_histJetPhi , "Cut 1 All Jet Phi", "Phi (GeV)", "Events", 0, 0);
		canvas_JetPhi->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetPhi.eps");

		//______________________________________________________________________
		// Jet PT 1, Eta 1, and Phi 1  SPECTRUM

		//bckg_histJetPT_1->Scale(1/bckg_histJetPT_1->Integral());

		signal_histJetPT_1->Scale( signal_cross);
		//signal_histJetPT_1->Scale(1/signal_histJetPT_1->Integral());

		TCanvas *canvas_JetPT_1 = new TCanvas("canvas_JetPT_1","title",2500,0,600,500);
		hist_same (canvas_JetPT_1, bckg_histJetPT_1, signal_histJetPT_1 , "Cut 1 Jet PT_1", "PT_1 (GeV)", "Events", 0, 0);
		canvas_JetPT_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetPT_1.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetEta_1->Scale(1/bckg_histJetEta_1->Integral());

		signal_histJetEta_1->Scale( signal_cross);
		//signal_histJetEta_1->Scale(1/signal_histJetEta_1->Integral());

		TCanvas *canvas_JetEta_1 = new TCanvas("canvas_JetEta_1","title",2500,0,600,500);
		hist_same (canvas_JetEta_1, bckg_histJetEta_1, signal_histJetEta_1 , "Cut 1 Jet Eta_1", "Eta_1 (GeV)", "Events", 0, 0);
		canvas_JetEta_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetEta_1.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetPhi_1->Scale(1/bckg_histJetPhi_1->Integral());

		signal_histJetPhi_1->Scale( signal_cross);
		//signal_histJetPhi_1->Scale(1/signal_histJetPhi_1->Integral());

		TCanvas *canvas_JetPhi_1 = new TCanvas("canvas_JetPhi_1","title",2500,0,600,500);
		hist_same (canvas_JetPhi_1, bckg_histJetPhi_1, signal_histJetPhi_1 , "Cut 1 Jet Phi_1", "Phi_1 (GeV)", "Events", 0, 0);
		canvas_JetPhi_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetPhi_1.eps");


		//______________________________________________________________________
		// Jet PT 2, Eta 2 and Phi 2 SPECTRUM

		//bckg_histJetPT_2->Scale(1/bckg_histJetPT_2->Integral());

		signal_histJetPT_2->Scale( signal_cross);
		//signal_histJetPT_2->Scale(1/signal_histJetPT_2->Integral());

		TCanvas *canvas_JetPT_2 = new TCanvas("canvas_JetPT_2","title",2500,0,600,500);
		hist_same (canvas_JetPT_2, bckg_histJetPT_2, signal_histJetPT_2 , "Cut 1 Jet PT_2", "PT_2 (GeV)", "Events", 0, 0);
		canvas_JetPT_2->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetPT_2.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetEta_2->Scale(1/bckg_histJetEta_2->Integral());

		signal_histJetEta_2->Scale( signal_cross);
		//signal_histJetEta_2->Scale(1/signal_histJetEta_2->Integral());

		TCanvas *canvas_JetEta_2 = new TCanvas("canvas_JetEta_2","title",2500,0,600,500);
		hist_same (canvas_JetEta_2, bckg_histJetEta_2, signal_histJetEta_2 , "Cut 1 Jet Eta_2", "Eta_2 (GeV)", "Events", 0, 0);
		canvas_JetEta_2->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetEta_2.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetPhi_2->Scale(1/bckg_histJetPhi_2->Integral());

		signal_histJetPhi_2->Scale( signal_cross);
		//signal_histJetPhi_2->Scale(1/signal_histJetPhi_2->Integral());

		TCanvas *canvas_JetPhi_2 = new TCanvas("canvas_JetPhi_2","title",2500,0,600,500);
		hist_same (canvas_JetPhi_2, bckg_histJetPhi_2, signal_histJetPhi_2 , "Cut 1 Jet Phi_2", "Phi_2 (GeV)", "Events", 0, 0);
		canvas_JetPhi_2->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetPhi_2.eps");

		//______________________________________________________________________
		// Jet Delta Eta, Delta Phi, DeltaR

		//bckg_histJetDeltaEta->Scale(1/bckg_histJetDeltaEta->Integral());

		signal_histJetDeltaEta->Scale( signal_cross);
		//signal_histJetDeltaEta->Scale(1/signal_histJetDeltaEta->Integral());

		TCanvas *canvas_JetDeltaEta = new TCanvas("canvas_JetDeltaEta","title",2500,0,600,500);
		hist_same (canvas_JetDeltaEta, bckg_histJetDeltaEta, signal_histJetDeltaEta , "Cut 1 Jet DeltaEta", "DeltaEta (GeV)", "Events", 0, 0);
		canvas_JetDeltaEta->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetDeltaEta.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetDeltaPhi->Scale(1/bckg_histJetDeltaPhi->Integral());

		signal_histJetDeltaPhi->Scale( signal_cross);
		//signal_histJetDeltaPhi->Scale(1/signal_histJetDeltaPhi->Integral());

		TCanvas *canvas_JetDeltaPhi = new TCanvas("canvas_JetDeltaPhi","title",2500,0,600,500);
		hist_same (canvas_JetDeltaPhi, bckg_histJetDeltaPhi, signal_histJetDeltaPhi , "Cut 1 Jet DeltaPhi", "DeltaPhi (GeV)", "Events", 0, 0);
		canvas_JetDeltaPhi->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetDeltaPhi.eps");

		//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetDeltaR->Scale(1/bckg_histJetDeltaR->Integral());

		signal_histJetDeltaR->Scale( signal_cross);
		//signal_histJetDeltaR->Scale(1/signal_histJetDeltaR->Integral());

		TCanvas *canvas_JetDeltaR = new TCanvas("canvas_JetDeltaR","title",2500,0,600,500);
		hist_same (canvas_JetDeltaR, bckg_histJetDeltaR, signal_histJetDeltaR , "Cut 1 Jet DeltaR", "DeltaR (GeV)", "Events", 0, 0);
		canvas_JetDeltaR->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetDeltaR.eps");

		//______________________________________________________________________
		// Jet Delta Eta, Delta Phi, DeltaR

		//bckg_histJetDeltaEta_1->Scale(1/bckg_histJetDeltaEta_1->Integral());

		signal_histJetDeltaEta_1->Scale( signal_cross);
		//signal_histJetDeltaEta_1->Scale(1/signal_histJetDeltaEta_1->Integral());

		TCanvas *canvas_JetDeltaEta_1 = new TCanvas("canvas_JetDeltaEta_1","title",2500,0,600,500);
		hist_same (canvas_JetDeltaEta_1, bckg_histJetDeltaEta_1, signal_histJetDeltaEta_1 , "Cut 1 Jet DeltaEta_1", "DeltaEta_1 (GeV)", "Events", 0, 0);
		canvas_JetDeltaEta_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetDeltaEta_1.eps");

//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetDeltaPhi_1->Scale(1/bckg_histJetDeltaPhi_1->Integral());

		signal_histJetDeltaPhi_1->Scale( signal_cross);
		//signal_histJetDeltaPhi_1->Scale(1/signal_histJetDeltaPhi_1->Integral());

		TCanvas *canvas_JetDeltaPhi_1 = new TCanvas("canvas_JetDeltaPhi_1","title",2500,0,600,500);
		hist_same (canvas_JetDeltaPhi_1, bckg_histJetDeltaPhi_1, signal_histJetDeltaPhi_1 , "Cut 1 Jet DeltaPhi_1", "DeltaPhi_1 (GeV)", "Events", 0, 0);
		canvas_JetDeltaPhi_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetDeltaPhi_1.eps");

		//--------------------------------------------------------------------------------------------------------------------------------------

		//bckg_histJetDeltaR_1->Scale(1/bckg_histJetDeltaR_1->Integral());

		signal_histJetDeltaR_1->Scale( signal_cross);
		//signal_histJetDeltaR_1->Scale(1/signal_histJetDeltaR_1->Integral());

		TCanvas *canvas_JetDeltaR_1 = new TCanvas("canvas_JetDeltaR_1","title",2500,0,600,500);
		hist_same (canvas_JetDeltaR_1, bckg_histJetDeltaR_1, signal_histJetDeltaR_1 , "Cut 1 Jet DeltaR_1", "DeltaR_1 (GeV)", "Events", 0, 0);
		canvas_JetDeltaR_1->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetDeltaR_1.eps");




		//______________________________________________________________________
		// JET MASS SPECTRUM

		//bckg_histJetMass->Scale(1/bckg_histJetMass->Integral());

		signal_histJetMass->Scale( signal_cross);
		//signal_histJetMass->Scale(1/signal_histJetMass->Integral());

		TCanvas *canvas_JetMass = new TCanvas("canvas_JetMass","title",2500,0,600,500);
		hist_same (canvas_JetMass, bckg_histJetMass, signal_histJetMass , "Cut 1 All Jet Mass", "Mass (GeV)", "Events", 0, 0.);
		canvas_JetMass->Print("plots_new_tfd/cut1_hadd/cut1_hadd_JetMass.eps");

		//______________________________________________________________________
		// Event HT

		//bckg_histHt->Scale(1/bckg_histHt->Integral());

		signal_histHt->Scale( signal_cross);
		//signal_histHt->Scale(1/signal_histHt->Integral());

		TCanvas *canvas_Ht = new TCanvas("canvas_Ht","title",2500,0,600,500);
		hist_same (canvas_Ht, bckg_histHt, signal_histHt , "Cut 1 Event HT", "HT (GeV)", "Events", 0, 0.);
		canvas_Ht->Print("plots_new_tfd/cut1_hadd/cut1_hadd_Ht.eps");

		//______________________________________________________________________
		// Event MET

		//bckg_histMet->Scale(1/bckg_histMet->Integral());

		signal_histMet->Scale( signal_cross);
		//signal_histMet->Scale(1/signal_histMet->Integral());

		TCanvas *canvas_Met = new TCanvas("canvas_Met","title",2500,0,600,500);
		hist_same (canvas_Met, bckg_histMet, signal_histMet , "Cut 1 Event MET", "MET (GeV)", "Events", 0, 0.);
		canvas_Met->Print("plots_new_tfd/cut1_hadd/cut1_hadd_Met.eps");

		//______________________________________________________________________
		// Event METEta

		//bckg_histMetEta->Scale(1/bckg_histMetEta->Integral());

		signal_histMetEta->Scale( signal_cross);
		//signal_histMetEta->Scale(1/signal_histMetEta->Integral());
		TCanvas *canvas_MetEta = new TCanvas("canvas_MetEta","title",2500,0,600,500);

		hist_same (canvas_MetEta, bckg_histMetEta, signal_histMetEta , "Cut 1 Event MET Eta", "Eta", "Events", 0, 0.);
		canvas_MetEta->Print("plots_new_tfd/cut1_hadd/cut1_hadd_MetEta.eps");

		//______________________________________________________________________
		// Muon Size SPECTRUM

		//bckg_histMuonSize->Scale(1/bckg_histMuonSize->Integral());

		signal_histMuonSize->Scale( signal_cross);
		//signal_histMuonSize->Scale(1/signal_histMuonSize->Integral());

		TCanvas *canvas_MuonSize = new TCanvas("canvas_MuonSize","title",2500,0,600,500);
		hist_same (canvas_MuonSize, bckg_histMuonSize, signal_histMuonSize , "Cut 1 Muon Size", "Size (GeV)", "Events", 0, 0);
		canvas_MuonSize->Print("plots_new_tfd/cut1_hadd/cut1_hadd_MuonSize.eps");

		//______________________________________________________________________
		// Electron Size SPECTRUM

		//bckg_histElectronSize->Scale(1/bckg_histElectronSize->Integral());

		signal_histElectronSize->Scale( signal_cross);
		//signal_histElectronSize->Scale(1/signal_histElectronSize->Integral());

		TCanvas *canvas_ElectronSize = new TCanvas("canvas_ElectronSize","title",2500,0,600,500);
		hist_same (canvas_ElectronSize, bckg_histElectronSize, signal_histElectronSize , "Cut 1 Electron Size", "Size (GeV)", "Events", 0, 0);
		canvas_ElectronSize->Print("plots_new_tfd/cut1_hadd/cut1_hadd_ElectronSize.eps");

		//______________________________________________________________________
		// Lepton Size SPECTRUM

		//bckg_histLeptonSize->Scale(1/bckg_histLeptonSize->Integral());

		signal_histLeptonSize->Scale( signal_cross);
		//signal_histLeptonSize->Scale(1/signal_histLeptonSize->Integral());

		TCanvas *canvas_LeptonSize = new TCanvas("canvas_LeptonSize","title",2500,0,600,500);
		hist_same (canvas_LeptonSize, bckg_histLeptonSize, signal_histLeptonSize , "Cut 1 Lepton Size", "Size (GeV)", "Events", 0, 0);
		canvas_LeptonSize->Print("plots_new_tfd/cut1_hadd/cut1_hadd_LeptonSize.eps");

}
