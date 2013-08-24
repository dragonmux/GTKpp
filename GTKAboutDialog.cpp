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

void WebURLCallback(GtkAboutDialog *AboutBox, const char *Link, void *Data)
{
	gtk_show_uri(NULL, Link, GDK_CURRENT_TIME, NULL);
}

GTKAboutDialog::GTKAboutDialog(GTKWindow *Parent) : GTKDialog(gtk_about_dialog_new())
{
	AboutBox = GTK_ABOUT_DIALOG(Dialog);
	gtk_window_set_transient_for(GTK_WINDOW(Widget), Parent->GetWindow());
}

void GTKAboutDialog::SetProgram(const char *Name)
{
	gtk_about_dialog_set_program_name(AboutBox, Name);
}

void GTKAboutDialog::SetVersion(const char *Version)
{
	gtk_about_dialog_set_version(AboutBox, Version);
}

void GTKAboutDialog::SetCopyright(const char *Copyright)
{
	gtk_about_dialog_set_copyright(AboutBox, Copyright);
}

void GTKAboutDialog::SetComments(const char *Comments)
{
	gtk_about_dialog_set_comments(AboutBox, Comments);
}

void GTKAboutDialog::SetLicense(const char *License)
{
	gtk_about_dialog_set_license(AboutBox, License);
	gtk_about_dialog_set_wrap_license(AboutBox, TRUE);
}

void GTKAboutDialog::SetWebsiteURL(const char *URL)
{
	gtk_about_dialog_set_url_hook(WebURLCallback, NULL, NULL);
	gtk_about_dialog_set_website(AboutBox, URL);
}

void GTKAboutDialog::SetWebsiteText(const char *Website)
{
	gtk_about_dialog_set_website_label(AboutBox, Website);
}

void GTKAboutDialog::SetAuthors(const char **Authors)
{
	gtk_about_dialog_set_authors(AboutBox, Authors);
}
