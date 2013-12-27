# ifndef H_GRNETWORK_SOCKET

# define H_GRNETWORK_SOCKET


class Socket
{

    Socket (Socket&);
    Socket& operator = (Socket&);

    protected:

    ErrorInfo lastError_;

    public:

    socketData socket_info_;

    Socket ();

    bool start ();
    void stop ();

    bool setIP     (const char* IP);
    void setPort   (short int port);

    bool send    (const char* what , unsigned int size);
    bool receive (      char* where, unsigned int size);

    void sync (bool makeAsync);
    bool blockError () const;

    ErrorInfo getLastError () const;

    ~Socket ();

};



# endif /* H_GRNETWORK_SOCKET */
