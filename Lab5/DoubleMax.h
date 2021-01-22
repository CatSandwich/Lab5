#pragma once

#include "UpgradeType.h"
#include "CalculatedValue.h"
#include "Stats.h"

namespace Upgrades
{
	class DoubleMax : UpgradeType
	{
		public:
		DoubleMax(CalculatedValue<float>* credsPerGuess, CalculatedValue<int>* max) : UpgradeType{}
		{
			Name = "DoubleMax";

			Names.push_back("Double Up");
			Names.push_back("Double Up^2");
			Names.push_back("Double Up (Again!?!)");

			Descriptions.push_back("Doubles the max and creds earned");
			Descriptions.push_back("Doubles the max and increases creds earned by 50%");
			Descriptions.push_back("Increases the max by 150% and doubles creds earned");

			Costs.push_back(10);
			Costs.push_back(50);
			Costs.push_back(250);

			Callbacks.push_back([=]()mutable
			{
				credsPerGuess->AddToLayer(0, Names[0], [](float& value)
					{
						value *= 2;
					})->Calculate();
				max->AddToLayer(0, Names[0], [](int& value)
					{
						value *= 2;
					})->Calculate();
			});
			Callbacks.push_back([=]()mutable
			{
				credsPerGuess->AddToLayer(0, Names[1], [](float& value)
					{
						value *= 1.5f;
					})->Calculate();
				max->AddToLayer(0, Names[1], [](int& value)
					{
						value *= 2;
					})->Calculate();
			});
			Callbacks.push_back([=]()mutable
			{
				credsPerGuess->AddToLayer(0, Names[2], [](float& value)
					{
						value *= 2;
					})->Calculate();
				max->AddToLayer(0, Names[2], [](int& value)
					{
						value *= 2.5f;
					})->Calculate();
			});
		}
	};
}