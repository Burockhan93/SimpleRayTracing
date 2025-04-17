#pragma once
#include "..\Light\AmbientLight.h"
#include "..\Light\Light.h"
#include "Material.h"
#include "Lambertian.h"
#include "..\Math\Constants.h"
#include "..\Utils\RayTracer.h"
class Matte : public Material {
public:
    //constructors
    Matte();
    Matte(Lambertian ambient, Lambertian* diffuse);
    Matte(Matte const& matte);
    ~Matte() = default;

    //methods
    virtual Vec3 direct_shade(Hit& hit, World& world, int depth);
    Vec3 indirect_shade(Hit& hit, World& world, int depth);
    Matte& operator= (Matte const& matte);

    //memebers
    RayTracer m_rt{};
    Lambertian* m_diffuse{};
    Lambertian m_ambient{};


};