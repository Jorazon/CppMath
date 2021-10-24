#pragma once
#include <vector>

class Vector
{
private:
	std::vector<double> array;
	int dimension;

public:
	Vector(std::vector<double> p_array);
	~Vector();
	int dimension() { return dimension; }
	Vector operator*(double p_scalar);
	Vector operator/(double p_scalar);
	Vector operator+(Vector p_V);
	Vector operator-(Vector p_V);
	static double dot(Vector p_Va, Vector p_Vb);
	double length();
	Vector normalized();
	static double distance(Vector p_Va, Vector p_Vb);
	static double angle(Vector p_Va, Vector p_Vb);
};