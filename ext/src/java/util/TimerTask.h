// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/lang/Runnable.h>

using java::lang::Object;
using java::lang::Runnable;


struct default_init_tag;
class java::util::TimerTask
	: public virtual Object
	, public virtual Runnable
{

public:
	typedef Object super;

public: /* package */
	static constexpr int32_t CANCELLED { 3 };
	static constexpr int32_t EXECUTED { 2 };
	static constexpr int32_t SCHEDULED { 1 };
	static constexpr int32_t VIRGIN { 0 };
	Object* lock {  };
	int64_t nextExecutionTime {  };
	int64_t period {  };
	int32_t state {  };

protected:
	void ctor();

public:
	virtual bool cancel();
	/*void run(); (already declared) */
	virtual int64_t scheduledExecutionTime();

	// Generated

public: /* protected */
	TimerTask();
protected:
	TimerTask(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
