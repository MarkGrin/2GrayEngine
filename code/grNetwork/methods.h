# ifndef H_GRNETWORK_METHODS

# define H_GRNETWORK_METHODS


int Start ();
int Stop  ();


int Start ()
{
    WSADATA tempData;
    return WSAStartup (MAKEWORD (2,2), &tempData);
}

int Stop  ()
{
    return WSACleanup ();
}



# endif /* H_GRNETWORK_METHODS */
