#include <stddef.h>
#include "vector3D.h"


void cross(struct vector3D *dst, const struct vector3D *lhs, const struct vector3D *rhs)
{
	if (dst == NULL || lhs == NULL || rhs == NULL)
	{
		return;
	}

	dst->x = lhs->y * rhs->z - lhs->z * rhs->y;
	dst->x = lhs->z * rhs->x - lhs->x * rhs->z;
	dst->z = lhs->x * rhs->y - lhs->y * rhs->x;
}


void scale(struct vector3D *vector, double scalar)
{
	if (vector == NULL)
	{
		return;
	}

	vector->x *= scalar;
	vector->y *= scalar;
	vector->z *= scalar;
}


void add(struct vector3D *vector, const struct vector3D *other)
{
	if (vector == NULL || other == NULL)
	{
		return;
	}

	vector->x += other->x;
	vector->y += other->y;
	vector->z += other->z;
}

void add_scaled(struct vector3D *vector, const struct vector3D *other, double scalar)
{
	if (vector == NULL || other == NULL)
	{
		return;
	}

	vector->x += other->x * scalar;
	vector->y += other->y * scalar;
	vector->z += other->z * scalar;
}
