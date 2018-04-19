#include <plugin.h>
#include "Utility.h"

#include "CTimer.h"

bool ShowFlashingItem(signed int nOnDuration, signed int nOffDuration)
{
	return CTimer::m_snTimeInMillisecondsPauseMode % (nOnDuration + nOffDuration) < nOnDuration;
}

