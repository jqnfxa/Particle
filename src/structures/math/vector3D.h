#ifndef VECTOR3D_H
#define VECTOR3D_H


struct vector3D
{
	double x;
	double y;
	double z;
};


/**
 * @brief stores cross product or lhs and rhs into dst [dst = lhs x rhs]
 * @param dst the destination vector
 * @param lhs left vector
 * @param rhs right vector
 */
void cross(struct vector3D *dst, const struct vector3D *lhs, const struct vector3D *rhs);


/**
 * @brief scale the vector [vector *= scalar]
 * @param vector vector to modify
 * @param scalar scalar
 */
void scale(struct vector3D *vector, double scalar);


/**
 * @brief add other vector to vector [vector = vector + other]
 * @param vector destination vector
 * @param other vector to add
 */
void add(struct vector3D *vector, const struct vector3D *other);


/**
 * @brief add scaled vector to vector [vector = vector + scalar * other]
 * @param vector destination vector
 * @param other vector to scale and add
 * @param scalar scalar
 */
void add_scaled(struct vector3D *vector, const struct vector3D *other, double scalar);

#endif // VECTOR3D_H
