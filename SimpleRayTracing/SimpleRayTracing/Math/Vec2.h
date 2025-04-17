#pragma once

class Vec2 {
public:
	double m_x{};
	double m_y{};
	//contructors
	Vec2()=default;
	Vec2(double x, double y);
	Vec2(const Vec2& other);
	//copy assignment
	Vec2& operator=(const Vec2& other);
	//methods
	double length();
	Vec2 normalize();
	Vec2 neg();
	double dot(const Vec2& other);
	void print();
	//operators
	bool operator==(const Vec2& other)const;
	bool operator!=(const Vec2& other) const;
	Vec2 operator+(const Vec2& right) const;
	Vec2 operator-(const Vec2& right) const;
	Vec2 operator*(const float& other) const;
	Vec2 operator/(const float& other) const;

};
