#pragma once

#include <climits>
#include <cstdint>

#define FORBID_CLASS_COPY(CLASS) \
	CLASS(const CLASS&) = delete; \
	CLASS& operator=(const CLASS&) = delete;

#if defined(MINISCRIPT_DLL_EXPORT)
	#define STATIC_DLL_IMPEXT __declspec(dllexport)
#elif defined(MINISCRIPT_DLL_IMPORT)
	#define STATIC_DLL_IMPEXT __declspec(dllimport)
#else
	#define STATIC_DLL_IMPEXT
#endif
