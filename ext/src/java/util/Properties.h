// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/Hashtable.h>

using java::util::Hashtable;
using java::io::BufferedWriter;
using java::io::InputStream;
using java::io::OutputStream;
using java::io::PrintStream;
using java::io::PrintWriter;
using java::io::Reader;
using java::io::Writer;
using java::lang::Object;
using java::lang::String;
using java::util::Enumeration;
using java::util::Properties_LineReader;
using java::util::Set;


struct default_init_tag;
class java::util::Properties
	: public Hashtable
{

public:
	typedef Hashtable super;

public: /* protected */
	Properties* defaults {  };

private:
	static char16_tArray* hexDigit;
	static constexpr int64_t serialVersionUID { 4112578634029874840LL };

protected:
	void ctor();
	void ctor(Properties* arg0);
	/*void enumerate(Hashtable* arg0); (private) */
	/*void enumerateStringProperties(Hashtable* arg0); (private) */

public:
	virtual String* getProperty(String* arg0);
	virtual String* getProperty(String* arg0, String* arg1);
	virtual void list(PrintStream* arg0);
	virtual void list(PrintWriter* arg0);
	virtual void load(Reader* arg0);
	virtual void load(InputStream* arg0);
	/*void load0(Properties_LineReader* arg0); (private) */
	/*String* loadConvert(char16_tArray* arg0, int32_t arg1, int32_t arg2, char16_tArray* arg3); (private) */
	virtual void loadFromXML(InputStream* arg0);
	virtual Enumeration* propertyNames();
	virtual void save(OutputStream* arg0, String* arg1);
	/*String* saveConvert(String* arg0, bool arg1, bool arg2); (private) */
	virtual Object* setProperty(String* arg0, String* arg1);
	virtual void store(Writer* arg0, String* arg1);
	virtual void store(OutputStream* arg0, String* arg1);
	/*void store0(BufferedWriter* arg0, String* arg1, bool arg2); (private) */
	virtual void storeToXML(OutputStream* arg0, String* arg1);
	virtual void storeToXML(OutputStream* arg0, String* arg1, String* arg2);
	virtual Set* stringPropertyNames();
	/*static char16_t toHex(int32_t arg0); (private) */
	/*static void writeComments(BufferedWriter* arg0, String* arg1); (private) */

	// Generated
	Properties();
	Properties(Properties* arg0);
protected:
	Properties(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
