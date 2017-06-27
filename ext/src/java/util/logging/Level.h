// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/logging/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::String;


struct default_init_tag;
class java::util::logging::Level
	: public virtual Object
	, public virtual Serializable
{

public:
	typedef Object super;
	static Level* ALL;
	static Level* CONFIG;
	static Level* FINE;
	static Level* FINER;
	static Level* FINEST;
	static Level* INFO;
	static Level* OFF;
	static Level* SEVERE;
	static Level* WARNING;

private:
	static String* defaultBundle;
	String* localizedLevelName {  };
	String* name {  };
	String* resourceBundleName {  };
	static constexpr int64_t serialVersionUID { -8176160795706313070LL };
	int32_t value {  };

protected:
	void ctor(String* arg0, int32_t arg1);
	void ctor(String* arg0, int32_t arg1, String* arg2);

public:
	bool equals(Object* arg0) override;

public: /* package */
	static Level* findLevel(String* arg0);
	String* getLevelName();
	String* getLocalizedLevelName();

public:
	virtual String* getLocalizedName();
	virtual String* getName();
	virtual String* getResourceBundleName();
	int32_t hashCode() override;
	int32_t intValue();
	static Level* parse(String* arg0);
	/*Object* readResolve(); (private) */
	String* toString() override;

	// Generated

public: /* protected */
	Level(String* arg0, int32_t arg1);
	Level(String* arg0, int32_t arg1, String* arg2);
protected:
	Level(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
