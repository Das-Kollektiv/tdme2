#include <tdme/utils/RTTI.h>

#include <cxxabi.h>
#include <stdlib.h>

using tdme::utils::RTTI;

const std::string RTTI::demangle(const char* name) {
	int status;
	char* demangledName = abi::__cxa_demangle(name, 0, 0, &status);
	std::string demangledNameString(demangledName);
	free(demangledName);
	return demangledNameString;
}
