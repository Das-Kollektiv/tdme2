#pragma once

#include <climits>
#include <cstdint>

#define CLASS_FORBID_COPY(CLASS) \
	CLASS(const CLASS&) = delete; \
	CLASS& operator=(const CLASS&) = delete;

#if defined(TDME2_DLL_EXPORT)
	#define STATIC_DLL_IMPEXT __declspec(dllexport)
#elif defined(TDME2_DLL_IMPORT)
	#define STATIC_DLL_IMPEXT __declspec(dllimport)
#else
	#define STATIC_DLL_IMPEXT
#endif
