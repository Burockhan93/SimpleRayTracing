#pragma once

#include "..\Math\Vec3.h"
#include "..\Math\Ray.h"
#include "WorldSettings.h"

class Camera {
private:
    const int width = WorldSettings::width, height= WorldSettings::height;
	const double m_distance{ 1 };
	Vec3 m_eye{};
	Vec3 m_up{};
	Vec3 m_lookat{};
	Vec3 m_direction{};
	double m_fovy{};//given ins angle
	double m_aspect{};//width/height
	Vec3 m_upper_corner{};
	double m_horizontal{};//full view variables
	double m_vertical{};
	Vec3 m_x{}, m_y{}, m_z{};

public:
#pragma region getter_setter
    // Getter and Setter for m_eye
    const Vec3& get_eye() const { return m_eye; }
    void set_eye(const Vec3& eye) { m_eye = eye; }

    // Getter and Setter for m_up
    const Vec3& get_up() const { return m_up; }
    void set_up(const Vec3& up) { m_up = up; }

    // Getter and Setter for m_lookat
    const Vec3& get_lookat() const { return m_lookat; }
    void set_lookat(const Vec3& lookat) { m_lookat = lookat; }

    // Getter and Setter for m_direction
    void set_direction(const Vec3& direction) { m_direction = direction; }

    // Getter and Setter for m_fovy
    double get_fovy() const { return m_fovy; }
    void set_fovy(double fovy) { m_fovy = fovy; }

    // Getter and Setter for m_aspect
    double get_aspect() const { return m_aspect; }
    void set_aspect(double aspect) { m_aspect = aspect; }

    // Getter and Setter for m_upper_corner
    const Vec3& get_upperCorner() const { return m_upper_corner; }
    void set_upperCorner(const Vec3& upperCorner) { m_upper_corner = upperCorner; }

    // Getter and Setter for m_horizontal
    double get_horizontal() const { return m_horizontal; }
    void set_horizontal(double horizontal) { m_horizontal = horizontal; }

    // Getter and Setter for m_vertical
    double get_vertical() const { return m_vertical; }
    void set_vertical(double vertical) { m_vertical = vertical; }

    // Getter and Setter for m_x
    const Vec3& get_x() const { return m_x; }
    void set_x(const Vec3& x) { m_x = x; }

    // Getter and Setter for m_y
    const Vec3& get_y() const { return m_y; }
    void set_y(const Vec3& y) { m_y = y; }

    // Getter and Setter for m_z
    const Vec3& get_z() const { return m_z; }
    void set_z(const Vec3& z) { m_z = z; }

    // Note: m_distance is const and does not have a setter.
    double get_distance() const { return m_distance; }

#pragma endregion

    //constructors

    Camera() = default;
    Camera(Vec3 lookfrom, Vec3 lookto, double fovy);
    Camera(const Camera& other);
    ~Camera() = default;

    //methods

    Ray construct_ray(int i, int j);

    //operators

    Camera& operator=(const Camera& other);

};
