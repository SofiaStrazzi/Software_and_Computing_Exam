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

# I ask the user to decide if he wants to use the whole datasamples or just the first 10000 events
print("\n\nPress 1 to use the whole datasamples (the analysis can take many time) or 2 to use just 10000 events for each datasample\t")
n_Events = input()

# Control on the input typed by the user:
# if the answer is not consistent, I let ask the user to type a right command
while (n_Events != '1' and n_Events != '2'):
	print("\nERROR: the input doesn't corrispond to any option \n")
	print("\n\nPress 1 to use the whole datasamples (the analysis can take many time) or 2 to use just 10000 events for each datasample to try the program\t")
	n_events = input()

if (n_Events == '1'):
	# I read the .root file containing all Higgs events, that is in the directory trees
	tree = uproot.open("./trees/higgsevents.root")[tree_name]
	#tree.show() # If I want to print the variables that I'm using
	# I read the .root file containing all top pair production events, that is in the directory trees
	tree = uproot.open("./trees/ttbarevents.root")[tree_name]
	#tree.show() # If I want to print the variables that I'm using
	# I read the .root file containing all real production events, that is in the directory trees
	tree = uproot.open("./trees/dataevents.root")[tree_name]
	#tree.show() # If I want to print the variables that I'm using
	
if (n_Events == '2'):
	# I read the .root file containing the first 10000 Higgs events, that is in the directory reducedtrees
	tree = uproot.open("./reducedtrees/reduced_higgsevents.root")[tree_name]
	#tree.show() # If I want to print the variables that I'm using
	# I read the .root file containing the first 10000 top pair production events, that is in the directory reducedtrees
	tree = uproot.open("./reducedtrees/reduced_ttbarevents.root")[tree_name]
	#tree.show() # If I want to print the variables that I'm using
		# I read the .root file containing the first 10000 real production events, that is in the directory reducedtrees
	tree = uproot.open("./reducedtrees/reduced_dataevents.root")[tree_name]
	#tree.show() # If I want to print the variables that I'm using
	

# Create a dataframe with all the variables of the tree I decided to use for the signal
df_higgsevents = tree.arrays(cols, library="pd")

# Create a dataframe with all the variables of the tree I decided to use for the background
df_ttbarevents = tree.arrays(cols, library="pd")

# Create a dataframe with all the variables of the tree I in which the real data are contained
df_dataevents = tree.arrays(cols, library="pd")


##### I have a look to some distributions in order to have an idea of the data that I have

# I try to have a look at the jet pTs
fig, ax = plt.subplots(figsize=(5, 5))
ax.set_xlabel("Jet $p_{T}$ [GeV]")

df_higgsevents.jet_pT.hist(ax=ax, bins=10, range=(0,300), alpha=0.7, label='Higgsevents(sgn)')
df_ttbarevents.jet_pT.hist(ax=ax, bins=10, range=(0,300), alpha=0.7, label='ttbarevents(bkg)')

ax.legend(frameon=False, prop={'size': 16})

plt.show()

# I plot the pT of the leading jet in every event for both signal and background datasets
leading_jet_higgs = df_higgsevents.jet_pT.xs(0, level='subentry')
leading_jet_ttbar = df_ttbarevents.jet_pT.xs(0, level='subentry')

fig, ax2 = plt.subplots(figsize=(5, 5))
ax2.set_xlabel("Leading jet $p_{T}$ [GeV]")

leading_jet_higgs.hist(ax=ax2, bins=10, range=(0,300), alpha=0.7, label='Higgsevents(sgn)')
leading_jet_ttbar.hist(ax=ax2, bins=10, range=(0,300), alpha=0.7, label='ttbarevents(bkg)')

ax2.legend(frameon=False, prop={'size': 16})

plt.show()

# I build an event-level variable: I visualize the number of jets in each event

njet_higgs = df_higgsevents.groupby('entry').size()
njet_ttbar = df_ttbarevents.groupby('entry').size()

fig, ax3 = plt.subplots(figsize=(5, 5))
ax3.set_xlabel("Jet multiplicity")

njet_higgs.hist(ax=ax3, bins=10, range=(0,10), alpha=0.7, label='Higgsevents (sgn)')
njet_ttbar.hist(ax=ax3, bins=10, range=(0,10), alpha=0.7, label='ttbarevents (bkg)')

ax3.legend(frameon=False, prop={'size': 16})

plt.show()


##### I create a dataframe in which I put all the information that I want to exploit:

# I do it for the signal first (Higgs events)
higgs_frame = { 'lead_jet': leading_jet_higgs, 'njet': njet_higgs }
higgs_df = pd.DataFrame(higgs_frame)

# I add a target for the training of the Machine Learning methods
higgs_df['target']=1

# I split the events one half to train the methods and the other half for the validation 
splitted_higgs_df = np.array_split(higgs_df, 2)

train_higgs_df = splitted_higgs_df[0]
eval_higgs_df = splitted_higgs_df[1]

# I do the same for the background now (ttbar events)
ttbar_frame = { 'lead_jet': leading_jet_ttbar, 'njet': njet_ttbar }
ttbar_df = pd.DataFrame(ttbar_frame)

# I add a target for the training of the Machine Learning methods
ttbar_df['target']=0

# I split the events one half to train the methods and the other half for the validation
splitted_ttbar_df = np.array_split(ttbar_df, 2)

train_ttbar_df = splitted_ttbar_df[0]
eval_ttbar_df = splitted_ttbar_df[1]


##### I mix the signal and background events in order to have a full sample for the training of the methods and for the evaluation

# I concatenate the higgs and ttbar samples to mix signal and background events for the training
train_df = pd.concat([train_higgs_df, train_ttbar_df])

# I concatenate the higgs and ttbar samples to mix signal and background events for the evaluation
eval_df = pd.concat([eval_higgs_df, eval_ttbar_df])

# I add a target for both the samples that I just defined
train_df_labels = train_df['target']
eval_df_labels = eval_df['target']

# I define a functionDefines a function constrinputfunction that I use to feed the data to the tensorflow functions
def constr_inputfunction(data_df, label_df, epochs=10, shuffle=True, batch_size=32):
  def inputfunc():
    dataset = tf.data.Dataset.from_tensor_slices((dict(data_df), label_df))
    if shuffle:
      dataset = dataset.shuffle(1000000)
    dataset = dataset.batch(batch_size).repeat(epochs)
    return dataset
  return inputfunc

# I define the number of epochs that I use to train the method:
# this is the number of time in which I show the datasets to the alghorithm in order to train it and have in the end the right weights
Nepochs = 30

# Training inputs preparation
train_input_fn = constr_inputfunction(train_df, train_df_labels, epochs=Nepochs, shuffle=True)
eval_input_fn = constr_inputfunction(eval_df, eval_df_labels, epochs=1, shuffle=False)

# I define the numeric columns and append the features
num_columns = ['lead_jet', 'njet']
feature_columns = []

# I append the features in the feature_columns variable
for feature_name in num_columns:
  feature_columns.append(tf.feature_column.numeric_column(feature_name, dtype=tf.float32))
  
##### I define the linear estimator that I want to use and its parameters
lin_estimator = tf.estimator.LinearClassifier(feature_columns=feature_columns,
                                               optimizer = tf.keras.optimizers.SGD(
                                               learning_rate=0.005,
                                               momentum=0.95,
                                               nesterov=True
                                             ),
                                              model_dir="ongoing/lin0")

# I train the linear estimator that I just defined
lin_estimator.train(train_input_fn)

# Evaluation of the training with the linear estimator 
lin_estimator_results = lin_estimator.evaluate(eval_input_fn)

# I clear the output to avoid problems
clear_output()

# I print on terminal the results of the precedent evaluation
print(lin_estimator_results)

# I count the number of higgs bosons present in the evaluation sample on the base of the previous results
# higgs_candidates = probs_challenge[probs_challenge > 0.3].count() 

# I print the number of higgs bosons present in the evaluation sample
# print('The alghorithms found ' + str(higgs_candidates) + ' candidates of higgs bosons into the evaluation dataset')
