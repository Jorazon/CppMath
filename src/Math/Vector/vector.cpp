#include <cmath>
#include <stdexcept>

#include "Vector.hpp"

Vector::Vector(std::vector<double> p_array)
{
	array = p_array;
}

Vector Vector::operator*(double p_scalar)
{
	Vector copy = *this;

	for (size_t i = 0; i < copy.array.size(); i++)
	{
		copy.array.at(i) *= p_scalar;
	}

	return copy;
}

Vector Vector::operator/(double p_scalar)
{
	return *this * (1.0 / p_scalar);
}

Vector Vector::operator+(Vector p_V)
{
	Vector copy = *this;

	for (size_t i = 0; i < copy.array.size(); i++)
	{
		copy.array.at(i) += p_V.array.at(i);
	}

	return copy;
}

Vector Vector::operator-(Vector p_V)
{
	return *this + (p_V * -1.0);
}

/**
 * Dot product of two vectors
 * \param p_Va First vector
 * \param p_Vb Second vector
 * \returns dot product
 */
double Vector::dot(Vector p_Va, Vector p_Vb)
{
	if (p_Va.array.size() != p_Vb.array.size())
		throw std::invalid_argument("Dimension mismathch");

	double squaresum = 0;

	for (size_t i = 0; i < p_Va.array.size(); i++)
	{
		squaresum += p_Va.array.at(i) * p_Vb.array.at(i);
	}

	return squaresum;
}

/**
 * Vector length
 * \returns length
 */
double Vector::length()
{
	//length of a vector is the square root of it's dot product with itself
	return std::sqrt(dot(*this, *this));
}

/**
 * Normalized direction vector
 * \returns Vector with same direction but length of 1
 */
Vector Vector::normalized()
{
	return *this / length();
}

/**
 * Distance between two point vectors
 * \param p_Va First vector
 * \param p_Vb Second vector
 * \returns distance
 */
double Vector::distance(Vector p_Va, Vector p_Vb)
{
	//The distance between two point vectors is
	//the square root of the dot product of their difference with itself
	return (p_Vb - p_Va).lenght();
}

/**
 * Angle between two direction vectors
 * \param p_Va First vector
 * \param p_Vb Second vector
 * \returns angle in radians
 */
double Vector::angle(Vector p_Va, Vector p_Vb)
{
	//The angle between two direction vectors is
	//the inverse cosine of their dot product
	//divided by the product of their lengths
	return std::acos(dot(p_Va, p_Vb) / (p_Va.length() * p_Vb.length()));
}
