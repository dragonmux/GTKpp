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
	long left, top, right, bottom;
} RECT;
#endif

#ifndef POINT
typedef struct _POINT
{
	long x, y;
} POINT;
#endif

#ifndef SIZE
typedef struct _SIZE
{
	long cx, cy;
} SIZE;
#endif

#ifndef __cdecl
#define __cdecl
#endif
#endif /*__GTKpp_Compat_H__*/
