# ifndef H_GRNETWORK_THREADINFO

# define H_GRNETWORK_THREADINFO


struct threadInfo
{
    bool killSwitch;

    Socket socket;
    DeltaManager* dManager;
};



# endif /* H_GRNETWORK_THREADINFO */
