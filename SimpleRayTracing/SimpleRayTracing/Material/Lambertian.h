#pragma once
#include "..\Math\Vec3.h"
#include "..\Math\Constants.h"
#include "BRDF.h"
//https://www.oceanopticsbook.info/view/surfaces/lambertian-brdfs
class Lambertian :public BRDF<Material> {
public:
    Lambertian() : m_diffuseReflectionCoefficient{ 0.0 }, m_diffuseColor{}
    {
    }

    ~Lambertian()
    {
    }

    Lambertian(double factor, Vec3 color) : m_diffuseReflectionCoefficient(factor), m_diffuseColor(color)
    {
    }

    Vec3 color()
    {
        return m_diffuseColor * m_diffuseReflectionCoefficient;

    }

    Vec3 f(Hit const& hit, Vec3& wi, Vec3 const& wo) {
        return (m_diffuseColor * m_diffuseReflectionCoefficient) * (1 / Constants::PI);
    }

    double pdf(Material* mat, Hit const& hit, Vec3 const& wi, Vec3 const& wo) {
        double cos_theta = std::max(0.0, hit.m_normal.dot(wi));
        return cos_theta * (1.0 / Constants::PI);
    }

    Vec3 sample_f(Material* mat, Hit const& hit, Vec3 const& wo) override {
        Vec3 w = hit.m_normal;
        Vec3 v = Vec3(0.0034, 1, 0.0071).cross(w);
        v = v.normalize();
        Vec3 u = v.cross(w);

        Vec3 p = m_sampler.hemisphere_sample(0);

        Vec3 wi = u * p.x + v * p.y + w * p.z;
        return wi.normalize();
       

    }

    Vec3 eval(Material* mat, Hit const& hit, Vec3 const& wi, Vec3 const& wo) {
        return (m_diffuseReflectionCoefficient * m_diffuseColor) * (1 / Constants::PI);
    }

    Lambertian& operator= (Lambertian const& lam)
    {
        if (this == &lam)
            return (*this);

        BRDF::operator=(lam);

        m_diffuseReflectionCoefficient = lam.m_diffuseReflectionCoefficient;
        m_diffuseColor = lam.m_diffuseColor;

        return (*this);
    }
public:
    double m_diffuseReflectionCoefficient;//diffuse reflectance coefficient
    Vec3 m_diffuseColor; //diffuse color
};