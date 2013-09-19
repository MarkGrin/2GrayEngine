namespace Network
{

struct Argument
{
    unsigned int column;
    unsigned int line;
    char RequestType;
};

namespace RequestType
{

    const char OneLine   = 'O',
               FullTable = 'F',
               Error     = 'E',
               OneCell   = 'C';
}

# include "backend.h"

bool receive (Table* table, char* IP, short int port)
{
    network::GrinSocketServer server;

    server.SetIP (IP);
    server.SetPort (port);

    unsigned int size = receiveSize (&server);
    if ( !size )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Bad size");
        return false;
    }

    char* message = allocMessage (size);
    if ( !message )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Bad message");
        return false;
    }

    char requestType = receiveMessage (message, &server, size);
    bool success = false;
    if ( requestType == RequestType::OneLine )
    {
        success = _OneLine_get (message, table, size);
    }
    delete[] message;
    return success;
}

bool send (Table* table, const Argument& arg, char* IP, const int port)
{
    unsigned int size = calcSize (table, arg.RequestType);
    if ( !size )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Null sized message cant exist");
        return false;
    }

    char* message = allocMessage (size);
    if ( !message )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Bad message created");
        return false;
    }

    if ( !fillMessage (message, table, size, arg) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant create message");
        delete[] message;
        return false;
    }

    char firstMessage[Setting::NETWORK_FIRST_MESSAGE] = "";
    *((unsigned int*)firstMessage) = size;

    network::GrinSocketClient client;
    client.SetIP   (IP);
    client.SetPort (port);

    if ( client.Start () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant start");
        PrintError (&client);
        delete[] message;
        return false;
    }
    if ( client.Connect () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant connect");
        PrintError (&client);
        delete[] message;
        return false;
    }
    if ( client.Send (firstMessage, Setting::NETWORK_FIRST_MESSAGE) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant send first size message");
        PrintError (&client);
        delete[] message;
        return false;
    }
    if ( client.Receive (firstMessage, Setting::NETWORK_FIRST_MESSAGE) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant Receive first back message");
        PrintError (&client);
        delete[] message;
        return false;
    }
    if ( client.Send (message, size) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant send message");
        PrintError (&client);
        delete[] message;
        return false;
    }
    if ( client.Receive (firstMessage, Setting::NETWORK_FIRST_MESSAGE) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant receive first back message");
        PrintError (&client);
        delete[] message;
        return false;
    }
    delete[] message;
    return true;
}


}  /*-*-*-*-*-*-*-*-*-*-*\
  | * namespace Network * |
   \*_*_*_*_*_*_*_*_*_*_*/
