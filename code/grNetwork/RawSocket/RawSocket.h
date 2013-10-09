# ifndef H_GRNETWORK_RAWSOCKET_RAWSOCKET

# define H_GRNETWORK_RAWSOCKET_RAWSOCKET


/**
 *
 * This class is an interface for Raw sockets. These sockets use IP protocol.
 *
 */
class RawSocket
{

    RawSocket (RawSocket&);
    RawSocket& operator = (RawSocket&);

    protected:

    ErrorInfo lastError_;

    public:

    RawSocket ();

    socketData socketData_;

    ErrorInfo GetLastError ();
    bool isBlockError ();

    bool sync         (bool makeAsync);
    bool customHeader (bool makeCustom);

    bool start ();

    bool setIP   (const char* IP);
    void setPort (short int port);

    int  send    (const char* data, unsigned int size);
    bool receive (char* data, unsigned int size);

    void stop ();

    ~RawSocket ();

};



# endif /* H_GRNETWORK_RAWSOCKET_RAWSOCKET */
