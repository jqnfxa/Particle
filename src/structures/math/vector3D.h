#ifndef VECTOR3D_H
#define VECTOR3D_H


struct vector3D
{
	double x;
	double y;
	double z;
};


void cross(struct vector3D *dst, const struct vector3D *lhs, const struct vector3D *rhs);
void scale(struct vector3D *vector, double scalar);
void add(struct vector3D *vector, const struct vector3D *other);
void add_scaled(struct vector3D *vector, const struct vector3D *other, double scalar);

#endif // VECTOR3D_H
