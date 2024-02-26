#include <stdio.h>
#include "simulation.h"
#include "equations.h"


bool run_simulation(struct vector3D *r, struct vector3D *v, struct system_state *state)
{
	if (r == NULL || v == NULL || state == NULL)
	{
		return false;
	}

	size_t data_size = state->time.total_time / state->time.dt;
	double cur_time = 0;

	dynarray_push(r, state->particle.r);
	dynarray_push(v, state->particle.v);

	for (size_t i = 0; i < data_size; ++i)
	{
		calculate_next_state_rk(state);
		cur_time += state->time.dt;

		if ((i + 1) % state->time.time_step == 0)
		{
			dynarray_push(r, state->particle.r);
			dynarray_push(v, state->particle.v);
		}
	}

	return true;
}
