import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

def read_data(filename):
    # Read data from file with tab delimiter
    data = np.loadtxt(filename, delimiter='\t')

    # Extract time, position, and velocity components
    time = data[:,   0]
    rx = data[:,   1]
    ry = data[:,   2]
    rz = data[:,   3]
    vx = data[:,   4]
    vy = data[:,   5]
    vz = data[:,   6]

    return time, rx, ry, rz, vx, vy, vz

def plot_data(filename):
    time, rx, ry, rz, vx, vy, vz = read_data(filename)

    # Plot   2D graphs for Rx(t), Ry(t), Rz(t), Vx(t), Vy(t), Vz(t)
    plt.figure(figsize=(15,   15))  # Increase figure size
    plt.subplots_adjust(hspace=0.5, wspace=0.5)  # Adjust space between subplots

    plt.subplot(2,   3,   1)
    plt.plot(time, rx, label='Rx(t)')
    plt.title('Rx(t)')
    plt.xlabel('Time')
    plt.ylabel('Rx')
    plt.legend()

    plt.subplot(2,   3,   2)
    plt.plot(time, ry, label='Ry(t)')
    plt.title('Ry(t)')
    plt.xlabel('Time')
    plt.ylabel('Ry')
    plt.legend()

    plt.subplot(2,   3,   3)
    plt.plot(time, rz, label='Rz(t)')
    plt.title('Rz(t)')
    plt.xlabel('Time')
    plt.ylabel('Rz')
    plt.legend()

    plt.subplot(2,   3,   4)
    plt.plot(time, vx, label='Vx(t)')
    plt.title('Vx(t)')
    plt.xlabel('Time')
    plt.ylabel('Vx')
    plt.legend()

    plt.subplot(2,   3,   5)
    plt.plot(time, vy, label='Vy(t)')
    plt.title('Vy(t)')
    plt.xlabel('Time')
    plt.ylabel('Vy')
    plt.legend()

    plt.subplot(2,   3,   6)
    plt.plot(time, vz, label='Vz(t)')
    plt.title('Vz(t)')
    plt.xlabel('Time')
    plt.ylabel('Vz')
    plt.legend()

    # Plot   3D plot for R(t)
    fig3d = plt.figure(figsize=(10,   10))  # Create a new figure instance for the   3D plot
    ax3d = fig3d.add_subplot(111, projection='3d')  # Add a   3D subplot to the new figure
    ax3d.plot(rx, ry, rz, label='R(t)')
    ax3d.set_xlabel('Rx')
    ax3d.set_ylabel('Ry')
    ax3d.set_zlabel('Rz')
    ax3d.set_title('R(t)')
    ax3d.legend()

    # Create a new figure for the animated   3D plot
    fig3d_animated = plt.figure(figsize=(10,   10))
    ax3d_animated = fig3d_animated.add_subplot(111, projection='3d')

    # Set the limits of the axes to the min and max values of the data
    ax3d_animated.set_xlim([np.min(rx), np.max(rx)])
    ax3d_animated.set_ylim([np.min(ry), np.max(ry)])
    ax3d_animated.set_zlim([np.min(rz), np.max(rz)])

    # Initialize the plot with the first frame
    line, = ax3d_animated.plot(rx[0], ry[0], rz[0], label='R(t)', color='blue')
    ax3d_animated.set_xlabel('Rx')
    ax3d_animated.set_ylabel('Ry')
    ax3d_animated.set_zlabel('Rz')
    ax3d_animated.set_title('R(t)')
    ax3d_animated.legend()

    # Initialize the scatter plot for the current point
    current_point, = ax3d_animated.plot(rx[0], ry[0], rz[0], 'ro')

    # Function to update the   3D plot
    def update(frame):
        nonlocal current_point  # Declare current_point as nonlocal to access it outside its scope
        # Clear the previous red point
        current_point.remove()
        # Update the line to include all points up to the current frame
        line.set_data_3d(rx[:frame+1], ry[:frame+1], rz[:frame+1])
        # Plot the current point in red
        current_point, = ax3d_animated.plot(rx[frame], ry[frame], rz[frame], 'ro')
        return line, current_point,

    # Create the animation with the calculated interval
    ani = FuncAnimation(fig3d_animated, update, frames=len(time), interval=1, blit=True)

    # Show plots
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) !=   2:
        print("Usage: python script.py <data_file>")
        sys.exit(1)

    filename = sys.argv[1]
    plot_data(filename)
