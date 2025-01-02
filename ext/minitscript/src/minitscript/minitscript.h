#pragma once

#include <climits>
#include <cstdint>
#include <string>

using std::string;

#define _FORBID_CLASS_COPY(CLASS) \
	CLASS(const CLASS&) = delete; \
	CLASS& operator=(const CLASS&) = delete;

#if defined(MINITSCRIPT_DLL_EXPORT)
	#define MINITSCRIPT_STATIC_DLL_IMPEXT __declspec(dllexport)
#elif defined(MINITSCRIPT_DLL_IMPORT)
	#define MINITSCRIPT_STATIC_DLL_IMPEXT __declspec(dllimport)
#else
	#define MINITSCRIPT_STATIC_DLL_IMPEXT
#endif

#if !defined(MINITSCRIPT_DATA)
	#define MINITSCRIPT_DATA string(".")
#endif

#define MINITSCRIPT_EVENTS
