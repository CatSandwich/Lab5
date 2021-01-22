#include "FirstTry.h"
#include "OnPlay.h"
#include "EventManager.h"

namespace Upgrades
{
	FirstTry::FirstTry()
	{
		Name = "FirstTry";

		Names.push_back("Got Lucky");
		Names.push_back("Got Lucky 2");
		Names.push_back("Got Lucky 3");

		Descriptions.push_back("If you guess the correct number first try, you get double creds.");
		Descriptions.push_back("If you guess the correct number first try, you get triple creds.");
		Descriptions.push_back("If you guess the correct number first try, you get 5x creds.");

		Costs.push_back(20);
		Costs.push_back(50);
		Costs.push_back(250);

		_onPlay = (Events::OnPlay*)(*Events::EventManagerType::Instance)[Events::EventList::OnPlay];

		Callbacks.push_back([=]() -> void
			{
				_onPlay->SetCallback(Events::OnPlay::OType::POST_GAME_FIRST_TRY, [](Events::OnPlay::CType& context, Events::OnPlay::RType& result) -> void
					{
						if(context == 1)
							result += Stats::Instance->CredsPerGuess.Value;
					});
			});
		Callbacks.push_back([=]() -> void
			{
				_onPlay->SetCallback(Events::OnPlay::OType::POST_GAME_FIRST_TRY, [](Events::OnPlay::CType& context, Events::OnPlay::RType& result) -> void
					{
						if (context == 1)
							result += Stats::Instance->CredsPerGuess.Value * 2;
					});
			});
		Callbacks.push_back([=]() -> void
			{
				_onPlay->SetCallback(Events::OnPlay::OType::POST_GAME_FIRST_TRY, [](Events::OnPlay::CType& context, Events::OnPlay::RType& result) -> void
					{
						if (context == 1)
							result += Stats::Instance->CredsPerGuess.Value * 4;
					});
			});
	}
}