// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/AbstractList.h>
#include <java/util/RandomAccess.h>
#include <java/io/Serializable.h>

using java::util::AbstractList;
using java::util::RandomAccess;
using java::io::Serializable;
using java::lang::Object;

using java::lang::ObjectArray;

struct default_init_tag;
class java::util::Arrays_ArrayList
	: public AbstractList
	, public virtual RandomAccess
	, public virtual Serializable
{

public:
	typedef AbstractList super;

private:
	ObjectArray* a {  };
	static constexpr int64_t serialVersionUID { -2764017481108945198LL };

protected:
	void ctor(ObjectArray* arg0);

public:
	bool contains(Object* arg0) override;
	Object* get(int32_t arg0) override;
	int32_t indexOf(Object* arg0) override;
	Object* set(int32_t arg0, Object* arg1) override;
	int32_t size() override;
	ObjectArray* toArray() override;
	ObjectArray* toArray(ObjectArray* arg0) override;

	// Generated

public: /* package */
	Arrays_ArrayList(ObjectArray* arg0);
protected:
	Arrays_ArrayList(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
