#pragma once

#include "UpgradeType.h"
#include "CalculatedValue.h"

namespace Upgrades
{
	class IncreaseCredsPerRound : UpgradeType
	{
		public:
		IncreaseCredsPerRound(CalculatedValue<float>* credsPerGuess, int* roundsCompleted) : UpgradeType{}
		{
			Name = "IncreaseCredsPerRound";

			Names.push_back("Greed 1");
			Names.push_back("Greed 2");
			Names.push_back("All the Greed");

			Descriptions.push_back("Doubles the number of creds earned per guess");
			Descriptions.push_back(Descriptions[0]);
			Descriptions.push_back("Increases the number of creds earned per guess by 1% for every guess completed");

			Costs.push_back(25);
			Costs.push_back(100);
			Costs.push_back(500);

			Callbacks.push_back([=]()mutable
			{
				credsPerGuess->AddToLayer(0, Names[0], [](float& value)
					{
						value *= 2;
					})->Calculate();
			});
			Callbacks.push_back([=]()mutable
				{
					credsPerGuess->AddToLayer(0, Names[1], [](float& value)
						{
							value *= 2;
						})->Calculate();
				});
			Callbacks.push_back([=]()mutable
			{
				credsPerGuess->AddToLayer(0, Names[2], [=](float& value)
					{
						value *= 1 + *roundsCompleted / 100.0f;
					})->Calculate();
			});
		}
	};
}