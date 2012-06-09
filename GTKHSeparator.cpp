#include "stdafx.h"

GTKHSeparator::GTKHSeparator() : GTKSeparator(gtk_hseparator_new())
{
	HSeparator = GTK_HSEPARATOR(Separator);
}

GTKHSeparator::~GTKHSeparator()
{
}
