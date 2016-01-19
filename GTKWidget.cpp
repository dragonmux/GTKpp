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
|*                   GTKWidget implementation                  *|
\***************************************************************/

constexpr uint16_t extendColour(const uint8_t colour) noexcept { return colour | (colour << 8); }

GTKWidget::GTKWidget(GtkWidget *W) : Widget(W)
{
	gtk_widget_ref(Widget);
}

GTKWidget::~GTKWidget()
{
	if (Widget != NULL)
	{
		if (Widget->window != NULL &&
#if (GTK_MAJOR_VERSION >= 2 && GTK_MINOR_VERSION >= 18)
			gdk_window_is_destroyed(Widget->window) == FALSE
#else
			((GdkWindowObject *)Widget->window)->destroyed == FALSE
#endif
		)
		gtk_widget_destroy(Widget);
		gtk_widget_unref(Widget);
	}
	//g_clear_object(&Widget);
	Widget = NULL;
}

GtkWidget *GTKWidget::GetWidget() const
{
	return Widget;
}

uint32_t GTKWidget::SetHandler(const char *Event, void *Handler, void *Data)
{
	return g_signal_connect(GTK_OBJECT(Widget), Event, G_CALLBACK(Handler), Data);
}

uint32_t GTKWidget::SetHandlerAfter(const char *Event, void *Handler, void *Data)
{
	return g_signal_connect_after(GTK_OBJECT(Widget), Event, G_CALLBACK(Handler), Data);
}

void GTKWidget::RemoveHandler(uint32_t ID)
{
	g_signal_handler_disconnect(GTK_OBJECT(Widget), ID);
}

void GTKWidget::Disable()
{
	gtk_widget_set_sensitive(Widget, FALSE);
}

void GTKWidget::Enable()
{
	gtk_widget_set_sensitive(Widget, TRUE);
}

void GTKWidget::Hide()
{
	gtk_widget_hide_all(Widget);
}

void GTKWidget::Show()
{
	gtk_widget_show_all(Widget);
}

void GTKWidget::Redraw(bool Now)
{
	gdk_window_invalidate_rect(Widget->window, NULL, TRUE);
	if (Now != FALSE)
		gdk_window_process_updates(Widget->window, TRUE);
}

void GTKWidget::SetForegroundColour(uint8_t R, uint8_t G, uint8_t B)
{
	GdkColor col{0, extendColour(R), extendColour(G), extendColour(B)};
	gtk_widget_modify_fg(Widget, GTK_STATE_NORMAL, &col);
	gtk_widget_modify_fg(Widget, GTK_STATE_ACTIVE, &col);
	gtk_widget_modify_fg(Widget, GTK_STATE_PRELIGHT, &col);
	gtk_widget_modify_text(Widget, GTK_STATE_NORMAL, &col);
	gtk_widget_modify_text(Widget, GTK_STATE_ACTIVE, &col);
	gtk_widget_modify_text(Widget, GTK_STATE_PRELIGHT, &col);
}

void GTKWidget::SetBackgroundColour(uint8_t R, uint8_t G, uint8_t B)
{
	GdkColor col{0, extendColour(R), extendColour(G), extendColour(B)};
	gtk_widget_modify_bg(Widget, GTK_STATE_NORMAL, &col);
	gtk_widget_modify_bg(Widget, GTK_STATE_ACTIVE, &col);
	gtk_widget_modify_bg(Widget, GTK_STATE_PRELIGHT, &col);
	gtk_widget_modify_base(Widget, GTK_STATE_NORMAL, &col);
	gtk_widget_modify_base(Widget, GTK_STATE_ACTIVE, &col);
	gtk_widget_modify_base(Widget, GTK_STATE_PRELIGHT, &col);
}

void GTKWidget::SetBold(bool Bold)
{
	PangoContext *ctx = gtk_widget_get_pango_context(Widget);
	PangoFontDescription *pfd = pango_font_description_copy(pango_context_get_font_description(ctx));
	pango_font_description_set_weight(pfd, (Bold == FALSE ? PANGO_WEIGHT_NORMAL : PANGO_WEIGHT_BOLD));
	gtk_widget_modify_font(Widget, pfd);
}

void GTKWidget::SetItalic(bool Italic)
{
	PangoContext *ctx = gtk_widget_get_pango_context(Widget);
	PangoFontDescription *pfd = pango_font_description_copy(pango_context_get_font_description(ctx));
	pango_font_description_set_style(pfd, (Italic == FALSE ? PANGO_STYLE_NORMAL : PANGO_STYLE_ITALIC));
	gtk_widget_modify_font(Widget, pfd);
}

void GTKWidget::SetUnderline(bool /*Underline*/)
{
/*	PangoContext *ctx = gtk_widget_get_pango_context(Widget);
	PangoFontDescription *pfd = pango_font_description_copy(pango_context_get_font_description(ctx));
	pango_font_description_set_style(pfd, (Underline == FALSE ? PANGO_UNDERLINE_NONE : PANGO_UNDERLINE_SINGLE));
	gtk_widget_modify_font(Widget, pfd);*/
}

void GTKWidget::SetFontSize(int Size)
{
	PangoContext *ctx = gtk_widget_get_pango_context(Widget);
	PangoFontDescription *pfd = pango_font_description_copy(pango_context_get_font_description(ctx));
	pango_font_description_set_size(pfd, Size * PANGO_SCALE);
	gtk_widget_modify_font(Widget, pfd);
}

void GTKWidget::SetFontName(const char *Name)
{
	PangoContext *ctx = gtk_widget_get_pango_context(Widget);
	PangoFontDescription *pfd = pango_font_description_copy(pango_context_get_font_description(ctx));
	pango_font_description_set_family(pfd, Name);
	gtk_widget_modify_font(Widget, pfd);
}

void GTKWidget::AddAccelerator(const char *Event, GtkAccelGroup *Group, const char Key, GdkModifierType Mods)
{
	gtk_widget_add_accelerator(Widget, Event, Group, Key, Mods, (GtkAccelFlags)0);
}
