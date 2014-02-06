# ifndef H_USERLIB_SOCKET

# define H_USERLIB_SOCKET


class Socket : public logic::Object
{
    grNetwork::Server server_;
    grNetwork::Client client_;
    bool              isServer_;

    public:

    Socket ();

    void setPort (const char* port);
    void setIP   (const char* IP);

    void listen  ();
    void connect ();

    void send    (const char* buff, int size);
    void receive (      char* txt , int size);

    void start   ();

    ~Socket ();
};

logic::Object* SOCKETcreateOn (const char*);
logic::Object* SOCKETcreate   ();

logic::TypeAttributes SOCKETattributes (777, "Socket", userlib::SOCKETcreate, userlib::SOCKETcreateOn);


# endif /* H_USERLIB_SOCKET */
