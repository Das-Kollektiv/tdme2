// Generated from /tdme/lib/json.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/json/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::InputStream;
using java::io::Reader;
using java::lang::String;
using org::json::JSONException;


struct default_init_tag;
class org::json::JSONTokener
	: public virtual Object
{

public:
	typedef Object super;

private:
	int32_t character {  };
	bool eof {  };
	int32_t index {  };
	int32_t line {  };
	char16_t previous {  };
	Reader* reader {  };
	bool usePrevious {  };

protected:
	void ctor(Reader* reader);
	void ctor(InputStream* inputStream);
	void ctor(String* s);

public:
	virtual void back();
	static int32_t dehexchar(char16_t c);
	virtual bool end();
	virtual bool more();
	virtual char16_t next();
	virtual char16_t next(char16_t c);
	virtual String* next(int32_t n);
	virtual char16_t nextClean();
	virtual String* nextString(char16_t quote);
	virtual String* nextTo(char16_t arg0);
	virtual String* nextTo(String* delimiters);
	virtual Object* nextValue();
	virtual char16_t skipTo(char16_t arg0);
	virtual JSONException* syntaxError(String* message);
	String* toString() override;

	// Generated
	JSONTokener(Reader* reader);
	JSONTokener(InputStream* inputStream);
	JSONTokener(String* s);
protected:
	JSONTokener(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
