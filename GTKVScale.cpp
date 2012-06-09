#include "stdafx.h"

GTKVScale::GTKVScale(double min, double max, double step) : GTKScale(gtk_vscale_new_with_range(min, max, step))
{
	VScale = GTK_VSCALE(Scale);
	SetHandlers();
}
