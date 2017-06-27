// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/concurrent/fwd-tdme.h>
#include <java/util/concurrent/locks/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/concurrent/locks/Condition.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::util::concurrent::locks::Condition;
using java::io::Serializable;
using java::util::Collection;
using java::util::Date;
using java::util::concurrent::TimeUnit;
using java::util::concurrent::locks::AbstractQueuedSynchronizer_Node;
using java::util::concurrent::locks::AbstractQueuedSynchronizer;


struct default_init_tag;
class java::util::concurrent::locks::AbstractQueuedSynchronizer_ConditionObject
	: public virtual Object
	, public virtual Condition
	, public virtual Serializable
{

public:
	typedef Object super;

private:
	static constexpr int32_t REINTERRUPT { 1 };
	static constexpr int32_t THROW_IE { -1 };
	AbstractQueuedSynchronizer_Node* firstWaiter {  };
	AbstractQueuedSynchronizer_Node* lastWaiter {  };
	static constexpr int64_t serialVersionUID { 1173984872572414699LL };

public: /* package */
	AbstractQueuedSynchronizer* this$0 {  };

protected:
	void ctor();
	/*AbstractQueuedSynchronizer_Node* addConditionWaiter(); (private) */

public:
	void await() override;
	bool await(int64_t arg0, TimeUnit* arg1) override;
	int64_t awaitNanos(int64_t arg0) override;
	void awaitUninterruptibly() override;
	bool awaitUntil(Date* arg0) override;
	/*int32_t checkInterruptWhileWaiting(AbstractQueuedSynchronizer_Node* arg0); (private) */
	/*void doSignal(AbstractQueuedSynchronizer_Node* arg0); (private) */
	/*void doSignalAll(AbstractQueuedSynchronizer_Node* arg0); (private) */

public: /* protected */
	int32_t getWaitQueueLength();
	Collection* getWaitingThreads();
	bool hasWaiters();

public: /* package */
	bool isOwnedBy(AbstractQueuedSynchronizer* arg0);
	/*void reportInterruptAfterWait(int32_t arg0); (private) */

public:
	void signal() override;
	void signalAll() override;
	/*void unlinkCancelledWaiters(); (private) */

	// Generated
	AbstractQueuedSynchronizer_ConditionObject(AbstractQueuedSynchronizer *AbstractQueuedSynchronizer_this);
protected:
	AbstractQueuedSynchronizer_ConditionObject(AbstractQueuedSynchronizer *AbstractQueuedSynchronizer_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	AbstractQueuedSynchronizer *AbstractQueuedSynchronizer_this;

private:
	virtual ::java::lang::Class* getClass0();
};
