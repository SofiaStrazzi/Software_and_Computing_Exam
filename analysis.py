# This is the main file that asks the user how to proceede and what he wants to do


# The user can decide if use an analysis based on PYTHON libraries or based on ROOT TMVA

print("\nYou can decide to use the PYTHON script to see the performances of a linear estimator or the TMVA to compare 4 different Machine Learning methodes and then use one of them to analyze the data\n")
print("Press 1 to use the PYTHON script or 2 to use ROOT TMVA \t")
type_of_analysis = input()

# Control on the input typed by the user:
# if the answer is not consistent, I let ask the user to type a right command
while (type_of_analysis != '1' and type_of_analysis != '2'):
	print("\nERROR: the input doesn't corrispond to any option \n")
	print("Press 1 to use the PYTHON script or 2 to use ROOT TMVA \t")
	type_of_analysis = input()
	
import os

# The program uses one of the 2 different files depending on the input of the user: 
# in the case of the TMVA analysis the program also open ROOT framework
if (type_of_analysis == '1'):
	os.system ("python3 MLpython.py")
else:
	os.system ("root MLtmva.C")

