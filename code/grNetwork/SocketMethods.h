# ifndef H_GRNETWORK_SOCKETMETHODS

# define H_GRNETWORK_SOCKETMETHODS


Socket :: Socket ()
    :
    lastError_   (0, 0),
    socket_info_ ()
{
    socket_info_.socket              = INVALID_SOCKET;
    socket_info_.addrInfo.sin_family = AF_INET;
}

bool Socket :: start ()
{
    if ( socket_info_.socket != INVALID_SOCKET )
        this->stop ();
    
    socket_info_.socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if ( socket_info_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::CantStart, GetLastError ());
        return false;
    }

    return true;
}

void  Socket :: stop ()
{
    closesocket (socket_info_.socket);
    socket_info_.socket = INVALID_SOCKET;
}

bool Socket :: setIP    (const char * IP)
{
    socket_info_.addrInfo.sin_addr.S_un.S_addr = inet_addr (IP);
    if ( socket_info_.addrInfo.sin_addr.S_un.S_addr == INADDR_NONE )
    {
        lastError_.set (error::CantSetIP, GetLastError ());
        return false;
    }
    return true;
}

void Socket :: setPort  (short int port)
{
    socket_info_.addrInfo.sin_port = htons (port);
}

bool Socket :: out (const char* what, unsigned int size)
{
    if ( socket_info_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }
    int result = send (socket_info_.socket, what, size, 0);

    if ( result == SOCKET_ERROR )
    {
        lastError_.set (error::UnableToSend, GetLastError ());
        return false;
    }

    return true;
}

bool Socket :: in (char* where, unsigned int size)
{
    if ( socket_info_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }
    int result = recv (socket_info_.socket, where, size, 0);

    if ( result == SOCKET_ERROR )
    {
        lastError_.set (error::UnableToReceive, GetLastError ());
        return false;
    }
    else
        return true;
}

ErrorInfo Socket :: getLastError () const
{
    return lastError_;
}

void Socket :: sync (bool makeAsync)
{
    unsigned long enable = (unsigned long)true;
    if ( makeAsync )
        ioctlsocket (socket_info_.socket, FIONBIO, &enable);
    else
        ioctlsocket (socket_info_.socket, 0, NULL);
}

Socket :: ~Socket ()
{
    this->stop ();
}



# endif /* H_GRNETWORK_SOCKETMETHODS */
