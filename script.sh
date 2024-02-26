#!/bin/bash

# Check if the correct number of arguments is provided
if [ $# -ne  3 ]; then
    echo "Usage: ./script.sh <input> <method> <output>"
    exit  1
fi

# Assign the arguments to variables for clarity
input_file="$1"
method="$2"
output_file="$3"

# Run the compiled program with specific input and output files
./build/Particle "$input_file" "$method" "$output_file"

# Check if the previous command was successful
if [ $? -eq  0 ]; then
    echo "Simulation completed successfully."
    # Run the Python script
    python3 ./plot/plot_xyz.py "$output_file"
else
    echo "Simulation failed. Exiting."
    exit  1
fi
