#include "stdafx.h"

GTKScale::GTKScale()
{
}

GTKScale::~GTKScale()
{
}

void GTKScale::SetDecimalPrecision(uint32_t Places)
{
	gtk_scale_set_digits(Scale, Places);
}

void GTKScale::SetValueDrawn(bool Drawn)
{
	gtk_scale_set_draw_value(Scale, (Drawn ? TRUE : FALSE));
}

void GTKScale::SetValuePosition(GtkPositionType Position)
{
	gtk_scale_set_value_pos(Scale, Position);
}

void GTKScale::AddMark(double MarkValue, GtkPositionType MarkPosition, const char *MarkText)
{
	gtk_scale_add_mark(Scale, MarkValue, MarkPosition, MarkText);
}

void GTKScale::ClearAllMarks()
{
	gtk_scale_clear_marks(Scale);
}
