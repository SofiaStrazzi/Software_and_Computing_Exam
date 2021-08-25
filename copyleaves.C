#include <ROOT/RDataFrame.hxx>

//using namespace ROOT::Experimental; // TDF lives here (until ROOT v6.14)

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