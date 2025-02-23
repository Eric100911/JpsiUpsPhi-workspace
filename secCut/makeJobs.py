#! /bin/python3

# This script performs a "cartesian product" from the input lists of parameters
# Sample input file:
#   - Ups_pT 4.0 4.5 5.0 5.5 6.0 7.0
# 	- Ups_mu_pT 2.0 2.5 3.0 3.5 4.0 5.0
# 	- Ups_mu_ID loose medium tight
# Seaprated by spaces, the first element is the name of the parameter, the rest are the values

import os
import sys
import numpy as np

# Define the command line arguments
if len(sys.argv) != 2:
    print("Usage: python3 makeJobDirs.py <input_file>")
    sys.exit(1)


# Read the input file
input_file = sys.argv[1]

# Read the input file
with open(input_file) as f:
    lines = f.readlines()

# Create a dictionary to store the parameters
# Use np.array to store the values
params = {}
for line in lines:
    line = line.strip().split()
    params[line[0]] = np.array(line[1:])

# Create a list of all the parameters
param_list = list(params.keys())

# Do cartesian product
# Create a list of all the combinations
combinations = np.array(np.meshgrid(*params.values())).T.reshape(-1, len(params))

# Create the directories named with each cut configuration
for comb in combinations:
    # Create the directory name
    # All decimal points are replaced with letter p
    dir_name = "_".join([f"{param_list[i]}_{str(comb[i]).replace('.', 'p')}" for i in range(len(param_list))])
    print(dir_name)



