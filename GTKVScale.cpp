#include "Globals.h"
#include "GTK++.h"

GTKVScale::GTKVScale(double min, double max, double step)
{
	Widget = gtk_vscale_new_with_range(min, max, step);
	Scale = GTK_SCALE(Widget);
	VScale = GTK_VSCALE(Scale);
}
