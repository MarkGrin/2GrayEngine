unsigned int calcSize       (Table*                     table,   char                   RequestType);
unsigned int calcSize_O     (Table*                     table);
bool         fillMessage    (char*                    message, Table*                      table,  unsigned int size, const Argument& arg );
bool         fillMessage_O  (char*                    message, Table*                      table,  unsigned int size, unsigned int    line);
bool         _OneLine_get   (char*                    message, Table*                      table,  unsigned int size);
char         receiveMessage (char*                    message, network::GrinSocketServer* server, unsigned int size);
char*        allocMessage   (unsigned int             size   );
unsigned int receiveSize    (network::GrinSocketServer* server);
void         PrintError     (network::GrinSocket*       server)
{
    START_FUNCTION;
    network::ErrorInfo error = server->GetError ();
    OUTPUT_DEBUG (PLACE, "ERROR:Grin:%d Win:%d", error.GrinSocketError,
                                                 error.WinSocketError );
    return;
}

unsigned int receiveSize (network::GrinSocketServer* server)
{
    START_FUNCTION;
    char message[8] = "";
    unsigned int size = 0;
    if ( server->Start () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant start server");
        PrintError (server);
        return size;
    }
    OUTPUT_DEBUG (PLACE, "DEBUG:Started");

    if ( server->Listen () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Listen failure");
        PrintError (server);
        return size;
    }
    OUTPUT_DEBUG (PLACE, "DEBUG:Listened");

    if ( server->Receive (message, 8) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant receive message");
        PrintError (server);
        return size;
    }
    size = *((unsigned int*)message);
    OUTPUT_DEBUG (PLACE, "DEBUG:Message size:%d", size);

    if ( server->Send (message, 8) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant receive message");
        PrintError (server);
        return 0;
    }
    OUTPUT_DEBUG (PLACE, "DEBUG:Send back complete");

    return size;
}

char* allocMessage (unsigned int size)
{
    START_FUNCTION;
    char* result = nullptr;
    try
    {
        result = new char[size];
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant alloc message");
        return nullptr;
    }
    return result;
}

char receiveMessage (char* message, network::GrinSocketServer* server, unsigned int size)
{
    START_FUNCTION;
    if ( server->Receive (message, size) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant receive");
        PrintError (server);
        return '\0';
    }
    char backsend[8] = "";
    *((unsigned int*)backsend) = size;
    if ( server->Send (backsend, 8 ) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant receive");
        PrintError (server);
        return '\0';
    }
    OUTPUT_DEBUG (PLACE, "DEBUG:Message type:%c", message[0]);
    return message[0];
}

bool _OneLine_get (char* message, Table* table, unsigned int size)
{
    START_FUNCTION;
    unsigned int index = 1;

    if ( !table->expand () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant expand table");
        return false;
    }

    unsigned int columnNumber = table->columnNumber ();
    for (unsigned int column = 0; column < columnNumber; column++)
    {
        unsigned int currentSize = table->size (column);
        if ( size - currentSize - index < 0 )
        {
            OUTPUT_DEBUG (PLACE, "ERROR:Missing part of message. Message too small");
            return false;
        }
        if ( !table->put (column, table->height () - 1, message + index) )
        {
            OUTPUT_DEBUG (PLACE, "ERROR:Cant put %d", column);
            return false;
        }
        index += currentSize;
    }
    return true;
}

unsigned int lineSize (Table* table)
{
    unsigned int size = 0;
    for (int i = 0; i < table->columnNumber (); i++)
    {
        size += table->size (i);
    }
    return size;
}

unsigned int calcSize (Table* table, char RequestType)
{
    START_FUNCTION;
    if ( RequestType == RequestType::OneLine )
    {
        return calcSize_O (table);
    }
    return 0;
}

unsigned int calcSize_O (Table* table)
{
    START_FUNCTION;
    unsigned int size = 0;
    for (int i = 0; i < table->columnNumber (); i++)
    {
        size += table->size (i);
    }
    OUTPUT_DEBUG (PLACE, "ERROR:No such type");
    return size + 1;
}

bool fillMessage (char* message, Table* table, unsigned int size, const Argument& arg)
{
    START_FUNCTION;
    if ( arg.RequestType == RequestType::OneLine )
    {
        return fillMessage_O (message, table, size, arg.line);
    }
    OUTPUT_DEBUG (PLACE, "ERROR:No such type");
    return false;
}

bool fillMessage_O (char* message, Table* table, unsigned int size, unsigned int line)
{
    START_FUNCTION;
    *message = 'O';
    unsigned int index = 1;
    for (int i = 0; i < table->columnNumber (); i++)
    {
        Element* element = table->get (i, line);
        if ( !element )
        {
            OUTPUT_DEBUG (PLACE, "ERROR:Null object x:%d y:%d", i, line);
            return false;
        }
        element->get (message + index);
        index += table->size (i);
    }
    return true;
}
