/* 
This macro compares the performances of 4 different machine learning methods:
    - Cut optimisation (CutsGA)
    - Linear Discriminant Analysis (Fisher discriminant)
    - Neural Networks MLPBNN (feed-forward Multilayer Perceptrons
    - Boosted Decision Trees (Adaptive Boost) 
The macro creates an output .root file with the results and shows the ROC curve for the user
*/


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

using namespace std;

void MLtmva() {
  
  //I ask the user if he wants to use the whole dataset or just a part of the events
  int answer=0;
  
  cout << "\nPress 1 to use the whole datasamples (the analysis can take many time) or 2 to use just 10000 events for each datasample\t";
  cin >> answer;

  // I put a control on the answer of the user
  while (answer != 1 && answer !=2)
    {
    cout << "\nERROR: You have to press 1 or 2" << endl;
    cout << "Press 1 to use the whole datasamples (the analysis can take many time) or 2 to use just 10000 events for each datasample\t";
    cin >> answer;
    }

  TFile *inputFile_higgs, *inputFile_ttbar;
    
  // I open and assign a name to the input .root files on the base of the decision of the user
  if (answer == 1)
    {
    inputFile_higgs = TFile::Open("./trees/higgsevents.root");
    inputFile_ttbar = TFile::Open("./trees/ttbarevents.root");
    }
  
  else
    {
    inputFile_higgs = TFile::Open("./reducedtrees/reduced_higgsevents.root");
    inputFile_ttbar = TFile::Open("./reducedtrees/reduced_ttbarevents.root");
    }

  
  // I create an output file in which I can put the output of the TMVA
  TString outfileName("OutputTMVA_higgs.root");
  TFile* TMVAoutput_higgs = TFile::Open(outfileName, "RECREATE");
  
  // I create a factory TMVAClassification
  TMVA::Factory factory("TMVAClassification", TMVAoutput_higgs, "!V:ROC:!Correlations:!Silent:Color:!DrawProgressBar:AnalysisType=Classification");
  
  // I add all the variables to the loader
  TMVA::DataLoader loader("trainingevents");
  
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
  inputFile_higgs->GetObject("EventsTree", higgsTree);
  inputFile_ttbar->GetObject("EventsTree", ttbarTree);
  
  // I add the signal and background trees to the loader
  loader.AddSignalTree(higgsTree, 1.0);
  loader.AddBackgroundTree(ttbarTree, 1.0);
  
  // Additional cuts in the case I need them 
  TCut sgn_cut = "";
  TCut bkg_cut = "";
  
  // I prepare the Trees for the training and the test
  loader.PrepareTrainingAndTestTree(sgn_cut, bkg_cut, "NTrain_Signal=0:NTrain_Background=0:NTest_Signal=0:NTest_Background=0");
  
  
  // I choose 4 different methods for my evaluation and book them:
  
  // Cut optimisation (CutsGA)
  factory.BookMethod( &loader, TMVA::Types::kCuts, "CutsGA", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart");
   
  // Linear Discriminant Analysis (Fisher discriminant)
  factory.BookMethod( &loader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10");
   
  // Neural Networks MLPBNN (feed-forward Multilayer Perceptrons)
  factory.BookMethod( &loader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator");
    
  // Boosted Decision Trees (Adaptive Boost)
  factory.BookMethod( &loader, TMVA::Types::kBDT, "BDT","NTrees=200:BoostType=AdaBoost");
  
  
  // Now I give to the factory the commands to train all the MVAs and then for the test and evaluation
  
  // I train MVAs. I use the training tree that I create before.
  factory.TrainAllMethods();

  // I Evaluate all MVAs. I use the Tree that I prepared before with the test events
  factory.TestAllMethods();
  
  // I Have an evaluation of the different methods and see a comparison of the performances
  factory.EvaluateAllMethods();
  
  
  // I close the output file to save the evaluations given by TMVA
  TMVAoutput_higgs -> Close();
  
  // I inform the user that TMVA finished the evaluation and the results are written in the output file
  cout << "\n\n\n\nMLtmva MACRO FINISHED THE EVALUATION OF THE METHODS FOR THE INSERTED SIGNAL AND BACKGROUND DATASAMPLES.\n" << endl;
  cout << "\nThe output of the TMVA evaluation is written in the file: " << outfileName << endl;
  
  
  //I ask the user if he wants to see the ROC curve
  char ROCanswer;
  
  cout << "\nDo you want to see the ROC curve with all the methods? (y/n) \t";
  cin >> ROCanswer;
  
  if (ROCanswer == 'y')
  {
    // I plot the ROC curve
    auto canvas = factory.GetROCCurve (&loader);
    canvas -> Draw( "AL" );
  }
  
  // Launch the GUI for the root macros
  if (!gROOT->IsBatch()) TMVA::TMVAGui(outfileName);

  cout << "\n\nNow looking at the output file and at the ROC curve you can decide which method is the best one for the analysis that you want to do." << endl;
  cout << "THEN TO RUN THE MACRO THAT ANALYZES THE DATA, GIVE TO THE TERMINAL (inside root) THE COMMAND:" << endl << endl
          << ".x MLtmva_analysis.C" << endl;

   return 0;
  
  
}
