// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/logging/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using java::util::Map;
using java::util::logging::Level;


struct default_init_tag;
class java::util::logging::Level_KnownLevel final
	: public Object
{

public:
	typedef Object super;

private:
	static Map* intToLevels;

public: /* package */
	Level* levelObject {  };
	Level* mirroredLevel {  };

private:
	static Map* nameToLevels;

protected:
	void ctor(Level* arg0);

public: /* package */
	static void add(Level* arg0);
	static Level_KnownLevel* findByLocalizedLevelName(String* arg0);
	static Level_KnownLevel* findByLocalizedName(String* arg0);
	static Level_KnownLevel* findByName(String* arg0);
	static Level_KnownLevel* findByValue(int32_t arg0);
	static Level_KnownLevel* matches(Level* arg0);

	// Generated
	Level_KnownLevel(Level* arg0);
protected:
	Level_KnownLevel(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
