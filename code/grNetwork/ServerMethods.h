# ifndef H_GRNETWORK_SERVERMETHODS

# define H_GRNETWORK_SERVERMETHODS


Server :: Server ()
    :
    asyncState_ (false)
{
}

bool Server :: listen (Client* listenSocket /* = nullptr*/)
{
    if ( socket_info_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }

    int result = 0;

    if ( !asyncState_ )
    result = bind (socket_info_.socket, (sockaddr*) &socket_info_.addrInfo,
                       sizeof (socket_info_.addrInfo) );
    if ( result == SOCKET_ERROR && !asyncState_ )
    {
        result = WSAGetLastError ();
        lastError_.set (error::CantBindSocket, result);
        return false;
    }

    if ( !asyncState_ )
        result = ::listen (socket_info_.socket, SOMAXCONN);
    if ( result == SOCKET_ERROR )
    {
        result = WSAGetLastError ();
        lastError_.set (error::CantListen, result);
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
            if ( result == 10035 )
                asyncState_ = true;
            else
                asyncState_ = false;
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
            if ( result == 10035 )
                asyncState_ = true;
            else
                asyncState_ = false;
            lastError_.set (error::CantAccept, result);
            return false;
        }
        this->stop ();
        socket_info_.socket = swap;
    }
    return true;

}



# endif /* H_GRNETWORK_SERVERMETHODS */
