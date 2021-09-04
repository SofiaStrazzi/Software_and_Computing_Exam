// In this macro are present different function to copy just some leaves that I need from the original trees 
// and which reduce the number of total events in each tree in order to make the program faster for the trials

#include <ROOT/RDataFrame.hxx>

    //using namespace ROOT::Experimental;

// Functions that copy just the leaves that I intend to use for my analysis in a new .root files with a smaller dimension, but the same number of events


int copyleaveshiggs() {
  ROOT::RDataFrame df("Delphes", "higgs.root");
  df.Snapshot("EventsTree", "higgsevents.root", {"EventNumber", "EventWeight", "MET", "jet_pT", "jet_eta", "jet_phi", "jet_m", "jet_isB"});
  return 0;
}

int copyleavesttbar() {
  ROOT::RDataFrame df("Delphes", "ttbar.root");
  df.Snapshot("EventsTree", "ttbarevents.root", {"EventNumber", "EventWeight", "MET", "jet_pT", "jet_eta", "jet_phi", "jet_m", "jet_isB"});
  return 0;
}

int copyleavesdata() {
  ROOT::RDataFrame df("Delphes", "data.root");
  df.Snapshot("EventsTree", "dataevents.root", {"EventNumber", "EventWeight", "MET", "jet_pT", "jet_eta", "jet_phi", "jet_m", "jet_isB"});
  return 0;
}

// Functions that copy all the leaves present in the previous files, but reducing the number of events to 10000 for each file
// This is useful to make all the trials in a relatively short time before to run the whole datasets, which take many ours to run

int reducehiggs() {
  ROOT::RDataFrame df("EventsTree", "higgsevents.root");
  df.Range(10000).Snapshot("EventsTree", "reduced_higgsevents.root", {"EventNumber", "EventWeight", "MET", "jet_pT", "jet_eta", "jet_phi", "jet_m", "jet_isB"});
  return 0;
}

int reducettbar() {
  ROOT::RDataFrame df("EventsTree", "ttbarevents.root");
  df.Range(10000).Snapshot("EventsTree", "reduced_ttbarevents.root", {"EventNumber", "EventWeight", "MET", "jet_pT", "jet_eta", "jet_phi", "jet_m", "jet_isB"});
  return 0;
}

int reducedata() {
  ROOT::RDataFrame df("EventsTree", "dataevents.root");
  df.Range(10000).Snapshot("EventsTree", "reduced_dataevents.root", {"EventNumber", "EventWeight", "MET", "jet_pT", "jet_eta", "jet_phi", "jet_m", "jet_isB"});
  return 0;
}
