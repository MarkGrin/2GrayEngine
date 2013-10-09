# ifndef H_GRNETWORK_SOCKET_SERVER

# define H_GRNETWORK_SOCKET_SERVER


/**
 *
 * This is Server class. It is inherited from Socket class. It represents
 * Server side in TCP connection.
 *
 */
class Server : public Socket
{

    bool asyncState_;

    public:

    Server ();

    bool listen (Client * listenSocket = nullptr);

};



# endif /* H_GRNETWORK_SOCKET_SERVER */
