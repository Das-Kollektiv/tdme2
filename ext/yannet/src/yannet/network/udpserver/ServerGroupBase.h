#pragma once

#include <string>

#include <yannet/yannet.h>
#include <yannet/utilities/Exception.h>
#include <yannet/utilities/Reference.h>

using std::string;

namespace yannet {
namespace network {
namespace udpserver {

using ::yannet::utilities::Exception;
using ::yannet::utilities::Reference;

/**
 * Base class for network server group
 * @author Andreas Drewke
 */
class ServerGroupBase : public ::yannet::utilities::Reference {
	friend class ServerWorkerThread;

protected:
	/*
	 * @brief event method called if group will be initiated, will be called from worker
	 */
	virtual void onInit() = 0;

	/*
	 * @brief event method called if client will be closed, will be called from worker
	 */
	virtual void onClose() = 0;

	/*
	 * @brief custom event method called if fired, will be called from worker
	 */
	virtual void onCustomEvent(const string& type) = 0;
};

};
};
};
