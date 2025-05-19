#pragma once

#include <Windows.h>

class c_protect
{

public:
	bool start( );
};

inline c_protect* g_protect = new c_protect( );