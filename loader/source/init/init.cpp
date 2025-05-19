#include "init.h"

#include "../protect/protect.h"
#include "../request/request.h"

bool c_init::start( )
{
	// start protect
	if ( g_protect->start( ) )
		return true;

	// connection
	if ( g_request->start_session( ) )
		return true;

	// login
	if ( g_request->start_auth( ) )
		return true;

	// logged in
	printf( "[ + ] welcome, %s\n", g_user_info->username.c_str( ) );
	printf( "[ + ] days left, %d\n\n", g_user_info->days );

	return false;
}