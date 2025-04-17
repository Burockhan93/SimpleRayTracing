#include <cmath>
#include <iostream>
#include "Vec2.h"


Vec2::Vec2(double x, double y) : m_x{ x }, m_y{ y } {}
Vec2::Vec2(const Vec2& other) {
	m_x = other.m_x;
	m_y = other.m_y;
}
Vec2& Vec2::operator=(const Vec2& other) {
	if (this == &other)
		return *this;

	m_x = other.m_x;
	m_y = other.m_y;
	return *this;

}
double Vec2::length() {
	return std::sqrt(m_x * m_x + m_y * m_y);
}
Vec2 Vec2::normalize() {
	return *this / length();
}
Vec2 Vec2::neg() {
	return *this * -1;
}
double Vec2::dot(const Vec2& v1) {
	return v1.m_x * m_x + v1.m_y * m_y;
}
void Vec2::print() {
	std::cout <<'(' <<m_x<<','<< ' ' << m_y<<')' << std::endl;
}
bool Vec2::operator==(const Vec2& other)const {
	return (this->m_x == other.m_x) && (this->m_y == other.m_y);
}

bool Vec2::operator!=(const Vec2& other) const {
	return !(*this == other);
}
Vec2 Vec2::operator+(const Vec2& other) const {
	return Vec2(m_x + other.m_x, m_y + other.m_y);
}
Vec2 Vec2::operator-(const Vec2& other) const {
	return Vec2(m_x - other.m_x, m_y - other.m_y);
}
Vec2 Vec2::operator*(const float& other) const {
	return Vec2(this->m_x * other, this->m_y * other);
}
Vec2 Vec2::operator/(const float& other) const {
	return Vec2(this->m_x / other, this->m_y / other);
}
