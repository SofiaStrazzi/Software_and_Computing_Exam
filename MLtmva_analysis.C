 // This macro analyse the data with the method chosen by the user
   // Cut optimisation (CutsGA)
   // Linear Discriminant Analysis (Fisher discriminant)
   // Neural Networks MLPBNN (feed-forward Multilayer Perceptrons
   // Boosted Decision Trees (Adaptive Boost) 


#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
 
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
 
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
 
using namespace TMVA;
using namespace std;
 
void MLtmva_analysis()
{
   // Library loading
   TMVA::Tools::Instance();
 
   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;
 

   // I ask to the user to select the chosen method to analyse the data
   int_t method = 0;

   cout << "\n\nPRESS 1, 2, 3 OR 4 TO SELECT THE METHOD THAT YOU WANT TO USE TO ANALYZE THE DATA:" << endl << endl;

   cout << "Press 1, 2, 3 or 4:" << endl;

   cout << "1 Cut optimisation (CutsGA)" << endl
   		<< "2 Linear Discriminant Analysis (Fisher discriminant)" << endl
   		<< "3 Neural Networks MLPBNN (feed-forward Multilayer Perceptrons" << endl
   		<< "4 Boosted Decision Trees (Adaptive Boost) " << endl;

   cin >> method;
 
   // I put a control on the answer of the user
   while (method != 1 && method != 2 && method != 3 && method != 4
     {
     cout << "\n\nPRESS 1, 2, 3 OR 4 TO SELECT THE METHOD THAT YOU WANT TO USE TO ANALYZE THE DATA:" << endl << endl;

     cout << "Press 1, 2, 3 or 4:" << endl;

     cout << "1 Cut optimisation (CutsGA)" << endl
   		  << "2 Linear Discriminant Analysis (Fisher discriminant)" << endl
   	  	<< "3 Neural Networks MLPBNN (feed-forward Multilayer Perceptrons" << endl
   		  << "4 Boosted Decision Trees (Adaptive Boost) " << endl;

     cin >> method;
     }
 
 
    //I ask the user if he wants to use the whole dataset or just a part of the events
   int answer=0;
  
   cout << "\nPress 1 to use the whole datasample (the analysis can take many time) 
           or 2 to analyze just 10000 events\t";
   cin >> answer;

   // I put a control on the answer of the user
   while (answer != 1 && answer !=2)
     {
     cout << "\nERROR: You have to press 1 or 2" << endl;
   	 cout << "\nPress 1 to use the whole datasample (the analysis can take many time) 
           or 2 to analyze just 10000 events\t";
     cin >> answer;
     }

   // I prepare the input tree
   TFile *input(0);

   // I open and assign a name to the input .root file with the data I want to analyze on the base of the decision of the user
   if (answer == 1)
     TString fname = "./trees/dataevents.root";
  
   else
     TString fname = "./reducedtrees/reduced_dataevents.root";


   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }

   if (!input) {
      cout << "ERROR: could not open data file" endl;
      exit(1);
   }
   
   cout << "\nAnalysing data in the file: " << input->GetName() << endl;
