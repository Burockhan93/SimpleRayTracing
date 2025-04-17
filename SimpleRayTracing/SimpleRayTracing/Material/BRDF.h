#pragma once
#include "..\Math\Vec3.h"
#include "..\Utils\Hit.h"
#include "Material.h"
#include "..\Utils\Sampler.h"
template<class M>
class BRDF {
public:

	BRDF() = default;
	BRDF(const BRDF<M>& other) = default;
	~BRDF() = default;
	virtual Vec3 f(Hit const& hitinfo, Vec3& wi, const Vec3& wo)
	{
		//Just return black
		return Vec3{};
	}

	virtual Vec3 sample_f(M* mat, const Hit& hit, const Vec3& wo) {
		return Vec3{};
	}

	virtual Vec3 color()
	{
		//Just return black
		return Vec3{};
	}

	BRDF<M>& operator= (const BRDF<M>& brdf)
	{
		if (this == &brdf)
			return (*this);

		m_sampler = brdf.m_sampler;
		return (*this);
	}

	virtual double pdf(M* mat, const Hit& hit, Vec3 const& wi, Vec3 const& wo) = 0;

	virtual Vec3 eval(M* mat, const Hit& hit, const Vec3& wi, const Vec3& wo) = 0;
protected:
	Sampler m_sampler;
};