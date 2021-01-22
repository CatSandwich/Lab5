#include "OnShop.h"

namespace Events
{
	OnShop::OnShop(EventList event) : Event{ event }
	{
		DisplayHeader	= [](CType& context, RType& result)
		{
			std::cout << DisplayConstants::NEW_LINES << DisplayConstants::GAME_NAME << DisplayConstants::SHOPPING << J::TimeStr() << std::endl;
		};
		DisplayStats	= [](CType& context, RType& result)
		{
			std::cout << "Creds: " << Stats::Instance->Creds << " | " << "Rounds: " << Stats::Instance->RoundsCompleted << std::endl;
		};
		DisplayFeedback = [](CType& context, RType& result)
		{
			if (context.Feedback == "") return;

			std::cout << context.Feedback << std::endl;
		};
		DisplayShop		= [](CType& context, RType& result)
		{
			std::cout << Stats::Instance->GetShopMessage();
		};
		GetInput		= [](CType& context, RType& result)
		{
			context.Choice = J::ReadNumValidated(1, (int)Stats::Instance->Upgrades.size() + 1, "Choose an upgrade: ");
		};
		TryUpgrade		= [](CType& context, RType& result)
		{
			auto c = context.Choice;

			if (c == Stats::Instance->Upgrades.size() + 1)
			{
				result = true;
				return;
			}

			auto u = (UpgradeType*)Stats::Instance->Upgrades[c - 1];
			if (u->Level == u->Names.size())
			{
				context.Feedback = "That upgrade is already maxed";
			}
			else if (Stats::Instance->Creds >= u->Costs[u->Level])
			{
				Stats::Instance->Creds -= u->Costs[u->Level];
				u->Upgrade();
				context.Feedback = "Successfully upgraded";
			}
			else
			{
				context.Feedback = "Not enough creds.";
			}
		};

		SetCallback(OType::DISPLAY_HEADER  , DisplayHeader  );
		SetCallback(OType::DISPLAY_STATS   , DisplayStats   );
		SetCallback(OType::DISPLAY_FEEDBACK, DisplayFeedback);
		SetCallback(OType::DISPLAY_SHOP    , DisplayShop    );
		SetCallback(OType::GET_INPUT	   , GetInput       );
		SetCallback(OType::TRY_UPGRADE     , TryUpgrade     );
	}
}