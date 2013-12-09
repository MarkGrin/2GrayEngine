# ifndef H_GRNETWORK_METHODS

# define H_GRNETWORK_METHODS


int Start ();
int Stop  ();


/**
 *
 * This function starts GrSocket library. Without it you can't use any
 * GrSocket functions or classes. So don't forget to call this function
 * before using anything from grNetwork.
 *
 * @return error code
 *
 */
int Start ()
{
    WSADATA tempData;
    return WSAStartup (MAKEWORD (2,2), &tempData);
}

/**
 *
 * This function stops GrSocket library. It unloads library so it's
 * important to call it, in order to realease resources. But after you called
 * it you can't use any grNetwork classes or methods.
 *
 * @return error code
 *
 */
int Stop  ()
{
    return WSACleanup ();
}



# endif /* H_GRNETWORK_METHODS */
