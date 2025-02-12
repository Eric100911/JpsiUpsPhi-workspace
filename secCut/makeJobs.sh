#! /bin/bash

# This script creates name of jobs for each combination of parameters.
# A cartesian product of the parameters is created and a directory is created for each combination.
# The directories are named according to the parameters they represent.

# List of default parameters
Ups_mu_pT="2.5 3.0 3.5 4.0 4.5 5.0 5.5 6.0 7.0 8.0"
Ups_pT="4.0 6.0 8.0 10.0 12.0"
Ups_muID="loose medium tight"

# Default input file
input="config/cutlist.txt"

# May read in from a list.
# Use parsing in command line.
while getopts "i:" opt; do
    case $opt in
        i) input="$OPTARG";;
    esac
done

# Read in the input file
# The input file should contain the list of parameters.
# Use the first element of each line to represent the parameter.
while read line; do
    # Skip empty lines
    if [ -z "$line" ]; then
        continue
    fi

    # Skip comments
    if [[ $line == \#* ]]; then
        continue
    fi

    # Split the line into an array
    IFS=' ' read -r -a array <<< "$line"

    # Check if the array is empty
    if [ -z "$array" ]; then
        continue
    fi

    # Check if the first element is empty
    if [ -z "${array[0]}" ]; then
        continue
    fi

    # Check if the first element is a number
    if [[ ! "${array[0]}" =~ ^[0-9]+([.][0-9]+)?$ ]]; then
        continue
    fi

    # For line as Ups_mu_pT Ups_pT Ups_muID, take in the parameters
    if [ "${array[1]}" == "Ups_mu_pT" ]; then
        Ups_mu_pT="${array[@]:2}"
    elif [ "${array[1]}" == "Ups_pT" ]; then
        Ups_pT="${array[@]:2}"
    elif [ "${array[1]}" == "Ups_muID" ]; then
        Ups_muID="${array[@]:2}"
    fi
done < $input



# Create the cartesian product of the parameters.
for mu_pT in $Ups_mu_pT; do
    for pT in $Ups_pT; do
        for muID in $Ups_muID; do
            # Create the directory name
            # Use 'p' to substitute '.' in the float numbers
            dirName="Ups_mu_pT_${mu_pT//./p}_Ups_pT_${pT//./p}_Ups_muID_${muID}"
            echo $dirName
        done
    done
done
