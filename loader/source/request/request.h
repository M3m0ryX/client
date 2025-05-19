#pragma once

#include "..\..\additionals\json.h"

#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

struct s_user_info
{
	std::string token;

	std::string avatar;
	std::string username;

	int days;
	int user_id;
};

class c_request
{
	WSADATA m_wsa_data;

public:
	SOCKET m_socket;

	bool start_session( const char* address = "127.0.0.1", int port = 1234 );
	bool start_auth( );
};

inline s_user_info* g_user_info = new s_user_info( );
inline c_request* g_request = new c_request( );