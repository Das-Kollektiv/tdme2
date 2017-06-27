// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/logging/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using java::lang::Throwable;
using java::util::ArrayList;
using java::util::Locale;
using java::util::ResourceBundle;
using java::util::logging::Filter;
using java::util::logging::Handler;
using java::util::logging::Level;
using java::util::logging::LogManager_LoggerWeakRef;
using java::util::logging::LogManager;
using java::util::logging::LogRecord;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace util {
namespace logging {
typedef ::SubArray< ::java::util::logging::Handler, ::java::lang::ObjectArray > HandlerArray;
}  // namespace logging
}  // namespace util
}  // namespace java

using java::lang::ObjectArray;
using java::util::logging::HandlerArray;

struct default_init_tag;
class java::util::logging::Logger
	: public virtual Object
{

public:
	typedef Object super;
	static String* GLOBAL_LOGGER_NAME;

public: /* package */
	static String* SYSTEM_LOGGER_RB_NAME;

private:
	bool anonymous {  };
	ResourceBundle* catalog {  };
	Locale* catalogLocale {  };
	String* catalogName {  };
	static HandlerArray* emptyHandlers;
	Filter* filter {  };

public:
	static Logger* global;

private:
	ArrayList* handlers {  };
	ArrayList* kids {  };
	Level* levelObject {  };
	std::atomic< int32_t > levelValue {  };
	LogManager* manager {  };
	String* name {  };
	static int32_t offValue;
	Logger* parent {  };
	String* resourceBundleName {  };
	static Object* treeLock;
	bool useParentHandlers {  };

	/*void ctor(String* arg0); (private) */
protected:
	void ctor(String* arg0, String* arg1);

public:
	virtual void addHandler(Handler* arg0);
	/*void checkPermission(); (private) */
	virtual void config(String* arg0);
	/*static Logger* demandLogger(String* arg0, String* arg1); (private) */
	/*void doLog(LogRecord* arg0); (private) */
	/*void doLog(LogRecord* arg0, String* arg1); (private) */
	/*void doSetParent(Logger* arg0); (private) */
	virtual void entering(String* arg0, String* arg1);
	virtual void entering(String* arg0, String* arg1, Object* arg2);
	virtual void entering(String* arg0, String* arg1, ObjectArray* arg2);
	virtual void exiting(String* arg0, String* arg1);
	virtual void exiting(String* arg0, String* arg1, Object* arg2);
	/*ResourceBundle* findResourceBundle(String* arg0); (private) */
	/*static ResourceBundle* findSystemResourceBundle(Locale* arg0); (private) */
	virtual void fine(String* arg0);
	virtual void finer(String* arg0);
	virtual void finest(String* arg0);
	static Logger* getAnonymousLogger();
	static Logger* getAnonymousLogger(String* arg0);
	/*String* getEffectiveResourceBundleName(); (private) */
	virtual Filter* getFilter();
	virtual HandlerArray* getHandlers();
	virtual Level* getLevel();
	static Logger* getLogger(String* arg0);
	static Logger* getLogger(String* arg0, String* arg1);
	virtual String* getName();
	virtual Logger* getParent();
	virtual ResourceBundle* getResourceBundle();
	virtual String* getResourceBundleName();
	virtual bool getUseParentHandlers();
	virtual void info(String* arg0);
	virtual bool isLoggable(Level* arg0);
	virtual void log(LogRecord* arg0);
	virtual void log(Level* arg0, String* arg1);
	virtual void log(Level* arg0, String* arg1, Object* arg2);
	virtual void log(Level* arg0, String* arg1, ObjectArray* arg2);
	virtual void log(Level* arg0, String* arg1, Throwable* arg2);
	virtual void logp(Level* arg0, String* arg1, String* arg2, String* arg3);
	virtual void logp(Level* arg0, String* arg1, String* arg2, String* arg3, Object* arg4);
	virtual void logp(Level* arg0, String* arg1, String* arg2, String* arg3, ObjectArray* arg4);
	virtual void logp(Level* arg0, String* arg1, String* arg2, String* arg3, Throwable* arg4);
	virtual void logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4);
	virtual void logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4, Object* arg5);
	virtual void logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4, ObjectArray* arg5);
	virtual void logrb(Level* arg0, String* arg1, String* arg2, String* arg3, String* arg4, Throwable* arg5);

public: /* package */
	void removeChildLogger(LogManager_LoggerWeakRef* arg0);

public:
	virtual void removeHandler(Handler* arg0);
	virtual void setFilter(Filter* arg0);
	virtual void setLevel(Level* arg0);

public: /* package */
	virtual void setLogManager(LogManager* arg0);

public:
	virtual void setParent(Logger* arg0);
	virtual void setUseParentHandlers(bool arg0);
	/*void setupResourceInfo(String* arg0); (private) */
	virtual void severe(String* arg0);
	virtual void throwing(String* arg0, String* arg1, Throwable* arg2);
	/*void updateEffectiveLevel(); (private) */
	virtual void warning(String* arg0);

	// Generated

public: /* protected */
	Logger(String* arg0, String* arg1);
protected:
	Logger(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
