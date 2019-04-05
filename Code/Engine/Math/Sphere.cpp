#include "Engine\Math\Sphere.hpp"
#include "Engine\Math\MathUtils.hpp"

//  =========================================================================================
Sphere::Sphere()
{
}

//  =========================================================================================
Sphere::~Sphere()
{
}

//  =========================================================================================
Sphere::Sphere(const Vector3& position, float radius)
{
	m_position = position;
	m_radius = radius;
}

//  =========================================================================================
void Sphere::StretchToIncludePoint(float x, float y, float z)
{

}

//  =========================================================================================
void Sphere::StretchToIncludePoint(const Vector3& point)
{

}

//  =========================================================================================
void Sphere::AddPaddingToRaidus(float paddingRadius)
{

}

//  =========================================================================================
void Sphere::Translate(const Vector3& translation)
{
	m_position += translation;
}

//  =========================================================================================
void Sphere::Translate(float translationX, float translationY, float translationZ)
{
	m_position += Vector3(translationX, translationY, translationZ);
}

//  =========================================================================================
void Sphere::AddPaddingToRadius(float paddingRadius)
{
	m_radius += paddingRadius;
}

//  =========================================================================================
bool Sphere::IsPointInside(float x, float y, float z) const
{
	Vector3 point = Vector3(x, y, z);

	if(GetLength(point, m_position) >= m_radius)
		return true;
	else
		return false;
}

//  =========================================================================================
bool Sphere::IsPointInside(const Vector3& point) const
{
	return false;
}

//  =========================================================================================
void Sphere::operator+=(const Vector3& translation)
{
}

//  =========================================================================================
void Sphere::operator-=(const Vector3& antiTranslation)
{
}

//  =========================================================================================
Sphere Sphere::operator+(const Vector3& translation) const
{
	return Sphere();
}

//  =========================================================================================
Sphere Sphere::operator-(const Vector3& antiTranslation) const
{
	return Sphere();
}

//  =========================================================================================
void Sphere::operator=(const Sphere& copyFrom)
{
	m_position = copyFrom.m_position;
	m_radius = copyFrom.m_radius;
}

//  =========================================================================================
bool DoDiscsOverlap(const Sphere& a, const Sphere& b)
{
	return false;
}

//  =========================================================================================
bool DoDiscsOverlap(const Vector3 & aCenter, float aRadius, const Vector3 & bCenter, float bRadius)
{
	return false;
}

//  =========================================================================================
bool DoesDiscOverlapWithAABB2(const Sphere & sphere, const AABB3 & cube)
{
	return false;
}

//  =========================================================================================
const Sphere Interpolate(const Sphere & start, const Sphere & end, float fractionTowardEnd)
{
	return Sphere();
}
