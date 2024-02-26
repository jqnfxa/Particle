#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdbool.h>
#include "../structures/general/dynarray.h"
#include "../structures/math/vector3D.h"
#include "../structures/simulation/system_state.h"


/**
 * @brief read vector3D from file
 * @param dst output structure
 * @param file input file
 * @return `true` if data was successfully read and `false` otherwise
 */
bool read_vector3D(struct vector3D *dst, FILE *file);


/**
 * @brief load vectors and time variables from file
 * @param state output state structure
 * @param filename for reading
 * @return `true` if data was successfully read and `false` otherwise
 */
bool load_simulation_parameters(struct system_state *state, const char *filename);


/**
 * @brief load butcher tableau from file
 * @param tableau output butcher tableau structure
 * @param filename for for tableau
 * @return `true` if data was successfully read and `false` otherwise
 */
bool load_butcher_tableau(struct butcher_tableau *tableau, const char *filename);


/**
 * @brief setup initial simulation state
 * @param state output state structure
 * @param input input file for vector
 * @param table input file for tableau
 * @return `true` if data was successfully read and `false` otherwise
 */
bool setup_simulation(struct system_state *state, const char *input, const char *table);


/**
 * @brief write simulated r and v vectors to given file
 * @param time time structure
 * @param r array of positions
 * @param v array of velocities
 * @param filename - output filename
 * @return `true` if data was successfully written and `false` otherwise
 */
bool unload_data(struct time *time, struct vector3D *r, struct vector3D *v, const char *filename);

#endif // IO_H
