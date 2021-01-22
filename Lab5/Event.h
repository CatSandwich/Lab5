#pragma once

#include <map>
#include <functional>
#include <iostream>

#include "EventList.h"
#include "EventManager.h"

//empty allows me to omit context and result types in derived event classes since void can't be passed by reference
class Empty {};

namespace Events
{
	template<class OType, class CType, class RType>
	class Event
	{

		public:

		typedef OType OType;
		typedef CType CType;
		typedef RType RType;

		typedef std::function<void(CType&, RType&)> Callback;

		CType Context;
		RType Result;

		Event(EventList event)
		{
			Callbacks = {};

			EventManagerType::Instance->InsertPair(event, this);

			std::cout << (*EventManagerType::Instance)[event] << std::endl;
		}

		inline void SetCallback(OType ID, Callback callback)
		{
			Callbacks[ID] = callback;
		}

		inline void RemoveCallback(OType ID)
		{
			auto it = Callbacks.find(ID);

			//remove entry if one is found with that ID
			if (it != Callbacks.end())
				Callbacks.erase(it);
		}

		inline void Run()
		{
			for (auto it = Callbacks.begin(); it != Callbacks.end(); it++)
			{
				((*it).second)(Context, Result);
			}
		}

		private:

		std::map<OType, Callback> Callbacks;
	};
}