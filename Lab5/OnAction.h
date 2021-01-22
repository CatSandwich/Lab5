#pragma once
#pragma warning(disable:4996)

#include "OnPlay.h"
#include "OnShop.h"

/* OnAction is the event at the highest level. It displays the choices 
   the user has, reads in their choice and calls the respective event. */

namespace Events
{
	enum class OnActionOrder
	{
		DISPLAY_HEADER,
		DISPLAY_STATS,
		PROMPT_INPUT, 
		GET_INPUT,
		CALL_EVENTS
	};

	class OnActionContext
	{
		public:
		int Choice;
		std::vector<std::string> Choices;
		EventManagerType* EventManager;
		OnActionContext();
	};

	class OnAction : public Event<OnActionOrder, OnActionContext, bool>
	{
		private:
		Callback DrawHeader;
		Callback DisplayStats;
		Callback ShowChoices;
		Callback GetInput;
		Callback CallEvents;

		public:
		OnAction(EventList);
	};
}