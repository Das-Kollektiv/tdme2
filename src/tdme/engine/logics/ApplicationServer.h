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
	// forbid class copy
	FORBID_CLASS_COPY(ApplicationServer)

	/**
	 * Public constructor
	 * @param name name
	 * @param host host
	 * @param port port
	 * @param maxCCU max CCU
	 * @param pathFindingThreadCount path finding thread count
	 */
	ApplicationServer(const string& name, const string& host, const uint16_t port, const unsigned int maxCCU, int pathFindingThreadCount);

	/**
	 * Destructor
	 */
	virtual ~ApplicationServer();

	// overridden methods
	virtual void start() override;
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
	virtual UDPServerClient* accept(const uint32_t clientId, const string& ip, const uint16_t port) override;

	/**
	 * Setup default / minumum required logics
	 */
	virtual void setupLogics() = 0;

private:
	ServerThread* logicsThread { nullptr };
	int pathFindingThreadCount;

};
