#include "stdafx.h"

/***************************************************************\
|*                      GTK implementation                     *|
\***************************************************************/

void GTK::GTKInit(int argc, char **argv)
{
	gtk_set_locale();
	gtk_init(&argc, &argv);
}

GTK::GTK()
{
}

GTK::~GTK()
{
}

void GTK::SetDefaultWindowIcon(GList *Icons)
{
	gtk_window_set_default_icon_list(Icons);
}
