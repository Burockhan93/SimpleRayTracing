#pragma once
#include "Vec3.h"
inline double clamp(double value,double min, double max) {
	return value<min ? min : value>max ? max : value;
}
inline double lerp(double t,double a, double b) {
	return (1 - t) * a + t * b;
}
inline Vec3 lerp(const Vec3& t, const Vec3& min,const Vec3& max) {
	return (Vec3{ 1 }-t) * min + (t * max);
}
