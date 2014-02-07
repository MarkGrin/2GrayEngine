# ifndef H_GRNETWORK_THREAD

# define H_GRNETWORK_THREAD

void thread     (void* threadInfo_void);
bool fullUpdate (Socket* socket, DeltaManager* manager);
bool newSync (Socket* socket, DeltaManager* manager);

void thread (void* threadInfo_void)
{
    threadInfo* inf = (threadInfo*)smthInfo_void;
    if ( !inf || !dManager || !dManager->verify () || dManager->blockError ())
    {
        OUTPUT_INTERNAL ("bad arg");
        return;
    }

    bool*         killSwitch = &inf->killSwitch;
    Socket*       socket     = &inf->socket;
    DeltaManager* dManager   = inf->dManager;

    newSync ();
    fullUpdate ();
    while ( *killSwitch )
    {
        send diff;
    }
    disconnect;
}

bool fullUpdate (Socket* socket, DeltaManager* manager)
{
    if ( !socket || !manager || !socket->verify () || !manager->verify () )
    {
        OUTPUT_INTERNAL ("bad param");
        return false;
    }
    char buffer[thread::size::MAX_MESSAGE] = {};

    int  size        = manager->size ();
    int  headerSize  = thread::size::MAX_SESSAGE - thread::size::UPDATE_HEADER;
    int  payLoadSize = size - headerSize;
    int  tailSize    = size % payLoadSize;
    int  repeat      = size / payLoadSize;

    for (unsigned int i = 0; i <= repeat; i++)
    {
        int getSize = (i == repeat) ? tailSize : payLoadSize;
        buffer[0] = thread::code::PART_UPDATE;

        memcpy (buffer + 1, &getSize, sizeof (int));

        memcpy (buffer + 1 + sizeof (int), &payLoadSize, sizeof (int));

        manager->get (buffer + thread::size::UPDATE_HEADER);

        if ( !socket->send (buffer, thread::size::MAX_MESSAGE) )
        {
            ErrorInfo err = socket->getLastError ();
            OUTPUT_INTERNAL ("cant send err detail:%d %d", err.lib (), err.local ());
            return false;
        }

        if ( !socket->receive (buffer, thread::size::REGULAR_HEADER) )
        {
            ErrorInfo err = socket->getLastError ();
            OUTPUT_INTERNAL ("cant receive err detail:%d %d", err.lib (), err.local ());
            return false;
        }
        if ( buffer[0] != thread::code::PART_UPDATE_OK )
        {
            OUTPUT_INTERNAL ("bad receive%d", buffer[0]);
            return false;
        }
    }
    return true;
}


# endif /* H_GRNETWORK_THREAD */
