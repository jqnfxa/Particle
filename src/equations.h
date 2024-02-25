#ifndef EQUATIONS_H
#define EQUATIONS_H

#include "tables/tableau.h"
#include "structures/system_state.h"


void calculate_next_state_rk(struct system_state *state, const struct butcher_tableau *tableau, double dt);

#endif // EQUATIONS_H
