#pragma once

#include "..\..\additionals\httplib.h"
#include "..\..\additionals\json.h"

#include <Windows.h>
#include <winsock2.h>

class c_request
{
	std::string m_web_domain = "localhost";

	WSADATA m_wsa_data;

public:
	SOCKET m_socket_server;

	bool start_socket( const char* address = "127.0.0.1", int port = 1234 );
};

inline c_request* g_request = new c_request( );