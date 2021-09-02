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
  
  // I create a Tree for the higgs (sgn) events
  TTree* higgsTree;

  // I create a Tree for the higgs (sgn) events
  TTree* ttbarTree;

  // I get the trees for the signal and the background from the respective input files
  inputFile_higgs->GetObject("signalTree", higgsTree);
  inputFile_ttbar->GetObject("bkgTree", ttbarTree);
  
  // I add the signal and background trees to the loader
  loader.AddSignalTree(higgsTree, 1.0);
  loader.AddBackgroundTree(ttbarTree, 1.0);
  
  // Additional cuts in the case I need them 
  TCut sgn_cut = "";
  TCut bkg_cut = "";
  
  // I prepare the Trees for the training and the test
  loader.PrepareTrainingAndTestTree(sgn_cut, bkg_cut, "NTrain_Signal=0:NTrain_Background=0:NTest_Signal=0:NTest_Background=0");
  
  // I choose 4 different methods for my evaluation and book them:
  
  // Rectangular Cuts
  factory.BookMethod( &loader, TMVA::Types::kCuts, "Cuts", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart");
   
  // Fisher Discriminant
  factory.BookMethod( &loader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10");
   
  // MLPBNN
  factory.BookMethod( &loader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator");
    
  // Adaptive Boost (Boosted Decision Trees)
  factory.BookMethod( &loader, TMVA::Types::kBDT, "BDT","NTrees=200:BoostType=AdaBoost");

  
  
    

}
