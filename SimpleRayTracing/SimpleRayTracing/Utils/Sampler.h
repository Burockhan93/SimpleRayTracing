#pragma once
#include <random>
#include "..\Math\Vec3.h"

class Sampler {

private:
	std::mt19937 m_mt{};
	std::uniform_real_distribution<> m_dis{.0,1.0};

public:
	//constructors

	Sampler();
	~Sampler() = default;

	//copy assignment

	Sampler& operator=(const Sampler& sample) {
		if (this == &sample)
			return *this;
		m_mt = sample.m_mt;
		m_dis = sample.m_dis;
		return *this;
	}

	// methods

	Vec3 hemisphere_sample(double exp);//rando point on hemisphere
	double sample();
};