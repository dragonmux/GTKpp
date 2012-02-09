#include "stdafx.h"

GTKVSeparator::GTKVSeparator()
{
	Widget = gtk_vseparator_new();
	Separator = GTK_SEPARATOR(Widget);
	VSeparator = GTK_VSEPARATOR(Separator);
}

GTKVSeparator::~GTKVSeparator()
{
}
