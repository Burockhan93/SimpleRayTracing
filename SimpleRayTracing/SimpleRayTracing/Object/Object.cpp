#include "Object.h"

Object::Object(Material* mat) : m_shader{ mat } {}
Object::Object(Object& other): m_shader{other.m_shader}{}
Object::~Object() { delete m_shader; }
Object& Object::operator=(const Object& other) {
	if (this == &other)
		return *this;
	m_shader = other.m_shader;
}
Vec3 Object::get_sample() {
	return Vec3{};
}
Vec3 Object::get_normal(const Vec3& point) {
	return Vec3{};
}
double Object::get_pdf() {
	return .0;
}
void Object::add_object(Object* object) {

}
