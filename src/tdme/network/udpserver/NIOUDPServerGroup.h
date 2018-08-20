#pragma once

#include <tdme/network/udpserver/fwd-tdme.h>
#include <tdme/network/udpserver/NIOServerGroup.h>
#include <tdme/network/udpserver/NIOUDPServer.h>
#include <tdme/network/udpserver/NIOUDPServerClient.h>

using tdme::network::udpserver::NIOServerGroup;
using tdme::network::udpserver::NIOUDPServer;
using tdme::network::udpserver::NIOUDPServerClient;

/**
 * NIO UDP server group
 * @author Andreas Drewke
 */
class tdme::network::udpserver::NIOUDPServerGroup : public NIOServerGroup<NIOUDPServer, NIOUDPServerClient, NIOUDPServerGroup> {
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

