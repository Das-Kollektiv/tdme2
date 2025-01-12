#pragma once

#include <climits>
#include <cstdint>

#define FORBID_CLASS_COPY(CLASS) \
	CLASS(const CLASS&) = delete; \
	CLASS& operator=(const CLASS&) = delete;

#if defined(YANNET_DLL_EXPORT)
	#define YANNET_STATIC_DLL_IMPEXT __declspec(dllexport)
#elif defined(YANNET_DLL_IMPORT)
	#define YANNET_STATIC_DLL_IMPEXT __declspec(dllimport)
#else
	#define YANNET_STATIC_DLL_IMPEXT
#endif
