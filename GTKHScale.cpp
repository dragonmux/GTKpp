#include "Globals.h"
#include "GTK++.h"

GTKHScale::GTKHScale(double min, double max, double step)
{
	Widget = gtk_hscale_new_with_range(min, max, step);
	Range = GTK_RANGE(Widget);
	Scale = GTK_SCALE(Range);
	HScale = GTK_HSCALE(Scale);
}
