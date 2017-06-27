// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/logging/Level.h>

using java::util::logging::Level;
extern void unimplemented_(const char16_t* name);
java::util::logging::Level::Level(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::logging::Level::Level(String* arg0, int32_t arg1)
	: Level(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::util::logging::Level::Level(String* arg0, int32_t arg1, String* arg2)
	: Level(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}

Level* java::util::logging::Level::ALL;
Level* java::util::logging::Level::CONFIG;
Level* java::util::logging::Level::FINE;
Level* java::util::logging::Level::FINER;
Level* java::util::logging::Level::FINEST;
Level* java::util::logging::Level::INFO;
Level* java::util::logging::Level::OFF;
Level* java::util::logging::Level::SEVERE;
Level* java::util::logging::Level::WARNING;
String* java::util::logging::Level::defaultBundle;
constexpr int64_t java::util::logging::Level::serialVersionUID;

void Level::ctor(String* arg0, int32_t arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Level::ctor(String* arg0, int32_t arg1)");
}

void Level::ctor(String* arg0, int32_t arg1, String* arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Level::ctor(String* arg0, int32_t arg1, String* arg2)");
}

bool Level::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Level::equals(Object* arg0)");
	return 0;
}

Level* Level::findLevel(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Level* Level::findLevel(String* arg0)");
	return 0;
}

String* Level::getLevelName()
{ /* stub */
	unimplemented_(u"String* Level::getLevelName()");
	return 0;
}

String* Level::getLocalizedLevelName()
{ /* stub */
return localizedLevelName ; /* getter */
}

String* Level::getLocalizedName()
{ /* stub */
	unimplemented_(u"String* Level::getLocalizedName()");
	return 0;
}

String* Level::getName()
{ /* stub */
return name ; /* getter */
}

String* Level::getResourceBundleName()
{ /* stub */
return resourceBundleName ; /* getter */
}

int32_t Level::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Level::hashCode()");
	return 0;
}

int32_t Level::intValue()
{ /* stub */
	unimplemented_(u"int32_t Level::intValue()");
	return 0;
}

Level* Level::parse(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Level* Level::parse(String* arg0)");
	return 0;
}

/* private: Object* Level::readResolve() */
String* Level::toString()
{ /* stub */
	unimplemented_(u"String* Level::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Level::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.logging.Level", 23);
    return c;
}

java::lang::Class* Level::getClass0()
{
	return class_();
}

