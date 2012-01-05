#include "Globals.h"
#include "GTK++.h"

GTKHScale::GTKHScale(double min, double max, double step)
{
	Widget = gtk_hscale_new_with_range(min, max, step);
	Scale = GTK_SCALE(Widget);
	HScale = GTK_HSCALE(Scale);
}
