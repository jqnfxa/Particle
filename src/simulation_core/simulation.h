#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdbool.h>
#include "../structures/simulation/system_state.h"
#include "../structures/general/dynarray.h"


bool run_simulation(struct vector3D *r, struct vector3D *v, struct system_state *state);

#endif // SIMULATION_H
