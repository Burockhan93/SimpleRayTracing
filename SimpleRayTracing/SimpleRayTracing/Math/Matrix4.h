#pragma once
#include <cassert>
#include "Vec3.h"

class Matrix4 {
private:
	double m_matrix[4][4]{};
public:
	//constructors

	Matrix4();
	Matrix4(const Matrix4& matrix);
	~Matrix4() = default;

	//getter setter

	void set_matrix(int x, int y, double value) {
		assert(x >= 0 && y >= 0 && x < 4 && y < 4);
		m_matrix[x][y] = value;
	}
	double get_matrix(int x, int y) const {
		assert(x >= 0 && y >= 0 && x < 4 && y < 4);
		return m_matrix[x][y];
	}

	//copy assignment

	Matrix4& operator=(const Matrix4& matrix);

	//operators-unary

	Matrix4 operator* (const Matrix4& other);
	Vec3 operator* (const Vec3& vec);
	Matrix4 operator/(double constant);

	//access

	double* operator[](int row) {
		assert(row >= 0 && row < 4);
		return m_matrix[row];
	}
	const double* operator[](int row) const {
		assert(row >= 0 && row < 4);
		return m_matrix[row];
	}

	// methods

	Matrix4 transpose();
	void random_fill();
	void set_identity();
	void process_small_numbers();
	void print();

};