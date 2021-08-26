# Program to find events containing Higgs bosons decaying to b quark pairs in the LHC data

# Three different datasets are used to test the program:
#    - Higgs bosons (higgsevents.root) which contains the signal events
#    - Top quark pairs (ttbarevents.root) which contains background events
#    - Data (dataevents.root) containing both signal and background events that I want to analyze

# The three datasets are extracted from files downloaded by Delphes portal:
# they have been cutted through the macro copyleaves in order to obtain smaller files with just the information that I needed

# All the trees are called EventsTree 

import tensorflow as tf
import pandas as pd
import uproot
import numpy as np
from matplotlib import pyplot as plt
from sklearn.metrics import roc_curve
from IPython.display import clear_output
clear_output()

# Print the version of TensorFlow
print("TensorFlow " + str(tf.__version__))

# Configuration of the tree
tree_name = "EventsTree" #All the trees in the different files are called EventsTree

# Define list of variables which the file takes from the trees in order to analyze the data
cols = ['EventNumber', 'jet_pT', 'jet_eta', 'jet_phi', 'jet_m', 'jet_isB']

# I read the .root file containing the Higgs events that is in the same directory of the file
tree = uproot.open("higgsevents.root")[tree_name]

#tree.show() # If I want to print the variables that I'm using

# Create a dataframe with all the variables of the tree I decided to use for the signal
df_higgsevents = tree.arrays(cols, library="pd")

# I read the .root file containing the top pair production events that is in the same directory of the file
tree = uproot.open("ttbarevents.root")[tree_name]

# Create a dataframe with all the variables of the tree I decided to use for the background
df_ttbarevents = tree.arrays(cols, library="pd")

# I try to have a look at the jet pTs
fig, ax = plt.subplots(figsize=(5, 5))
ax.set_xlabel("Jet $p_{T}$ [GeV]")

df_higgsevents.jet_pT.hist(ax=ax, bins=10, range=(0,300), alpha=0.7, label='Higgsevents(sgn)')
df_ttbarevents.jet_pT.hist(ax=ax, bins=10, range=(0,300), alpha=0.7, label='ttbarevents(bkg)')

ax.legend(frameon=False, prop={'size': 16})
plt.show()
