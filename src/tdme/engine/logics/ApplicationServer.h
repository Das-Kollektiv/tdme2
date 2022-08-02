#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/network/udpserver/UDPServer.h>
#include <tdme/network/udpserver/UDPServerClient.h>
#include <tdme/utilities/Exception.h>

using std::string;
using std::vector;

using tdme::engine::logics::Context;
using tdme::engine::logics::ServerThread;
using tdme::network::udpserver::UDPServer;
using tdme::network::udpserver::UDPServerClient;
using tdme::utilities::Exception;

/**
 * Application server
 */
class tdme::engine::logics::ApplicationServer: public UDPServer {
	friend class ApplicationServerClient;

public:
	/**
	 * Public constructor
	 * @param name name
	 * @param host host
	 * @param port port
	 * @param maxCCU max CCU
	 * @param pathFindingThreadCount path finding thread count
	 */
	ApplicationServer(const string& name, const string& host, const unsigned int port, const unsigned int maxCCU, int pathFindingThreadCount);

	/**
	 * Destructor
	 */
	virtual ~ApplicationServer();

	/**
	 * Setup default / minumum required logics
	 */
	virtual void setupLogics() = 0;

	// overridden methods
	virtual void run() override;

protected:
	Context* context { nullptr };

	/**
	 * Create context
	 * @return context
	 */
	virtual Context* createContext();

	/**
	 * Accept
	 * @param clientId client id
	 * @param ip ip
	 * @param port port
	 */
	virtual UDPServerClient* accept(const uint32_t clientId, const string& ip, const unsigned int port) override;

private:
	ServerThread* logicsThread { nullptr };
	int pathFindingThreadCount;

};
