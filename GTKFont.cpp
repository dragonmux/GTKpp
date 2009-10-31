#include "Globals.h"
#include "GTK++.h"

/***************************************************************\
|*                    GTKFont implementation                   *|
\***************************************************************/

SIZE GTKFont::GetStringMetrics(char *String)
{
	PangoLayout *PL;
	PangoContext *PC;
	PangoFontMap *PFM;
	PangoFontDescription *PFD;
	static PangoRectangle PR_Logic;
	static SIZE ret;

	PFD = pango_font_describe(Font);
	PFM = pango_font_get_font_map(Font);
	PC = pango_context_new();
	pango_context_set_font_description(PC, PFD);
	pango_context_set_font_map(PC, PFM);
	PL = pango_layout_new(PC);
	pango_layout_set_font_description(PL, PFD);
	pango_layout_set_width(PL, -1);
	pango_layout_set_text(PL, String, -1);

	pango_layout_get_pixel_extents(PL, NULL, &PR_Logic);
	ret.cy = PR_Logic.height;
#ifndef _WINDOWS
	ret.cy -= 10;
#endif
	pango_font_description_set_size(PFD, FontSize * PANGO_SCALE);
	pango_layout_set_font_description(PL, PFD);
	pango_layout_get_pixel_extents(PL, NULL, &PR_Logic);
	ret.cx = PR_Logic.width;

	g_object_unref(PL);
	pango_font_description_free(PFD);
	g_object_unref(PC);

	return ret;
}
