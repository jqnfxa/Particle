#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include "../math/vector3D.h"
#include "../tables/tableau.h"
#include "particle.h"
#include "time.h"


struct system_state
{
	struct particle particle;
	struct vector3D E;
	struct vector3D B;

	struct butcher_tableau tableau;
	struct time time;
};

#endif // SYSTEM_STATE_H
