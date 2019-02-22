#include "Engine\Math\RNG.hpp"
#include "Engine\Math\RawNoise.hpp"
#include "Engine\Math\MathUtils.hpp"

//  =========================================================================================
RNG::RNG()
{
}

//  =========================================================================================
RNG::~RNG()
{
	
}

//  =========================================================================================
uint RNG::GetRandomUint()
{
	uint randomValue = Get1dNoiseUint(m_position, m_seed);
	++m_position;

	return randomValue;
}

//  =========================================================================================
float RNG::GetRandomZeroToOne()
{
	float randomValue = Get1dNoiseZeroToOne(m_position, m_seed);
	++m_position;

	return randomValue;
}

//  =========================================================================================
float RNG::GetRandomNegativeOneToOne()
{
	float randomValue = Get1dNoiseNegOneToOne(m_position, m_seed);
	++m_position;

	return randomValue;
}

//  =========================================================================================
float RNG::GetRandomInRange(const float startRange, const float endRange)
{
	float randomValue = GetRandomZeroToOne();
	return RangeMapFloat(randomValue, 0.f, 1.f, startRange, endRange);

	//calls into other method. don't update position
}

//  =========================================================================================
uint RNG::GetRandomUintInRange(const uint startRange, const uint endRange)
{
	float randomValue = GetRandomZeroToOne();

	//add one to the end range because we are going to round down, otherwise the last element won't be ever possible
	float rangeMappedFloat =  RangeMapFloat(randomValue, 0.f, 1.f, (uint)startRange, ((uint)endRange) + 1.f);

	//fine because this will always be positive;
	return (uint)rangeMappedFloat;

	//calls into other method. don't update position
}

//  =========================================================================================
bool RNG::FlipCoin()
{
	float value = 0.f;
	
	// roll until we get a non zero value (otherwise one is advantaged)
	while(value == 0.f)
	{
		value = GetRandomNegativeOneToOne();
	}

	if(value > 0)
		return true;
	else
		return false;	

	//calls into other method. don't update position
}