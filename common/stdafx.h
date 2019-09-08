#ifndef _STDAFX_H_
#define _STDAFX_H_

//=============================================================================
#ifdef _WIN32

//#pragma pack(1)
#pragma warning(disable:4996) // Using open/close/read... for file access

// Including SDKDDKVer.h defines the highest available Windows platform.
// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <GL/glu.h>

#include <assert.h>
#define LEAK_CONTROL
#define ASSERT(v) assert(v)

#include "leaks.h"

#define RET_ERR 0
#define RET_OK  1

#define SAFE_DELETE(p)				{DEL(p);			 p = NULL;}
#define SAFE_DELETE_ARRAY(p)	{DEL_ARRAY(p); p = NULL;}

#ifdef SWALIB_SOUND
#include <al.h>
#include <alc.h>
#endif //SWALIB_SOUND

#include <io.h>

//=============================================================================
#elif defined(__APPLE__)

#include "TargetConditionals.h"

#if defined(__MACH__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
#include <unistd.h>
#include <GL/glfw.h>

#define GL_BGRA_EXT GL_BGRA

#include <OpenAL/al.h>
#include <OpenAL/alc.h>


#endif
#endif

//=============================================================================
// PNG loading library
#include "lodepng.h"

//=============================================================================
// Common includes

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

#endif
