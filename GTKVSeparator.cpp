#include "stdafx.h"

GTKVSeparator::GTKVSeparator() : GTKSeparator(gtk_vseparator_new())
{
	VSeparator = GTK_VSEPARATOR(Separator);
}

GTKVSeparator::~GTKVSeparator()
{
}
