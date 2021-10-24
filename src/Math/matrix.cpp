#include <algorithm>
#include <stdexcept>

#include "Matrix.hpp"
#include "Vector.hpp"

Matrix::Matrix(int p_w, int p_h)
{
	std::vector<double> col(p_h);
	std::fill(col.begin(), col.end(), 0.0);
	array.resize(p_w);
	std::fill(array.begin(), array.end(), col);
}

Matrix::Matrix(std::vector<std::vector<double>> p_array)
{
	array = p_array;
}

Matrix::Matrix(Matrix &p_M)
{
	array = p_M.array;
}

/**
 * Create NxN identity matrix
 * \param p_size side length
 * \returns NxN matrix with 1's on the diagonal
 */
Matrix Matrix::identity(int p_size)
{
	Matrix identitymatrix(p_size, p_size);
	for (size_t i = 0; i < identitymatrix.width(); i++)
	{
		identitymatrix.array[i][i] = 1.0;
	}

	return identitymatrix;
}

/**
 * Transpose (flip) the matrix
 * \returns transposed matrix
 */
Matrix Matrix::T()
{
	Matrix transposedmatrix(this->height(), this->width());

	for (size_t m = 0; m < this->width(); m++)
	{
		for (size_t n = 0; n < this->height(); n++)
		{
			transposedmatrix.array[n][m] = this->array[m][n];
		}
	}

	return transposedmatrix;
}

Matrix Matrix::operator*(double p_scalar)
{
	Matrix multipliedmatrix(this->width(), this->height());

	for (size_t m = 0; m < this->width(); m++)
	{
		for (size_t n = 0; n < this->height(); n++)
		{
			multipliedmatrix.array[m][n] = this->array[m][n] * p_scalar;
		}
	}

	return multipliedmatrix;
}

Matrix Matrix::operator/(double p_scalar)
{
	return *this * (1.0 / p_scalar);
}

Matrix Matrix::operator*(Matrix p_M)
{
	if (this->height() != p_M.width())
		throw std::invalid_argument("Size mismathch");

	Matrix multipliedmatrix(this->height(), p_M.width());

	Matrix p_transposed = p_M.T();

	for (int m = 0; m < this->height(); m++)
	{
		for (int n = 0; n < p_M.width(); n++)
		{
			multipliedmatrix.array[m][n] = Vector::dot(this->array[m], p_transposed.array[n]);
		}
	}

	return multipliedmatrix;
}

Matrix Matrix::operator+(Matrix p_M)
{
	if (this->height() != p_M.height() || this->width() != p_M.width())
		throw std::invalid_argument("Size mismathch");

	Matrix sumMatrix(this->width(), this->height());

	for (int m = 0; m < this->height(); m++)
	{
		for (int n = 0; n < this->width(); n++)
		{
			sumMatrix.array[m][n] = this->array[m][n] + p_M.array[m][n];
		}
	}

	return sumMatrix;
}

Matrix Matrix::operator-(Matrix p_M)
{
	return *this + (p_M * -1.0);
}

Matrix Matrix::submatrix(Matrix p_M, int p_i, int p_j)
{
	if (p_i > p_M.height() || p_j > p_M.width())

		if (p_M.width() < 2 && p_M.height() < 2)
			return p_M;

	Matrix submatrix(p_M.height() - 1, p_M.width() - 1);

	for (int m = 0; m < p_M.height(); m++)
	{
		if (m == p_i - 1)
			continue;
		for (int n = 0; n < p_M.width(); n++)
		{
			if (n == p_j - 1)
				continue;
			int mM = m < p_j ? m : m - 1;
			int nM = n < p_j ? n : n - 1;
			submatrix.array[mM][nM] = p_M.array[m][n];
		}
	}

	return submatrix;
}

Matrix Matrix::submatrix(int p_i, int p_j)
{
	return submatrix(*this, p_i, p_j);
}

double Matrix::determinant(Matrix p_M)
{
	p_M.testSquare();

	if (p_M.height() == 1 && p_M.width() == 1)
	{
		return p_M.array[0][0];
	}

	if (p_M.height() == 2 && p_M.width() == 2)
	{
		return p_M.array[0][0] * p_M.array[1][1] - p_M.array[1][0] * p_M.array[0][1];
	}

	double determinantSum = 0;

	for (int n = 0; n < p_M.width(); n++)
	{
		determinantSum += sign(n) * p_M.array[0][n] * p_M.submatrix(1, n + 1).determinant();
	}

	return determinantSum;
}

double Matrix::determinant()
{
	return determinant(*this);
}

double Matrix::minor(Matrix p_M, int p_i, int p_j)
{
	return p_M.submatrix(p_i, p_j).determinant();
}

double Matrix::minor(int p_i, int p_j)
{
	return minor(*this, p_i, p_j);
}

double Matrix::cofactor(Matrix p_M, int p_i, int p_j)
{
	return sign(p_i + p_j) * p_M.minor(p_i, p_j);
}

Matrix Matrix::cofactor(Matrix p_M)
{
	Matrix cofactorMatrix(p_M.height(), p_M.width());

	for (int i = 1; i <= p_M.height(); i++)
	{
		for (int j = 1; j <= p_M.width(); j++)
		{
			cofactorMatrix.array[i - 1][j - 1] = cofactor(p_M, i, j);
		}
	}

	return cofactorMatrix;
}

Matrix Matrix::adjoint(Matrix p_M)
{
	p_M.testSquare();

	return cofactor(p_M).T();
}

Matrix Matrix::adjoint()
{
	return adjoint(*this);
}

Matrix Matrix::inverse(Matrix p_M)
{
	p_M.testSquare();

	double determinant = p_M.determinant();

	if (determinant == 0)
		throw std::logic_error("Inverse does not exist");

	return p_M.adjoint() / determinant;
}

Matrix Matrix::inverse()
{
	return inverse(*this);
}

Matrix Matrix::pow(Matrix p_M, int p_power)
{
	p_M.testSquare();

	if (p_power == 0)
		return identity(p_M.height());

	Matrix *powermatrix;

	if (p_power < 0)
	{
		powermatrix = &p_M.inverse();
		p_power *= -1;
	}
	else
	{
		powermatrix = &p_M;
	}

	for (int i = 1; i < p_power; i++)
	{
		powermatrix = &(*powermatrix * p_M);
	}

	return *powermatrix;
}

Matrix Matrix::operator/(Matrix p_M)
{
	if (this->determinant() == 0 || p_M.determinant() == 0)
		throw std::logic_error("Division not possible");

	return *this * p_M.inverse();
}

double Matrix::trace(Matrix p_M)
{
	p_M.testSquare();

	double traceSum = 0;

	for (int i = 0; i < p_M.width(); i++)
	{
		traceSum += p_M.array[i][i];
	}

	return traceSum;
}
