#include "OnPlay.h"

namespace Events
{
	OnPlay::OnPlay(EventList event) : Event{ event }
	{
		DisplayHeader = [](CType& context, RType& result)->void
		{
			std::cout << DisplayConstants::NEW_LINES << DisplayConstants::GUESSING << J::TimeStr() << std::endl;
		};
		DisplayStats  = [](CType& context, RType& result)->void
		{
			std::cout << "Creds: " << Stats::Instance->Creds << " | " << "Rounds: " << Stats::Instance->RoundsCompleted << std::endl;
		};
		GameLoop      = [](CType& context, RType& result)->void
		{
			int r = rand() % Stats::Instance->Max.Value + 1;
			int guess = -1;
			while (guess != r)
			{
				guess = J::ReadNumValidated<int>(1, Stats::Instance->Max.Value, "Guess a number from 1 - " + std::to_string(Stats::Instance->Max.Value) + ": ");
				context++;

				if (guess < r)
				{
					std::cout << "Too low." << std::endl;
				}
				else if (guess > r)
				{
					std::cout << "Too high." << std::endl;
				}
			}
			std::cout << "Correct! ";
		};
		PostGame      = [](CType& context, RType& result)->void
		{
			result += Stats::Instance->CredsPerGuess.Calculate();
		};
		DisplayEarned = [](CType& context, RType& result)->void
		{
			Stats::Instance->Creds += result;
			std::cout << "You have earned " << result * Stats::Instance->CredsPerGuess.Calculate() << " creds. Press any button to continue...";
			_getch();
		};

		SetCallback(OType::HEADER, DisplayHeader);
		SetCallback(OType::STATS, DisplayStats);
		SetCallback(OType::GAME_LOOP, GameLoop);
		SetCallback(OType::POST_GAME, PostGame);
		SetCallback(OType::DISPLAY_EARNED, DisplayEarned);
	}
}