// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/concurrent/locks/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::Thread;


struct default_init_tag;
class java::util::concurrent::locks::AbstractQueuedSynchronizer_Node final
	: public Object
{

public:
	typedef Object super;

public: /* package */
	static constexpr int32_t CANCELLED { 1 };
	static constexpr int32_t CONDITION { -2 };
	static AbstractQueuedSynchronizer_Node* EXCLUSIVE;
	static constexpr int32_t PROPAGATE { -3 };
	static AbstractQueuedSynchronizer_Node* SHARED;
	static constexpr int32_t SIGNAL { -1 };
	std::atomic< AbstractQueuedSynchronizer_Node* > next {  };
	AbstractQueuedSynchronizer_Node* nextWaiter {  };
	std::atomic< AbstractQueuedSynchronizer_Node* > prev {  };
	std::atomic< Thread* > thread {  };
	std::atomic< int32_t > waitStatus {  };

protected:
	void ctor();
	void ctor(Thread* arg0, AbstractQueuedSynchronizer_Node* arg1);
	void ctor(Thread* arg0, int32_t arg1);

public: /* package */
	bool isShared();
	AbstractQueuedSynchronizer_Node* predecessor();

	// Generated
	AbstractQueuedSynchronizer_Node();
	AbstractQueuedSynchronizer_Node(Thread* arg0, AbstractQueuedSynchronizer_Node* arg1);
	AbstractQueuedSynchronizer_Node(Thread* arg0, int32_t arg1);
protected:
	AbstractQueuedSynchronizer_Node(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
