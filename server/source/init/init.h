#pragma once

#include <Windows.h>
#include <iostream>
#include <winsock2.h>
#include <vector>

class c_init
{

public:
	bool start( );
	bool start_session( SOCKET m_socket, const char* m_address );
};

inline c_init* g_init = new c_init( );