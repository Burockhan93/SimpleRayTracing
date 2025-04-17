#pragma once
#include "Matrix4.h"

class Transform {
private:
	Matrix4 to_global{};
	Matrix4 to_local{};
public:
	//constructors

	Transform() = default;
	~Transform() = default;

	//getter

	Matrix4 get_global()const { return to_global; }
	Matrix4 get_local()const { return to_local; }

	//methods

	Vec3 local_to_global(const Vec3& vec);

	Vec3 global_to_local(const Vec3& vec);

	void translate(const Vec3& vec);
	void scale(const Vec3& vec);
	void rotate(double x, double y, double z);

};