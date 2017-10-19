#pragma once

#include <stdint.h>

#include <exception>
#include <string>
#include <sstream>

#include <tdme/utils/Exception.h>
#include <tdme/utils/ReferenceCounter.h>

using std::string;

using tdme::utils::Exception;
using tdme::utils::ReferenceCounter;

namespace tdme {
namespace network {
namespace udpserver {

/**
 * Base class for NIO server groups events
 * @author Andreas Drewke
 */
class NIOServerGroupBase : public ReferenceCounter {
friend class NIOServerWorkerThread;

protected:
	/*
	 * @brief event method called if group will be initiated, will be called from worker
	 */
	virtual void onInit() throw (Exception) = 0;

	/*
	 * @brief event method called if client will be closed, will be called from worker
	 */
	virtual void onClose() throw (Exception) = 0;

	/*
	 * @brief custom event method called if fired, will be called from worker
	 */
	virtual void onCustomEvent(const string& type) throw (Exception) = 0;
};

};
};
};
