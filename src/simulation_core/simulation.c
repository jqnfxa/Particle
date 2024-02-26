#include <stdio.h>
#include "simulation.h"
#include "equations.h"


bool setup_simulation(struct vector3D **r, struct vector3D **v, struct system_state *state)
{
	if (r == NULL || v == NULL || state == NULL)
	{
		return false;
	}

	if (!RK4_classic(&state->tableau))
	{
		perror("Error: failed to initialize tableau");
		return false;
	}

	size_t data_size = state->time.total_time / state->time.dt;
	*r = (struct vector3D *)dynarray_create_prealloc(struct vector3D, data_size + 1);
	*v = (struct vector3D *)dynarray_create_prealloc(struct vector3D, data_size + 1);

	return *r != NULL && *v != NULL;
}


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

		dynarray_push(r, state->particle.r);
		dynarray_push(v, state->particle.v);
	}

	return true;
}
