#pragma once
#include <cmath>
#include "MiscMath.h"

class TVector
{
public:
	float x, y;

	TVector()
		: x(0.f)
		, y(0.f)
	{}

	TVector(const float& x, const float& y)
		: x(x)
		, y(y)
	{}

	// magnitude/length
	float mag() {
		return sqrt((x * x) + (y * y));
	}

	// normalise
	void normalise() {
		x /= mag();
		y /= mag();
	}

	// get directional angle
	float getArcTangent() {
		return atan2(y, x);
	}
	// get actual angle from x=0 in degrees
	float getAngle() {
		float angle = 0.f;
		if (x < 0) {
			angle = MiscMath::getPI() + atan(y/x);
		} else if (x > 0 && y >= 0) {
			angle = atan(y/x);
		} else if (x > 0 && y < 0) {
			angle = (2.f*MiscMath::getPI()) + atan(y/x);
		} else if (x == 0 && y == 0) {
			angle = 0.f;
		} else if (x == 0 && y >= 0) {
			angle = 90.f;
		} else {
			angle = 270.f;
		}
		return angle;
	}
	
	// get distance
	float getDistance(const TVector& v) {
		return sqrt(((v.x - x) * (v.x - x)) + ((v.y - y) * (v.y - y)));
	}
	float getDistance(const int& x, const int& y) {
		return sqrt(((x - this->x) * (x - this->x)) + ((y - this->y) * (y - this->y)));
	}

	// overloaded arithmetic opeators
	TVector operator+(const TVector& v) {
		return TVector(v.x + x, v.y + y);
	}
	TVector operator-(const TVector& v) {
		return TVector(v.x - x, v.y - y);
	}
	TVector operator*(const TVector& v) {
		return TVector(v.x * x, v.y * y);
	}
	TVector operator/(const TVector& v) {
		return TVector(v.x / x, v.y / y);
	}
	TVector operator*(const float& f) {
		return TVector(f * x, f * y);
	}
	TVector operator/(const float& f) {
		return TVector(f / x, f / y);
	}
	
	// overoaded compound operators
	// vector with vector
	TVector& operator+=(const TVector& v) {
		this->x += v.x;
		this->y += v.y;
		return *this;
	}
	TVector& operator-=(const TVector& v) {
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	}
	TVector& operator*=(const TVector& v) {
		this->x *= v.x;
		this->y *= v.y;
		return *this;
	}
	TVector& operator/=(const TVector& v) {
		this->x /= v.x;
		this->y /= v.y;
		return *this;
	}
	// vector with float
	TVector& operator+=(const float& f) {
		this->x += f;
		this->y += f;
		return *this;
	}
	TVector& operator-=(const float& f) {
		this->x -= f;
		this->y -= f;
		return *this;
	}
	TVector& operator*=(const float& f) {
		this->x *= f;
		this->y *= f;
		return *this;
	}
	TVector& operator/=(const float& f) {
		this->x /= f;
		this->y /= f;
		return *this;
	}
};