
{
   #include "CMSTDRStyle.h"
   setTDRStyle();

    bool plot_ABC_PT       = true;

    // definitions ---------------------------------------------------------------------------------------------------------------------------------

   //  Float_t ptIntervals[]={60,100,150,250,500,800};
    Float_t ptIntervals[]={60,100,150,250,500,800,1100,1500,2000,2600,3300,4000,5000};
    Int_t ptBinArraySize = sizeof(ptIntervals)/sizeof(Float_t);

     Float_t pileUpIntervals[]={0,25,50,100};
    //Float_t pileUpIntervals[]={0,50};
    Int_t pileUpArraySize = sizeof(pileUpIntervals)/sizeof(Float_t);

    TFile * rootfile[8];

    char rootFileName[100];

    for ( int i = 0; i < pileUpArraySize; i++ )
    {
      sprintf(rootFileName,"Hadd_C_CombinedPileUp_%i.root",pileUpIntervals[i]);
      TFile * rootfile[i] = new TFile( rootFileName, "READ" );
    }


    char hist_name[100];
    char hist_name1[100];
    char hist_name2[100];
    char hist_name3[100];
    char hist_name4[100];
    char hist_name5[100];
    char hist_name6[100];

    char LegPileUp[100];


    char canvas_name[100];
    char canvas_name1[100];
    char canvas_name2[100];
    char canvas_name3[100];
    char canvas_name4[100];

    char hist_title[1000];

    char save[100];
    char save1[100];
    char save2[100];
    char save3[100];
    char save4[100];

    double sigma_values_forPT[pileUpArraySize][2][ptBinArraySize-1];
    double sigma_error_values_forPT[pileUpArraySize][2][ptBinArraySize-1];

    double mean_values_forPT[pileUpArraySize][2][ptBinArraySize-1];
    double mean_error_values_forPT[pileUpArraySize][2][ptBinArraySize-1];

    double noiseCoeff[pileUpArraySize][2];
    double stoCoeff[pileUpArraySize][2];
    double constant[pileUpArraySize][2];

    // Gauss fit functions for Eta Resolution histograms ----------------------------------------------------------------------------------------

    TF1 *fitting = new TF1("fitting","gaus",0.95,1.1);
    fitting->SetLineColor(kRed);
    fitting->SetLineWidth(3);
    TF1 *fitFuncForSigma = new TF1( "fitFuncForSigma", "([0]/sqrt(x))+([1]/x)+[2]", 0.0, 10000.0);
   //  TF1 *fitFuncForSigma = new TF1( "fitFuncForSigma", "sqrt((([0]/x)*([0]/x))+([1]*[1]/x)+[2]*[2])",0.0,3000.0);
    fitFuncForSigma->SetLineWidth(3);
   //  fitFuncForSigma->SetParameter(2, 0.01);
    fitFuncForSigma->SetParName(0,"N");
    fitFuncForSigma->SetParName(1,"S");
    fitFuncForSigma->SetParName(2,"C");
   //  fitFuncForSigma->SetParName(3,"m");

    //  Histograms for sigma from PT bins -----------------------------------------------------------------------------------------------------------------------------

    double histMean;
    double histRms;

    gStyle->SetOptTitle(1);
    gStyle->SetOptFit(1111);
    gStyle->SetOptStat(0);


    TH1F *histo_sigma_from_PTbins[pileUpArraySize][2];
    TH1F *hist_sigma_PTBin[pileUpArraySize][2];
    TH1F *hist_mean_PTBin[pileUpArraySize][2];
    TH1F *hist_SigmaOvermMean_PTBin[pileUpArraySize][2];

   if ( plot_ABC_PT )
   {
      for (int j = 0; j < pileUpArraySize; j++ )
      {

         for (int k = 0; k < 2; k++ )
         {

            for ( int a = 0; a < ptBinArraySize-1; a++ )
            {
               sprintf(hist_name,"JetRelativePtResolutionPTBins_%i/pt_Reso_PT%ito%i_%i",k+1,ptIntervals[a],ptIntervals[a+1],k+1);
               sprintf(hist_title,"JetRelativePtResolutionPTBins/Relative Jet Pt Reso %i<Pt<%i Pile Up %i JetAlgo %i",ptIntervals[a],ptIntervals[a+1],pileUpIntervals[j],k+1);
               sprintf(save,"Tez_Eps_Files/Sigma_vs_PT_PileUp_%i/pt_Reso_PT%ito%i_PU%i_JetAlgo%i.eps",pileUpIntervals[j],ptIntervals[a],ptIntervals[a+1],pileUpIntervals[j],k+1);
               sprintf(canvas_name,"Pt Reso PT %i to %i PU %i JetAlgo %i",ptIntervals[a],ptIntervals[a+1],pileUpIntervals[j],k+1);

               histo_sigma_from_PTbins[j][k] = (TH1F*)rootfile[j]->Get(hist_name);

               TCanvas *canvas_PT_ResolutionNEW = new TCanvas(canvas_name,"",0,0,600,600);
               canvas_PT_ResolutionNEW->cd();
               //   gPad->SetGrid();
               //   gStyle->SetOptFit(1111);
               //   gStyle->SetOptStat(1111111);
               // gStyle->SetOptTitle(1);
               histMean = histo_sigma_from_PTbins[j][k]->GetMean();
               histRms = histo_sigma_from_PTbins[j][k]->GetRMS();
               histo_sigma_from_PTbins[j][k]->SetFillColor(kYellow);
               histo_sigma_from_PTbins[j][k]->GetXaxis()->SetTitle("Response");
               histo_sigma_from_PTbins[j][k]->GetYaxis()->SetTitle("Events");
               histo_sigma_from_PTbins[j][k]->GetXaxis()->SetTitleSize(0.045);
               histo_sigma_from_PTbins[j][k]->GetYaxis()->SetTitleSize(0.045);
               histo_sigma_from_PTbins[j][k]->GetYaxis()->SetTitleFont(62);
               histo_sigma_from_PTbins[j][k]->GetXaxis()->SetTitleFont(62);
               histo_sigma_from_PTbins[j][k]->GetYaxis()->SetTitleOffset(1.4);
               histo_sigma_from_PTbins[j][k]->GetXaxis()->SetTitleOffset(1.2);
               histo_sigma_from_PTbins[j][k]->Fit("fitting","","",histMean - histRms, histMean + histRms);
               histo_sigma_from_PTbins[j][k]->Draw();
               sigma_values_forPT[j][k][a] = fitting->GetParameter(2);
               mean_values_forPT[j][k][a] = fitting->GetParameter(1);
               sigma_error_values_forPT[j][k][a] = fitting->GetParError(2);
               mean_error_values_forPT[j][k][a] = fitting->GetParError(1);
               canvas_PT_ResolutionNEW->Print(save);
               canvas_PT_ResolutionNEW->Close();
            }

            sprintf(hist_name1,"sigma_From_PtReso PU %i JetAlgo %i",pileUpIntervals[j],k+1);
            sprintf(hist_name2,"mean_From_PtReso PU %i JetAlgo %i",pileUpIntervals[j],k+1);
            sprintf(hist_name3,"sigmaOverMean_From_PtReso PU %i JetAlgo %i",pileUpIntervals[j],k+1);
            hist_sigma_PTBin[j][k] = new TH1F(hist_name1,"sigma vs PT",ptBinArraySize-1,ptIntervals);
            hist_mean_PTBin[j][k] = new TH1F(hist_name2,"mean vs PT",ptBinArraySize-1,ptIntervals);
            hist_SigmaOvermMean_PTBin[j][k] = new TH1F(hist_name3,"sigmaOverMean vs PT",ptBinArraySize-1,ptIntervals);

            gStyle->SetOptTitle(0);
            sprintf(canvas_name1,"Sigma Plot PU %i JetAlgo %i",pileUpIntervals[j],k+1);
            TCanvas *canvas_Sigma_fromPT = new TCanvas(canvas_name1,"",0,0,600,600);
            canvas_Sigma_fromPT->cd();
            // gPad->SetGrid();
            // gStyle->SetOptFit(1111);
            // gStyle->SetOptStat(1111111);
            for ( int i = 0; i < ptBinArraySize-1; i++)
            {
               // if ( ( a == 2 ) && ( i > 9) ) continue;
               // if ( ( a == 3 ) && ( i > 7) ) continue;
               // if ( ( a == 4 ) && ( i > 5) ) continue;
               //   hist_sigma_PTBin[j][k]->SetBinContent( i+1, sigma_values_forPT[i]/((ptIntervals[i] + ptIntervals[i+1])/2) );
               //   hist_sigma_PTBin[j][k]->SetBinError( i+1, sigma_error_values_forPT[i]/((ptIntervals[i] + ptIntervals[i+1])/2) );
               hist_sigma_PTBin[j][k]->SetBinContent( i+1, sigma_values_forPT[j][k][i] );
               //   hist_sigma_PTBin[j][k]->SetBinError( i+1, sigma_error_values_forPT[i] );
            }
            hist_sigma_PTBin[j][k]->SetMinimum(0);
            //  hist_sigma_PTBin[j][k]->SetMaximum(0.0002);
            hist_sigma_PTBin[j][k]->SetMaximum(0.2);
            hist_sigma_PTBin[j][k]->GetXaxis()->SetTitle("P_{T} (GeV)");
            hist_sigma_PTBin[j][k]->GetYaxis()->SetTitle("#sigma");
            hist_sigma_PTBin[j][k]->GetXaxis()->SetTitleSize(0.045);
            hist_sigma_PTBin[j][k]->GetYaxis()->SetTitleSize(0.045);
            hist_sigma_PTBin[j][k]->GetYaxis()->SetTitleFont(62);
            hist_sigma_PTBin[j][k]->GetXaxis()->SetTitleFont(62);
            hist_sigma_PTBin[j][k]->GetYaxis()->SetTitleOffset(1.4);
            hist_sigma_PTBin[j][k]->GetXaxis()->SetTitleOffset(1.2);
            hist_sigma_PTBin[j][k]->Fit(fitFuncForSigma);
            // if ( a < 2 )      hist_sigma_PTBin[j][k]->Fit(fitFuncForSigma,"","",0,5000);
            // if ( a == 2 )     hist_sigma_PTBin[j][k]->Fit(fitFuncForSigma,"","",0,3300);
            // if ( a == 3 )     hist_sigma_PTBin[j][k]->Fit(fitFuncForSigma,"","",0,2000);
            // if ( a == 4 )     hist_sigma_PTBin[j][k]->Fit(fitFuncForSigma,"","",0,600);
            hist_sigma_PTBin[j][k]->Draw();
            sprintf(save1,"Tez_Eps_Files/Sigma_vs_PT_PileUp_%i/SigmaVsPt_PU%i_JetAlgo%i.eps",pileUpIntervals[j],pileUpIntervals[j],k+1);
            canvas_Sigma_fromPT->Print(save1);
            canvas_Sigma_fromPT->Close();

            sprintf(canvas_name2,"Mean Plot PU %i JetAlgo %i",pileUpIntervals[j],k+1);
            TCanvas *canvas_Mean_fromPT = new TCanvas(canvas_name2,"",0,0,600,600);
            canvas_Mean_fromPT->cd();
            // gPad->SetGrid();
            // gStyle->SetOptFit(1111);
            // gStyle->SetOptStat(1111111);
            for ( int i = 0; i < ptBinArraySize-1; i++)
            {
               //   hist_mean_PTBin[j][k]->SetBinContent( i+1, mean_values_forPT[i]/((ptIntervals[i] + ptIntervals[i+1])/2) );
               //   hist_mean_PTBin[j][k]->SetBinError( i+1, mean_error_values_forPT[i]/((ptIntervals[i] + ptIntervals[i+1])/2) );
               hist_mean_PTBin[j][k]->SetBinContent( i+1, mean_values_forPT[j][k][i] );
               //   hist_mean_PTBin[j][k]->SetBinError( i+1, mean_error_values_forPT[i]);
            }
            hist_mean_PTBin[j][k]->SetMinimum(0);
            //  hist_mean_PTBin[j][k]->SetMaximum(0.0002);
            hist_mean_PTBin[j][k]->SetMaximum(1.5);
            hist_mean_PTBin[j][k]->GetXaxis()->SetTitle("P_{T} (GeV)");
            hist_mean_PTBin[j][k]->GetYaxis()->SetTitle("#mu");
            hist_mean_PTBin[j][k]->GetXaxis()->SetTitleSize(0.045);
            hist_mean_PTBin[j][k]->GetYaxis()->SetTitleSize(0.045);
            hist_mean_PTBin[j][k]->GetYaxis()->SetTitleFont(62);
            hist_mean_PTBin[j][k]->GetXaxis()->SetTitleFont(62);
            hist_mean_PTBin[j][k]->GetYaxis()->SetTitleOffset(1.1);
            hist_mean_PTBin[j][k]->GetXaxis()->SetTitleOffset(1.2);
            hist_mean_PTBin[j][k]->Fit(fitFuncForSigma);
            hist_mean_PTBin[j][k]->Draw();
            sprintf(save2,"Tez_Eps_Files/Sigma_vs_PT_PileUp_%i/MeanVsPt_PU%i_JetAlgo%i.eps",pileUpIntervals[j],pileUpIntervals[j],k+1);
            canvas_Mean_fromPT->Print(save2);
            canvas_Mean_fromPT->Close();


            sprintf(canvas_name3,"SigmaOverMean Plot PU %i JetAlgo %i",pileUpIntervals[j],k+1);
            TCanvas *canvas_SigmaOverMean_fromPT = new TCanvas(canvas_name3,"",0,0,600,600);
            canvas_SigmaOverMean_fromPT->cd();
            // gPad->SetGrid();
            // gStyle->SetOptFit(1111);
            // gStyle->SetOptStat(1111111);
		gPad->SetLogx();
            for ( int i = 0; i < ptBinArraySize-1; i++)
            {
               //   if ( ( a == 4 ) && ( i > 4 ) ) continue;
               //   if ( ( a == 4 ) && ( i == 0) ) continue;
               //   hist_SigmaOvermMean_PTBin[j][k]->SetBinContent( i+1, sigma_values_forPT[i]/((ptIntervals[i] + ptIntervals[i+1])/2) );
               //   hist_SigmaOvermMean_PTBin[j][k]->SetBinError( i+1, sigma_error_values_forPT[i]/((ptIntervals[i] + ptIntervals[i+1])/2) );
               hist_SigmaOvermMean_PTBin[j][k]->SetBinContent( i+1, sigma_values_forPT[j][k][i]/mean_values_forPT[j][k][i]);
               //   hist_SigmaOvermMean_PTBin[j][k]->SetBinError( i+1, sigma_error_values_forPT[a]/mean_error_values_forPT[i] );
            }
            hist_SigmaOvermMean_PTBin[j][k]->SetMinimum(0);
            //  hist_SigmaOvermMean_PTBin[j][k]->SetMaximum(0.0002);
            hist_SigmaOvermMean_PTBin[j][k]->SetMaximum(0.2);
            hist_SigmaOvermMean_PTBin[j][k]->GetXaxis()->SetTitle("P_{T} (GeV)");
            hist_SigmaOvermMean_PTBin[j][k]->GetYaxis()->SetTitle("#sigma / P_{T}");
            hist_SigmaOvermMean_PTBin[j][k]->GetXaxis()->SetTitleSize(0.045);
            hist_SigmaOvermMean_PTBin[j][k]->GetYaxis()->SetTitleSize(0.045);
            hist_SigmaOvermMean_PTBin[j][k]->GetYaxis()->SetTitleFont(62);
            hist_SigmaOvermMean_PTBin[j][k]->GetXaxis()->SetTitleFont(62);
            hist_SigmaOvermMean_PTBin[j][k]->GetYaxis()->SetTitleOffset(1.4);
            hist_SigmaOvermMean_PTBin[j][k]->GetXaxis()->SetTitleOffset(1.2);
            hist_SigmaOvermMean_PTBin[j][k]->SetMarkerStyle(20);
            hist_SigmaOvermMean_PTBin[j][k]->Fit(fitFuncForSigma,"R","");
            hist_SigmaOvermMean_PTBin[j][k]->GetFunction("fitFuncForSigma")->SetLineColor(j+2);
            noiseCoeff[j][k] = fitFuncForSigma->GetParameter(0);
            stoCoeff[j][k] = fitFuncForSigma->GetParameter(1);
            constant[j][k] = fitFuncForSigma->GetParameter(2);
            hist_SigmaOvermMean_PTBin[j][k]->Draw();
            sprintf(save3,"Tez_Eps_Files/Sigma_vs_PT_PileUp_%i/SigmaOverMeanVsPt_PU%i_JetAlgo%i.eps",pileUpIntervals[j],pileUpIntervals[j],k+1);
            canvas_SigmaOverMean_fromPT->Print(save3);
            canvas_SigmaOverMean_fromPT->Close();

         }
      }


      gStyle->SetOptTitle(1);

      TCanvas *canvas_SJA_DPU;
      for ( int k = 0; k < 2; k++ )
      {
         sprintf(canvas_name4,"Jet Energy Resolutions with PileUps (Jet Algo %i)",k+1);
         sprintf(save4,"Tez_Eps_Files/SameJetAlgo_%i_DiffPileUp.eps",k+1);
         canvas_SJA_DPU = new TCanvas(canvas_name4,"Jet Energy Resolutions",0,0,600,600);
         canvas_SJA_DPU->cd();
         // leg->SetHeader("Pile Up Values","C");
         TLegend* leg = new TLegend(0.65,0.65,0.85,0.85);
         leg->AddEntry(hist_SigmaOvermMean_PTBin[0][k]->GetFunction("fitFuncForSigma"),"Pile Up 0","l");
         hist_SigmaOvermMean_PTBin[0][k]->SetTitle("Jet Energy Resolutions");
         hist_SigmaOvermMean_PTBin[0][k]->GetXaxis()->SetRangeUser(0,4000);
         hist_SigmaOvermMean_PTBin[0][k]->Draw();
         gPad->SetLogx();
         for ( int j = 1; j < pileUpArraySize; j++ )
         {
            sprintf(LegPileUp,"Pile Up %i",pileUpIntervals[j]);
            leg->AddEntry(hist_SigmaOvermMean_PTBin[j][k]->GetFunction("fitFuncForSigma"),LegPileUp,"l");
            // hist_SigmaOvermMean_PTBin[j][k]->SetTitle("Jet Energy Resolutions");
            hist_SigmaOvermMean_PTBin[j][k]->Draw("SAME");
         }
         leg->Draw();
         canvas_SJA_DPU->Print(save4);
         canvas_SJA_DPU->Close();
      }

      TH1F *hist_Noise[3];
      TH1F *hist_Stoch[3];
      TH1F *hist_Constant[3];

      for (int k=0; k<2; k++)
      {
         sprintf(hist_name4,"Noise Difference with Pile Up JetAlgo %i",k+1);
         hist_Noise[k] = new TH1F(hist_name4,"Noise Difference With Pile Up values",pileUpArraySize-1,pileUpIntervals);
         for ( int j = 0; j < pileUpArraySize; j++)
         {
            hist_Noise[k]->SetBinContent( j+1, noiseCoeff[j][k]);
         }
      }
      TCanvas *canvas_Noise = new TCanvas("Noise","",0,0,600,600);
      canvas_Noise->cd();
      hist_Noise[0]->Draw();
      hist_Noise[0]->GetYaxis()->SetRangeUser(-0.5,0.5);
      hist_Noise[1]->Draw("SAME");
      canvas_Noise->Print("Tez_Eps_Files/Noise.eps");
      canvas_Noise->Close();

      for (int k=0; k<2; k++)
      {
         sprintf(hist_name5,"Stochastic Difference with Pile Up JetAlgo %i",k+1);
         hist_Stoch[k] = new TH1F(hist_name5,"Stochastic Difference With Pile Up values",pileUpArraySize-1,pileUpIntervals);
         for ( int j = 0; j < pileUpArraySize; j++)
         {
            hist_Stoch[k]->SetBinContent( j+1, stoCoeff[j][k]);
         }
      }
      TCanvas *canvas_Stochastic = new TCanvas("Stochastic","",0,0,600,600);
      canvas_Stochastic->cd();
      hist_Stoch[0]->Draw();
      // hist_Stoch[0]->GetYaxis()->SetRangeUser(-0.5,0.5);
      hist_Stoch[1]->Draw("SAME");
      canvas_Stochastic->Print("Tez_Eps_Files/Stochastic.eps");
      canvas_Stochastic->Close();


      for (int k=0; k<2; k++)
      {
         sprintf(hist_name6,"Constant Difference with Pile Up JetAlgo %i",k+1);
         hist_Constant[k] = new TH1F(hist_name6,"Constant Difference With Pile Up values",pileUpArraySize-1,pileUpIntervals);
         for ( int j = 0; j < pileUpArraySize; j++)
         {
            hist_Constant[k]->SetBinContent( j+1, constant[j][k]);
         }
      }
      TCanvas *canvas_Constant = new TCanvas("Constant","",0,0,600,600);
      canvas_Constant->cd();
      hist_Constant[0]->Draw();
      // hist_Constant[0]->GetYaxis()->SetRangeUser(-0.5,0.5);
      hist_Constant[1]->Draw("SAME");
      canvas_Constant->Print("Tez_Eps_Files/Constant.eps");
      canvas_Constant->Close();


   }

   //  JET_Size Plots-----------------------------------------------------------------------------------

//    TH1F * histJetSize = (TH1F*)rootfile_PU_50->Get("JetSizePlots/Jet_Size");
//    TCanvas *canvas_JetSize = new TCanvas("JetSize", "Jet Dağılımı",0,0,600,600);
//    canvas_JetSize->cd();
//    // gPad->SetLogy();
//    gStyle->SetOptStat(1111);
//
//    histJetSize->GetXaxis()->SetTitle("Jet Sayisi");
//    histJetSize->GetYaxis()->SetTitle("Olay Sayisi");
//    histJetSize->GetYaxis()->SetTitleOffset(1.1);
//    histJetSize->GetYaxis()->SetTitleFont(42);
//    histJetSize->GetXaxis()->SetTitleSize(0.06);
//    histJetSize->GetYaxis()->SetTitleSize(0.06);
//    histJetSize->SetFillColor(kBlue-7);
//    histJetSize->Draw();
//    canvas_JetSize->Print("Tez_Eps_Files/JetSize.eps");
//    canvas_JetSize->Close();
//
//
//    TH1F * histJetPtDist = (TH1F*)rootfile_PU_50->Get("JetPtDistribution/calojetpt");
//    TCanvas *canvas_PtDist = new TCanvas("JetPtDist", "Jet Pt Dağılımı",0,0,600,600);
//    canvas_PtDist->cd();
//    gPad->SetLogy();
//    histJetPtDist->GetXaxis()->SetTitle("P_{T} (GeV)");
//    histJetPtDist->GetYaxis()->SetTitle("Olay Sayisi");
//    histJetPtDist->GetYaxis()->SetTitleOffset(1.1);
//    histJetPtDist->GetYaxis()->SetTitleFont(42);
//    histJetPtDist->GetXaxis()->SetTitleSize(0.06);
//    histJetPtDist->GetYaxis()->SetTitleSize(0.06);
//    histJetPtDist->SetFillColor(kBlue-7);
//    histJetPtDist->Draw();
//    canvas_PtDist->Print("Tez_Eps_Files/JetPtDagilimi.eps");
//    canvas_PtDist->Close();
//
}

