// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/util/concurrent/locks/fwd-tdme.h>
#include <java/util/concurrent/locks/ReentrantLock_Sync.h>

using java::util::concurrent::locks::ReentrantLock_Sync;


struct default_init_tag;
class java::util::concurrent::locks::ReentrantLock_FairSync final
	: public ReentrantLock_Sync
{

public:
	typedef ReentrantLock_Sync super;

private:
	static constexpr int64_t serialVersionUID { -3000897897090466540LL };

protected:
	void ctor();

public: /* package */
	void lock() override;

public: /* protected */
	bool tryAcquire(int32_t arg0) override;

	// Generated

public: /* package */
	ReentrantLock_FairSync();
protected:
	ReentrantLock_FairSync(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
