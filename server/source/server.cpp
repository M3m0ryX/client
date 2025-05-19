#include "init/init.h"
#include "request/request.h"

int main( )
{
	// init server
	if ( g_init->start( ) )
		return 1;

	// handle
	while ( g_request->m_socket_server )
	{ 
		SOCKET m_socket;
		SOCKADDR_IN m_address;

		// accpet
		if ( ( m_socket = accept( g_request->m_socket_server, reinterpret_cast< SOCKADDR* >( &m_address ), reinterpret_cast< int* >( &m_address ) ) ) != INVALID_SOCKET )
		{
			// start hadler
			std::thread( [ & ]( ) { 
				g_init->start_session( m_socket, inet_ntoa( m_address.sin_addr ) ); 
				} ).detach( );
		}

		// wsa error's
		const auto wsa_error = WSAGetLastError( );
		
		if ( wsa_error > 0 ) 
		{
			printf( "[ - ] [ %d ] wsa error %d.\n", ( int )m_socket, wsa_error );
			break;
		}
	}

	WSACleanup( );

	// exit process
	return 0;
}