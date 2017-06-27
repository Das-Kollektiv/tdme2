// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/w3c/dom/ls/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using org::w3c::dom::ls::LSInput;
using org::w3c::dom::ls::LSOutput;
using org::w3c::dom::ls::LSParser;
using org::w3c::dom::ls::LSSerializer;


struct org::w3c::dom::ls::DOMImplementationLS
	: public virtual Object
{
	static constexpr int16_t MODE_ASYNCHRONOUS { 2 };
	static constexpr int16_t MODE_SYNCHRONOUS { 1 };

	virtual LSInput* createLSInput() = 0;
	virtual LSOutput* createLSOutput() = 0;
	virtual LSParser* createLSParser(int16_t arg0, String* arg1) = 0;
	virtual LSSerializer* createLSSerializer() = 0;

	// Generated
	static ::java::lang::Class *class_();
};
