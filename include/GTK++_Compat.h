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

#ifndef __GTKpp_Compat_H__
#define __GTKpp_Compat_H__

#include <inttypes.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#ifndef UINT
	#define UINT uint32_t
#endif

#ifndef ULONG
	#define ULONG unsigned long
#endif

#ifndef BOOL
	#define BOOL int32_t
#endif

#ifndef BYTE
	#define BYTE uint8_t
#endif

#ifndef RECT
typedef struct _RECT
{
	int left, top, right, bottom;
} RECT;
#endif

#ifndef POINT
typedef struct _POINT
{
	int x, y;
} POINT;
#endif

#ifndef SIZE
typedef struct _SIZE
{
	int cx, cy;
} SIZE;
#endif

#ifndef __cdecl
#define __cdecl
#endif
#endif /*__GTKpp_Compat_H__*/
