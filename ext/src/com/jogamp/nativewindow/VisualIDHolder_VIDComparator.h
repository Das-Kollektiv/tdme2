// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Comparator.h>

using java::lang::Object;
using java::util::Comparator;
using com::jogamp::nativewindow::VisualIDHolder_VIDType;
using com::jogamp::nativewindow::VisualIDHolder;


struct default_init_tag;
class com::jogamp::nativewindow::VisualIDHolder_VIDComparator
	: public virtual Object
	, public virtual Comparator
{

public:
	typedef Object super;

private:
	VisualIDHolder_VIDType* type {  };

protected:
	void ctor(VisualIDHolder_VIDType* arg0);

public:
	virtual int32_t compare(VisualIDHolder* arg0, VisualIDHolder* arg1);

	// Generated
	VisualIDHolder_VIDComparator(VisualIDHolder_VIDType* arg0);
protected:
	VisualIDHolder_VIDComparator(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual bool equals(Object* obj);
	virtual int32_t compare(Object* o1, Object* o2) override;

private:
	virtual ::java::lang::Class* getClass0();
};
