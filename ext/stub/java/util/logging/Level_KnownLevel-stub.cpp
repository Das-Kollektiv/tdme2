// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/logging/Level_KnownLevel.h>

using java::util::logging::Level_KnownLevel;
extern void unimplemented_(const char16_t* name);
java::util::logging::Level_KnownLevel::Level_KnownLevel(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::logging::Level_KnownLevel::Level_KnownLevel(Level* arg0)
	: Level_KnownLevel(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

Map* java::util::logging::Level_KnownLevel::intToLevels;
Map* java::util::logging::Level_KnownLevel::nameToLevels;

void Level_KnownLevel::ctor(Level* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Level_KnownLevel::ctor(Level* arg0)");
}

void Level_KnownLevel::add(Level* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"void Level_KnownLevel::add(Level* arg0)");
}

Level_KnownLevel* Level_KnownLevel::findByLocalizedLevelName(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Level_KnownLevel* Level_KnownLevel::findByLocalizedLevelName(String* arg0)");
	return 0;
}

Level_KnownLevel* Level_KnownLevel::findByLocalizedName(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Level_KnownLevel* Level_KnownLevel::findByLocalizedName(String* arg0)");
	return 0;
}

Level_KnownLevel* Level_KnownLevel::findByName(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Level_KnownLevel* Level_KnownLevel::findByName(String* arg0)");
	return 0;
}

Level_KnownLevel* Level_KnownLevel::findByValue(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Level_KnownLevel* Level_KnownLevel::findByValue(int32_t arg0)");
	return 0;
}

Level_KnownLevel* Level_KnownLevel::matches(Level* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Level_KnownLevel* Level_KnownLevel::matches(Level* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Level_KnownLevel::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.logging.Level.KnownLevel", 34);
    return c;
}

java::lang::Class* Level_KnownLevel::getClass0()
{
	return class_();
}

