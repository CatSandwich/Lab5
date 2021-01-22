#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <functional>

#include "CalculatedValue.h"

class UpgradeType
{
	public:

	unsigned int Level;
	std::string Name;

	std::vector<std::string> Names;
	std::vector<std::string> Descriptions;
	std::vector<int> Costs;
	std::vector<std::function<void()>> Callbacks;

	void Upgrade();
};