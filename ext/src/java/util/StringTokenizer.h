// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Enumeration.h>

using java::lang::Object;
using java::util::Enumeration;
using java::lang::String;


struct default_init_tag;
class java::util::StringTokenizer
	: public virtual Object
	, public virtual Enumeration
{

public:
	typedef Object super;

private:
	int32_t currentPosition {  };
	int32_tArray* delimiterCodePoints {  };
	String* delimiters {  };
	bool delimsChanged {  };
	bool hasSurrogates {  };
	int32_t maxDelimCodePoint {  };
	int32_t maxPosition {  };
	int32_t newPosition {  };
	bool retDelims {  };
	String* str {  };

protected:
	void ctor(String* arg0);
	void ctor(String* arg0, String* arg1);
	void ctor(String* arg0, String* arg1, bool arg2);

public:
	virtual int32_t countTokens();
	bool hasMoreElements() override;
	virtual bool hasMoreTokens();
	/*bool isDelimiter(int32_t arg0); (private) */
	Object* nextElement() override;
	virtual String* nextToken();
	virtual String* nextToken(String* arg0);
	/*int32_t scanToken(int32_t arg0); (private) */
	/*void setMaxDelimCodePoint(); (private) */
	/*int32_t skipDelimiters(int32_t arg0); (private) */

	// Generated
	StringTokenizer(String* arg0);
	StringTokenizer(String* arg0, String* arg1);
	StringTokenizer(String* arg0, String* arg1, bool arg2);
protected:
	StringTokenizer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
