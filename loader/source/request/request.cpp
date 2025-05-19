#include "request.h"

bool c_request::start_session( const char* address, int port )
{
	if ( WSAStartup( MAKEWORD( 2, 1 ), &m_wsa_data ) )
		return true;

	m_socket = socket( AF_INET, SOCK_STREAM, 0 );

	if ( m_socket < 0 )
	{
		printf( "[ - ] failed to setup m_socket.\n" );
		return true;
	}

	sockaddr_in server_info;
	memset( &server_info, 0, sizeof server_info );

	server_info.sin_family = AF_INET;
	server_info.sin_port = htons( port );

	if ( inet_pton( AF_INET, address, &server_info.sin_addr ) <= 0 )
		return true;

	if ( connect( m_socket, reinterpret_cast< const sockaddr* >( &server_info ), sizeof server_info ) != 0 )
	{
		printf( "[ - ] can't connect to server.\n" );
		return true;
	}

	return false;
}

bool c_request::start_auth( )
{
	std::vector< char > m_body( BUFSIZ );
	nlohmann::json json_auth;

	json_auth[ "message" ][ "id" ] = 1;
	json_auth[ "message" ][ "token" ] = "1234567890";
	json_auth[ "message" ][ "hwid" ] = "a62554365473654367563474321";

	// send message
	int result = send( m_socket, json_auth.dump( ).data( ), json_auth.dump( ).size( ), 0 );

	// clear
	json_auth.clear( );

	if ( result <= 0 )
	{
		printf( "[ ! ] failed to login.\n" );
		return true;
	}

	// get response
	result = recv( m_socket, m_body.data( ), m_body.size( ), 0 );

	if ( result <= 0 )
	{
		printf( "[ ! ] invalid response.\n" );
		return true;
	}

	// parse response
	auto json_data = nlohmann::json::parse( m_body );

	// clear
	m_body.clear( );

	// failed login display message error
	if ( !json_data[ "message" ][ "success" ].get< bool >( ) )
	{
		printf( "[ * ] %s.\n", json_data[ "message" ][ "reason" ].get< std::string >( ).c_str( ) );
		return true;
	}

	g_user_info->avatar = json_data[ "message" ][ "avatar_path" ].get< std::string >( );
	g_user_info->username = json_data[ "message" ][ "username" ].get< std::string >( );
	g_user_info->days = json_data[ "message" ][ "remaining_days" ].get< int >( );
	g_user_info->user_id = json_data[ "message" ][ "user_id" ].get< int >( );

	return false;
}