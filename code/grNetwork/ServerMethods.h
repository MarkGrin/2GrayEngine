# ifndef H_GRNETWORK_METHODS

# define H_GRNETWORK_METHODS

bool Server :: listen (Client* listenSocket /* = nullptr*/)
{
    if ( socket_info_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }
    socket_info_.addrInfo.sin_addr.S_un.S_addr = htonl (INADDR_ANY);

    int result = bind (socket_info_.socket, (sockaddr*) &socket_info_.addrInfo,
                       sizeof (socket_info_.addrInfo) );
    if ( result == SOCKET_ERROR )
    {
        result = WSAGetLastError ();
        lastError_.set (error::CantBindSocket, Result);
        return false;
    }

    result = listen (socket_info_.socket, SOMAXCONN);
    if ( result == SOCKET_ERROR )
    {
        this->stop ();
        result = WSAGetLastError ();
        lastError.set (error::CantListen, result);
        return false;
    }

    if ( listenSocket )
    {
        if ( listenSocket->socket_info_.socket != INVALID_SOCKET )
            listenSocket->stop ();

        listenSocket->socket_info_.socket = accept (socket_info_.socket,
                                                   NULL, NULL);

        if ( listenSocket->socket_info_.socket == INVALID_SOCKET )
        {
            result = WSAGetLastError ();
            lastError_.set (error::CantAccept, result);
            return false;
        }
    }
    else
    {
        SOCKET swap = accept (socket_info_.socket, NULL, NULL);
        if ( swap == INVALID_SOCKET )
        {
            result = WSAGetLastError ();
            lastError.set (error::CantAccept, Result);
            this->stop ();
            return false;
        }
        this->stop ();
        socket_info_.socket = swap;
    }
    return true;

}

# endif /* H_GRNETWORK_METHODS */
