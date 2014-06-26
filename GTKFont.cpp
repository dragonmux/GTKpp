/*
 * This file is part of GTK++ (libGTK++)
 * Copyright © 2012 Rachel Mant (dx-mon@users.sourceforge.net)
 *
 * GTK++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GTK++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"

/***************************************************************\
|*                    GTKFont implementation                   *|
\***************************************************************/

GTKSize GTKFont::GetStringMetrics(const char *String)
{
	PangoLayout *PL;
	PangoContext *PC;
	PangoFontMap *PFM;
	PangoFontDescription *PFD;
	static PangoRectangle PR_Logic;
	GTKSize ret = {0, 0};

	if (String == NULL)
		return ret;

	PFD = pango_font_describe(Font);
	PFM = pango_font_get_font_map(Font);
	PC = pango_context_new();
	pango_context_set_font_description(PC, PFD);
	pango_context_set_font_map(PC, PFM);
	PL = pango_layout_new(PC);
	pango_layout_set_font_description(PL, PFD);
	pango_layout_set_width(PL, -1);
	pango_layout_set_text(PL, String, -1);

#ifdef _WINDOWS
	pango_font_description_set_size(PFD, (FontSize - 1) * PANGO_SCALE);
	pango_layout_set_font_description(PL, PFD);
#endif
	pango_layout_get_pixel_extents(PL, NULL, &PR_Logic);
	ret.cy = PR_Logic.height;
	ret.cx = PR_Logic.width;

	g_object_unref(PL);
	pango_font_description_free(PFD);
	g_object_unref(PC);

	return ret;
}

uint32_t GTKFont::GetBaseline()
{
	PangoFontMetrics *PFM = pango_font_get_metrics(Font, NULL);
	uint32_t ret = pango_font_metrics_get_descent(PFM) / PANGO_SCALE;
	pango_font_metrics_unref(PFM);
	return ret;
}

void GTKFont::RenderString(const char *String)
{
	if (String == NULL)
		return;
	GTKSize size = GetStringMetrics(String);
}
