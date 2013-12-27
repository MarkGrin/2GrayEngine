# ifndef H_NETWORK_GRINSOCKET

# define H_NETWORK_GRINSOCKET


/*\
 *
 * This file contain GrinSocket.h 
 * It contain TCPGrinSocket class
 *
\*/

/* * * * * * * * * * * * * * * *\
 *  TODO:                      *
 *  Add comment and documents  *
 *                             *
 *                             *
 *                             *
 *                             *
 *                             *
 *                             *
 *                             *
\* * * * * * * * * * * * * * * */

# include "Ws2tcpip.h"

int StartGrinSocket ()
{
    WSADATA tempData;
    return WSAStartup (MAKEWORD (2,2), &tempData);
}

int StopGrinSocket  ()
{
    return WSACleanup ();
}

struct ErrorInfo
{
    int GrinSocketError;
    int WinSocketError;
};

ErrorInfo MakeError (int grin, int win)
{
    ErrorInfo info;
    info.GrinSocketError = grin;
    info.WinSocketError  = win;
    return info;
}

class ProtectedFromCopy
{
    ProtectedFromCopy (ProtectedFromCopy&);
    ProtectedFromCopy operator = (ProtectedFromCopy);
public:
    ProtectedFromCopy (){};
};

struct WindowSocket
{
    sockaddr_in AddrInfo;
    SOCKET Socket;
};

namespace GrinSocketError
{
    enum Error
    { 
        CantStart           = 19,
        BadAllocation       = 20,
        CantInitilazeData   = 21,
        GrinSocketIsWorking = 22,
        GetAddrFailed       = 23,
        CantCreateWinSocket = 24,
        CantBindSocket      = 25,
        CantListen          = 26,
        CantAccept          = 27,
        SessionWasntStarted = 28,
        ErrorConnect        = 29,
        UnableToConnect     = 30,
        UnableToSend        = 31,
        UnableToReceive     = 32,
        NotConnected        = 33,
        NoSuchProtocol      = 34,
        FakeError           = 35,
        NotStarted          = 36
    };
}

class GrinSocket
{
protected:
    ErrorInfo Error;
public:

    WindowSocket socket_info;

    int Send   (char * What , int Size);
    int Receive (char * Where, int Size);

    void Stop ();

    int SetIP     (const char* IP);
    void SetPort  (short int Port);

    void Sync (bool Sync);

    ErrorInfo GetError ();

    GrinSocket ();
    ~GrinSocket ();
    bool Start ();
};

ErrorInfo GrinSocket :: GetError ()
{
    return Error;
}

int   GrinSocket :: Send (char * What, int Size)
{
    if (socket_info.Socket == INVALID_SOCKET)
    {
        Error = MakeError (GrinSocketError::NotStarted, 0);
        return 1;
    }
    int Result = send (socket_info.Socket, What, Size, 0);

    if (Result == SOCKET_ERROR)
    {
        Error =  MakeError (GrinSocketError::UnableToSend,
                            GetLastError ());
        return 1;
    }
    else
        return 0;
}

int   GrinSocket :: Receive (char * Where, int Size)
{
    if (socket_info.Socket == INVALID_SOCKET)
    {
        Error = MakeError (GrinSocketError::NotStarted, 0);
        return 1;
    }
    int Result = recv (socket_info.Socket, Where, Size, 0);

    if (Result == SOCKET_ERROR)
    {
        Error = MakeError ( GrinSocketError::UnableToReceive,
                            GetLastError ());
        return 1;
    }
    else
        return 0;
}

void  GrinSocket :: Stop ()
{
    closesocket (socket_info.Socket);
    socket_info.Socket = INVALID_SOCKET;
}

GrinSocket :: GrinSocket ():
    socket_info (),
    Error       ()
{
    socket_info.Socket              = INVALID_SOCKET;
    socket_info.AddrInfo.sin_family = AF_INET;
    Error.GrinSocketError           = 0;
    Error.WinSocketError            = 0;
}

GrinSocket :: ~GrinSocket ()
{
    Stop ();
}

int GrinSocket :: SetIP    (const char * IP)
{
    socket_info.AddrInfo.sin_addr.S_un.S_addr = inet_addr (IP);
    if (socket_info.AddrInfo.sin_addr.S_un.S_addr == INADDR_NONE)
    {
        return 1;
    }
    return 0;
}

void GrinSocket :: SetPort  (short int Port)
{
    socket_info.AddrInfo.sin_port = htons (Port);
}

bool GrinSocket :: Start ()
{
    if ( socket_info.Socket != INVALID_SOCKET )
        Stop ();
    
    socket_info.Socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if ( socket_info.Socket == INVALID_SOCKET )
    {
        Error = MakeError (GrinSocketError::CantStart, GetLastError ());
        return true;
    }

    return false;
}

void GrinSocket :: Sync (bool MakeASync)
{
    unsigned long enable = (unsigned long)true;
    if (MakeASync)
        ioctlsocket (socket_info.Socket, FIONBIO, &enable);
    else
        ioctlsocket (socket_info.Socket, 0, NULL);
}

class GrinSocketClient : public GrinSocket
{
public:
    int Connect ();
};

int GrinSocketClient :: Connect ()
{
    if (socket_info.Socket == INVALID_SOCKET)
    {
        Error = MakeError (GrinSocketError::NotStarted, 0);
        return 1;
    }
    int Result = connect (socket_info.Socket,
                         (sockaddr*)(&socket_info.AddrInfo),
                         sizeof (socket_info.AddrInfo) );

    if (Result == SOCKET_ERROR)
    {
        Result = WSAGetLastError ();
        Error = MakeError (GrinSocketError::ErrorConnect, Result);
        return 1;
    }

    return 0;
}

class GrinSocketServer : public GrinSocket
{
public:
    int Listen (GrinSocketClient * ListenSocket = NULL);
};

int GrinSocketServer :: Listen (GrinSocketClient * ListenSocket /* = NULL*/)
{
    if (socket_info.Socket == INVALID_SOCKET)
    {
        Error = MakeError (GrinSocketError::NotStarted, 0);
        return 1;
    }
    socket_info.AddrInfo.sin_addr.S_un.S_addr = htonl (INADDR_ANY);

    int Result = bind (socket_info.Socket, (sockaddr*) &socket_info.AddrInfo,
                       sizeof (socket_info.AddrInfo) );
    if (Result == SOCKET_ERROR)
    {
        Result = WSAGetLastError ();
        Error = MakeError (GrinSocketError::CantBindSocket, Result);
        return 1;
    }

    Result = listen (socket_info.Socket, SOMAXCONN);
    if (Result == SOCKET_ERROR)
    {
        Stop ();
        Result = WSAGetLastError ();
        Error = MakeError (GrinSocketError::CantListen, Result);
        return 1;
    }

    if (ListenSocket)
    {
        if (ListenSocket->socket_info.Socket != INVALID_SOCKET)
            ListenSocket->Stop ();

        ListenSocket->socket_info.Socket = accept (socket_info.Socket,
                                                   NULL, NULL);

        if (ListenSocket->socket_info.Socket == INVALID_SOCKET)
        {
            Result = WSAGetLastError ();
            Error = MakeError (GrinSocketError::CantAccept, Result);
            return 1;
        }
    }
    else
    {
        /*socket_info.Socket = accept (socket_info.Socket, NULL, NULL);
        if (socket_info.Socket == INVALID_SOCKET)
        {
            Result = WSAGetLastError ();
            Error = MakeError (GrinSocketError::CantAccept, Result);
            return 1;
        }*/
        SOCKET swap = accept (socket_info.Socket, NULL, NULL);
        if (swap == INVALID_SOCKET)
        {
            Result = WSAGetLastError ();
            Error = MakeError (GrinSocketError::CantAccept, Result);
            Stop ();
            return 1;
        }
        Stop ();
        socket_info.Socket = swap;
    }
    return 0;

}

# endif /* H_NETWORK_GRINSOCKET */
