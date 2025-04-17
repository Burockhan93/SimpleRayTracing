#include <cmath>
#include "Vec3.h"
#include <exception>

Vec3::Vec3(double x, double y, double z) :x{ x }, y{ y }, z{ z } {}
Vec3::Vec3(double x) :x{ x }, y{ x }, z{ x} {}
Vec3::Vec3(const Vec3& other) : x{ other.x }, y{ other.y }, z{ other.z } {}

double Vec3::length() { return std::sqrt(x * x + y * y + z * z); }
Vec3 Vec3::normalize()
{
	double length = this->length();
	return *this / length;
}
Vec3 Vec3::neg() {
	return *this * -1;
}
Vec3 Vec3::neg() const {
	return *this * -1;
}
double Vec3::dot(const Vec3& other) {
	return  x * other.x+y * other.y+ z * other.z ;
}double Vec3::dot(const Vec3& other) const{
	return  x * other.x+y * other.y+ z * other.z ;
}
//https://en.wikipedia.org/wiki/Cross_product
Vec3 Vec3::cross(const Vec3& other) {
	double i = y * other.z - z*other.y;
	double j = z * other.x - x*other.z;
	double k = x * other.y - y*other.x;

	return Vec3{ i, j, k };
}Vec3 Vec3::cross(const Vec3& other)const {
	double i = y * other.z - z*other.y;
	double j = z * other.x - x*other.z;
	double k = x * other.y - y*other.x;

	return Vec3{ i, j, k };
}
Vec3& Vec3::operator=(const Vec3& other) {
	if (this == &other) 
		return *this;
	this->x =  other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;

}
double Vec3::operator[](int i) {
	if(i<0 || i>2)
		throw std::out_of_range("Vectors have elements at 0 1 and 2");
	return i == 0 ? this->x : i == 1 ? this->y : this->z;
}
double Vec3::operator[](int i) const{
	if (i < 0 || i>2)
		throw std::out_of_range("Vectors have elements at 0 1 and 2");
	return i == 0 ? this->x : i == 1 ? this->y : this->z;
}
bool Vec3::operator==(const Vec3& other)const {
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}
bool Vec3::operator!=(const Vec3& other) const {
	return !(*this == other);
}
Vec3 Vec3::operator+(const Vec3& other) const {
	return Vec3{ this->x + other.x,this->y + other.y ,this->z + other.z };
}
Vec3 Vec3::operator+(Vec3& other)  {
	return Vec3{ this->x + other.x,this->y + other.y ,this->z + other.z };
}
Vec3 Vec3::operator-(const Vec3& other) const {
	return Vec3{ this->x - other.x,this->y - other.y ,this->z - other.z };
}

Vec3 Vec3::operator*(const double& other) const {
	return Vec3{ this->x * other, this->y * other,this->z * other};
}

Vec3 Vec3::operator*(const Vec3& other) const {
	return  Vec3{ this->x * other.x, this->y * other.y , this->z * other.z };
}

Vec3 Vec3::operator/(const double& other) const {
	return Vec3{ this->x / other, this->y / other,this->z / other };
}
