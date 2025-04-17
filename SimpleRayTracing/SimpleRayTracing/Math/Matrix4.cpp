#include <cstdlib>
#include <ctime>
#include "Matrix4.h"
#include "Constants.h"



Matrix4::Matrix4() {
	//default constructor is identity
	set_identity();
}
Matrix4::Matrix4(const Matrix4& matrix) {
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m_matrix[i][j] = matrix.get_matrix(i, j);
		}
	}
}
Matrix4& Matrix4::operator=(const Matrix4& other) {
	if (this == &other) return *this;

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m_matrix[i][j] = other[i][j];
		}
	}
	return *this;

}
Matrix4 Matrix4::operator*(const Matrix4& other) {
	Matrix4 result;

	for (size_t i = 0; i < 4; i++)
	{

		for (size_t j = 0; j < 4; j++)
		{
			double sum{ 0 };
			for (size_t k = 0; k < 4; k++)
			{
				sum += m_matrix[i][k] * other[k][j];
			}
			result[i][j] = sum;
		}
	}
	return result;

}
Vec3 Matrix4::operator*(const Vec3& vec) {

	return Vec3{
		m_matrix[0][0] * vec[0] + m_matrix[0][1] * vec[1] + m_matrix[0][2] * vec[2],
		m_matrix[1][0] * vec[0] + m_matrix[1][1] * vec[1] + m_matrix[1][2] * vec[2],
		m_matrix[2][0] * vec[0] + m_matrix[2][1] * vec[1] + m_matrix[2][2] * vec[2]

	};
}

Matrix4 Matrix4::transpose() {
	Matrix4 result = *this;
	for (int i = 0; i < 4; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			std::swap(result.m_matrix[i][j], result.m_matrix[j][i]);
		}
	}
	return result;
}
void Matrix4::process_small_numbers() {
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if(std::abs(m_matrix[i][j])<Constants::kEPSILON)
				m_matrix[i][j] = .0;
		}
	}
}
void Matrix4::random_fill() {
	std::srand(std::time(0));
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m_matrix[i][j] = static_cast<double>(std::rand() % 11);
		}
	}
}
void Matrix4::print() {
	for (size_t i = 0; i < 16; i++)
	{
		int x, y;
		y = i % 4;
		x = i / 4;
		std::cout << m_matrix[x][y] << '\t';
		if (i > 0 && y == 3) std::cout << '\n';
	}
	std::cout << std::endl;
}
void Matrix4::set_identity() {
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (i == j) m_matrix[i][j] = 1.0;
			else m_matrix[i][j] = .0;
		}
	}
}