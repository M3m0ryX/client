#pragma once

#include <Windows.h>
#include <cstdint>

class c_utils
{
public:
	void exit( );
};

inline c_utils* g_utils = new c_utils( );