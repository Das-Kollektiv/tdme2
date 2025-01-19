#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>

using std::string;

/**
 * New client logic interface
 * @author Andreas Drewke
 */
struct tdme::engine::logics::NewClientLogic {

	/**
	 * Public destructor
	 */
	virtual ~NewClientLogic() {}

	/**
	 * Handle new client
	 * @param clientId client id
	 * @param hostName host name
	 * @returns success
	 */
	virtual bool handleNewClient(const string& clientId, const string& hostName) = 0;

};
