# ifndef H_GRNETWORK_RAWSOCKET_RAWSOCKET

# define H_GRNETWORK_RAWSOCKET_RAWSOCKET


class RawSocket
{

    RawSocket (RawSocket&);
    RawSocket& operator = (RawSocket&);

    protected:

    ErrorInfo error_;

    public:

    RawSocket ();

    SocketData socket_;

    bool verify ();

    bool start ();

    int send    (const char* data, unsigned int size);
    int receive (char* data, unsigned int size);

    void stop ();

    ~RawSocket ();

};



# endif /* H_GRNETWORK_RAWSOCKET_RAWSOCKET */
