#include "Globals.h"
#include "GTK++.h"

#ifdef _WINDOWS
extern int EnumPixelFormats(HDC hDC);
extern "C" GdkGLConfig *gdk_win32_gl_config_new_from_pixel_format(int pixel_format);
#else
#include <errno.h>
#endif

/***************************************************************\
|*                  GTKGLWidget implementation                 *|
\***************************************************************/

GTKGLWidget::GTKGLWidget(GdkGLConfig *Config, GtkWidget *W, int PixFormat)
{
	Widget = W;
	gtk_widget_set_gl_capability(Widget, Config, NULL, TRUE, PixFormat);
	Conf = Config;
	ctx = NULL;
	drw = NULL;
}

GdkGLConfig *GTKGLWidget::MakeStandardConfig()
{
#ifdef _WINDOWS
	HDC hDC = GetDC(NULL);
	GdkGLConfig *ret = gdk_win32_gl_config_new_from_pixel_format(EnumPixelFormats(hDC));
	DeleteDC(hDC);
	return ret;
#else
	GdkGLConfig *ret = gdk_gl_config_new_by_mode((GdkGLConfigMode)(GDK_GL_MODE_RGBA | GDK_GL_MODE_DOUBLE | GDK_GL_MODE_DEPTH | GDK_GL_MODE_STENCIL));
	if (ret == NULL)
	{
		ret = gdk_gl_config_new_by_mode((GdkGLConfigMode)(GDK_GL_MODE_RGBA | GDK_GL_MODE_SINGLE | GDK_GL_MODE_DEPTH | GDK_GL_MODE_STENCIL));
		if (ret == NULL)
		{
			printf("Cannot generate a suitable OpenGL Context Configuration, exiting.....");
			exit(-1);
		}
	}
	return ret;
#endif
}

BOOL GTKGLWidget::glBegin()
{		
	ctx = gtk_widget_get_gl_context(Widget);
	drw = gtk_widget_get_gl_drawable(Widget);

	return gdk_gl_drawable_gl_begin(drw, ctx);
}

void GTKGLWidget::glSwapBuffers()
{
	if (gdk_gl_drawable_is_double_buffered(drw) == TRUE)
		gdk_gl_drawable_swap_buffers(drw);
	else
		glFlush();
}

void GTKGLWidget::glEnd()
{
	gdk_gl_drawable_gl_end(drw);
	drw = NULL;
	ctx = NULL;
}

GTKFont *GTKGLWidget::SetupGLFont(const char *FontName, int Size, int Start, int Num)
{
	PangoFontDescription *PFD;
	GTKFont *Font = new GTKFont();
	PangoFont *PF;

	PFD = pango_font_description_new();
	pango_font_description_set_family(PFD, FontName);
#ifdef _WINDOWS
	pango_font_description_set_size(PFD, (Size - 2) * PANGO_SCALE);
#else
	pango_font_description_set_size(PFD, Size * PANGO_SCALE);
#endif
	pango_font_description_set_weight(PFD, PANGO_WEIGHT_NORMAL);
	pango_font_description_set_variant(PFD, PANGO_VARIANT_NORMAL);
	pango_font_description_set_style(PFD, PANGO_STYLE_NORMAL);
	pango_font_description_set_stretch(PFD, PANGO_STRETCH_NORMAL);

	this->glBegin();

	Font->DisplayBase = glGenLists(Num);
	PF = gdk_gl_font_use_pango_font(PFD, Start, Num, Font->DisplayBase);
	if (PF == NULL)
	{
		printf("Cannot get a font from Pango with name and size %s %ipt, exiting.....\n\n", FontName, Size);
		exit(1);
	}
	Font->Font = PF;
	Font->NumEntries = Num;
	Font->FontSize = Size;
	Fonts.push_back(Font);
	Font->Parent = this;

	this->glEnd();

	pango_font_description_free(PFD);

	return Font;
}

void GTKGLWidget::DestroyGLFont(GTKFont **Font)
{
	for (UINT i = 0; i < Fonts.size(); i++)
	{
		if (Fonts[i] == *Font)
		{
			g_object_unref(Fonts[i]->Font);
			glDeleteLists(Fonts[i]->DisplayBase, Fonts[i]->NumEntries);
			free(Fonts[i]);
			*Font = NULL;
			return;
		}
	}
}

void GTKGLWidget::DestroyGLFonts()
{
	this->glBegin();
	for (UINT i = 0; i < Fonts.size(); i++)
	{
		g_object_unref(Fonts[i]->Font);
		glDeleteLists(Fonts[i]->DisplayBase, Fonts[i]->NumEntries);
		free(Fonts[i]);
	}
	Fonts.clear();
	this->glEnd();
}

ULONG GTKGLWidget::glSetHandler(char *Event, void *Handler, void *Data)
{
	return SetHandler(Event, Handler, Data);
}

void GTKGLWidget::glRemoveHandler(ULONG ID)
{
	RemoveHandler(ID);
}
