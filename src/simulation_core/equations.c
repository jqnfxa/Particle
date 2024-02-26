#include <stddef.h>
#include <stdlib.h>
#include "structures/math/vector3D.h"
#include "equations.h"


/**
 * @brief calculates [dv / dt = f(v)] i.e: [a = F_L / m = q / m * (E + vxB)], where F_L - Lorentz force
 * @param dst - destination vector
 * @param state - previous state of system
 */
void acceleration(struct vector3D *dst, const struct system_state *state)
{
	if (dst == NULL || state == NULL)
	{
		return;
	}

	cross(dst, &state->particle.v, &state->B);
	add(dst, &state->E);
	scale(dst, state->particle.q / state->particle.m);
}

/**
 * @brief calculates next system state by given butcher tableau
 * @param state previous state of system
 */
void calculate_next_state_rk(struct system_state *state)
{
	if (state == NULL)
	{
		return;
	}

	// allocate additional variables to calculate 'k' coefficients
	struct vector3D *k_a = (struct vector3D *)malloc(sizeof(struct vector3D) * state->tableau.s);
	struct vector3D *k_v = (struct vector3D *)malloc(sizeof(struct vector3D) * state->tableau.s);

	// store initial velocity and radius vector values
	struct vector3D initial_r = state->particle.r;
	struct vector3D initial_v = state->particle.v;


	// apply S steps
	for (size_t step = 0; step < state->tableau.s; ++step)
	{
		state->particle.r = initial_r;
		state->particle.v = initial_v;

		for (size_t column = 0; column < step; ++column)
		{
			add_scaled(&state->particle.r, &k_v[column], state->tableau.a[step][column] * state->time.dt);
			add_scaled(&state->particle.v, &k_a[column], state->tableau.a[step][column] * state->time.dt);
		}

		k_v[step] = state->particle.v;
		acceleration(&k_a[step], state);
	}


	// calculate resulting X(t + h) = X(t) + h * sum {bi*ki}, i = 1, 2, ... s
	state->particle.r = initial_r;
	state->particle.v = initial_v;

	for (size_t i = 0; i < state->tableau.s; ++i)
	{
		add_scaled(&state->particle.r, &k_v[i], state->tableau.b[i] * state->time.dt);
		add_scaled(&state->particle.v, &k_a[i], state->tableau.b[i] * state->time.dt);
	}


	// don't forget to clean up used memory
	free(k_v);
	free(k_a);
}
