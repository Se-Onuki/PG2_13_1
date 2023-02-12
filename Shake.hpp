#pragma once

#include "Math/Vector2.hpp"
#include "Math/PolarCoordinates.hpp"
#include "Math/Math.hpp"

#include "BaseData.hpp"

class Shaker
{
public:
	Shaker() {};
	~Shaker() {};

	inline void Shake(const float &minRadian, const float &maxRadian, const float &strength, const unsigned int &flame) {
		this->minRadian = minRadian;
		this->maxRadian = maxRadian;
		this->strength = strength;

		shakeFlame = flame;
		maxShakeFlame = flame;
	}
	inline Vector2 ShakeUpdate() {
		if (shakeFlame) {
			shakeFlame--;
			return Polar2Rectangular(Polar{ GetRandom(strength * 0.3f, strength) * (shakeFlame / maxShakeFlame) ,GetRandom(minRadian,maxRadian) });
		}
		else {
			return ZeroVector2;
		}
	}

private:
	float minRadian = 0.0f;
	float maxRadian = 0.0f;
	float strength = 0.0f;

	float shakeFlame = 0.0f;
	float maxShakeFlame = 0.0f;

};

