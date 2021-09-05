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
