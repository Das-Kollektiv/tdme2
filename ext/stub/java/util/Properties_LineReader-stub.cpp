// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Properties_LineReader.h>

#include <java/util/Properties.h>

using java::util::Properties_LineReader;
using java::util::Properties;

extern void unimplemented_(const char16_t* name);
java::util::Properties_LineReader::Properties_LineReader(Properties *Properties_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, Properties_this(Properties_this)
{
	clinit();
}

java::util::Properties_LineReader::Properties_LineReader(Properties *Properties_this, InputStream* arg0)
	: Properties_LineReader(Properties_this, *static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::Properties_LineReader::Properties_LineReader(Properties *Properties_this, Reader* arg0)
	: Properties_LineReader(Properties_this, *static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void Properties_LineReader::ctor(InputStream* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Properties_LineReader::ctor(InputStream* arg0)");
}

void Properties_LineReader::ctor(Reader* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Properties_LineReader::ctor(Reader* arg0)");
}

int32_t Properties_LineReader::readLine()
{ /* stub */
	unimplemented_(u"int32_t Properties_LineReader::readLine()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Properties_LineReader::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Properties.LineReader", 31);
    return c;
}

java::lang::Class* Properties_LineReader::getClass0()
{
	return class_();
}

