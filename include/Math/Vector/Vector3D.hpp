#pragma once
#include <vector>

#include "Vector.hpp"
#include "Matrix.hpp"

class Vector3D : public Vector
{
private:
	std::vector<double> array;

public:
	Vector3D(std::vector<double> p_array);
	~Vector3D();
	int dimension() { return 3; }
	static Vector3D cross(Vector3D p_Va, Vector3D p_Vb);
	static double tripleProduct(Vector3D p_Va, Vector3D p_Vb, Vector3D p_Vc);
};