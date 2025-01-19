#include <agui/agui.h>
#include <agui/utilities/RTTI.h>

#if defined(_WIN32) && defined(_MSC_VER)
	// no op
#else
	#include <cxxabi.h>
	#include <stdlib.h>

	#if !defined(_WIN32) && !defined(__HAIKU__)
		#include <stdio.h>
		#include <execinfo.h>
		#include <signal.h>
		#include <unistd.h>
	#endif
#endif

#include <string>

using std::string;
using std::to_string;

using agui::utilities::RTTI;

const string RTTI::demangle(const string& name) {
	#if defined(_WIN32) && defined(_MSC_VER)
		auto demangledNameString = name;
		return demangledNameString;
	#else
		int status;
		char* demangledName = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
		string demangledNameString(demangledName == nullptr?name:demangledName);
		free(demangledName);
		return demangledNameString;
	#endif
}

const string RTTI::backtrace() {
	#if defined(_WIN32) || defined(__HAIKU__)
		return "No backtrace available";
	#else
		// Note: This is *nix only and requires to compile with -rdynamic flag
		void* buffer[50];
		auto size = ::backtrace(buffer, 50);
		auto strings = ::backtrace_symbols(buffer, size);
		if (strings == nullptr) return "No backtrace available";
		string result;
		// https://stackoverflow.com/questions/77005/how-to-automatically-generate-a-stacktrace-when-my-program-crashes
		for (int i = 1; i < size && strings != nullptr; ++i) {
			char* mangledName = 0, *offsetBegin = 0, *offsetEnd = 0;
			// find parantheses and +address offset surrounding mangled name
			for (char* p = strings[i]; *p; ++p) {
				if (*p == '(') {
					mangledName = p;
				} else if (*p == '+') {
					offsetBegin = p;
				} else if (*p == ')') {
					offsetEnd = p;
					break;
				}
			}
			// if the line could be processed, attempt to demangle the symbol
			if (mangledName && offsetBegin && offsetEnd && mangledName < offsetBegin) {
				*mangledName++ = '\0';
				*offsetBegin++ = '\0';
				*offsetEnd++ = '\0';
				int status;
				char* realName = abi::__cxa_demangle(mangledName, 0, 0, &status);
				// if demangling is successful, output the demangled function name
				if (status == 0) {
					result+= to_string(i) + ": " + strings[i] + ": " + realName + "\n";
				} else {
					// otherwise, output the mangled function name
					result+= to_string(i) + ": " + strings[i] + ": " + mangledName + "\n";
				}
				free(realName);
			} else {
				// otherwise, print the whole line
				result+= to_string(i) + ": " + strings[i] + "\n";
			}
		}
		free(strings);
		return result;
	#endif
}
