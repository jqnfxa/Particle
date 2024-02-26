#include <stdio.h>
#include "io/io.h"
#include "simulation_core/simulation.h"
#include "structures/general/dynarray.h"
#include "structures/simulation/system_state.h"


int main(int argc, char *argv[])
{
	// check if the correct number of arguments are provided
	if (argc < 4)
	{
		fprintf(stderr, "Usage: '%s' <input_file> <tableau_file> <output_file>\n", argv[0]);
		return 1;
	}

	// initialize system
	size_t total_steps = 0;
	struct system_state state;
	struct vector3D *r = NULL;
	struct vector3D *v = NULL;

	if (!setup_simulation(&state, argv[1], argv[2]))
	{
		return 1;
	}

	do
	{
		if (!setup_simulation(&state, argv[1], argv[2]))
		{
			break;
		}

		total_steps = state.time.total_time / state.time.dt / state.time.time_step;
		r = (struct vector3D *)dynarray_create_prealloc(struct vector3D, total_steps + 1);
		v = (struct vector3D *)dynarray_create_prealloc(struct vector3D, total_steps + 1);

		if (!run_simulation(r, v, &state))
		{
			break;
		}

		if (!unload_data(&state.time, r, v, argv[3]))
		{
			break;
		}
	} while (false);


	// clean up allocated memory
	destroy_tableau(&state.tableau);
	dynarray_destroy(r);
	dynarray_destroy(v);

	return 0;
}
