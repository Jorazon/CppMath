#pragma once
#include <vector>

class Matrix
{
private:
	std::vector<std::vector<double>> array;
	int shape[2];
	static int sign(int n) { return n % 2 == 0 ? 1 : -1; }
	void testSquare(){if (height() != width()) throw std::invalid_argument("Non-square matrix");}
public:
	Matrix(int p_w, int p_h);
	Matrix(std::vector<std::vector<double>> p_array);
	Matrix(Matrix &p_M);
	~Matrix(){};
	int width() { return shape[0]; }
	int height() { return shape[1]; }
	static Matrix identity(int p_size);
	Matrix T();
	Matrix operator*(double p_scalar);
	Matrix operator/(double p_scalar);
	Matrix operator*(Matrix p_M);
	Matrix operator+(Matrix p_M);
	Matrix operator-(Matrix p_M);
	static Matrix submatrix(Matrix p_M, int p_i, int p_j);
	Matrix submatrix(int p_i, int p_j);
	static double determinant(Matrix p_M);
	double determinant();
	static double minor(Matrix p_M, int p_i, int p_j);
	double minor(int p_i, int p_j);
	static double cofactor(Matrix p_M, int p_i, int p_j);
	static Matrix cofactor(Matrix p_M);
	static Matrix adjoint(Matrix p_M);
	Matrix adjoint();
	static Matrix inverse(Matrix p_M);
	Matrix inverse();
	static Matrix pow(Matrix p_M, int p_power);
	Matrix operator/(Matrix p_M);
	static double trace(Matrix p_M);
};
