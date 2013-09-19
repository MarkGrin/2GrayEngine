# ifndef H_GRNETWORK_SERVER

# define H_GRNETWORK_SERVER


class Server : public Socket
{

    public:

    bool listen (Client * listenSocket = nullptr);

};



# endif /* H_GRNETWORK_SERVER */
