#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <tdme/tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Time.h>

using namespace std;

using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;
using tdme::utilities::Console;
using tdme::utilities::Time;

Mutex Console::mutex("console");
bool Console::newline = false;
vector<string> Console::messages;
Console::Logger* Console::logger = nullptr;
unique_ptr<Console::LogWriterThread> Console::logWriterThread = make_unique<Console::LogWriterThread>();

Console::LogWriterThread::LogWriterThread(): Thread("console-logwriter-thread") {
	ofstream ofs(std::filesystem::u8path("console.log"), ofstream::trunc);
	ofs.close();
	start();
}

Console::LogWriterThread::~LogWriterThread() {
}

void Console::LogWriterThread::run() {
	Console::println("Console::LogWriterThread(): start");
	while (isStopRequested() == false) {
		Console::mutex.lock();
		if (Console::messages.size() > HISTORY_LINECOUNT) flush();
		Console::mutex.unlock();
		Thread::sleep(1000);
	}
	Console::mutex.lock();
	if (Console::messages.size() > 0) flush();
	Console::mutex.unlock();
	Console::println("Console::LogWriterThread(): done");
}

void Console::LogWriterThread::flush() {
	ofstream ofs(std::filesystem::u8path("console.log"), ofstream::app);
	for (const auto& message: Console::messages) {
		ofs << message << endl;
	}
	ofs.close();
	Console::messages.clear();
}

void Console::setLogger(Console::Logger* logger) {
	if (Console::logger == logger) return;
	if (Console::logger != nullptr) delete Console::logger;
	Console::logger = logger;
}

void Console::println(const string_view& str)
{
	mutex.lock();
	//
	if (messages.empty() == true || newline == true) messages.push_back(string());
	messages[messages.size() - 1]+= str;
	if (messages.size() == HISTORY_LINECOUNT) messages.erase(messages.begin());
	newline = true;
	//
	if (logger != nullptr) logger->println(str);
	cout << str << endl;
	//
	mutex.unlock();
}

void Console::print(const string_view& str)
{
	mutex.lock();
	//
	if (messages.empty() == true || newline == true) messages.push_back(string());
	messages[messages.size() - 1]+= str;
	if (messages.size() == HISTORY_LINECOUNT) messages.erase(messages.begin());
	newline = false;
	//
	if (logger != nullptr) logger->print(str);
	cout << str;
	//
	mutex.unlock();
}

void Console::println()
{
	mutex.lock();
	//
	messages.push_back(string());
	if (messages.size() == HISTORY_LINECOUNT) messages.erase(messages.begin());
	newline = true;
	//
	if (logger != nullptr) logger->println();
	cout << endl;
	//
	mutex.unlock();
}

void Console::shutdown() {
	// shut down logwriter thread
	Console::logWriterThread->stop();
	Console::logWriterThread->join();
	Console::logWriterThread = nullptr;
}
