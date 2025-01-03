#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include <yannet/yannet.h>

#include <yannet/network/udpserver/Server.h>
#include <yannet/network/udpserver/ServerGroupBase.h>

#include <yannet/os/threading/ReadWriteLock.h>
#include <yannet/utilities/Exception.h>
#include <yannet/utilities/Reference.h>

using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;

namespace yannet {
namespace network {
namespace udpserver {

using ::yannet::os::threading::ReadWriteLock;
using ::yannet::utilities::Exception;
using ::yannet::utilities::Reference;

/**
 * Base class for network server groups
 * @author Andreas Drewke
 */
template <typename SERVER, typename CLIENT, typename GROUP>
class ServerGroup : public ServerGroupBase {
public:
	typedef unordered_set<string> ClientKeySet;

	// forbid class copy
	FORBID_CLASS_COPY(ServerGroup)

	/**
	 * Public constructor
	 */
	ServerGroup(const uint32_t groupId) :
		server(nullptr),
		groupId(groupId),
		clientKeyListsReadWriteLock("nioservergroup_clientlists"){
		//
		key = "unnamed." + to_string(groupId);
	}

	/**
	 * @brief group identification key
	 * @return group key
	 */
	inline const string& getKey() {
		return key;
	}

	/**
	 * @brief sets the group identification key
	 * @param &key group identification key
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
	 * @param client client
	 */
	virtual const bool addClient(CLIENT* client) {
		clientKeyListsReadWriteLock.writeLock();
		auto it = clientKeySet.find(client->getKey());
		// check if already exists
		if (it != clientKeySet.end()) {
			clientKeyListsReadWriteLock.unlock();
			return false;
		}
		clientKeySet.insert(client->getKey());
		clientKeyListsReadWriteLock.unlock();
		return true;
	}

	/**
	 * @brief Removes a client from this group
	 * @param client client
	 */
	virtual const bool removeClient(CLIENT* client) {
		clientKeyListsReadWriteLock.writeLock();
		auto it = clientKeySet.find(client->getKey());
		// check if not exists
		if (it == clientKeySet.end()) {
			clientKeyListsReadWriteLock.unlock();
			return false;
		}
		clientKeySet.erase(client->getKey());
		clientKeyListsReadWriteLock.unlock();
		return true;
	}

	/**
	 * @brief Shuts down this server group
	 */
	virtual void shutdown() = 0;
protected:
	typedef unordered_map<string, CLIENT*> ClientKeyMap;

	/*
	 * @brief event method called if group will be created, will be called from worker
	 */
	virtual void onCreate() = 0;

	/*
	 * @brief event method called if client will be closed, will be called from worker
	 */
	virtual void onClose() = 0;

	/**
	 * @brief Shuts down this group
	 */
	virtual void close() {
		// acquire reference for worker
		acquireReference();
		// create request
		ServerRequest* request = new ServerRequest(
			ServerRequest::REQUESTTYPE_GROUP_CLOSE,
			this
		);
		// delegate it to thread pool, but make close request not declinable
		server->workerThreadPool->addElement(request, false);
		// server call back
		server->closeGroup(static_cast<GROUP*>(this));
	}

	//
	SERVER* server;
	uint32_t groupId;
	string key;

	ClientKeySet clientKeySet;

	ReadWriteLock clientKeyListsReadWriteLock;
};

};
};
};
