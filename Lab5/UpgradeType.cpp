#include "UpgradeType.h"

void UpgradeType::Upgrade()
{
	Callbacks[Level++]();
}