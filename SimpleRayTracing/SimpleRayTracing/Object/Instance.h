#pragma once
#include "Object.h"
#include "..\Math\Transform.h"
class Instance: public Object {
private:
	Transform m_transform{};
	Object* m_object{};
public:
	//constructors

	Instance();
	Instance(Object* object, Material* mat);
	~Instance();

	//methods

	bool ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) override;
	Box calculate_bb() override;
	void translate(const Vec3& vec);
	void scale(const Vec3& vec);
	void rotate(double x, double y, double z);


};