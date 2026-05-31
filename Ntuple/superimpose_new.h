#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>

#include <TSystem.h>
#include <TROOT.h>
#include <TRint.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1D.h>
#include <TH1D.h>
#include <TChain.h>
#include <TBranch.h>
#include <TEventList.h>
#include "TClonesArray.h"
#include <TFile.h>
#include <TH1F.h>
#include <TPad.h>
#include <TF1.h>
#include <TH2F.h>
#include "TLorentzVector.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TFrame.h"
#include "TCanvas.h"
#include "TAttMarker.h"
#include <TAttMarker.h>
//#include "TClone.h"
//#include "TROOT.h"
#include <TAttFill.h>
#include "TStyle.h"
#include "TColor.h"
#include "TF2.h"
#include "TExec.h"
#include "TCanvas.h"
#include <TAxis.h>
#include "TColor.h"
#include <TMath.h>
#include <TProfile.h>
#include "TStyle.h"
#include <TString.h>
#include "TLatex.h"
#include "TLegend.h"
#include "TVectorD.h"
#include "TGaxis.h"
//#include "TProfile2D.h."
#include "TLine.h"
#include <algorithm>
#include <time.h>
//#include <vector>
#include "TGraph.h"
#include <cmath>
#include <string>
#include <vector>

using namespace std;

void hist_same (TCanvas *canvas, TH1F *same_hist_1, TH1F *same_hist_2 , char *same_title, char *same_xaxis, char *same_yaxis, double same_ymin, double same_ymax)
{

  gPad->SetLogy();
  gPad->SetGrid();
  //same_hist_1->GetYaxis()->SetRangeUser(same_ymin,same_ymax);
  same_hist_1->Draw();
  same_hist_1->SetLineColor(kBlue);
  same_hist_1->SetFillStyle(3000);
	same_hist_1->SetFillColor(kBlue);

  same_hist_2->SetLineColor(kRed);
  same_hist_2->SetFillStyle(3004);
	same_hist_2->SetFillColor(kRed);
  //same_hist_2->SetMarkerColor(kRed);
  //same_hist_2->GetYaxis()->SetRangeUser(same_ymin,same_ymax);
  //same_hist_2->GetXaxis()->SetRangeUser(0,same_hist_2->FindLastBinAbove());
  //same_hist_2->GetXaxis()->SetRangeUser(0,1000);
  same_hist_2->Draw("same");
  same_hist_1->SetLineWidth(2);
  same_hist_2->SetLineWidth(2);
  //same_hist_1->SetStats(0);
  //same_hist_2->SetStats(0);
  same_hist_1->GetXaxis()->SetTitle(same_xaxis);
  same_hist_1->GetYaxis()->SetTitle(same_yaxis);
  //same_hist_1->GetXaxis()->SetTitleOffset(1.2);
  //same_hist_1->GetYaxis()->SetTitleOffset(1.22);
  canvas->BuildLegend(0.7,0.75,0.99,0.92);

//BuildLegend (Double_t x1=0.5, Double_t y1=0.67, Double_t x2=0.88, Double_t y2=0.88, const char *title="", Option_t *option="")
  same_hist_1->SetTitle(same_title);
  //canvas->SetLeftMargin(1.0);
  //canvas->SetRightMargin(2.2);


//  same_hist_1->SetMarkerStyle(24);
//  same_hist_1->SetMarkerSize(0.45);
//  same_hist_1->SetLineColor(kBlue);
//  same_hist_1->SetMarkerColor(kBlue);
//  same_hist_1->GetXaxis()->SetRangeUser(same_xmin,same_xmax);
// // same_hist_1->GetYaxis()->SetRangeUser(same_ymin,same_ymax);
//  same_hist_1->Draw();
//
//  same_hist_2->SetMarkerStyle(23);
//  same_hist_2->SetMarkerSize(0.45);
//  same_hist_2->SetLineColor(kRed);
//  same_hist_2->SetMarkerColor(kRed);
//  same_hist_2->GetXaxis()->SetRangeUser(same_xmin, same_xmax);
// // same_hist_2->GetYaxis()->SetRangeUser(y_min,y_max);
//  same_hist_2->GetXaxis()->SetTitle(same_xaxis);
//  same_hist_2->GetYaxis()->SetTitle(same_yaxis);
//  same_hist_2->SetTitle(same_title);
//  same_hist_2->Draw("same hist");

  //TH1F *div_same_hist_1_clone  = (TH1F*) div_same_hist_1->Clone("");
	//TH1F *div_same_hist_2_clone  = (TH1F*) div_same_hist_2->Clone("");

	//gPad->SetGrid();
	//gPad->SetLogy();
	//same_hist_1->SetStats(0);   // No statistics on upper plot
	//same_hist_1->SetFillStyle(3003);
	//same_hist_1->SetFillColor(kBlue+1);
  //same_hist_1->GetXaxis()->SetRangeUser(same_xmin,same_xmax);
	//same_hist_1->Draw("hist same E1");
	//same_hist_2->SetFillStyle(3003);
	//same_hist_2->SetFillColor(kRed);
  //same_hist_2->GetXaxis()->SetRangeUser(same_xmin,same_xmax);
	//same_hist_2->Draw("hist same E1");

}
