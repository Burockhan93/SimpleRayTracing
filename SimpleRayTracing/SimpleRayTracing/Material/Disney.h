#pragma once

#include "Material.h"
#include "..\Utils\EnvironmentTracer.h"
//#include "..\Light\DisneyBRDF.h"

class DisneyBRDF;

class Disney : public Material {
public:
	//members
    Vec3 m_baseColor = Vec3{ 1 };
    double m_metallic = 0;
    double m_subsurface = 0;
    double m_specular = 0.5;
    double m_roughness = 0;
    double m_specularTint = 0;
    double m_anisotropic = 0;
    double m_sheen = 0;
    double m_sheenTint = 0;
    double m_clearcoat = 0;
    double m_clearcoatGloss = 0;
    EnvironmentTracer m_etr;
    DisneyBRDF*   m_brdf;


	//constructor
    Disney();
    Disney(double baseColor,
        double metallic,
        double subsurface,
        double specular,
        double roughness,
        double specularTint,
        double anisotropic,
        double sheen,
        double sheenTint,
        double cleaercoat,
        double clearcoatGloss);
    ~Disney()=default;

    Disney(const Disney& other);
    Disney& operator=(const Disney& other);

    //methods

    virtual Vec3 direct_shade(Hit& hit, World& world, int depth) override;
    virtual Vec3 indirect_shade(Hit& hit, World& world, int depth) override;

};