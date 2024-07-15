# Particle

This project is dedicated to exploring numerical integration methods through the simulation of a charged particle's motion in magnetic and electric fields.

## Usage

1. **Setup Input Data**: First, configure the vectors and simulation parameters in `data/input.txt`. The file should contain the following information:

    - `Ex Ey Ez`: Electric field components
    - `Bx By Bz`: Magnetic field components
    - `rx ry rz`: Initial position of the particle
    - `vx vy vz`: Initial velocity of the particle
    - `q m`: Charge and mass of the particle
    - `total_time dt time_step`: Total simulation time, time step size

2. **Build and Run**: To execute the simulation, build the program and run `script.sh`. This script will automatically run the simulation and then invoke the Python plotter.

## Configuration

The project allows for customization of the integration method, input/output files, and other parameters. By default, the following settings are applied:

- **Integration Method**: `./data/methods/dp8.txt`
- **Input File**: `./data/input.txt`
- **Output File**: `./data/output.txt`

To modify these defaults, pass your relative paths to files.

## Plots

The simulation generates three types of plots to visualize the particle's motion:

1. **Static   2D Plots**: These plots display the position (R) and velocity (V) of the particle in two dimensions.

2. **Static   3D Plot**: This plot shows the position of the particle over time (R(t)) in three dimensions.

3. **Animated   3D Plot**: An animated version of the static   3D plot, also showing the particle's motion over time.

