#include "stdafx.h"

#ifdef _WINDOWS
extern int EnumPixelFormats(HDC hDC);
extern "C" GdkGLConfig *gdk_win32_gl_config_new_from_pixel_format(int pixel_format);
#else
#include <errno.h>
#endif

void GLBase::GLBaseInit(GdkGLConfig *Config)
{
	init(Config, GDK_GL_RGBA_TYPE);
}

void GLBase::GLBaseInit(GdkGLConfig *Config, int PixFormat)
{
	init(Config, PixFormat);
}

int32_t Redraw_Internal(void *W)
{
	GTKWidget *Widget = (GTKWidget *)W;
	Widget->Redraw(true);
	return 1;
}

void GLBase::GLBaseInit(GdkGLConfig *Config, int PixFormat, bool AutoRedraw, int Timeout)
{
	init(Config, PixFormat);
	if (AutoRedraw == true)
	{
		AddTimeout(Timeout);
		getGTKWidget()->SetHandler("visibility_notify_event", (void *)CheckVisibility, this);
	}
}

void GLBase::init(GdkGLConfig *Config, int PixFormat)
{
	gtk_widget_set_gl_capability(this->getGTKWidget()->GetWidget(), Config, NULL, true, PixFormat);
	gtk_widget_set_app_paintable(this->getGTKWidget()->GetWidget(), true);
	Conf = Config;
	ctx = NULL;
	drw = NULL;
	TimeoutID = 0;
}

void GLBase::GLBaseDeinit()
{
	DestroyGLFonts();
}

GLBase::~GLBase()
{
//	g_clear_object(&Conf);
	g_object_unref(Conf);
	Conf = NULL;
}

GdkGLConfig *GLBase::MakeStandardConfig()
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

bool GLBase::glBegin()
{
	if (ctx != NULL || drw != NULL)
	{
		printf("Error, glBegin() called without interviening glEnd() call\n");
		return false;
	}
	ctx = gtk_widget_get_gl_context(this->getGTKWidget()->GetWidget());
	drw = gtk_widget_get_gl_drawable(this->getGTKWidget()->GetWidget());

	return (gdk_gl_drawable_gl_begin(drw, ctx) == FALSE ? false : true);
}

void GLBase::glSwapBuffers()
{
	if (gdk_gl_drawable_is_double_buffered(drw) == TRUE)
		gdk_gl_drawable_swap_buffers(drw);
	else
		glFlush();
}

void GLBase::glEnd()
{
	if (drw == NULL)
	{
		printf("Error, glEnd() called twice without interviening glBegin() call\n");
		return;
	}
	gdk_gl_drawable_gl_end(drw);
	drw = NULL;
	ctx = NULL;
}

GTKFont *GLBase::SetupGLFont(const char *FontName, int Size, int Start, int Num)
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

void GLBase::DestroyGLFont(GTKFont **Font)
{
	if (Font == NULL || *Font == NULL)
		return;
	for (uint32_t i = 0; i < Fonts.size(); i++)
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

void GLBase::DestroyGLFonts()
{
	if (Fonts.size() == 0)
		return;
	this->glBegin();
	for (uint32_t i = 0; i < Fonts.size(); i++)
	{
		g_object_unref(Fonts[i]->Font);
		glDeleteLists(Fonts[i]->DisplayBase, Fonts[i]->NumEntries);
		free(Fonts[i]);
	}
	Fonts.clear();
	this->glEnd();
}

bool GLBase::CheckVisibility(GtkWidget *widget, GdkEventVisibility *event, void *data)
{
	GLBase *Self = (GLBase *)data;
	if (event->state == GDK_VISIBILITY_FULLY_OBSCURED)
		Self->RemoveTimeout();
	else
		Self->AddTimeout(Self->Timeout);

	return true;
}

void GLBase::AddTimeout(int Timeout)
{
	if (TimeoutID == 0)
	{
		TimeoutID = g_timeout_add(Timeout, Redraw_Internal, getGTKWidget());
		this->Timeout = Timeout;
	}
}

void GLBase::RemoveTimeout()
{
	if (TimeoutID > 0)
	{
		g_source_remove(TimeoutID);
		TimeoutID = 0;
		Timeout = -1;
	}
}
