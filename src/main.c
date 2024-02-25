#include <stdio.h>
#include "tables/tableau.h"
#include "equations.h"
#include "structures/system_state.h"


int main()
{
	// read information from input file

	// run calculations
	double t = 1e6;
	double dt = 1e9;

	struct butcher_tableau table;

	if (!RK4_classic(&table))
	{
		perror("Failed to initialize butcher tableau");
	}

	struct system_state state;

	state.particle.r.x = 0;
	state.particle.r.y = 0;
	state.particle.r.z = 0;
	state.particle.v.x = 0;
	state.particle.v.y = 0;
	state.particle.v.z = 0;
	state.E.x = 0;
	state.E.y = 0;
	state.E.z = 0;
	state.B.x = 0;
	state.B.y = 0;
	state.B.z = 0;

	calculate_next_state_rk(&state, &table, dt);

	// log calculations to output file


	destroy_tableau(&table);
	return 0;
}
