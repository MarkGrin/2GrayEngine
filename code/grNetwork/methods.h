# ifndef H_GRNETWORK_METHODS

# define H_GRNETWORK_METHODS


int Start ();
int Stop  ();


<<<<<<< HEAD
/**
 *
 * This function starts GrSocket library. Without it you can't use any
 * GrSocket functions or classes. So don't forget to call this function
 * before using anything from grNetwork.
 *
 * @return error code
 *
 */
=======
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79
int Start ()
{
    WSADATA tempData;
    return WSAStartup (MAKEWORD (2,2), &tempData);
}

<<<<<<< HEAD
/**
 *
 * This function stops GrSocket library. It unloads library so it's
 * important to call it, in order to realease resources. But after you called
 * it you can't use any grNetwork classes or methods.
 *
 * @return error code
 *
 */
=======
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79
int Stop  ()
{
    return WSACleanup ();
}



# endif /* H_GRNETWORK_METHODS */
