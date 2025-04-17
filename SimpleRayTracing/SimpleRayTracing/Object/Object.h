#pragma once
#include <vector>
#include "Box.h"
#include "..\Math\Vec3.h"
class Material;

class Object {
private:
	bool m_shadowCast{ true };
	Material* m_shader{};
public:
	//constructors

	Object() = default;
	Object(Material* material);
	Object(Object& other);
	virtual ~Object();//destructor m_shader referenasini silmeli

	//copy asignment

	Object& operator=(const Object& other);

	//getters setters
	Material* get_shader() const { return m_shader; }
	bool get_shadowCast() const { return m_shadowCast; }
	void set_shadowCast(bool value) { m_shadowCast = value; }
	void set_shader(Material* shader) { m_shader = shader; }
	
	//methods

	Vec3 virtual get_sample();
	Vec3 virtual get_normal(const Vec3& point);
	double virtual get_pdf();//prob debnsity function
	void virtual add_object(Object* object);

	//abstract
	Box virtual calculate_bb() = 0;
	bool virtual ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) = 0;

};
