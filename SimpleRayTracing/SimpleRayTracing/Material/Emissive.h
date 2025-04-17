#pragma once
#include "Material.h"

class Emissive : public Material {
public:
    Emissive(double ls, Vec3 cl) :m_lightScale(ls), m_lightColor(cl)
    {
    }

    Emissive(Emissive const& mat) :m_lightScale(mat.m_lightScale), m_lightColor(mat.m_lightColor)
    {
    }

    ~Emissive()
    {
    }

    Emissive& operator= (Emissive const& mat)
    {
        if (this == &mat)
            return (*this);
        m_lightScale = mat.m_lightScale;
        m_lightColor = mat.m_lightColor;
        return (*this);
    }

    virtual Vec3 direct_shade(Hit& hitinfo, World& world, int depth)override;
    virtual Vec3 indirect_shade(Hit& hit, World& world, int depth)override;

private:
    double m_lightScale;
    Vec3 m_lightColor;

};