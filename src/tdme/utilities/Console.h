#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/os/threading/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;


/**
 * Console class
 * @author Andreas Drewke
 * @versio $Id$
 */
class tdme::utilities::Console
{
public:
	struct Logger
	{
		virtual ~Logger() {}
		virtual void println(const string& str) = 0;
		virtual void print(const string& str) = 0;
		virtual void println() = 0;
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
	static void println(const string& str);

	/**
	 * Print given string
	 * @param str string
	 */
	static void print(const string& str);

	/**
	 * Print new line to console
	 */
	static void println();

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

	/**
	 * Initialize log writer thread
	 */
	static void initLogWriterThread();

	//
	STATIC_DLL_IMPEXT static Mutex* mutex;
	STATIC_DLL_IMPEXT static bool newline;
	STATIC_DLL_IMPEXT static vector<string>* messages;
	STATIC_DLL_IMPEXT static LogWriterThread logWriterThread;
	STATIC_DLL_IMPEXT static Logger* logger;
};
