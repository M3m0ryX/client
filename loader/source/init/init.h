#pragma once

#include <Windows.h>
#include <iostream>

class c_init
{

public:
	bool start( );
};

inline c_init* g_init = new c_init( );