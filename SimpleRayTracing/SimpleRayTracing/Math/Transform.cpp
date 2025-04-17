#include <cmath>
#include "Transform.h"
#include "Constants.h"


Vec3 Transform::local_to_global(const Vec3& vec) {
	return to_global * vec;
}

Vec3 Transform::global_to_local(const Vec3& vec) {
	return to_local * vec;
}
void Transform::translate(const Vec3& translation_vec) {

	//Translation matrices are 4x4
	Matrix4 local_translation_matrix{};
	local_translation_matrix[0][3] = -translation_vec[0];
	local_translation_matrix[1][3] = -translation_vec[1];
	local_translation_matrix[2][3] = -translation_vec[2];
	
	this->to_local = this->to_local* local_translation_matrix;

	Matrix4 global_translation_matrix{};
	global_translation_matrix[0][3] = translation_vec[0];
	global_translation_matrix[1][3] = translation_vec[1];
	global_translation_matrix[2][3] = translation_vec[2];

	this->to_global =  global_translation_matrix * this->to_global;

}

void Transform::scale(const Vec3& scale_vec) {

	//Translation matrices are 4x4
	Matrix4 local_scale_matrix{};
	local_scale_matrix[0][3] = -scale_vec[0];
	local_scale_matrix[1][3] = -scale_vec[1];
	local_scale_matrix[2][3] = -scale_vec[2];

	this->to_local = this->to_local * local_scale_matrix;

	Matrix4 global_scale_matrix{};
	global_scale_matrix[0][3] = scale_vec[0];
	global_scale_matrix[1][3] = scale_vec[1];
	global_scale_matrix[2][3] = scale_vec[2];

	this->to_global =  global_scale_matrix * this->to_global;


}

//https://en.wikipedia.org/wiki/Rotation_matrix
void Transform::rotate(double x, double y, double z) {

	//get radians
	double costheta_x = std::cos(Constants::PI * x / 180);
	double sintheta_x = std::sin(Constants::PI * x / 180);
	double costheta_y = std::cos(Constants::PI * y / 180);
	double sintheta_y = std::sin(Constants::PI * y / 180);
	double costheta_z = std::cos(Constants::PI * z / 180);
	double sintheta_z = std::sin(Constants::PI * z / 180);

	Matrix4 rotation_x{}, rotation_y{}, rotation_z{};

	rotation_x[1][1] = costheta_x;
	rotation_x[1][2] = -sintheta_x;
	rotation_x[2][1] = sintheta_x;
	rotation_x[2][2] = costheta_x;

	rotation_y[0][0] = costheta_y;
	rotation_y[0][2] = sintheta_y;
	rotation_y[2][0] = -sintheta_y;
	rotation_y[2][2] = costheta_y;

	rotation_z[0][0] = costheta_z;
	rotation_z[0][1] = -sintheta_z;
	rotation_z[1][0] = sintheta_z;
	rotation_z[1][1] = costheta_z;

	Matrix4 rotation = rotation_x * rotation_y * rotation_z;

	this->to_local = this->to_local * rotation;
	this->to_local.process_small_numbers();
	this->to_global = rotation.transpose() * this->to_global;
	this->to_global.process_small_numbers();

}