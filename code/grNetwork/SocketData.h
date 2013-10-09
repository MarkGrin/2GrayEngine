# ifndef H_GRNETWORK_SOCKETDATA

# define H_GRNETWORK_SOCKETDATA


/**
 *
 * This struct contains varibles from network library (winsock) that are
 * often used together and without them you can't use library (winsock).
 * So it's natural to put them in structure.
 *
 */
struct socketData
{
    sockaddr_in addrInfo;
    SOCKET socket;
};



# endif /* H_GRNETWORK_SOCKETDATA */
