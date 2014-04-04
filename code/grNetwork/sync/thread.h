# ifndef H_GRNETWORK_THREAD

# define H_GRNETWORK_THREAD


void thread       (void* threadInfo_void);

bool partUpdate   (Socket* socket, DeltaManager* manager);

int informUpdate  (Socket* socket, unsigned int repeat, unsigned int size);

int checkHash     (Socket* socket, DeltaManager* manager);
int checkSize     (Socket* socket, DeltaManager* manager);

bool connect      (Socket* socket);
bool idle         (Socket* socket);
bool disconnect   (Socket* socket);

void thread (void* threadInfo_void)
{
    threadInfo* inf = (threadInfo*)threadInfo_void;
    if ( !inf || !inf->dManager             || !inf->dManager->verify ()
              || !inf->socket.blockError ()                             )
    {
        OUTPUT_INTERNAL ("bad arg");
        return;
    }

    bool*         killSwitch = &inf->killSwitch;
    Socket*       socket     = &inf->socket;
    DeltaManager* dManager   = inf->dManager;

    if ( connect    (socket) <= 0 )
    {
        OUTPUT_INTERNAL ("cant connect");
        return;
    }
    if ( checkSize (socket, dManager) <= 0)
    {
        OUTPUT_INTERNAL ("cant check size of size is wrong");
        return;
    }
    int hashDiff = checkHash (socket, dManager);
    if ( hashDiff < 0 )
    {
        OUTPUT_INTERNAL ("cant check hashes");
        return;
    }
    if ( hashDiff )
        dManager->changeAll ();
    while ( *killSwitch )
    {
        Sleep (100);
        while ( dManager->changed () )
        {
            if ( !partUpdate (socket, dManager) )
            {
                OUTPUT_INTERNAL ("error at updating");
                return;
            }
            continue;
        }
        if ( !idle (socket) )
        {
            OUTPUT_INTERNAL ("cant idle");
            return;
        }
    }
    disconnect (socket);
    return ;
}

int informUpdate (Socket* socket, unsigned int repeat, unsigned int size)
{
    if ( !socket || socket->blockError () )
    {
        OUTPUT_INTERNAL ("bad param");
        return 0;
    }
    char buffer[sync::size::MAX_MESSAGE] = {};

    buffer[0] = sync::code::PART_UPDATE;
    memcpy (buffer + 1, &repeat, sizeof (repeat));
    memcpy (buffer + 1 + sizeof (repeat), &size, sizeof (size));

    if ( !socket->send (buffer, sync::size::REGULAR_HEADER) )
    {
        OUTPUT_INTERNAL ("error with sending PART_UPDATE header");
        return 0;
    }

    if ( !socket->receive (buffer, sync::size::REGULAR_HEADER) )
    {
        OUTPUT_INTERNAL ("error with receiving PART_UPDATE header");
        return 0;
    }

    if ( *buffer != sync::code::PART_UPDATE_OK )
    {
        OUTPUT_INTERNAL ("wrong header returned:%d to INFORM_UPDATE", *buffer);
        return -1;
    }
    if ( *( (unsigned int*)(buffer                + 1) ) != size )
    {
        OUTPUT_INTERNAL ("wrong size received");
        return -2;
    }
    if ( *( (unsigned int*)(buffer + sizeof (int) + 1) ) != repeat )
    {
        OUTPUT_INTERNAL ("wrong start received");
        return -3;
    }
    return 1;
}

int checkHash (Socket* socket, DeltaManager* manager)
{
    if ( !socket || !manager || socket->blockError () || !manager->verify () )
    {
        OUTPUT_INTERNAL ("bad param");
        return 0;
    }
    char buffer[sync::size::REGULAR_HEADER] = {};
    unsigned int hash         = manager->hash ();
    unsigned int hashFuncCode = manager->hashFuncCode ();

    buffer[0] = sync::code::HASH_CHECK;
    memcpy (buffer + 1                , &hash        , sizeof (hash        ));
    memcpy (buffer + 1 + sizeof (hash), &hashFuncCode, sizeof (hashFuncCode));

    if ( !socket->send (buffer, sync::size::REGULAR_HEADER)
    {
        OUTPUT_INTERNAL ("error with sending CHECK_HASH header");
        return 0;
    }
    if ( !socket->receive (buffer, sync::size::REGULAR_HEADER) )
    {
        OUTPUT_INTERNAL ("error with receiving CHECK_HASH_OK header");
        return 0;
    }
    if ( *buffer != sync::code::HASH_CHECK_OK )
    {
        OUTPUT_INTERNAL ("wrong header received");
        return -1;
    }
    if ( *( (unsigned int*)(buffer                + 1) ) != hashFuncCode )
    {
        OUTPUT_INTERNAL ("wrong hash function code received");
        return -2;
    }
    if ( *( (unsigned int*)(buffer + sizeof (int) + 1) ) != hash )
    {
        OUTPUT_INTERNAL ("wrong hash received");
        return -3;
    }
    return 1;
}

int checkSize (Socket* socket, DeltaManager* manager)
{
    if ( !socket || !manager || socket->isBlockError () || !manager->verify () )
    {
        OUTPUT_INTERNAL ("bad param");
        return 0;
    }
    char buffer[sync::size::REGULAR_HEADER] = {};
    unsigned int size         = manager->size ();
    unsigned int ignored      = 0;

    buffer[0] = sync::code::SIZE_CHECK;
    memcpy (buffer + 1                , &size   , sizeof (size));
    memcpy (buffer + 1 + sizeof (hash), &ignored, sizeof (ignored));

    if ( !socket->send (buffer, sync::size::REGULAR_HEADER)
    {
        OUTPUT_INTERNAL ("error with sending CHECK_HASH header");
        return 0;
    }
    if ( !socket->receive (buffer, sync::size::REGULAR_HEADER) )
    {
        OUTPUT_INTERNAL ("error with receiving CHECK_HASH_OK header");
        return 0;
    }
    if ( *buffer != sync::code::CHECK_SIZE_OK )
    {
        OUTPUT_INTERNAL ("wrong header received");
        return -1;
    }
    if ( *( (unsigned int)(buffer + sizeof (int) + 1) ) != size )
    {
        OUTPUT_INTERNAL ("wrong size here:%d there%d",
                          size, *( (unsigned int)(buffer + sizeof (int) + 1) ));
        return -2;
    }
    return 1;
}

int disconnect (Socket* socket)
{
    if ( !socket || !socket->isBlockError () )
    {
        OUTPUT_INTERNAL ("bad param");
        return 0;
    }
    char buffer[sync::size::REGULAR_HEADER] = {};
    unsigned int ignored      = 0;

    buffer[0] = sync::code::DISCONNECT;
    memcpy (buffer + 1                   , &ignored, sizeof (ignored));
    memcpy (buffer + 1 + sizeof (ignored), &ignored, sizeof (ignored));

    if ( !socket->send (buffer, sync::size::REGULAR_HEADER)
    {
        OUTPUT_INTERNAL ("error with sending CHECK_HASH header");
        return 0;
    }
    if ( !socket->receive (buffer, sync::size::REGULAR_HEADER) )
    {
        OUTPUT_INTERNAL ("error with receiving CHECK_HASH_OK header");
        return 0;
    }
    if ( *buffer != sync::code::DISCONNECT_OK )
    {
        OUTPUT_INTERNAL ("wrong header received");
        return -1;
    }
    return 1;
}

int idle (Socket* socket)
{
    if ( !socket || !socket->isBlockError () )
    {
        OUTPUT_INTERNAL ("bad param");
        return 0;
    }
    char buffer[sync::size::REGULAR_HEADER] = {};
    unsigned int ignored      = 0;

    buffer[0] = sync::code::IDLE;
    memcpy (buffer + 1                   , &ignored, sizeof (ignored));
    memcpy (buffer + 1 + sizeof (ignored), &ignored, sizeof (ignored));

    if ( !socket->send (buffer, sync::size::REGULAR_HEADER)
    {
        OUTPUT_INTERNAL ("error with sending CHECK_HASH header");
        return 0;
    }
    if ( !socket->receive (buffer, sync::size::REGULAR_HEADER) )
    {
        OUTPUT_INTERNAL ("error with receiving CHECK_HASH_OK header");
        return 0;
    }
    if ( *buffer != sync::code::IDLE_OK )
    {
        OUTPUT_INTERNAL ("wrong header received");
        return -1;
    }
    return 1;
}

int connect (Socket* socket)
{
    if ( !socket || !socket->isBlockError () )
    {
        OUTPUT_INTERNAL ("bad param");
        return 0;
    }
    char buffer[sync::size::REGULAR_HEADER] = {};
    unsigned int ignored      = 0;

    buffer[0] = sync::code::HANDSHAKE;
    memcpy (buffer + 1                   , &ignored, sizeof (ignored));
    memcpy (buffer + 1 + sizeof (ignored), &ignored, sizeof (ignored));

    if ( !socket->send (buffer, sync::size::REGULAR_HEADER)
    {
        OUTPUT_INTERNAL ("error with sending CHECK_HASH header");
        return 0;
    }
    if ( !socket->receive (buffer, sync::size::REGULAR_HEADER) )
    {
        OUTPUT_INTERNAL ("error with receiving CHECK_HASH_OK header");
        return 0;
    }
    if ( *buffer != sync::code::HANDSHAKE_OK )
    {
        OUTPUT_INTERNAL ("wrong header received");
        return -1;
    }
    return 1;
}

bool partUpdate (Socket* socket, DeltaManager* manager)
{
    if ( !socket || !manager || !socket->isBlockError () || !manager->verify () )
    {
        OUTPUT_INTERNAL ("bad param");
        return false;
    }
    char buffer[sync::size::MAX_MESSAGE] = {};

    int  size        = manager->deltaPartSize ();
    int  headerSize  = sync::size::REGULAR_HEADER;
    int  availible   = sync::size::MAX_MESSAGE - headerSize;
    int  usingSize   = ( availible > size ) ? size : availible;

    int result = informUpdate (1, headerSize + usingSize);
    if ( result <= 0 )
    {
        OUTPUT_INTERNAL ("informing about update failed with code:%d", result);
        return false;
    }

        int index = manager->deltaIndex ();

        buffer[0] = sync::code::DATA_SEND;
        memcpy (buffer + 1                   , &index    , sizeof(index    ));
        memcpy (buffer + 1 + sizeof(tailSize), &usingSize, sizeof(usingSize));

        result = manager->getDelta (buffer + sync::size::UPDATE_HEADER,
                                    usingSize, true);
        if ( !result )
        {
            OUTPUT_INTERNAL ("manager cant get delta");
            return false;
        }

        if ( !socket->send (buffer, usingSize + headerSize) )
        {
            ErrorInfo err = socket->getLastError ();
            OUTPUT_INTERNAL ("cant send err detail:%d %d", err.lib (), err.local ());
            return false;
        }

        if ( !socket->receive (buffer, sync::size::REGULAR_HEADER) )
        {
            ErrorInfo err = socket->getLastError ();
            OUTPUT_INTERNAL ("cant receive err detail:%d %d", err.lib (), err.local ());
            return false;
        }
        if (        buffer         [0] != sync::code::DATA_SEND_OK ||
             ( (int*)(buffer + 1) )[1] != usingSize                  ||
             ( (int*)(buffer + 1) )[2] != index                       )
        {
            OUTPUT_INTERNAL ("bad receive %d:%d:%d", 
                                       buffer       [0], 
                              ( (int*)(buffer + 1) )[1],
                              ( (int*)(buffer + 1) )[2]);
            return false;
        }
    }
    return true;
}



# endif /* H_GRNETWORK_THREAD */
