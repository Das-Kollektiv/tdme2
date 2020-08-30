#pragma once

namespace tdme {
namespace os {
namespace network {

/**
 * @brief type definiton for io interest, see NetworkServerClient::INTEREST_*
 */
typedef uint8_t NIOInterest;
const NIOInterest NIO_INTEREST_NONE = 0;
const NIOInterest NIO_INTEREST_READ = 1;
const NIOInterest NIO_INTEREST_WRITE = 2;

}
}
}
