#include <iostream>
#include <string>
#include <cstdlib>
#include <map>

#include "TMVA/TMVAGui.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TChain.h"

void MLtmva() {
  
  // I open and assign a name to the input .root files
  auto inputfile_higgs = TFile::Open("higgsevents.root");
  auto inputFile_ttbar = TFile::Open("ttbarevents.root");
  
  // I create an output file in which I can put the output of the TMVA
  TString outfileName( "OutputTMVA_higgs.root" );
  TFile* outputFile = TFile::Open(outfileName, "RECREATE");
  
  // I create a factory TMVAClassification
  TMVA::Factory factory("TMVAClassification", outputFile, "!V:ROC:!Correlations:!Silent:Color:!DrawProgressBar:AnalysisType=Classification");
  
  // I add all the variables to the loader
  TMVA::DataLoader loader("dataevents");
  
  loader.AddVariable("EventNumber");
  loader.AddVariable("MET");
  loader.AddVariable("jet_pT");
  loader.AddVariable("jet_eta");
  loader.AddVariable("jet_phi");
  loader.AddVariable("jet_m");
  loader.AddVariable("jet_isB");
    

}
