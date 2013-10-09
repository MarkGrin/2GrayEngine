# ifndef H_GRNETWORK_SOCKET_CLIENT

# define H_GRNETWORK_SOCKET_CLIENT


/**
 *
 * This is Client socket. It is inherited from Socket class. It represent
 * client side of TCP connection.
 *
 */
class Client : public Socket
{

    public:

    bool connect ();

};



# endif /* H_GRNETWORK_SOCKET_CLIENT */
