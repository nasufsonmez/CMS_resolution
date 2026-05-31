# CMS Jet Energy Resolution Study with MadGraph5, Delphes and ROOT

## Overview

This repository contains a complete simulation and analysis workflow developed for a study of jet energy resolution under various pileup conditions using a CMS-like detector parameterization.

The workflow includes:

- Event generation with MadGraph5_aMC@NLO
- Detector simulation with Delphes
- ROOT-based event analysis and ntuple production
- Resolution extraction studies
- Production of final plots and figures

The analysis was performed for multiple QCD transverse momentum ranges and several pileup scenarios.

---

## Physics Motivation

Jet energy resolution is one of the key performance quantities in hadron collider experiments. Detector effects, pileup interactions, and jet reconstruction algorithms all influence the ability to accurately reconstruct the energy of jets.

The purpose of this study is to investigate the dependence of jet energy resolution on:

- Jet transverse momentum
- Pileup conditions
- Detector response parameterizations

using a fast simulation framework based on MadGraph5 and Delphes.

---

## Workflow

### 1. Event Generation

QCD multijet events are generated using MadGraph5_aMC@NLO.

Relevant directories:

- QCD_Cards/
- QCD_run_cards/
- RunCard/
- proc_cards/

The generated samples cover several transverse momentum intervals.

---

### 2. Detector Simulation

Generated events are processed through Delphes using CMS detector cards configured for different pileup scenarios.

Relevant directories:

- Delphes/
- PosterScripts/

Pileup scenarios included:

- PU = 0
- PU = 5
- PU = 10
- PU = 15
- PU = 25
- PU = 50
- PU = 100
- PU = 200

---

### 3. ROOT Analysis and Ntuple Production

Detector-level events are analyzed using custom C++ and ROOT-based codes.

Relevant directory:

- Ntuple/

Main analysis tasks include:

- Event selection
- Ntuple creation
- Jet matching
- Resolution extraction
- Statistical studies

---

### 4. Result Production

Final analysis outputs are stored as ROOT files and are used to generate the final performance plots.

Relevant directories:

- AnalysisPosterOutputs/
- Tez_Eps_Files/

---

## QCD Transverse Momentum Bins

The study was performed for the following QCD transverse momentum ranges:

| Range (GeV) |
|------------|
| 100 – 250 |
| 250 – 500 |
| 500 – 1000 |
| 1000 – 2500 |
| 2500 – 4000 |
| 4000 – 6000 |
| > 6000 |

---

## Software Stack

The project uses:

- MadGraph5_aMC@NLO
- Delphes
- ExRootAnalysis
- ROOT
- C++
- Shell scripting

---

## Repository Structure

| Directory | Description |
|------------|------------|
| QCD_Cards/ | MadGraph card files |
| QCD_run_cards/ | Run cards for different momentum bins |
| Delphes/ | Delphes detector simulation framework |
| Ntuple/ | ROOT-based analysis codes |
| PosterScripts/ | Delphes cards and automation scripts |
| AnalysisPosterOutputs/ | Final analysis ROOT files |
| Tez_Eps_Files/ | Final figures and plots |
| ExRootAnalysis/ | Delphes ROOT analysis framework |

---

## Academic Context

This repository contains the simulation framework, detector studies, and analysis codes developed as part of a Bachelor's thesis project.

The work focuses on the study of jet energy resolution in CMS-like detector conditions using MadGraph5 event generation, Delphes detector simulation, and ROOT-based analysis. The repository preserves the complete workflow used in the thesis, including event generation, detector simulation, analysis, and final plot production.

Supervisor: Nasuf Sönmez

Institution: Ege Üniversitesi / Fizik Bölümü

---

## Disclaimer

This repository is intended for academic and educational purposes. It preserves the complete simulation and analysis chain used during the thesis study and may contain generated output files, intermediate analysis products, and software packages required to reproduce the results.
