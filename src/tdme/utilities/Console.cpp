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

Mutex* Console::mutex = nullptr;
bool Console::newline = false;
vector<string>* Console::messages = nullptr;
Console::LogWriterThread Console::logWriterThread;
Console::Logger* Console::logger = nullptr;

Console::LogWriterThread::LogWriterThread(): Thread("console-logwriter-thread") {
	Console::mutex = new Mutex("console");
	Console::messages = new vector<string>();
	ofstream ofs("console.log", ofstream::trunc);
	ofs.close();
	start();
}

Console::LogWriterThread::~LogWriterThread() {
	Console::logWriterThread.stop();
	Console::logWriterThread.join();
}

void Console::LogWriterThread::run() {
	Console::println("Console::LogWriterThread(): start");
	while (isStopRequested() == false) {
		Console::mutex->lock();
		if (Console::messages->size() > 100) flush();
		Console::mutex->unlock();
		Thread::sleep(1000);
	}
	Console::mutex->lock();
	if (Console::messages->size() > 0) flush();
	Console::mutex->unlock();
	Console::println("Console::LogWriterThread(): done");
}

void Console::LogWriterThread::flush() {
	cout << "Console::LogWriterThread::flush()\n";
	ofstream ofs("console.log", ofstream::app);
	for (const auto& message: *Console::messages) {
		ofs << message;
		ofs << "\n";
	}
	ofs.close();
	Console::messages->clear();
}

void Console::setLogger(Console::Logger* logger) {
	if (Console::logger != nullptr) delete Console::logger;
	Console::logger = logger;
}

void Console::println(const string& str)
{
	mutex->lock();
	//
	auto& messages = *Console::messages;
	if (messages.empty() == true || newline == true) messages.push_back(string());
	messages[messages.size() - 1]+= str;
	if (messages.size() == 100) messages.erase(messages.begin());
	newline = true;
	//
	if (logger != nullptr) logger->println(str);
	cout << str << endl;
	//
	mutex->unlock();
}

void Console::print(const string& str)
{
	mutex->lock();
	//
	auto& messages = *Console::messages;
	if (messages.empty() == true || newline == true) messages.push_back(string());
	messages[messages.size() - 1]+= str;
	if (messages.size() == 100) messages.erase(messages.begin());
	newline = false;
	//
	if (logger != nullptr) logger->print(str);
	cout << str;
	//
	mutex->unlock();
}

void Console::println()
{
	mutex->lock();
	//
	auto& messages = *Console::messages;
	messages.push_back(string());
	if (messages.size() == 100) messages.erase(messages.begin());
	newline = true;
	//
	if (logger != nullptr) logger->println();
	cout << endl;
	//
	mutex->unlock();
}

void Console::shutdown() {
	mutex->lock();
	cout << "Console::shutdown()\n";
	ofstream ofs("console.log", ofstream::app);
	for (const auto& message: *Console::messages) {
		ofs << message;
		ofs << "\n";
	}
	ofs.close();
	Console::messages->clear();
	mutex->unlock();
}
