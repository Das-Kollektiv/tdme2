#include <tdme/tdme.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

#include <yannet/network/httpclient/HTTPDownloadClient.h>
#include <yannet/os/network/Network.h>

using std::to_string;

using tdme::os::threading::Thread;
using tdme::utilities::Console;
using tdme::utilities::Exception;

using yannet::network::httpclient::HTTPDownloadClient;
using yannet::os::network::Network;

int main(int argc, char *argv[]) {
	Network::initialize();
	//
	try {
		HTTPDownloadClient httpDownloadClient;
		httpDownloadClient.setFile("haiku-r1beta4-x86_64-anyboot.iso");
		httpDownloadClient.setURL("http://mirror.rit.edu/haiku/r1beta4/haiku-r1beta4-x86_64-anyboot.iso");
		httpDownloadClient.start();
		Console::printLine("Download started");
		while (httpDownloadClient.isFinished() == false) {
			Console::printLine("Download progress: " + to_string(httpDownloadClient.getProgress() * 100.0f));
			Thread::sleep(1000LL);
		}
		httpDownloadClient.join();
		Console::printLine("Download finished");
	} catch (Exception& exception) {
		Console::printLine(string("Fail: ") + exception.what());
	}
	//
	Console::shutdown();
	return 0;
}

