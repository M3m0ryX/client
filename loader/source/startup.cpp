#include "init/init.h"
#include "request/request.h"

int main( )
{
	// init protect & connection
	if ( g_init->start( ) )
		return 1;

	// pause to inject
	system( "pause" );

	//if ( g_inject->start( ) )
	//	return 1;

	WSACleanup( );

	// exit process
	return 0;
}