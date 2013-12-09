# ifndef H_GRNETWORK_RAWSOCKET_RAWSOCKETMETHODS

# define H_GRNETWORK_RAWSOCKET_RAWSOCKETMETHODS


/**
 *
 * This is standard constructor that sets everything to zero.
 *
 */
RawSocket :: RawSocket ()
    :
    lastError_     (( 0), (0 )) /* good ones */
{
    socketData_.socket              = INVALID_SOCKET;
    socketData_.addrInfo.sin_family = AF_INET;
}

/**
 *
 * This function returns last error.
 *
 * @return last error.
 *
 */
ErrorInfo RawSocket :: GetLastError ()
{
    return lastError_;
}

/**
 *
 * This function looks if error was real or if it is fake error that happened,
 * because socket is non blocking. Try to search non blocking sockets in msdn. 
 *
 * @return true - fake error, false - real error.
 *
 */
bool RawSocket :: isBlockError ()
{
    if ( lastError_.lib () == 1035 ||
         lastError_.lib () == 0
       )
        return true;
    return false;
}

/**
 *
 * This function sets socket in blocking or nonblocking mode. It can be called
 * after start function.
 *
 * @param makeAsync true - make non - blocking, false - make blocking
 *
 * @return succes.
 *
 */
bool RawSocket :: sync         (bool makeAsync)
{ 
    unsigned long enable = (unsigned long)true;
    int result = 0;

    if ( makeAsync )
        result = ioctlsocket (socketData_.socket, FIONBIO, &enable);
    else
        result = ioctlsocket (socketData_.socket, 0, NULL);

    if ( isBlockError () )
        return true;

    return false;
}

/**
 *
 * By default IP header is made automaticly, but by calling this function
 * with true argument you can set it to mode in which IP header won't
 * be generated. It will be expected you to build it.
 *
 * @param makeCustom true - custom headers, false - normal headers
 *
 * @return success
 *
 */
bool RawSocket :: customHeader (bool makeCustom)
{
    int result = 0;
    if ( makeCustom )
    {
        result = setsockopt (socketData_.socket, IPPROTO_IP, IP_HDRINCL, 0, 0);
        if ( result == SOCKET_ERROR )
            return false;
    }
    return true;
}

/**
 *
 * This function start socket. Before using network functions of this class
 * start socket. After using use stop function
 *
 * @return success
 *
 */
bool RawSocket :: start ()
{
    if ( socketData_.socket != INVALID_SOCKET )
        this->stop ();
    
    socketData_.socket = socket (AF_INET, SOCK_RAW, IPPROTO_IP);
    socketData_.addrInfo.sin_family = AF_INET;

    if ( socketData_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::CantStart, ::GetLastError ());
        return false;
    }

    return true;

}

/**
 *
 * This function Sets IP.
 *
 * @param IP - IP to be set
 *
 * @return success
 *
 */
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
    if ( bind (socketData_.socket, (sockaddr*)&socketData_.addrInfo,
                sizeof (socketData_.addrInfo) ) )
        return false;
    
    return true;
}

/**
 *
 * This function sets port
 *
 * @param port - port to be set
 *
 */
void RawSocket :: setPort (short int port)
{
    socketData_.addrInfo.sin_port = htons (port);
}

/**
 *
 * Function that sends your information.
 *
 * @param data - data to be sent
 * @param size - size of data buffer to be sent
 *
 * @return - success
 *
 */
int  RawSocket :: send    (const char* data, unsigned int size)
{
    if ( socketData_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }
    sockaddr_in* sockAddrPtr = &socketData_.addrInfo;
    int result = ::sendto (socketData_.socket, data, size, 0,
                          (sockaddr*)sockAddrPtr,
                         sizeof (socketData_.addrInfo));

    if ( result == SOCKET_ERROR )
    {
        lastError_.set (error::UnableToSend, ::GetLastError ());
        return false;
    }

    return true;
}

/**
 *
 * This function receives data from socket.
 *
 * @param where - where tp put data
 * @param size  - size of data to be putted in data buffer
 *
 * @return - success
 *
 */
bool RawSocket :: receive (char* where, unsigned int size)
{
    if ( socketData_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }
    int addrSize = sizeof (socketData_.addrInfo);
    int result = ::recvfrom (socketData_.socket, where, size, 0,
                            (sockaddr*)&socketData_.addrInfo,
                             &addrSize);

    if ( result == SOCKET_ERROR )
    {
        lastError_.set (error::UnableToReceive, ::GetLastError ());
        return false;
    }
    return true;
}

/**
 *
 * This function stops socket.
 *
 */
void RawSocket :: stop ()
{
    closesocket (socketData_.socket);
    socketData_.socket = INVALID_SOCKET;
}

/**
 *
 * This is just destructor, it calls stop function.
 *
 */
RawSocket :: ~RawSocket ()
{
    stop ();
}



# endif /* H_GRNETWORK_RAWSOCKET_RAWSOCKETMETHODS */
