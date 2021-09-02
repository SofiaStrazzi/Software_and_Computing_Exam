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

}
