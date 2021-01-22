#include "OnAction.h"
#include "EventManager.h"

namespace Events
{
	enum ChoicesEnum
	{
		INVALID,
		PLAY,
		SHOP,
		QUIT
	};

	OnActionContext::OnActionContext()
	{
		Choice = -1;
		EventManager = EventManagerType::Instance;
		Choices.push_back("Play");
		Choices.push_back("Shop");
		Choices.push_back("Quit");
	}

	OnAction::OnAction(EventList event) : Event{ event }
	{
		DrawHeader   = [](CType& context, RType& result) -> void
		{
			std::cout << DisplayConstants::NEW_LINES << DisplayConstants::GAME_NAME << J::TimeStr() << std::endl;
		};
		DisplayStats = [](CType& context, RType& result) -> void
		{
			std::cout << "Creds: " << Stats::Instance->Creds << " | Rounds: " << Stats::Instance->RoundsCompleted << std::endl;
		};
		ShowChoices  = [](CType& context, RType& result) -> void
		{
			for (unsigned int i = 0; i < context.Choices.size(); i++)
			{
				std::cout << i + 1 << " - " << context.Choices[i] << std::endl;
			}
			std::cout << "Choose an option: ";
		};
		GetInput     = [](CType& context, RType& result) -> void
		{
			int min = 1;
			int max = context.Choices.size();
			context.Choice = J::ReadNumValidated<int>(min, max, "", "That's not a valid choice. Please try again: ");
		};
		CallEvents   = [](CType& context, RType& result) -> void
		{
			switch (context.Choice)
			{
				case PLAY:
				{
					auto onPlay = (OnPlay*)(*EventManagerType::Instance)[Events::EventList::OnPlay];
					onPlay->Context = 0;
					onPlay->Result = 0.0f;
					onPlay->Run();
					break;
				}
				case SHOP:
				{
					auto onShop = (OnShop*)(*EventManagerType::Instance)[Events::EventList::OnShop];

					onShop->Context.Feedback = "";
					onShop->Result = false;

					while (!onShop->Result)
					{
						onShop->Run();
					}

					break;
				}
				case QUIT:
				{
					result = true;
					break;
				}
				default:
				{
					std::cout << "Error: event choice reached default" << std::endl;
					break;
				}
			}
		};

		SetCallback(OType::DISPLAY_HEADER, DrawHeader  );
		SetCallback(OType::DISPLAY_STATS , DisplayStats);
		SetCallback(OType::PROMPT_INPUT  , ShowChoices );
		SetCallback(OType::GET_INPUT     , GetInput    );
		SetCallback(OType::CALL_EVENTS   , CallEvents  );
	}
}