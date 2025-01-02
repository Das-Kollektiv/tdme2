#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <yannet/yannet.h>
#include <yannet/network/udpserver/ServerWorkerThreadPool.h>
#include <yannet/os/threading/Barrier.h>
#include <yannet/os/threading/ReadWriteLock.h>

using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;

namespace yannet {
namespace network {
namespace udpserver {

using yannet::os::threading::Barrier;
using yannet::os::threading::ReadWriteLock;

class ServerWorkerThreadPool;

/**
 * Base class for network servers
 * @author Andreas Drewke
 */
template <typename CLIENT, typename GROUP>
class Server {
public:
	typedef unordered_set<string> ClientKeySet;
	typedef unordered_set<string> GroupKeySet;

	// forbid class copy
	FORBID_CLASS_COPY(Server)

	/**
	 * @brief Public constructor
	 * @param name server name
	 * @param host host where to bind the server socket
	 * @param port port to listen on
s			 * @param maxCCU max ccu
	 */
	Server(const string& name, const string& host, uint16_t port, int maxCCU) :
		name(name),
		host(host),
		port(port),
		maxCCU(maxCCU),
		clientKeyListsReadWriteLock("nioserver_clientlist"),
		groupKeyListsReadWriteLock("nioserver_grouplist"),
		ioThreadCount(1),
		workerThreadPoolCount(2),
		workerThreadPoolMaxElements(128) {
		//
	}

	/**
	 * @brief Sets up the numbers of threads to handle IO and framing
	 * @param ioThreadCount IO thread count
	 */
	inline void setIOThreadCount(int ioThreadCount) {
		this->ioThreadCount = ioThreadCount;
	}

	/**
	 * @brief Sets up the number of workers that handle requests in thread pool
	 * @param workerThreadCount number of workers in thread pool
	 */
	inline void setWorkerThreadCount(int workerThreadCount) {
		workerThreadPoolCount = workerThreadCount;
	}

	/**
	 * @brief Sets up max number of elements in worker thread pool queue
	 * @param maxElements max elements
	 */
	inline void setThreadPoolMaxElements(int maxElements) {
		workerThreadPoolMaxElements = maxElements;
	}

	/**
	 * @brief destructor
	 */
	virtual ~Server() {
	}

	/**
	 * @brief get a copy of current client keys
	 * @return client list
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
	 * @brief retrieve a client by key, the client reference is acquired, must be released after usage
	 * @param clientKey client identification key
	 * @return client or nullptr
	 */
	CLIENT* getClientByKey(const string& clientKey) {
		clientKeyListsReadWriteLock.readLock();
		auto it = clientKeyMap.find(clientKey);
		auto client = it != clientKeyMap.end()?it->second:nullptr;
		if (client != nullptr) {
			client->acquireReference();
		}
		clientKeyListsReadWriteLock.unlock();
		//
		return client;
	}

	/**
	 * @brief get a copy of current group keys
	 * @return group list
	 */
	ClientKeySet getGroupKeySet() {
		// make a copy of the group key set
		GroupKeySet _groupKeySet;
		groupKeyListsReadWriteLock.readLock();
		_groupKeySet = groupKeySet;
		groupKeyListsReadWriteLock.unlock();
		// return copy
		return _groupKeySet;
	}

	/**
	 * @brief retrieve a group by key, the group reference is acquired, must be released after usage
	 * @param groupKey group identification key
	 * @return group or nullptr
	 */
	GROUP* getGroupByKey(const string& groupKey) {
		groupKeyListsReadWriteLock.readLock();
		auto it = groupKeyMap.find(groupKey);
		auto group = it != groupKeyMap.end()?it->second:nullptr;
		if (group != nullptr) {
			group->acquireReference();
		}
		groupKeyListsReadWriteLock.unlock();
		//
		return group;
	}

protected:
	typedef unordered_map<string, CLIENT*> ClientKeyMap;
	typedef unordered_map<string, CLIENT*> GroupKeyMap;
	typedef unordered_set<CLIENT*> ClientSet;

	/**
	 * @brief sets a client identification key
	 * @param client client
	 * @param &clientKey client identification key
	 * @return if setting the key was successful
	 */
	bool setClientKey(CLIENT* client, const string &clientKey) {
		clientKeyListsReadWriteLock.writeLock();
		// set new client key association
		auto it = clientKeyMap.find(clientKey);
		if (it != clientKeyMap.end()) {
			clientKeyListsReadWriteLock.unlock();
			// nope, we could't set the key
			return false;
		}
		// remove old client key association if changed
		if (client->getKey() != clientKey) {
			clientKeyMap.erase(client->getKey());
		}
		// set client in map
		clientKeyMap[clientKey] = client;
		// set client key in set
		clientKeySet.insert(clientKey);
		clientKeyListsReadWriteLock.unlock();
		// success
		return true;
	}

	/**
	 * @brief closes a client connection
	 * @param client client
	 */
	void closeClient(CLIENT* client) {
		clientKeyListsReadWriteLock.writeLock();
		// erase client in client map
		clientKeyMap.erase(client->getKey());
		// erase client key in key set
		clientKeySet.erase(client->getKey());
		//
		clientKeyListsReadWriteLock.unlock();
	}

	/**
	 * @brief sets a group identification key
	 * @param group group
	 * @param &groupKey group identification key
	 * @return if setting the key was successful
	 */
	bool setGroupKey(GROUP* group, const string &groupKey) {
		groupKeyListsReadWriteLock.writeLock();
		// set new client key association
		auto it = groupKeyMap.find(groupKey);
		if (it != groupKeyMap.end()) {
			groupKeyListsReadWriteLock.unlock();
			// nope, we could't set the key
			return false;
		}
		// remove old client key association if changed
		if (group->getKey() != groupKey) {
			groupKeyMap.erase(group->getKey());
		}
		// set group in map
		groupKeyMap[groupKey] = group;
		// set client key in set
		groupKeySet.insert(groupKey);
		groupKeyListsReadWriteLock.unlock();
		// success
		return true;
	}

	/**
	 * @brief closes a group connection
	 * @param group group
	 */
	void closeGroup(GROUP* group) {
		groupKeyListsReadWriteLock.writeLock();
		// erase client in client map
		groupKeyMap.erase(group->getKey());
		// erase client key in key set
		groupKeySet.erase(group->getKey());
		//
		groupKeyListsReadWriteLock.unlock();
	}

	string name;
	string host;
	uint16_t port;
	int maxCCU;

	ClientKeyMap clientKeyMap;
	ClientKeySet clientKeySet;

	ReadWriteLock clientKeyListsReadWriteLock;

	GroupKeyMap groupKeyMap;
	GroupKeySet groupKeySet;

	ReadWriteLock groupKeyListsReadWriteLock;

	int ioThreadCount;
	int workerThreadPoolCount;
	int workerThreadPoolMaxElements;
};

};
};
};
