#pragma once
#include "Engine\Core\EngineCommon.hpp"

class RNG
{
public:
	RNG();
	~RNG();

	void SetSeed(uint seed){ m_seed = seed; }
	void ResetSeed(){ m_seed = 0; }
	void SetPosition(const int position){ m_position = position; }
	void ResetPosition(){ m_position = 0; }

	uint GetRandomUint();
	float GetRandomZeroToOne();
	float GetRandomNegativeOneToOne();
	float GetRandomInRange(const float startRange, const float endRange);
	uint GetRandomUintInRange(const uint startRange, const uint endRange);
	bool FlipCoin();

private:
	int m_position = 0;
	uint m_seed = 0;
};

