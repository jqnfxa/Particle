#include <stdio.h>
#include "io/io.h"
#include "simulation_core/simulation.h"
#include "structures/general/dynarray.h"
#include "structures/simulation/system_state.h"


int main(int argc, char *argv[])
{
	// check if the correct number of arguments are provided
	if (argc < 3)
	{
		//perror("Usage: %s <input_file> <output_file>\n", argv[0]);
		return 1;
	}


	const char *input_filename = argv[1];
	const char *output_filename = argv[2];

	struct system_state state;
	struct vector3D *r;
	struct vector3D *v;


	// load initial state
	if (!load_simulation_parameters(&state, input_filename))
	{
		return 1;
	}


	// setup butcher tableau and allocate memory for r,v
	if (!setup_simulation(&r, &v, &state))
	{
		return 1;
	}


	// TODO: error handling
	// simulation
	run_simulation(r, v, &state);
	unload_data(r, v, output_filename, state.time.dt);


	// clean up allocated memory
	destroy_tableau(&state.tableau);
	dynarray_destroy(r);
	dynarray_destroy(v);

	return 0;
}
