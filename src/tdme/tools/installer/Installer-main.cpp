#include <tdme/tools/installer/Installer.h>

#include <tdme/tdme.h>
#include <tdme/os/network/Network.h>

using tdme::os::network::Network;

int main(int argc, char** argv)
{
	// initialize network module
	Network::initialize();

	//
	return tdme::tools::installer::Installer::main(argc, argv);
}
