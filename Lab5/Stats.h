#pragma once

#include "CalculatedValue.h"

#include "DoubleMax.h"
#include "IncreaseCredsPerRound.h"
#include "FirstTry.h"

#include <sstream>

class Stats
{
	public:

	static Stats* Instance;

	int Creds;
	int RoundsCompleted;

	CalculatedValue<int> Max;
	CalculatedValue<float> CredsPerGuess;

	std::vector<void*> Upgrades;

	Stats(int);
	std::string GetShopMessage();
};