#include "Stats.h"

//creds is starting creds for testing purposes

Stats* Stats::Instance = nullptr;

Stats::Stats(int creds)
{
	Instance = this;

	Creds = creds;
	RoundsCompleted = 0;

	//stats
	Max = { 2, 5 };
	CredsPerGuess = { 2, 1 };

	//register upgrades here
	Upgrades = {};
	Upgrades.push_back(new Upgrades::DoubleMax(&CredsPerGuess, &Max));
	Upgrades.push_back(new Upgrades::IncreaseCredsPerRound(&CredsPerGuess, &RoundsCompleted));
	Upgrades.push_back(new Upgrades::FirstTry());
}

std::string Stats::GetShopMessage()
{
	std::ostringstream oss;
	for (uint8_t i = 0; i < Upgrades.size(); i++)
	{
		auto u = (UpgradeType*)Upgrades[i];
		if (u->Level == u->Names.size()) continue;

		oss << '\n' << i + 1 << " - " << u->Names[u->Level] << '\n';
		oss << u->Descriptions[u->Level] << '\n';
		oss << "Cost: " << u->Costs[u->Level] << '\n';
	}
	oss << '\n' << Upgrades.size() + 1 << " - Exit" << '\n' << std::endl;
	return oss.str();
}