# Software_and_Computing_Exam

The project contains 3 .root files that contain the datasets (signal, background and mixed data), 2 macros for the Machine Learning analysis (one with PYTHON methods and the other with TMVA based methods), a main macro that let the user decide what to do and on the base of the answer open the different files and finally the macro that was used to cut the datasets in order to have just the leaves of the trees that I needed.

All the files can be downloaded from the GitHub repository at the link:

https://github.com/SofiaStrazzi/Software_and_Computing_Exam.git

Program used to find events containing Higgs bosons decaying to b quark pairs in the LHC data

Three different datasets are used to test the program:
- Higgs bosons (higgsevents.root) which contains the signal events
- Top quark pairs (ttbarevents.root) which contains background events
- Data (dataevents.root) containing both signal and background events that I want to analyze

The three datasets are extracted from files downloaded by Delphes portal:
they have been cutted through the macro copyleaves in order to obtain smaller files with just the information that I needed

All the trees are called EventsTree 


# Version used and required packages

The program was tested with the version of python 3.8.10 and the version of root 6.20.08

For the python script some packages are required:
- tensorflow
- pandas
- uproot
- numpy
- matplotlib
- sklearn


# How to run the code 

Analysis can be generated starting from the script analysis.py, giving on the terminal the command:
"python3 analysis.py" 
and then answering to the questions.

On the base of the answers the script will run MLpython.py or MLtmva.C
