#pragma once

#include "Event.h"
#include "Stats.h"
#include "DisplayConstants.h"
#include "JInclude.h"

#include <ctime>
#include <cstdlib>
#include <conio.h>

namespace Events
{
	enum class OnPlayOrder
	{
		HEADER,
		STATS,
		GAME_LOOP,
		POST_GAME,
		POST_GAME_FIRST_TRY,
		DISPLAY_EARNED
	};

	class OnPlay : public Event<OnPlayOrder, int, float>
	{
		private:
		Callback DisplayHeader;
		Callback DisplayStats;
		Callback GameLoop;
		Callback PostGame;
		Callback PostGameFirstTry;
		Callback DisplayEarned;

		public:
		OnPlay(EventList);
		int test;
	};
}