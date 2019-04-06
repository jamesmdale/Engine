#include "Engine\Math\Sphere.hpp"
#include "Engine\Math\AABB3.hpp"
#include "Engine\Math\MathUtils.hpp"
#include "Engine\Core\EngineCommon.hpp"

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
	this->StretchToIncludePoint(Vector3(x, y, z));
}

//  =========================================================================================
void Sphere::StretchToIncludePoint(const Vector3& point)
{
	float newRadius = GetDistance(m_position, point);
	if (newRadius > m_radius)
		m_radius = newRadius;
}

//  =========================================================================================
void Sphere::AddPaddingToRaidus(float paddingRadius)
{
	m_radius += paddingRadius;
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
	if (GetLength(point, m_position) >= m_radius)
		return true;
	else
		return false;
}

//  =========================================================================================
void Sphere::operator+=(const Vector3& translation)
{
	m_position += translation;
}

//  =========================================================================================
void Sphere::operator-=(const Vector3& antiTranslation)
{
	m_position -= antiTranslation;
}

//  =========================================================================================
Sphere Sphere::operator+(const Vector3& translation) const
{
	return Sphere(m_position + translation, m_radius);
}

//  =========================================================================================
Sphere Sphere::operator-(const Vector3& antiTranslation) const
{
	return Sphere(m_position - antiTranslation, m_radius);
}

//  =========================================================================================
void Sphere::operator=(const Sphere& copyFrom)
{
	m_position = copyFrom.m_position;
	m_radius = copyFrom.m_radius;
}

//  =========================================================================================
bool DoSpheresOverlap(const Sphere& a, const Sphere& b)
{
	float distance = GetDistance(a.m_position, b.m_position);

	if (distance <= (a.m_radius + b.m_radius))
		return true;
	else
		return false;
}

//  =========================================================================================
bool DoSpheresOverlap(const Vector3& aCenter, float aRadius, const Vector3& bCenter, float bRadius)
{
	float distance = GetDistance(aCenter, bCenter);
	if (distance <= (aRadius + bRadius))
		return true;
	return false;
}

//  =========================================================================================
bool DoesSphereOverlapWithAABB3(const Sphere& sphere, const AABB3& cube)
{
	Vector3 directionToCubeCenter = cube.GetCenter() - sphere.m_position;
	float length = directionToCubeCenter.NormalizeAndGetLength();
	UNUSED(length);

	Vector3 positionToCheck = (directionToCubeCenter * sphere.m_radius) + sphere.m_position;

	if (cube.IsPointInside(positionToCheck))
		return true;
	else
		return false;
}

//  =========================================================================================
const Sphere Interpolate(const Sphere & start, const Sphere & end, float fractionTowardEnd)
{
	return Sphere();
}
