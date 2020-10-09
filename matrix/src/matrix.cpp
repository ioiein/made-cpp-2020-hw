#include "matrix.h"

using namespace task;


Matrix::Matrix()
{
	rows_count = 1;
	columns_count = 1;
	matrix = new double* [1];
	matrix[0] = new double[1];
	matrix[0][0] = 1.0;
}

Matrix::Matrix(size_t rows, size_t columns)
{
	rows_count = rows;
	columns_count = columns;
	matrix = new double* [rows_count];
	for (size_t i = 0; i < rows_count; i++)
	{
		matrix[i] = new double[columns_count];
	}
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < columns_count; j++)
		{
			if (i == j)
			{
				matrix[i][j] = 1.0;
			}
			else
			{
				matrix[i][j] = 0.0;
			}
		}
	}
}

Matrix::Matrix(const Matrix& copy)
{
	rows_count = copy.rows_count;
	columns_count = copy.columns_count;
	matrix = new double* [rows_count];
	for (size_t i = 0; i < rows_count; i++)
	{
		matrix[i] = new double[columns_count];
	}
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < columns_count; j++)
		{
			matrix[i][j] = copy.matrix[i][j];
		}
	}
}

Matrix& Matrix::operator=(const Matrix& a)
{
	for (size_t i = 0; i < rows_count; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	rows_count = a.rows_count;
	columns_count = a.columns_count;
	matrix = new double* [rows_count];
	for (size_t i = 0; i < rows_count; i++)
	{
		matrix[i] = new double[columns_count];
	}
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < columns_count; j++)
		{
			matrix[i][j] = a.matrix[i][j];
		}
	}
	return *this;
}

double& Matrix::get(size_t row, size_t col)
{
	if (row >= rows_count || row < 0 || col < 0 || col >= columns_count)
	{
		throw OutOfBoundsException();
	}
	else
	{
		return matrix[row][col];
	}
}

const double& Matrix::get(size_t row, size_t col) const
{
	if (row >= rows_count || row < 0 || col < 0 || col >= columns_count)
	{
		throw OutOfBoundsException();
	}
	else
	{
		return matrix[row][col];
	}
}

void Matrix::set(size_t row, size_t col, const double& value)
{
	if (row >= rows_count || row < 0 || col < 0 || col >= columns_count)
	{
		throw OutOfBoundsException();
	}
	else
	{
		matrix[row][col] = value;
	}
}

void Matrix::resize(size_t new_rows, size_t new_cols)
{
	Matrix new_matrix(new_rows, new_cols);
	for (size_t i = 0; i < new_rows; i++)
	{
		for (size_t j = 0; j < new_cols; j++)
		{
			if (i < rows_count && j < columns_count)
			{
				new_matrix.matrix[i][j] = matrix[i][j];
			}
			else
			{
				new_matrix.matrix[i][j] = 0.0;
			}
		}
	}
	*this = new_matrix;
	for (size_t i = 0; i < new_rows; i++)
	{
		delete[] new_matrix.matrix[i];
	}
	delete[] new_matrix.matrix;
}

double* Matrix::operator[](size_t row)
{
	return &matrix[0][row];
}
double const* Matrix::operator[](size_t row) const
{
	return &matrix[0][row];
}

Matrix& Matrix::operator+=(const Matrix& a)
{
	if (a.rows_count != rows_count || a.columns_count != columns_count)
	{
		throw SizeMismatchException();
	}
	else
	{
		for (size_t i = 0; i < rows_count; i++)
		{
			for (size_t j = 0; j < columns_count; j++)
			{
				matrix[i][j] += a.matrix[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& a)
{
	if (a.rows_count != rows_count || a.columns_count != columns_count)
	{
		throw SizeMismatchException();
	}
	else
	{
		for (size_t i = 0; i < rows_count; i++)
		{
			for (size_t j = 0; j < columns_count; j++)
			{
				matrix[i][j] -= a.matrix[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& a)
{
	if (a.rows_count != columns_count || a.columns_count != rows_count)
	{
		throw SizeMismatchException();
	}
	else
	{
		Matrix new_matrix(rows_count, rows_count);
		for (size_t i = 0; i < rows_count; i++)
		{
			new_matrix.matrix[i][i] = 0;
		}
		for (size_t i = 0; i < rows_count; i++)
		{
			for (size_t j = 0; j < rows_count; j++)
			{
				for (size_t s = 0; s < columns_count; s++)
				{
					new_matrix.matrix[i][j] += matrix[i][s] * a.matrix[s][j];
				}
			}
		}
		*this = new_matrix;
		for (size_t i = 0; i < rows_count; i++)
		{
			delete[] new_matrix.matrix[i];
		}
		delete[] new_matrix.matrix;
		return *this;
	}
}

Matrix& Matrix::operator*=(const double& number)
{
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < columns_count; j++)
		{
			matrix[i][j] *= number;
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& a) const
{
	if (a.rows_count != rows_count || a.columns_count != columns_count)
	{
		throw SizeMismatchException();
	}
	else
	{
		Matrix new_matrix(*this);
		new_matrix += a;
		return new_matrix;
	}
}

Matrix Matrix::operator-(const Matrix& a) const
{
	if (a.rows_count != rows_count || a.columns_count != columns_count)
	{
		throw SizeMismatchException();
	}
	else
	{
		Matrix new_matrix(*this);
		new_matrix -= a;
		return new_matrix;
	}
}

Matrix Matrix::operator*(const Matrix& a) const
{
	if (a.rows_count != columns_count || a.columns_count != rows_count)
	{
		throw SizeMismatchException();
	}
	else
	{
		Matrix new_matrix(rows_count, rows_count);
		for (size_t i = 0; i < rows_count; i++)
		{
			new_matrix[i][i] = 0;
		}
		for (size_t i = 0; i < rows_count; i++)
		{
			for (size_t j = 0; j < rows_count; j++)
			{
				for (size_t s = 0; s < columns_count; s++)
				{
					new_matrix[i][j] += matrix[i][s] * a.matrix[s][j];
				}
			}
		}
		return new_matrix;
	}
}
Matrix Matrix::operator*(const double& a) const
{
	Matrix new_matrix(*this);
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < columns_count; j++)
		{
			new_matrix[i][j] *= a;
		}
	}
	return new_matrix;
}

Matrix Matrix::operator-() const
{
	Matrix new_matrix(*this);
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < columns_count; j++)
		{
			new_matrix.matrix[i][j] *= -1;
		}
	}
	return new_matrix;
}

Matrix Matrix::operator+() const
{
	Matrix new_matrix(*this);
	return new_matrix;
}

double Matrix::det() const
{
	if (rows_count != columns_count)
	{
		throw SizeMismatchException();
	}
	else
	{
		int n = rows_count;
		int det = 0;
		Matrix submatrix(n - 1, n - 1);
		if (n == 2)
			return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
		else {
			for (int x = 0; x < n; x++) {
				int subi = 0;
				for (int i = 1; i < n; i++) {
					int subj = 0;
					for (int j = 0; j < n; j++) {
						if (j == x)
							continue;
						submatrix.matrix[subi][subj] = matrix[i][j];
						subj++;
					}
					subi++;
				}
				det = det + (pow(-1, x) * matrix[0][x] * submatrix.det());
			}
		}
		return det;
	}
}

void Matrix::transpose()
{
	Matrix new_matrix(columns_count, rows_count);
	for (size_t i = 0; i < columns_count; i++)
	{
		for (size_t j = 0; j  < rows_count; j ++)
		{
			new_matrix.matrix[i][j] = matrix[j][i];
		}
	}
	*this = new_matrix;
	for (size_t i = 0; i < columns_count; ++i)
	{
		delete[] new_matrix.matrix[i];
	}
	delete[] new_matrix.matrix;
}

Matrix Matrix::transposed() const
{
	Matrix new_matrix(columns_count, rows_count);
	for (size_t i = 0; i < columns_count; i++)
	{
		for (size_t j = 0; j < rows_count; j++)
		{
			new_matrix.matrix[i][j] = matrix[j][i];
		}
	}
	return new_matrix;
}

double Matrix::trace() const
{
	if (rows_count != columns_count)
	{
		throw SizeMismatchException();
	}
	else
	{
		double result = 0;
		for (size_t i = 0; i < rows_count; i++)
		{
			result += matrix[i][i];
		}
		return result;
	}
}

bool Matrix::operator==(const Matrix& a) const
{
	if (rows_count != a.rows_count || columns_count != a.columns_count)
	{
		return false;
	}
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < columns_count; j++)
		{
			if (matrix[i][j] - a.matrix[i][j] > EPS || a.matrix[i][j] - matrix[i][j] > EPS)
			{
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& a) const
{
	if (rows_count != a.rows_count || columns_count != a.columns_count)
	{
		return true;
	}
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < columns_count; j++)
		{
			if (matrix[i][j] - a.matrix[i][j] > EPS || a.matrix[i][j] - matrix[i][j] > EPS)
			{
				return true;
			}
		}
	}
	return false;
}

std::ostream& task::operator<<(std::ostream& output, const Matrix& matrix)
{
	for (size_t i = 0; i < matrix.rows_count; i++)
	{
		for (size_t j = 0; j < matrix.columns_count; j++)
		{
			output << matrix[i][j] << ' ';
		}
		output << '\n';
	}
	return output;
}

std::istream& task::operator>>(std::istream& input, Matrix& matrix)
{
	size_t n, m;
	input >> n >> m;
	matrix.resize(n, m);
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			input >> matrix[i][j];
		}
	}
	return input;
}

Matrix task::operator*(const double& a, const Matrix& b)
{
		Matrix new_matrix(b);
		for (size_t i = 0; i < b.rows_count; i++)
		{
			new_matrix[i][i] = 0;
		}
		for (size_t i = 0; i < b.rows_count; i++)
		{
			for (size_t j = 0; j < b.columns_count; j++)
			{
				new_matrix[i][j] *= a;
			}
		}
		return new_matrix;
}

std::vector<double> Matrix::getRow(size_t row)
{
	if (row < 0 || row >= rows_count)
	{
		throw SizeMismatchException();
	}
	else
	{
		std::vector<double> line;
		line.reserve(columns_count);
		for (size_t i = 0; i < columns_count; i++)
		{
			line.push_back(matrix[row][i]);
		}
		return line;
	}
}
std::vector<double> Matrix::getColumn(size_t column)
{
	if (column < 0 || column >= columns_count)
	{
		throw SizeMismatchException();
	}
	else
	{
		std::vector<double> pillar;
		pillar.reserve(rows_count);
		for (size_t i = 0; i < rows_count; i++)
		{
			pillar.push_back(matrix[i][column]);
		}
		return pillar;
	}
}

