# ifndef H_GRNETWORK_SOCKET_SOCKETMETHODS

# define H_GRNETWORK_SOCKET_SOCKETMETHODS

/**
 *
 * This is standard constructor that sets everything to zero.
 *
 */
Socket :: Socket ()
    :
    lastError_   (0, 0),
    socket_info_ ()
{
    socket_info_.socket              = INVALID_SOCKET;
    socket_info_.addrInfo.sin_family = AF_INET;
}

/**
 *
 * This function start socket. Before using network functions of this class
 * start socket. After using use stop function
 *
 * @return success
 *
 */
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

/**
 *
 * This function stops socket.
 *
 */
void  Socket :: stop ()
{
    closesocket (socket_info_.socket);
    socket_info_.socket = INVALID_SOCKET;
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
bool Socket :: setIP    (const char * IP)
{
    if ( !IP )
    {
        socket_info_.addrInfo.sin_addr.S_un.S_addr = htonl (INADDR_ANY);
        return true;
    }

    socket_info_.addrInfo.sin_addr.S_un.S_addr = inet_addr (IP);
    if ( socket_info_.addrInfo.sin_addr.S_un.S_addr == INADDR_NONE )
    {
        lastError_.set (error::CantSetIP, GetLastError ());
        return false;
    }
    return true;
}

/**
 *
 * This function sets port
 *
 * @param port - port to be set
 *
 */
void Socket :: setPort  (short int port)
{
    socket_info_.addrInfo.sin_port = htons (port);
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
bool Socket :: send (const char* what, unsigned int size)
{
    if ( socket_info_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }
    int result = ::send (socket_info_.socket, what, size, 0);

    if ( result == SOCKET_ERROR )
    {
        lastError_.set (error::UnableToSend, GetLastError ());
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
bool Socket :: receive (char* where, unsigned int size)
{
    if ( socket_info_.socket == INVALID_SOCKET )
    {
        lastError_.set (error::NotStarted, 0);
        return false;
    }
    int result = ::recv (socket_info_.socket, where, size, 0);

    if ( result == SOCKET_ERROR )
    {
        lastError_.set (error::UnableToReceive, GetLastError ());
        return false;
    }
    return true;
}

/**
 *
 * This function returns last error.
 *
 * @return last error.
 *
 */
ErrorInfo Socket :: getLastError () const
{
    return lastError_;
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
void Socket :: sync (bool makeAsync)
{
    unsigned long enable = (unsigned long)true;
    if ( makeAsync )
        ioctlsocket (socket_info_.socket, FIONBIO, &enable);
    else
        ioctlsocket (socket_info_.socket, 0, NULL);
}

/**
 *
 * This function looks if error was real or if it is fake error that happened,
 * because socket is non blocking. Try to search non blocking sockets in msdn. 
 *
 * @return true - fake error, false - real error.
 *
 */
bool Socket :: blockError () const
{
    if ( lastError_.lib () == 1035 ||
         lastError_.lib () == 0 )
        return true;
    return false;
}

/**
 *
 * This is just destructor, it calls stop function.
 *
 */
Socket :: ~Socket ()
{
    this->stop ();
}



# endif /* H_GRNETWORK_SOCKET_SOCKETMETHODS */
