#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdbool.h>
#include "../structures/general/dynarray.h"
#include "../structures/math/vector3D.h"
#include "../structures/simulation/system_state.h"


/**
 * @brief read initial simulation state from file with name passed via filename
 * @param state output structure to which the data will be written
 * @param filename name of the file from which the data will be read
 * @return `true` if read was successful and `false` otherwise
 */
bool load_simulation_parameters(struct system_state *state, const char *filename);


/**
 * @brief write simulated r and v vectors to given file
 * @param r array of positions
 * @param v array of velocities
 * @param filename - output filename
 * @return `true` if data was successfully written and `false` otherwise
 */
bool unload_data(struct vector3D *r, struct vector3D *v, const char *filename, double dt);

#endif // IO_H
