#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include "math/vector3D.h"
#include "particle.h"


struct system_state
{
	struct particle particle;
	struct vector3D E;
	struct vector3D B;
};

#endif // SYSTEM_STATE_H
