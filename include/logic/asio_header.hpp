#if !defined(SIP0X_LOGIC_ASIO_HEADER_HPP__)
#define SIP0X_LOGIC_ASIO_HEADER_HPP__

#if defined(_WIN32)
#define _WIN32_WINNT 0x601
// TODO: investigate if it is realy needed!!!
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif



#define ASIO_STANDALONE
#include "asio.hpp"

#endif // SIP0X_LOGIC_ASIO_HEADER_HPP__
