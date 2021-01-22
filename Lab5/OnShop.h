#pragma once

#include "Event.h"
#include "UpgradeType.h"
#include "DisplayConstants.h"
#include "Stats.h"
#include "JInclude.h"

namespace Events
{
	enum class OnShopOrder
	{
		DISPLAY_HEADER,
		DISPLAY_STATS,
		DISPLAY_FEEDBACK,
		DISPLAY_SHOP,
		GET_INPUT,
		TRY_UPGRADE
	};

	class OnShopContext
	{
		public:
		int Choice;
		std::string Feedback;
	};

	class OnShop : public Event<OnShopOrder, OnShopContext, bool>
	{
		private:
		Callback DisplayHeader;
		Callback DisplayStats;
		Callback DisplayFeedback;
		Callback DisplayShop;
		Callback GetInput;
		Callback TryUpgrade;

		public:
		OnShop(EventList);
	};
}