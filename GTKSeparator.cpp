#include "stdafx.h"

GTKSeparator::GTKSeparator(GtkWidget *Widget) : GTKWidget(Widget)
{
	Separator = GTK_SEPARATOR(Widget);
}

GTKSeparator::~GTKSeparator()
{
}
