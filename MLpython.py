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
!pip3 install uproot
import uproot
import numpy as np
from matplotlib import pyplot as plt
from sklearn.metrics import roc_curve
from IPython.display import clear_output
clear_output()

# Print the version of TensorFlow
print("TensorFlow " + str(tf.__version__))
