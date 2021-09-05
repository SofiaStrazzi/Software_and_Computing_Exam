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
   int_t method;

   cout << "\n\nPRESS 1, 2, 3 OR 4 TO SELECT THE METHOD THAT YOU WANT TO USE TO ANALYZE THE DATA:" << endl << endl;

   cout << "Press 1, 2, 3 or 4:" << endl;

   cout << "1 Cut optimisation (CutsGA)" << endl
   		<< "2 Linear Discriminant Analysis (Fisher discriminant)" << endl
   		<< "3 Neural Networks MLPBNN (feed-forward Multilayer Perceptrons" << endl
   		<< "4 Boosted Decision Trees (Adaptive Boost) " << endl;

   cin >> method;
