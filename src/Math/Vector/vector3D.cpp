#include <stdexcept>

#include "Vector3D.hpp"

Vector3D::Vector3D(std::vector<double> p_array)
	: Vector(p_array)
{
	if (sizeof(p_array) / sizeof(p_array[0]) != 3)
		throw std::invalid_argument("Dimension mismatch");

	array = p_array;
}

Vector3D Vector3D::cross(Vector3D p_Va, Vector3D p_Vb)
{
	Matrix matrix({{1, 1, 1},
				   p_Va.array,
				   p_Vb.array});

	return Vector3D({Matrix::minor(matrix, 1, 1),
					 Matrix::minor(matrix, 1, 2),
					 Matrix::minor(matrix, 1, 3)});
}

double Vector3D::tripleProduct(Vector3D p_Va, Vector3D p_Vb, Vector3D p_Vc)
{
	return dot(p_Va, cross(p_Vb, p_Vc));
}
