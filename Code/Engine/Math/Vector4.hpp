#pragma once
#include <math.h>
#include "engine\math\MathUtils.hpp"
#include "Engine\Math\Vector3.hpp"
#include "Engine\Core\Rgba.hpp"

class Vector3;
//-----------------------------------------------------------------------------------------------
class Vector4
{
public:
	// Construction/Destruction
	Vector4();											// default constructor: do nothing (for speed)
	~Vector4() {}											// destructor: do nothing (for speed)
												
	Vector4( const Vector4& copyFrom );						// copy constructor (from another vec4)
	explicit Vector4( float initialX, float initialY, float initialZ, float initialW );		// explicit constructor (from x, y, z, w)
	explicit Vector4( Vector3 vec, float appendedW);
	explicit Vector4(Rgba color);

	// Operators
	const Vector4 operator+(const Vector4& vecToAdd) const;		// vec3 + vec3
	const Vector4 operator-(const Vector4& vecToSubtract) const;	// vec3 - vec3
	const Vector4 operator*(float uniformScale) const;			// vec3 * float
	const Vector4 operator*(const Vector4& uniformScale) const;			// vec3 * float
	const Vector4 operator/(float inverseScale) const;			// vec3 / float
	const Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }// -vec3
	void operator*=(const Vector4& vecToMultiply);
	void operator+=(const Vector4& vecToAdd);						// vec4 += vec4
	void operator-=(const Vector4& vecToSubtract);				// vec4 -= vec4
	void operator*=(const float uniformScale);					// vec4 *= float
	void operator/=(const float uniformDivisor);					// vec4 /= float
	void operator=(const Vector4& copyFrom);						// vec4 = vec4
	bool operator==(const Vector4& compare) const;				// vec4 == vec4
	bool operator!=(const Vector4& compare) const;				// vec4 != vec4

	void SetFromText(const char * text);

	float GetLength() const;
	float Dot(const Vector4& dotVector);
	float NormalizeAndGetLength();
	Vector4 GetNormalized() const;
	void Normalize();

public: // NOTE: this is one of the few cases where we break both the "m_" naming rule AND the avoid-public-members rule
	float x;
	float y;
	float z;
	float w;

	static const Vector4 IDENTITY_POINT_TRANSLATION;
	static const Vector4 IDENTITY_VECTOR_TRANSLATION;

	static const Vector4 ZERO;
	static const Vector4 ONE;
};

const Vector4 Interpolate(const Vector4& start, const Vector4& end, float fractionTowardEnd);