#pragma once
#include <math.h>
#include "engine\math\MathUtils.hpp"

class Vector4;
class Vector2;
class IntVector3;
class IntVector2;

//-----------------------------------------------------------------------------------------------
class Vector3
{
public:
	// Construction/Destruction
	~Vector3() {}											// destructor: do nothing (for speed)
	Vector3();											// default constructor: do nothing (for speed)
	Vector3( const Vector3& copyFrom );						// copy constructor (from another vec2)
	explicit Vector3( float initialX, float initialY, float initialZ );		// explicit constructor (from x, y)
	explicit Vector3(const float& uniformSize);
	explicit Vector3(const IntVector3& vector);
	explicit Vector3(const Vector4& vector);
	explicit Vector3(const Vector2& vector);
	explicit Vector3(const IntVector2& vector);

	// Operators
	const Vector3 operator+( const Vector3& vecToAdd ) const;		// vec3 + vec3
	const Vector3 operator-( const Vector3& vecToSubtract ) const;	// vec3 - vec3
	const Vector3 operator*( float uniformScale ) const;			// vec3 * float
	const Vector3 operator*( const Vector3& uniformScale ) const;			// vec3 * float
	const Vector3 operator/( float inverseScale ) const;			// vec3 / float
	const Vector3 operator-() const { return Vector3(-x, -y, -z ); }// -vec3
	void operator*=(const Vector3& vecToMultiply);
	void operator+=( const Vector3& vecToAdd );						// vec3 += vec3
	void operator-=( const Vector3& vecToSubtract );				// vec3 -= vec3
	void operator*=( const float uniformScale );					// vec3 *= float
	void operator/=( const float uniformDivisor );					// vec3 /= float
	void operator=( const Vector3& copyFrom );						// vec3 = vec3
	bool operator==( const Vector3& compare ) const;				// vec3 == vec3
	bool operator!=( const Vector3& compare ) const;				// vec3 != vec3
	friend Vector3 operator*( float uniformScale, const Vector3& vecToScale);	// float * vec3
	float GetLength() const;
	float Dot(const Vector3& dotVector);
	float GetLengthSquared() const;
	float NormalizeAndGetLength();
	Vector3 GetNormalized() const;
	void Normalize();
	bool CompareZero(float inclusiveMin = -0.01f, float inclusiveMax = 0.01f);

	//float GetOrientationDegrees() const;
	//static Vector3 MakeDirectionAtDegrees(float degrees);
	void SetFromText(const char* text);

public: // NOTE: this is one of the few cases where we break both the "m_" naming rule AND the avoid-public-members rule
	float x;
	float y;
	float z;

	static const Vector3 ZERO;
	static const Vector3 ONE;
	static const Vector3 RIGHT;		//x
	static const Vector3 UP;		//y
	static const Vector3 FORWARD;	//z
	static const Vector3 DEFAULT_LIGHT_ATTENUATION;
	static const Vector3 GRAVITY_FORCE; //-9.8f
};

float GetDistance(const Vector3& a, const Vector3& b);
float GetRadius(const Vector3& a);
Vector3 GetMidpoint(const Vector3& a, const Vector3& b);
float GetDistanceSquared(const Vector3& a, const Vector3& b);
Vector3 GetMin(const Vector3& a, const Vector3& b);
int MoveRegularPolygonX(float centerX, Vector3 movementVector);
int MoveRegularPolygonY(float centerY, Vector3 movementVector);
Vector3 AbsoluteValue(const Vector3& initialValue);

//const Vector3 GetProjectedVector(const Vector3& vectorToProject, const Vector3& projectOnto);
//const Vector3 GetTransformedIntoBasis (const Vector3& originalVector, const Vector3& newBasisI, const Vector3& newBasisJ);
//const Vector3 GetTransformedOutOfBasis( const Vector3& vectorInBasis, const Vector3& oldBasisI, const Vector3& oldBasisJ );
//void DecomposeVectorIntoBasis( const Vector3& originalVector,	const Vector3& newBasisI, const Vector3& newBasisJ,	Vector3& out_vectorAlongI, Vector3& out_vectorAlongJ );
//const Vector3 Reflect(const Vector3& originalVector2, const Vector3& bounceDirection);
const Vector3 Interpolate(const Vector3& start, const Vector3& end, float fractionTowardEnd);
const Vector3 SphericalInterpolate(const Vector3& start, const Vector3& end, float fractionTowardEnd);
const Vector3 SphericalInterpolateUnit(const Vector3& start, const Vector3& end, float fractionTowardEnd);