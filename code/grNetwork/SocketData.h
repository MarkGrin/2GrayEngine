# ifndef H_GRNETWORK_SOCKETDATA

# define H_GRNETWORK_SOCKETDATA


<<<<<<< HEAD
/**
 *
 * This struct contains varibles from network library (winsock) that are
 * often used together and without them you can't use library (winsock).
 * So it's natural to put them in structure.
 *
 */
=======
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79
struct socketData
{
    sockaddr_in addrInfo;
    SOCKET socket;
};



# endif /* H_GRNETWORK_SOCKETDATA */
