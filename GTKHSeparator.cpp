#include "Globals.h"
#include "GTK++.h"

GTKHSeparator::GTKHSeparator()
{
	Widget = gtk_hseparator_new();
	Separator = GTK_SEPARATOR(Widget);
	HSeparator = GTK_HSEPARATOR(Separator);
}

GTKHSeparator::~GTKHSeparator()
{
}
