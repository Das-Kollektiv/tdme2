#pragma once

#include <climits>
#include <cstdint>

#define FORBID_CLASS_COPY(CLASS) \
	CLASS(const CLASS&) = delete; \
	CLASS& operator=(const CLASS&) = delete;

#if defined(TDME2_DLL_EXPORT)
	#define STATIC_DLL_IMPEXT __declspec(dllexport)
#elif defined(TDME2_DLL_IMPORT)
	#define STATIC_DLL_IMPEXT __declspec(dllimport)
#else
	#define STATIC_DLL_IMPEXT
#endif

#if defined(TDMETOOLS_DLL_EXPORT)
	#define TDMETOOLS_STATIC_DLL_IMPEXT __declspec(dllexport)
#elif defined(TDMETOOLS_DLL_IMPORT)
	#define TDMETOOLS_STATIC_DLL_IMPEXT __declspec(dllimport)
#else
	#define TDMETOOLS_STATIC_DLL_IMPEXT
#endif
