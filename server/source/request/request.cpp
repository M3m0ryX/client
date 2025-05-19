#include "request.h"

bool c_request::start_socket( const char* address, int port )
{
	if ( WSAStartup( MAKEWORD( 2, 2 ), &m_wsa_data ) )
		return false;

	m_socket_server = socket( AF_INET, SOCK_STREAM, 0 );

	if ( m_socket_server < 0 )
	{
		printf( "[ - ] failed to setup m_socket_server.\n" );
		return false;
	}

	SOCKADDR_IN server_info;
	memset( &server_info, 0, sizeof server_info );

	server_info.sin_family = AF_INET;
	server_info.sin_port = htons( port );

	if ( inet_pton( AF_INET, address, &server_info.sin_addr ) <= 0 )
		return false;

	if ( bind( m_socket_server, reinterpret_cast< SOCKADDR * >( &server_info ), sizeof server_info ) != 0 )
	{
		printf( "[ - ] failed to bind port: %d.\n", port );
		return false;
	}

	listen( m_socket_server, 0 );

	printf( "[ + ] bind on port, %d\n", port );

	return false;
}