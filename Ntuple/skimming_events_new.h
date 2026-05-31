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
//TRefArray Particles;
}JET;
