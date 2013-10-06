# ifndef H_GRNETWORK_RAWSOCKET_RAWSOCKET

# define H_GRNETWORK_RAWSOCKET_RAWSOCKET


class RawSocket
{

    RawSocket (RawSocket&);
    RawSocket& operator = (RawSocket&);

    protected:

    ErrorInfo lastError_;

    public:

    RawSocket ();

    SocketData socketData_;

    ErrorInfo GetLastError ();
    bool isBlockError ();

    bool sync         (bool makeAsync);
    bool customHeader (bool makeCustom);

    bool start (bool IPv6);

    bool setIP   (const char* IP);
    void setPort (short int port);

    int send    (const char* data, unsigned int size);
    int receive (char* data, unsigned int size);

    void stop ();

    ~RawSocket ();

};



# endif /* H_GRNETWORK_RAWSOCKET_RAWSOCKET */
