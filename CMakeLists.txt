cmake_minimum_required(VERSION 3.27)

project(Particle)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")


# Include source headers
include_directories(src)

# Add your source files
add_executable(Particle src/main.c
			src/io/io.c
			src/simulation_core/equations.c
			src/simulation_core/simulation.c
			src/structures/general/dynarray.c
			src/structures/math/vector3D.c
			src/structures/tables/tableau.c)
