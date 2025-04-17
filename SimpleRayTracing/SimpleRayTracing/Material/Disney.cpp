#include "Disney.h"
#include "DisneyBRDF.h"

Disney::Disney() :Material{}, m_brdf{ new DisneyBRDF{} } {}

Disney::Disney(double baseColor,
    double metallic,
    double subsurface,
    double specular,
    double roughness,
    double specularTint,
    double anisotropic,
    double sheen,
    double sheenTint,
    double clearcoat,
    double clearcoatGloss) : Material{}, m_brdf{ new DisneyBRDF{} } {

    m_baseColor = baseColor;
    m_metallic = metallic;
    m_subsurface = subsurface;
    m_specular = specular;
    m_roughness = roughness;
    m_specularTint = specularTint;
    m_anisotropic = anisotropic;
    m_sheen = sheen;
    m_sheenTint = sheenTint;
    m_clearcoat = clearcoat;
    m_clearcoatGloss = clearcoatGloss;

}

Disney::Disney(const Disney& other) : Material{}, m_brdf{other.m_brdf}
{
    m_baseColor = other.m_baseColor;
    m_metallic = other.m_metallic;
    m_subsurface = other.m_subsurface;
    m_specular = other.m_specular;
    m_roughness = other.m_roughness;
    m_specularTint = other.m_specularTint;
    m_anisotropic = other.m_anisotropic;
    m_sheen = other.m_sheen;
    m_sheenTint = other.m_sheenTint;
    m_clearcoat = other.m_clearcoat;
    m_clearcoatGloss = other.m_clearcoatGloss;
}

Disney& Disney::operator=(const Disney& other) {
    if (this == &other)
        return *this;
    Material::operator=(other);

    m_brdf = other.m_brdf;
    m_baseColor = other.m_baseColor;
    m_metallic = other.m_metallic;
    m_subsurface = other.m_subsurface;
    m_specular = other.m_specular;
    m_roughness = other.m_roughness;
    m_specularTint = other.m_specularTint;
    m_anisotropic = other.m_anisotropic;
    m_sheen = other.m_sheen;
    m_sheenTint = other.m_sheenTint;
    m_clearcoat = other.m_clearcoat;
    m_clearcoatGloss = other.m_clearcoatGloss;

    return *this;
}

Vec3 Disney::direct_shade(Hit& hit, World& world, int depth) {
    return Vec3{ };
}
Vec3 Disney::indirect_shade(Hit& hit, World& world, int depth) {
    //1 Sample point
    Vec3 wi = m_brdf->sample_f(this, hit, hit.m_direction.neg());
    Ray r{ hit.m_normal + hit.m_normal, wi};
    //2 calculate pdf
    double pdf = m_brdf->pdf(this, hit, wi, hit.m_direction.neg());
    //3 evaluate brdf
    Vec3 f = m_brdf->eval(this, hit, wi, hit.m_direction.neg());

    return f * m_etr.trace_ray(r, world, depth + 1) * hit.m_normal.dot(wi) / pdf;

}

