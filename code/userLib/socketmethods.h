# ifndef H_USERLIB_SERVERMETHODS

# define H_USERLIB_SERVERMETHODS


/**
 *
 * constructor
 *
 */
Socket :: Socket ()
    :
    Object    (777),
    isServer_ (true)
{
    client_.setPort (0);
    client_.setIP   ("127.0.0.1");
    client_.stop    ();

    server_.setPort (0);
    server_.setIP   ("127.0.0.1");
    server_.stop    ();
}

/**
 *
 * this function sets port of a socket
 *
 * @param portStr - string with port number, example "80"
 *
 */
void Socket :: setPort (const char* portStr)
{
    if ( !portStr )
        return;
     int       get = 0;
    short int port = 0;

    sscanf (portStr, "%d", &get);

    port = get;
    client_.setPort (port);
    server_.setPort (port);

    return;
}


/**
 *
 * this function sets port of a socket
 *
 * @param portStr - string with port number, example "80"
 *
 */
void Socket :: setIP (const char* IP)
{
    if ( !IP )
        return;

    server_.setIP (IP);
    client_.setIP (IP);

    return;
}

/**
 *
 * this function listens and accept connection
 *
 */
void Socket :: listen ()
{
    isServer_ = true;
    server_.stop   ();
    server_.start  ();
    server_.listen ();

    return ;
}


/**
 *
 * this function connects to socket
 *
 */
void Socket :: connect ()
{
    isServer_ = false;
    client_.stop    ();
    client_.start   ();
    client_.connect ();

    return ;
}

/**
 *
 * this function sends data through the socket to the socket that socket is
 * connected to. To be able to send socket must be connected destination socket
 *
 * @param buff - what to send
 * @param size - size of a buffer to send
 *
 */
void Socket :: send (const char* buff, int size)
{
    if ( !buff || !size )
        return;

    if ( isServer_ )
        server_.send (buff, size);
    else
        client_.send (buff, size);
}
/**
 *
 * this function receives data throgh the server from socket that server
 * is connected to. Socket must be connected to socket to be able
 * to receive something
 *
 * @param buffer - buffer to write incoming message
 * @param size   - size of an incoming message
 *
 */
void Socket :: receive (char* buffer, int size)
{
    if ( !buffer || !size )
        return;
    if ( isServer_ )
        server_.receive (buffer, size);
    else
        client_.receive (buffer, size);
}

/**
 *
 * this function creates socket 
 *
 * @return
 * {nullptr} - error
 * {>=0}     - newly created server
 *
 */
logic::Object* SOCKETcreate ()
{
    Socket* result = nullptr;
    try
    {
        result = new Socket ();
    }
    catch (::std::bad_alloc)
    {
    }
    return (logic::Object*) result;
}

/**
 *
 * this function creates socket from an array
 *
 * @param p - unused
 *
 * @return
 * {nullptr} - error
 * {>=0}     - newly created server
 *
 */
logic::Object* SOCKETcreateOn (const char* p)
{
    Socket* result = nullptr;
    try
    {
        result = new Socket ();
    }
    catch (::std::bad_alloc)
    {
    }
    return (logic::Object*) result;
}


/**
 *
 * destructor
 *
 */
Socket :: ~Socket ()
{
    server_.stop ();
    client_.stop ();
}

# endif /* H_USERLIB_SERVERMETHODS */
