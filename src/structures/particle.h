#ifndef PARTICLE_H
#define PARTICLE_H

#include "math/vector3D.h"


struct particle
{
	struct vector3D r;
	struct vector3D v;

	const double q;
	const double m;
};

#endif // PARTICLE_H
