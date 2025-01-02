[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/andreasdr/yannet/blob/master/LICENSE)
[![NIX Build Status](https://github.com/andreasdr/yannet/actions/workflows/nix.yml/badge.svg)](https://github.com/andreasdr/yannet/actions)
[![MacOSX Build Status](https://github.com/andreasdr/yannet/actions/workflows/macosx.yml/badge.svg)](https://github.com/andreasdr/yannet/actions)
[![Windows/MINGW Build Status](https://github.com/andreasdr/yannet/actions/workflows/windows-mingw.yml/badge.svg)](https://github.com/andreasdr/yannet/actions)
[![Windows/MSC Build Status](https://github.com/andreasdr/yannet/actions/workflows/windows-msc.yml/badge.svg)](https://github.com/andreasdr/yannet/actions)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/15611/badge.svg)](https://scan.coverity.com/projects/andreasdr-yannet)  
  
# 1. What is Yannet?
- Yannet is a lightweight, multiplatform network code that includes a HTTP/S client, a HTTP/S download client and a UDP Server and UDP client 
- Yannet is open source
  - please check the [license](https://github.com/andreasdr/yannet/blob/master/LICENSE)
  - you find the source code at [https://github.com/andreasdr/yannet](https://github.com/andreasdr/yannet) 

# 2. Features
- UDP server
    - n:m threading model with non blocked IO via kernel event mechanismns(epoll, kqueue or select)
    - supports safe messages with acknowledgment and automatic resending
    - supports fast messages
    - can be used in a heavy multithreaded environment (the networking module is thread safe)
    - IPV6 ready
- UDP client
    - has single thread with a simple threadsafe API
    - supports all features required by UDP server
    - IPV6 ready
- Simple HTTP client
    - uses a blocking TCP socket, thus it has a simple blocking API
    - Ready for REST providing all methods, setting content type and body
    - be able to set GET and POST parameters via unordered map 
    - supports basic authentification
    - IPV6 ready
- HTTP download client
    - supports basic authentification
    - uses a separate thread to download to file
    - IPV6 ready

# 3. What does it (maybe still) lack
- ...

# 4. Technology
- designed for simple multi threading, but
    - UDP client has its own thread
    - UDP server can have multiple IO threads, multiple worker threads and always has its own server thread
    - HTTP download client has its own thread
- uses 3rd party libraries
    - needs to be installed, if not using port-msc
        - OpenSSH
- targeted platforms and its current state
    - Windows/MINGW(port completed)
    - Windows/MSC(port completed)
    - Linux(port completed)
    - MacOSX(port completed)
    - FreeBSD(port completed)
    - NetBSD(port completed)
    - OpenBSD(port completed)
    - Haiku(port completed)
    - Android(port pending)
    - iOS(port pending)

# 5. Collaboration
- Interested in collaboration? Then drop me a line via mail or use the issues section on [tdme2@github](https://github.com/andreasdr/yannet/issues)

# 6. Donation 
- I have to pay my bills, beer and stuff, so if you have any use for this open source project, like educational, productive or fun, ..., consider a donation here [PayPal](https://www.paypal.me/andreasdrewke), here [GitHub Sponsors](https://github.com/sponsors/andreasdr) or via [Amazon Wishlist](https://www.amazon.de/hz/wishlist/ls/250IBUL4JSZVR?ref_=wl_share)
