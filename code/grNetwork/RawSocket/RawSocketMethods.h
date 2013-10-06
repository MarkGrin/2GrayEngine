# ifndef H_GRNETWORK_RAWSOCKET_RAWSOCKETMETHODS

# define H_GRNETWORK_RAWSOCKET_RAWSOCKETMETHODS


RawSocket ()
    :
    lastError_   (0, 0),
    socketData_.info_ ()
{
    socketData_.socket              = INVALID_SOCKET;
    socketData_.addrInfo.sin_family = 0;
}

ErrorInfo RawSocket :: GetLastError ()
{
    return lastError_;
}

bool RawSocket :: isBlockError ()
{
    if ( lastError_.lib () == 1035 ||
         lastError_.lib () == 0
       )
        return true;
    return false;
}

bool RawSocket :: sync         (bool makeAsync)
{ 
    unsigned long enable = (unsigned long)true;
    if ( makeAsync )
        ioctlsocket (socketData_.socket, FIONBIO, &enable);
    else
        ioctlsocket (socketData_.socket, 0, NULL);

}
bool RawSocket :: customHeader (bool makeCustom)
{
    int result = 0;
    result = setsockopt (socketData_.socket, IPPROTO_IP, IP_HDRINCL, 0, 0);
    if ( result == SOCKET_ERROR )
        return false;
    return true;
}

bool RawSocket :: start (bool IPv6)
{
    if ( socketData_.socket != INVALID_SOCKET )
        this->stop ();
    
    if ( !IPv6 )
    {
        socketData_.socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
        socketData_.socket = AF_INET;
    }
    else
    {
        socketData_.socket = socket (AF_INET6, SOCK_RAW, 0);
        socketData_.socket = AF_INET6;
    }

    if ( socketData_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::CantStart, ::GetLastError ());
        return false;
    }

    return true;

}

bool RawSocket :: setIP   (const char* IP)
{
    if ( !IP )
    {
        socketData_.addrInfo.sin_addr.S_un.S_addr = htonl (INADDR_ANY);
        return true;
    }

    socketData_.addrInfo.sin_addr.S_un.S_addr = inet_addr (IP);
    if ( socketData_.addrInfo.sin_addr.S_un.S_addr == INADDR_NONE )
    {
        lastError_.set (error::CantSetIP, ::GetLastError ());
        return false;
    }
    return true;

}

void RawSocket :: setPort (short int port)
{
    socketData_.addrInfo.sin_port = htons (port);
}

int  RawSocket :: send    (const char* data, unsigned int size)
{
    if ( socketData_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }
    const sockaddr_in* sockAddrPtr = &(socketData_.addrInfo.sin_addr);
    int result = ::sendto (socketData_.socket, data, size, 0,
                         sockAddrPtr,
                         sizeof (socketData_.addrInfo));

    if ( result == SOCKET_ERROR )
    {
        lastError_.set (error::UnableToSend, ::GetLastError ());
        return false;
    }

    return true;
}

bool RawSocket :: receive (char* where, unsigned int size)
{
    if ( socketData_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }
    int result = ::recv (socketData_.socket, where, size, 0);

    if ( result == SOCKET_ERROR )
    {
        lastError_.set (error::UnableToReceive, ::GetLastError ());
        return false;
    }
    return true;
}

void RawSocket :: stop ()
{
    closesocket (socketData_.socket);
    socketData_.socket = INVALID_SOCKET;
}

RawSocket :: ~RawSocket ()
{
    stop ();
}



# endif /* H_GRNETWORK_RAWSOCKET_RAWSOCKETMETHODS */
