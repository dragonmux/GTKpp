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
#include <gl/gl.h>
#include <gl/glu.h>

PIXELFORMATDESCRIPTOR pfd;

static PIXELFORMATDESCRIPTOR pfdPreferredFormat =
{
	sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_SWAP_COPY | PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA, 32, 8, 0, 8, 8, 8, 16, 8, 24, 0, 0, 0, 0, 0, 32, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
};

int WeightPixelFormat(PIXELFORMATDESCRIPTOR& pfd)
{
	int weight = 0;

	if ((pfd.dwFlags & PFD_SUPPORT_OPENGL) != 0 || (pfd.dwFlags & PFD_DRAW_TO_WINDOW) != 0 || (pfd.dwFlags & PFD_DOUBLEBUFFER) != 0 ||
		pfd.cDepthBits <= 8 || pfd.iPixelType != PFD_TYPE_RGBA)
		return 0;

	weight = 1 + (pfd.cDepthBits - 16) + (pfd.cColorBits - 8);
	if ((pfd.dwFlags & PFD_SWAP_COPY) != 0)
		weight += 16;
	if ((pfd.dwFlags & PFD_GENERIC_FORMAT) != 0)
		weight /= 10;

	return weight;
}

int EnumPixelFormats(HDC hDC)
{
	int PixelFormat;
	int i, n, w, weight = 0;

	if (hDC == NULL)
		return 0;

	PixelFormat = 1;
	n = DescribePixelFormat(hDC, PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd) + 1;
	PixelFormat = ChoosePixelFormat(hDC, &pfdPreferredFormat);
	if (PixelFormat == 0)
		return 0;

	for (i = 1; i <= n; i++)
	{
		DescribePixelFormat(hDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
		w = WeightPixelFormat(pfd);
		if (((pfdPreferredFormat.dwFlags ^ pfd.dwFlags) & PFD_STEREO) == 0)
		{
			if (w > weight)
			{
				weight = w;
				PixelFormat = i;
			}
		}
	}
	if (weight == 0)
	{
		for (i = 1; i <= n; i++)
		{
			DescribePixelFormat(hDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
			w = WeightPixelFormat(pfd);
			if (w > weight)
			{
				weight = w;
				PixelFormat = i;
			}
		}
	}
	return PixelFormat;
}
