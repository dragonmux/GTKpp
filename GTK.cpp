#include "Globals.h"
#include "GTK++.h"

/***************************************************************\
|*                      GTK implementation                     *|
\***************************************************************/

void GTK::GTKInit(int argc, char **argv)
{
	gtk_set_locale();
	gtk_init(&argc, &argv);
}