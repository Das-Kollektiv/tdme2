// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/TimerTask.h>

using java::util::TimerTask;
extern void unimplemented_(const char16_t* name);
java::util::TimerTask::TimerTask(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::TimerTask::TimerTask()
	: TimerTask(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int32_t java::util::TimerTask::CANCELLED;
constexpr int32_t java::util::TimerTask::EXECUTED;
constexpr int32_t java::util::TimerTask::SCHEDULED;
constexpr int32_t java::util::TimerTask::VIRGIN;

void TimerTask::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void TimerTask::ctor()");
}

bool TimerTask::cancel()
{ /* stub */
	unimplemented_(u"bool TimerTask::cancel()");
	return 0;
}

int64_t TimerTask::scheduledExecutionTime()
{ /* stub */
	unimplemented_(u"int64_t TimerTask::scheduledExecutionTime()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TimerTask::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.TimerTask", 19);
    return c;
}

java::lang::Class* TimerTask::getClass0()
{
	return class_();
}

