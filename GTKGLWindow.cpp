/*
 * This file is part of GTK++ (libGTK++)
 * Copyright © 2012 Richard/Rachel Mant (dx-mon@users.sourceforge.net)
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
|*                  GTKGLWindow implementation                 *|
\***************************************************************/

GTKGLWindow::GTKGLWindow(GtkWindowType Type, GdkGLConfig *Config, void *CloseFunc, int PixFormat, bool AutoRedraw, int Timeout) :
	GTKWindow(Type, CloseFunc)
{
	GLBaseInit(Config, PixFormat, AutoRedraw, Timeout);
}

GTKGLWindow::~GTKGLWindow()
{
	GLBaseDeinit();
}

GTKWidget *GTKGLWindow::getGTKWidget()
{
	return GetGTKWidget();
}
