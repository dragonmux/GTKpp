#include <stdio.h>

#ifdef _WINDOWS
// Give us a break, M$!
#define WIN32_LEAN_AND_MEAN 1
#include <stdlib.h>
#include <windows.h>
#endif

#if defined(__MACOSX__)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#elif defined(__MACOS__)
	#include <gl.h>
	#include <glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <stdarg.h>
