#include "stdafx.h"

GTKHScale::GTKHScale(double min, double max, double step) : GTKScale(gtk_hscale_new_with_range(min, max, step))
{
	HScale = GTK_HSCALE(Scale);
	SetHandlers();
}
