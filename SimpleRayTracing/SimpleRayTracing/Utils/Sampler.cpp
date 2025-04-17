#include "..\Math\Constants.h"
#include "Sampler.h"

Sampler::Sampler() {
	std::random_device rd;
	m_mt = std::mt19937{ rd() };
}

//As exp increases, the points are concentrated more around the z-axis
// (the "top" of the hemisphere), simulating a directional bias,
// which is useful for effects like specular reflections
Vec3 Sampler::hemisphere_sample(double exp) {


    double x = m_dis(m_mt);
    double y = m_dis(m_mt);

    // Azimuth angle (random rotation around normal)
    double phi = 2.0 * Constants::PI * x;
    double cos_phi = cos(phi);
    double sin_phi = sin(phi);

    // Polar angle (biased using exponent for glossy surfaces)
    double cos_theta = pow(1.0 - y, 1.0 / (exp + 1.0));
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    // Convert to Cartesian coordinates
    double pu = sin_theta * cos_phi;
    double pv = sin_theta * sin_phi;
    double pw = cos_theta;

    return Vec3(pu, pv, pw);
}
double Sampler::sample() {
	return m_dis(m_mt);
}