#pragma once
#include <iostream>
//make vec3 a base class and make point and normal inherit from it
//if itsd unnecesarry delete normal and point.

class Vec3 {
private:
public:
	double x{};
	double y{};
	double z{};
	//constructors

	Vec3()=default; // color 0,0,0
	Vec3(double x, double y, double z);
	Vec3(double x);
	Vec3(const Vec3& other);

	//destructor

	~Vec3() = default;

	//Copy assignment

	Vec3& operator= (const Vec3& other);

	//getter setter

	void set_x(double x) {
		x = x;
	}void set_y(double y) {
		y = y;
	}void set_z(double z) {
		z = z;
	}




	//Methods

	double length();
	Vec3 normalize();
	Vec3 neg();
	Vec3 neg()const;
	double dot(const Vec3& other);
	double dot(const Vec3& other)const;
	Vec3 cross(const Vec3& other);
	Vec3 cross(const Vec3& other)const;
	void print() {
		std::cout <<'(' << x << ', ' << y << ', ' << z<<')' << std::endl;
	}

	//operators
	
	double operator[](int i);
	double operator[](int i)const;

	bool operator==(const Vec3& other)const;
	bool operator!=(const Vec3& other) const;

	Vec3 operator+(const Vec3& other) const;
	Vec3 operator+(Vec3& other);

	Vec3 operator-(const Vec3& other) const;

	Vec3 operator*(const Vec3& other) const;
	Vec3 operator*(const double& other) const;

	Vec3 operator/(const double& other) const;


	////friends

	//friend Vec3 operator+(const Vec3& v1, const Vec3& v2);
	//
	//friend Vec3 operator-( const Vec3& v1, const Vec3& v2);

	//friend Vec3 operator/(const Vec3& v, const double constant);

	//friend Vec3 operator*(const Vec3& v, const double constant);
	
	friend Vec3 operator*( const double constant, const Vec3& v);

	//friend double operator*(const Vec3& v1, const Vec3& v2);//dot
	//
};

////Binary operators outside of class- dot,negate and cross could also be added here
//inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
//	return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
//}
//
//
//inline Vec3 operator-( const Vec3& v1, const  Vec3& v2) {
//	return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
//}
//
//inline Vec3 operator/(const Vec3& v, const double constant) {
//	return Vec3(v.x / constant, v.y / constant, v.z / constant);
//}
//
//
//inline Vec3 operator*(const Vec3& v, const double constant) {
//	return Vec3(v.x * constant, v.y * constant, v.z * constant);
//}
//
//
inline Vec3 operator*( const double constant, const Vec3& v ) {
	return Vec3(v.x * constant, v.y * constant, v.z * constant);
}
//
//
//inline double operator*(const Vec3& v1, const Vec3& v2) {
//	return (v1.x * v2.x+ v1.y * v2.y+ v1.z * v2.z);
//}
