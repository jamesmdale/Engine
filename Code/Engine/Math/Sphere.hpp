#pragma once
#include "Engine\Math\Vector3.hpp"

class AABB3;

class Sphere
{
public:
	Sphere();
	~Sphere();

	Sphere(const Vector3& position, float radius);

	inline Vector3 GetCenter() { return m_position; }

	void StretchToIncludePoint(float x, float y, float z);  //expand radius if (x,y) is outside
	void StretchToIncludePoint(const Vector3& point); //expand radius if point outside
	void AddPaddingToRaidus(float paddingRadius);
	void Translate(const Vector3& translation); //move the center
	void Translate(float translationX, float translationY, float translationZ); //move the center

	bool IsPointInside(float x, float y, float z) const; //is (x,y) within disc's interior?
	bool IsPointInside(const Vector3& point) const; //is "point" within disc's interior?

	void operator+=(const Vector3& translation); //move
	void operator-=(const Vector3& antiTranslation);
	Sphere operator+(const Vector3& translation) const;
	Sphere operator-(const Vector3& antiTranslation) const;
	void Sphere::operator=(const Sphere& copyFrom);

public:
	Vector3 m_position = Vector3::ZERO;
	float m_radius = 1.f;
};

bool DoSpheresOverlap(const Sphere& a, const Sphere& b);
bool DoSpheresOverlap(const Vector3& aCenter, float aRadius, const Vector3& bCenter, float bRadius);
bool DoesSphereOverlapWithAABB3(const Sphere& sphere, const AABB3& cube);
const Sphere Interpolate(const Sphere& start, const Sphere& end, float fractionTowardEnd);