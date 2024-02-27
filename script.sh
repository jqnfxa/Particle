#!/bin/bash

# Default values
default_method="./data/methods/dp8.txt"
default_input_file="./data/input.txt"
default_output_file="./data/output.txt"

# Assign the arguments to variables for clarity, with default values if arguments are empty
method="${1:-$default_method}"
input_file="${2:-$default_input_file}"
output_file="${3:-$default_output_file}"

# Run the simulation
./build/Particle "$input_file" "$method" "$output_file"

# Check if the previous command was successful
if [ $? -eq  0 ]; then
    # Run the Python plotter
    python3 ./plot/plot.py "$output_file"
else
    echo "Simulation failed. Exiting."
    exit  1
fi
