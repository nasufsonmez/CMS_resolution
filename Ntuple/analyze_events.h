#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <time.h>

#include "ExRootAnalysis/ExRootTreeReader.h"
#include "DelphesClasses.h"
#include "Math/GenVector/VectorUtil.h"

using namespace std;

typedef struct
{
    //	double PVz;
    //	double PVx;
    //	double PVy;
    double HT;
    double MET;
    double METEta;
    double METPhi;
}EVENT_VAR;


typedef struct
{
    double PT;
    double Eta;
    double Phi;
    double Mass;
    double DeltaEta;
    double DeltaPhi;
    int Charge;
    int BTag;
    int TauTag;
//TRefArray Particles;
}JET;

typedef struct
{
    double PT;
    double Eta;
    double Phi;
    double E;
//TRefArray Particles;
}PHOTON;


typedef struct
{
    double PT;
    double Eta;
    double Phi;
    int Charge;
}MUON;


typedef struct
{
    double PT;
    double Eta;
    double Phi;
    int Charge;

}ELECTRON;

/*
typedef struct
{
    //	double PVz;
    //	double PVx;
    //	double PVy;
    double cross;
    double eff;
} SAMPLE;


typedef struct
{
    double	PT;
    double  Eta;
    double  Phi;
    int Charge;
    int ID;
    //double  Particle;
} LEPTON;
*/

/*

double lepton_invariant_mass(Muon *ptlep, MissingET *miss)
{
    double plx=(ptlep->PT)*cos(ptlep->Phi);
    double ply=(ptlep->PT)*sin(ptlep->Phi);
    double misspx=(miss->MET)*cos(miss->Phi);
    double misspy=(miss->MET)*sin(miss->Phi);

    double result=sqrt(2*(ptlep->PT)*(miss->MET)-2*(plx*misspx+ply*misspy ));
    return result;
}

double lepton_invariant_mass(Electron *ptlep, MissingET *miss)
{
    double plx=(ptlep->PT)*cos(ptlep->Phi);
    double ply=(ptlep->PT)*sin(ptlep->Phi);
    double misspx=(miss->MET)*cos(miss->Phi);
    double misspy=(miss->MET)*sin(miss->Phi);

    double result=sqrt(2*(ptlep->PT)*(miss->MET)-2*(plx*misspx+ply*misspy ));
    return result;
}
*/
double photon_invariant_mass(PHOTON photon1, PHOTON photon2)
{
	TLorentzVector photon_v1;
  TLorentzVector photon_v2;

	photon_v1.SetPtEtaPhiM(photon1.PT, photon1.Eta, photon1.Phi, 0.000);
  photon_v2.SetPtEtaPhiM(photon2.PT, photon2.Eta, photon2.Phi, 0.000);
	double photon_InvMass = (photon_v1 + photon_v2).M();

	return photon_InvMass;
}

//float DeltaR(float eta1,float phi1,float eta2,float phi2)
//{
//	float deltaPhi = TMath::Abs(phi1-phi2);
//	float deltaEta = eta1-eta2;
//	if(deltaPhi > TMath::Pi())
//	deltaPhi = TMath::TwoPi() - deltaPhi;
//	return TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
//}


/*double jet_invariant_mass(JET jet1, JET jet2)
{
	TLorentzVector jet_v1;
  TLorentzVector jet_v2;

	jet_v1.SetPtEtaPhiM(jet1.PT, jet1.Eta, jet1.Phi, jet1.Mass);
  jet_v2.SetPtEtaPhiM(jet2.PT, jet2.Eta, jet2.Phi, jet2.Mass);
	double jet_InvMass = (jet_v1 + jet_v2).M();

	return jet_InvMass;
}
*/
