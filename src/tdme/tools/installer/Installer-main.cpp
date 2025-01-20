#include <tdme/tools/installer/Installer.h>


#include <yannet/os/network/Network.h>

using yannet::os::network::Network;

int main(int argc, char** argv)
{
	// initialize network module
	Network::initialize();

	//
	return tdme::tools::installer::Installer::main(argc, argv);
}
