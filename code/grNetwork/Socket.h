# ifndef H_GRNETWORK_SOCKET

# define H_GRNETWORK_SOCKET


class Socket
{

    Socket& (Socket&);
    Socket operator = (Socket&);

    protected:

    ErrorInfo lastError_;
    socketData socket_info_;

    public:

    Socket ();

    bool start ();
    void stop ();

    bool setIP     (const char* IP);
    void setPort   (short int port);

    bool out    (const char* what , unsigned int size);
    bool in     (      char* where, unsigned int size);

    void sync (bool makeAsync);

    ErrorInfo getLastError () const;

    ~Socket ();

};



# endif /* H_GRNETWORK_SOCKET */
