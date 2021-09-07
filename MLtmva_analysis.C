 // This macro analyse the data with the method chosen by the user in TMVA:
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
   Int_t method = 0;

   cout << "\n\nPRESS 1, 2, 3 OR 4 TO SELECT THE METHOD THAT YOU WANT TO USE TO ANALYZE THE DATA:" << endl << endl;

   cout << "1 Cut optimisation (CutsGA)" << endl
   		<< "2 Linear Discriminant Analysis (Fisher discriminant)" << endl
   		<< "3 Neural Networks MLPBNN (feed-forward Multilayer Perceptrons" << endl
   		<< "4 Boosted Decision Trees (Adaptive Boost) " << endl;
   
   cout << "Press 1, 2, 3 or 4:" << endl;
   cin >> method;
 
   // I put a control on the answer of the user
   while (method != 1 && method != 2 && method != 3 && method != 4)
      {
      cout << "\n\nPRESS 1, 2, 3 OR 4 TO SELECT THE METHOD THAT YOU WANT TO USE TO ANALYZE THE DATA:" << endl << endl;

      cout << "1 Cut optimisation (CutsGA)" << endl
   		  << "2 Linear Discriminant Analysis (Fisher discriminant)" << endl
   	  	<< "3 Neural Networks MLPBNN (feed-forward Multilayer Perceptrons" << endl
   		  << "4 Boosted Decision Trees (Adaptive Boost) " << endl;
     
      cout << "Press 1, 2, 3 or 4:" << endl;
      cin >> method;
     }
 
 
    //I ask the user if he wants to use the whole dataset or just a part of the events
   Int_t answer = 0;
  
   cout << "\nPress 1 to use the whole datasample (the analysis can take many time) or 2 to analyze just 10000 events to try the program\t";
   cin >> answer;

   // I put a control on the answer of the user
   while (answer != 1 && answer !=2)
     {
     cout << "\nERROR: You have to press 1 or 2" << endl;
     cout << "\nPress 1 to use the whole datasample (the analysis can take many time) or 2 to analyze just 10000 events to try the program\t";
     cin >> answer;
     }

   // I prepare the input tree
   TFile *input(0);
   TString fname;
   
   // I open and assign a name to the input .root file with the data I want to analyze on the base of the decision of the user
   if (answer == 1)
     fname = "./trees/dataevents.root";
  
   else
     fname = "./reducedtrees/reduced_dataevents.root";


   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }

   if (!input) {
      cout << "ERROR: could not open data file" << endl;
      exit(1);
   }
   
   cout << "\nAnalysing data in the file: " << input->GetName() << endl;
          
   // //Create a set of variables and declare them to the reader
   //  Long64_t EventNumber;
   //  vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float>> MET, jet_pT, jet_eta, jet_phi, jet_m;
   //  vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int>> jet_isB;
   // //Float_t EventNumber, MET, jet_pT, jet_eta, jet_phi, jet_m, 
   // //Int_t jet_isB;
   //  //Float_t EventNumber;

   // // Create the Reader object
   // TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );


   // Create a set of variables and declare them to the reader

   //Float_t EventNumber, MET, jet_pT, jet_eta, jet_phi, jet_m, jet_isB;

   Long64_t *EventNumber=0;
   vector<float> *MET=0, *jet_pT=0, *jet_eta=0, *jet_phi=0, *jet_m=0;
   vector<int> *jet_isB=0;
   
   // Create the Reader object
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

   // I pass all the variables to the reader
   reader -> AddVariable("EventNumber", &(EventNumber[0]));
   reader -> AddVariable("MET", &(MET[0]));
   reader -> AddVariable("jet_pT", &(jet_pT[0]));
   reader -> AddVariable("jet_eta", &(jet_eta[0]));
   reader -> AddVariable("jet_phi", &(jet_phi[0]));
   reader -> AddVariable("jet_m", &(jet_m[0]));
   reader -> AddVariable("jet_isB", (&jet_isB[0]));
 
   delete EventNumber, MET, jet_pT, jet_eta, jet_phi, jet_m, jet_isB;
          
   // I assign the names to the methods
   TString methodString;

   if (method == 1)   
         methodString = "CutsGA";

   if (method == 2)   
         methodString = "Fisher";

   if (method == 3)   
         methodString = "MLPBNN";

   if (method == 4)   
         methodString = "BDT";
          
          
   // Book the MVA methods considering the pathe and the name of the files I created with the previous macro 
   TString dir    = "trainingevents/weights/"; //this is the name I used for the directory in the MLtmva.C file
   TString prefix = "TMVAClassification";

   TString methodName = methodString + TString(" method");
   TString weightfile = dir + prefix + TString("_") + methodString + TString(".weights.xml");
   reader->BookMVA( methodName, weightfile );
          
   // Book output histograms
   // Histogram definition
   UInt_t nbin = 100;
   TH1F *histFi(0);
   TH1F *histNnbnn(0);
   TH1F *histBdt(0);
 
   if (method == 2) 
   		histFi    = new TH1F( "MVA_Fisher", "MVA_Fisher", nbin, -4, 4 );

   if (method == 3) 
   		histNnbnn = new TH1F( "MVA_MLPBNN", "MVA_MLPBNN", nbin, -1.25, 1.5 );

   if (method == 4) 
   		histBdt   = new TH1F( "MVA_BDT", "MVA_BDT", nbin, -0.8, 0.8 );
          
          
   // Book histogram for probability for each method
   TH1F *probHistFi(0), *rarityHistFi(0);

   if (method == 2) 
   	  {
      probHistFi   = new TH1F( "MVA_Fisher_Proba", "MVA_Fisher_Proba", nbin, 0, 1 );
      rarityHistFi = new TH1F( "MVA_Fisher_Rarity", "MVA_Fisher_Rarity", nbin, 0, 1 );
   	  }
   
          
   // Event loop
   // Prepare the event tree
   cout << "--- Select the sample" << endl;
   TTree* theTree = (TTree*)input->Get("EventsTree");
  
 
   // I set branch adresses
   theTree->SetBranchAddress("EventNumber", &(EventNumber[0]));
   theTree->SetBranchAddress("MET", &(MET[0]));
   theTree->SetBranchAddress("jet_pT", &(jet_pT[0]));
   theTree->SetBranchAddress("jet_eta", &(jet_eta[0]));
   theTree->SetBranchAddress("jet_phi", &(jet_phi[0]));
   theTree->SetBranchAddress("jet_m", &(jet_m[0]));
   theTree->SetBranchAddress("jet_isB", &(jet_isB[0])); 
          
   // Efficiency calculator for cutsGA method
   Int_t nSelCutsGA = 0;
   Double_t effS = 0.7;
 
   std::vector<Float_t> vecVar(4); // vector for EvaluateMVA tests
 
   cout << "--- Processing: " << theTree->GetEntries() << " events" << endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) 
   	{
      if (ievt%1000 == 0) 
      	  cout << "--- ... Processing event: " << ievt << endl;
 
      theTree->GetEntry(ievt);
     
      // Return the MVA outputs and fill into histograms
      if (method == 1) 
    	 {
         // Cuts is a special case, it is not a machine learning method, so I give the signal efficiency of 0.7
         Bool_t passed = reader->EvaluateMVA( "CutsGA method", effS );
         if (passed) nSelCutsGA++;
      	 }
 
      if (method == 2)   
      		histFi ->Fill( reader->EvaluateMVA( "Fisher method" ) );

      if (method == 3)   
      		histNnbnn ->Fill( reader->EvaluateMVA( "MLPBNN method" ) );

      if (method == 4)   
      		histBdt ->Fill( reader->EvaluateMVA( "BDT method" ) );
      
      // Retrieve probability instead of MVA output
      if (method == 2)   
      	 {
         probHistFi  ->Fill( reader->GetProba ( "Fisher method" ));
         rarityHistFi->Fill( reader->GetRarity ( "Fisher method" ));
         }
   	}
          
   // Get elapsed time
   sw.Stop();
   cout << "--- End of event loop: "; 
   sw.Print();
          
          
   // Get efficiency for cuts classifier
   if (method == 1) 
   		cout << "--- Efficiency for CutsGA method: " << double(nSelCutsGA)/theTree->GetEntries()
             << " (for a required signal efficiency of " << effS << ")" << endl;
 
   if (method == 1) 
   {
      // test: retrieve cuts for particular signal efficiency
      // CINT ignores dynamic_casts so we have to use a cuts-specific Reader function to acces the pointer
      TMVA::MethodCuts* mcuts = reader->FindCutsMVA( "CutsGA method" ) ;
 
      if (mcuts) 
      {
         std::vector<Double_t> cutsMin;
         std::vector<Double_t> cutsMax;
         mcuts->GetCuts( 0.7, cutsMin, cutsMax );
         std::cout << "--- -------------------------------------------------------------" << endl;
         std::cout << "--- Retrieve cut values for signal efficiency of 0.7 from Reader" << endl;
         for (UInt_t ivar=0; ivar<cutsMin.size(); ivar++) 
         {
            std::cout << "... Cut: "
                      << cutsMin[ivar]
                      << " < \""
                      << mcuts->GetInputVar(ivar)
                      << "\" <= "
                      << cutsMax[ivar] << std::endl;
         }
         cout << "--- -------------------------------------------------------------" << endl;
      }
   }
          
          
   // Write histograms
   // I create an output file in which I can put the output of the TMVA performances comparison
   TString outfileName("MLtmva_analysis_output.root");
   TFile* target = TFile::Open(outfileName, "RECREATE");

  	//TFile* target  = new TFile( "MLtmva_analysis:output.root","RECREATE" );

   if (method == 2)   
   		histFi -> Write();

   if (method == 3)   
   		histNnbnn -> Write();

   if (method == 4)   
   		histBdt -> Write();

 
   // Write also probability histograms
   if (method == 2) 
   		{ 
   		if (probHistFi != 0) 
   				probHistFi->Write(); 
   		if (rarityHistFi != 0) 
   				rarityHistFi->Write(); 
   		}
 
          
   // I close the target
   target->Close();

   // I delete the reader
   delete reader;
 
   // I write to the user that the macro finisched the analysis and where to find the output histograms
   cout << "\n\nMLtmva_analysis MACRO FINISHED THE ANALYSIS FOR THE INSERTED DATA" << endl;
   cout << "The output histograms are contained in the output file MLtmva_analysis_output.root" << endl;

   return 0;
}
          
