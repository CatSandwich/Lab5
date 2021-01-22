#pragma once

#include "UpgradeType.h"

namespace Events
{
	class OnPlay;
}

namespace Upgrades
{
	class FirstTry : UpgradeType
	{
		public:

		FirstTry();

		private:

		Events::OnPlay* _onPlay;
	};
}