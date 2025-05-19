#include "init.h"

#include "../request/request.h"

bool c_init::start( )
{
	// login
	if ( g_request->start_socket( ) )
		return true;

	printf( "[ + ] ready!\n" );

	return false;
}

bool c_init::start_session( SOCKET m_socket, const char* m_address )
{
    printf( "[ + ] [ %d ] [ %s ] connected.\n", ( int )m_socket, m_address );

	// user data
	int m_user_id{ 0 };
	bool m_loggedin{ false };
	char m_username[ BUFSIZ ]{ 0 }, m_password[ BUFSIZ ]{ 0 };

	// body response
	std::vector< char > m_body( BUFSIZ );
	nlohmann::json json_body;

	// main
	while ( m_socket )
	{
		try
		{
			// receiver
			int result = recv( m_socket, m_body.data( ), m_body.size( ), 0 );

			if ( result <= 0 )
			{
				printf( "[ - ] [ %d ] [ %s ] bye.\n", ( int )m_socket, m_address );
				closesocket( m_socket );

				return true;
			}

			printf( "[ + ] [ %d ] [ %s ] message: %s\n", ( int )m_socket, m_address, m_body.data( ) );
		
			// decode data
			auto json_data = nlohmann::json::parse( m_body );

			for ( int i : json_data[ "message" ][ "id" ] )
			{
				switch ( i )
				{
				case 1: // login
				{
					json_body[ "message" ][ "success" ] = true;
					json_body[ "message" ][ "reason" ] = "success";

					json_body[ "message" ][ "avatar_path" ] = "/assets/avatars/1.png";
					json_body[ "message" ][ "username" ] = "admin";
					json_body[ "message" ][ "remaining_days" ] = 1337;
					json_body[ "message" ][ "user_id" ] = 1;
				} break;

				default: // idk
					closesocket( m_socket );
					break;
				}
			}

			// send
			if ( !json_body.empty( ) )
				result = send( m_socket, json_body.dump( ).data( ), json_body.dump( ).size( ), 0 );

			// clear
			json_body, m_body.clear( );

			if ( result <= 0 )
			{
				printf( "[ * ] [ %d ] [ %s ] -> failed to send response.\n", ( int )m_socket, m_address );
				closesocket( m_socket );

				return true;
			}
		}
		catch ( std::exception& ex )
        {
			printf( "[ * ] [ %d ] [ %s ] ex: %s.\n", ( int )m_socket, m_address, ex.what( ) );
            closesocket( m_socket );

			return true;
        }
	}

	return false;
}