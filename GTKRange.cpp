#include "Globals.h"
#include "GTK++.h"

GTKRange::GTKRange()
{
}

GTKRange::~GTKRange()
{
}

double GTKRange::GetValue()
{
	return gtk_range_get_value(Range);
}

void GTKRange::SetValue(double Value)
{
	gtk_range_set_value(Range, Value);
}
