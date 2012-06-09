#include "stdafx.h"

/***************************************************************\
|*                   GTKEvents implementation                  *|
\***************************************************************/

GTKEvents::GTKEvents()
{
	memset(&EventHandlers, 0x00, sizeof(EventHandlers));
}

GTKEvents::~GTKEvents()
{
}
