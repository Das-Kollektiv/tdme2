#pragma once

#include <climits>
#include <cstdint>

#define FORBID_CLASS_COPY(CLASS) \
	CLASS(const CLASS&) = delete; \
	CLASS& operator=(const CLASS&) = delete;

#if defined(AGUI_DLL_EXPORT)
	#define AGUI_STATIC_DLL_IMPEXT __declspec(dllexport)
#elif defined(AGUI_DLL_IMPORT)
	#define AGUI_STATIC_DLL_IMPEXT __declspec(dllimport)
#else
	#define AGUI_STATIC_DLL_IMPEXT
#endif
