#include <stddef.h>
#include <stdlib.h>
#include "structures/math/vector3D.h"
#include "equations.h"


/**
 * @brief calculates [F = q * (E + vxB)]
 * @param F - destination vector for lorentz force
 * @param particle - particle structure
 * @param B - vector of magnetic field
 * @param E - vector of electric field
 */
void lorentz_force(struct vector3D *F, const struct system_state *state)
{
	if (F == NULL || state == NULL)
	{
		return;
	}

	cross(F, &state->particle.v, &state->B);
	add(F, &state->E);
	scale(F, state->particle.q);
}

/**
 * @brief calculates [a = F_L / m], where F_L - Lorentz force
 * @param F - destination vector
 * @param particle - particle structure
 * @param B - vector of magnetic field
 * @param E - vector of electric field
 */
void acceleration(struct vector3D *a, const struct system_state *state)
{
	if (a == NULL || state == NULL)
	{
		return;
	}

	lorentz_force(a, state);
	scale(a, 1.0 / state->particle.m);
}

/**
 * @brief calculates next system state by given butcher tableau
 * @param state previous state of system
 * @param tableau butcher tableau (can be any method)
 * @param dt (step for methods 'h')
 */
// TODO: dt as part of state?
void calculate_next_state_rk(struct system_state *state, const struct butcher_tableau *tableau, double dt)
{
	if (state == NULL || tableau == NULL)
	{
		return;
	}

	// allocate additional variables to calculate 'k' coefficients
	struct vector3D *k_a = (struct vector3D *)malloc(sizeof(struct vector3D) * tableau->s);
	struct vector3D *k_v = (struct vector3D *)malloc(sizeof(struct vector3D) * tableau->s);

	// store initial velocity and radius vector values
	struct vector3D initial_r = state->particle.r;
	struct vector3D initial_v = state->particle.v;


	// apply S steps
	for (size_t step = 0; step < tableau->s; ++step)
	{
		state->particle.r = initial_r;
		state->particle.v = initial_v;

		for (size_t column = 0; column < step; ++column)
		{
			add_scaled(&state->particle.r, &k_v[column], tableau->a[step][column] * dt);
			add_scaled(&state->particle.v, &k_a[column], tableau->a[step][column] * dt);
		}

		k_v[step] = state->particle.v;
		acceleration(&k_a[step], state);
	}


	// calculate resulting X(t + h) = X(t) + h * sum {bi*ki}, i = 1, 2, ... s
	state->particle.r = initial_r;
	state->particle.v = initial_v;

	for (size_t i = 0; i < tableau->s; ++i)
	{
		add_scaled(&state->particle.r, &k_v[i], tableau->b[i] * dt);
		add_scaled(&state->particle.v, &k_a[i], tableau->b[i] * dt);
	}


	// don't forget to clean up used memory
	free(k_v);
	free(k_a);
}
