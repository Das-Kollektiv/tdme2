// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Map.h>

using java::lang::Object;
using java::util::Map;
using java::lang::String;
using java::util::Collection;
using java::util::Set;


struct default_init_tag;
class java::util::AbstractMap
	: public virtual Object
	, public virtual Map
{

public:
	typedef Object super;

public: /* package */
	std::atomic< Set* > keySet_ {  };
	std::atomic< Collection* > values_ {  };

protected:
	void ctor();

public:
	void clear() override;

public: /* protected */
	Object* clone() override;

public:
	bool containsKey(Object* arg0) override;
	bool containsValue(Object* arg0) override;
	/*Set* entrySet(); (already declared) */
	/*static bool eq(Object* arg0, Object* arg1); (private) */
	bool equals(Object* arg0) override;
	Object* get(Object* arg0) override;
	int32_t hashCode() override;
	bool isEmpty() override;
	Set* keySet() override;
	Object* put(Object* arg0, Object* arg1) override;
	void putAll(Map* arg0) override;
	Object* remove(Object* arg0) override;
	int32_t size() override;
	String* toString() override;
	Collection* values() override;

	// Generated

public: /* protected */
	AbstractMap();
protected:
	AbstractMap(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
