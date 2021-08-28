# The user can decide if using an analysis based on PYTHON libraries or based on ROOT TMVA

print("Press 1 to analyze data with PYTHON libraries or 2 to analyze them with TMVA \t")
type_of_analysis = raw_input()

# Control on the input typed by the user:
# if the answer is not consistent, I let ask the user to type a right command
while (type_of_analysis != 1 and type_of_analysis != 2):
	print("ERROR: the input doesn't corrispond to any option \n")
	print("Press 1 to analyze data with Python libraries or 2 to analyze them with TMVA \t")
	type_of_analysis = raw_input()
	
import os


