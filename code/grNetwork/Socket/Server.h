# ifndef H_GRNETWORK_SOCKET_SERVER

# define H_GRNETWORK_SOCKET_SERVER


class Server : public Socket
{

    bool asyncState_;

    public:

    Server ();

    bool listen (Client * listenSocket = nullptr);

};



# endif /* H_GRNETWORK_SOCKET_SERVER */
