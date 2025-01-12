#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <yannet/yannet.h>
#include <yannet/os/threading/fwd-yannet.h>
#include <yannet/os/threading/Mutex.h>
#include <yannet/os/threading/Thread.h>
#include <yannet/utilities/fwd-yannet.h>

using std::string;
using std::string_view;
using std::unique_ptr;
using std::vector;

// namespaces
namespace yannet {
namespace utilities {
	using ::yannet::os::threading::Mutex;
	using ::yannet::os::threading::Thread;
}
}

/**
 * Console class
 * @author Andreas Drewke
 * @versio $Id$
 */
class yannet::utilities::Console
{
public:
	static constexpr int HISTORY_LINECOUNT { 5000 };

	struct Logger
	{
		virtual ~Logger() {}
		virtual void printLine(const string_view& str) = 0;
		virtual void print(const string_view& str) = 0;
		virtual void printLine() = 0;
	};

	/**
	 * Set logger
	 * @param logger logger
	 */
	static void setLogger(Logger* logger);

	/**
	 * Print given string and trailing newline to console
	 * @param str string
	 */
	static void printLine(const string_view& str);

	/**
	 * Print given string
	 * @param str string
	 */
	static void print(const string_view& str);

	/**
	 * Print new line to console
	 */
	static void printLine();

	/**
	 * Shutdown console logging and especially writing log to file
	 */
	static void shutdown();

private:
	class LogWriterThread: public Thread {
	public:
		// forbid class copy
		FORBID_CLASS_COPY(LogWriterThread)
		//
		LogWriterThread();
		~LogWriterThread();
		void flush();
	private:
		void run();
	};

	//
	YANNET_STATIC_DLL_IMPEXT static Mutex mutex;
	YANNET_STATIC_DLL_IMPEXT static bool newline;
	YANNET_STATIC_DLL_IMPEXT static vector<string> messages;
	YANNET_STATIC_DLL_IMPEXT static Logger* logger;
	YANNET_STATIC_DLL_IMPEXT static unique_ptr<LogWriterThread> logWriterThread;
};
