# ifndef H_GRNETWORK_SOCKET_CLIENTMETHODS

# define H_GRNETWORK_SOCKET_CLIENTMETHODS


bool Client :: connect ()
{
    if ( socket_info_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }
    int result = ::connect (socket_info_.socket,
                           (sockaddr*)(&socket_info_.addrInfo),
                           sizeof (socket_info_.addrInfo) );

    if ( result == SOCKET_ERROR )
    {
        result = WSAGetLastError ();
        lastError_.set (error::ErrorConnect, result);
        return false;
    }

    return true;
}



# endif /* H_GRNETWORK_SOCKET_CLIENTMETHODS */
