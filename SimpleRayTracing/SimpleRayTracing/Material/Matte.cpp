#include "Matte.h"

Matte::Matte() :Material{} {}

Matte::Matte(Lambertian ambient, Lambertian* diffuse) :
	Material{}, m_ambient(ambient), m_diffuse(diffuse) {
}

Matte::Matte(const Matte& matte) :
	Material{}, m_diffuse(matte.m_diffuse), m_ambient(matte.m_ambient)
{
}

Vec3 Matte::direct_shade(Hit& hit, World& world, int depth) {

	//********** AMBIENT COLOR ********** \\
        //set color to ambient light.
	Vec3 color = m_ambient.color() * world.m_ambientLight->get_intensity(hit, world);

	for (Light* l : world.m_lights) {
		Vec3 lightDir = l->get_direction(hit);
		//********* CAST SHADOW RAY ********** \\
            //cast shadow ray to check if the object is in shadow.
		Ray shadowray(hit.m_hitPoint + Vec3(hit.m_normal) * Constants::kEPSILON, lightDir);

		if (!l->shadow_hit(shadowray, world)) {
			double ndotLightDir = hit.m_normal.dot(lightDir);
			Vec3 tmp;
			if (ndotLightDir > 0) {
				Vec3 df = m_diffuse->f(hit, lightDir, tmp) * ndotLightDir * l->get_intensity(hit, world);
				color = color + df;
			}
		}
	}
	return color;
}

Vec3 Matte::indirect_shade(Hit& hit, World& world, int depth) {
	Vec3 wo = hit.m_direction.neg();
	Vec3 wi = m_diffuse->sample_f(this, hit, wo);
	double pdf = m_diffuse->pdf(this, hit, wi, wo);
	Vec3 f = m_diffuse->eval(this, hit, wi, wo);

	//Create new ray
	Ray r(hit.m_hitPoint + wi * Constants::kEPSILON, wi);
	Vec3 tracedColor = m_rt.trace_ray(r, world, depth + 1);
	return (f * tracedColor * hit.m_normal.dot(wi) / pdf);
}

Matte& Matte::operator= (const Matte& matte)
{
	if (this == &matte)
		return (*this);

	Material::operator=(matte);

	m_diffuse = matte.m_diffuse;
	m_ambient = matte.m_ambient;

	return (*this);
}

