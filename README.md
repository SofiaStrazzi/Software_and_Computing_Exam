# Software_and_Computing_Exam

The project contains:
- 2 folders, each with 3 .root files with the datasets (signal, background and mixed data):
  - the trees folder contains the 3 data samples with all the events;
  - the reducedtrees folder contains 3 reduced data samples with just the first 10000 events for each leaf, useful to try the program in just few minutes
-  2 macros for the Machine Learning analysis:
    - one with PYTHON methods;
    - the other with TMVA based methods;
- a main macro that let the user decide which of the previous macros wants to open and which machine learning method wants to use to analize data. On the base of the answers this macro opens the different files;
- finally the macro that was used to cut the datasets in order to have just the leaves of the trees that I needed and reduce the samples.


All the files can be downloaded from the GitHub repository at the link:

https://github.com/SofiaStrazzi/Software_and_Computing_Exam.git

# PROJECT DESCRIPTION

Program used to find events containing Higgs bosons decaying to b quark pairs in the LHC data: the program compares the performances of 4 machine learning techniques with TMVA methods and other 4 with PYTHON file. An output file with all the results is created and a ROC curve. On the base of the results, the user can decide which method is the best one and use it to analyse the data, counting the Higgs boson contained in the data sample.

Three different datasets are used to test the program:
- Higgs bosons (higgsevents.root) which contains the signal events;
- Top quark pairs (ttbarevents.root) which contains background events;
- Data (dataevents.root) containing both signal and background events that I want to analyze.

The three datasets are extracted from files downloaded by Delphes portal:
they have been cutted through the macro copyleaves in order to obtain smaller files with just the information that I needed.

All the trees are called EventsTree. 


# Version used and required packages

The program was tested with the version of python 3.8.10 and the version of root 6.20.08.

The TMVA package is required (https://root.cern/manual/tmva/)

For the python script some packages are required:
- tensorflow (version 2.4.0)
- pandas
- uproot
- numpy
- matplotlib
- sklearn


# How to run the code 

Analysis can be generated starting from the script analysis.py, giving on the terminal the command:

"python3 analysis.py" 

and then answering to the questions. On the base of the answers the script will run MLpython.py or MLtmva.C.
