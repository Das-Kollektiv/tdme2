#pragma once

#include <yannet/yannet.h>
#include <yannet/network/udpserver/fwd-yannet.h>
#include <yannet/network/udpserver/ServerGroup.h>
#include <yannet/network/udpserver/UDPServer.h>
#include <yannet/network/udpserver/UDPServerClient.h>

/**
 * UDP server group class
 * @author Andreas Drewke
 */
class yannet::network::udpserver::UDPServerGroup :
	public
		ServerGroup<
			yannet::network::udpserver::UDPServer,
			yannet::network::udpserver::UDPServerClient,
			yannet::network::udpserver::UDPServerGroup
		> {
public:
	/**
	 * @brief Creates a frame to be used with send
	 * @return frame to be send
	 */
	// stringstream* createFrame();

	/**
	 * @brief Sends a frame to client, takes over ownership of frame
	 * @param frame frame data
	 * @param safe safe, requires ack and retransmission
	 */
	// void send(stringstream* frame, bool safe = true);
};

