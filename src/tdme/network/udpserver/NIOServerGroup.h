#pragma once

#include <stdint.h>

#include <exception>
#include <string>
#include <sstream>

#include <tdme/network/udpserver/NIOServer.h>
#include <tdme/network/udpserver/NIOServerGroupBase.h>

#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/ReferenceCounter.h>

using std::string;
using std::ostringstream;;

using tdme::os::threading::ReadWriteLock;
using tdme::utils::Exception;
using tdme::utils::ReferenceCounter;

namespace tdme {
namespace network {
namespace udpserver {

/**
 * Base class for NIO server groups
 * @author Andreas Drewke
 */
template <typename SERVER, typename CLIENT>
class NIOServerGroup : public NIOServerGroupBase {
public:
	typedef std::set<std::string> ClientKeySet;

	NIOServerGroup(const uint32_t groupId) :
		server(NULL),
		groupId(groupId),
		clientKeyListsReadWriteLock("nioservergroup_clientlists"){
		//
		ostringstream tmp;
		tmp << "unnamed.";
		tmp << groupId;
		key = tmp.str();
	}

	/**
	 * @brief group identification key
	 * @return group key
	 */
	const string& getKey() {
		return key;
	}

	/**
	 * @brief sets the group identification key
	 * @param group identification key
	 * @return if setting the key was succesful
	 */
	const bool setKey(const string &key) {
		if (server->setGroupKey(this, key) == true) {
			this->key = key;
			return true;
		} else {
			return false;
		}
	}

	/**
	 * @brief get a copy of current group client keys
	 * @return group client list
	 */
	ClientKeySet getClientKeySet() {
		// make a copy of the client key set
		ClientKeySet _clientKeySet;
		clientKeyListsReadWriteLock.readLock();
		_clientKeySet = clientKeySet;
		clientKeyListsReadWriteLock.unlock();
		// return copy
		return _clientKeySet;
	}

	/**
	 * @brief Adds a client to this group
	 * @param client
	 */
	virtual const bool addClient(CLIENT* client) {
		clientKeyListsReadWriteLock.writeLock();
		typename ClientKeySet::iterator it = clientKeySet.find(client->getId());
		// check if already exists
		if (it != clientKeySet.end()) {
			clientKeyListsReadWriteLock.unlock();
			return false;
		}
		clientKeySet.insert(make_pair(client->getId(), client));
		clientKeyListsReadWriteLock.unlock();
		return true;
	}

	/**
	 * @brief Removes a client from this group
	 * @param client
	 */
	virtual const bool removeClient(CLIENT* client) {
		clientKeyListsReadWriteLock.writeLock();
		typename ClientKeySet::iterator it = clientKeySet.find(client->getId());
		// check if not exists
		if (it == clientKeySet.end()) {
			clientKeyListsReadWriteLock.unlock();
			return false;
		}
		clientKeySet.erase(client->getId());
		clientKeyListsReadWriteLock.unlock();
		return true;
	}

	/**
	 * @brief Shuts down this server group
	 */
	virtual void shutdown() = 0;
protected:
	typedef std::map<const std::string, CLIENT*> ClientKeyMap;

	/*
	 * @brief event method called if group will be created, will be called from worker
	 */
	virtual void onCreate() throw (Exception) = 0;

	/*
	 * @brief event method called if client will be closed, will be called from worker
	 */
	virtual void onClose() throw (Exception) = 0;

	/**
	 * @brief Shuts down this group
	 */
	virtual void close() {
		// acquire reference for worker
		acquireReference();
		// create request
		NIOServerRequest* request = new NIOServerRequest(
			NIOServerRequest::REQUESTTYPE_GROUP_CLOSE,
			this
		);
		// delegate it to thread pool, but make close request not declinable
		server->workerThreadPool->addElement(request, false);
		// server call back
		server->closeClient(this);
	}

	//
	SERVER* server;
	uint32_t groupId;
	std::string key;

	ClientKeySet clientKeySet;

	ReadWriteLock clientKeyListsReadWriteLock;
};

};
};
};
