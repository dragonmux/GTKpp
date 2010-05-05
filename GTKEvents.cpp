#include "Globals.h"
#include "GTK++.h"

/***************************************************************\
|*                   GTKEvents implementation                  *|
\***************************************************************/

GTKEvents::GTKEvents()
{
	memset(&EventHandlers, 0x00, sizeof(EventHandlers));
}