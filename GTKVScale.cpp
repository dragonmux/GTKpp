#include "stdafx.h"

GTKVScale::GTKVScale(double min, double max, double step)
{
	Widget = gtk_vscale_new_with_range(min, max, step);
	Range = GTK_RANGE(Widget);
	Scale = GTK_SCALE(Range);
	VScale = GTK_VSCALE(Scale);
	SetHandlers();
}
