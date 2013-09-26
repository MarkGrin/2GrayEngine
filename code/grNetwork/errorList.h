# ifndef H_GRNETWORK_ERRORLIST

# define H_GRNETWORK_ERRORLIST


namespace error
{
    const unsigned int

        CantStart           = 19,
        BadAllocation       = 20,
        CantInitilazeData   = 21,
        GrinSocketIsWorking = 22,
        GetAddrFailed       = 23,
        CantCreateWinSocket = 24,
        CantBindSocket      = 25,
        CantListen          = 26,
        CantAccept          = 27,
        SessionWasntStarted = 28,
        ErrorConnect        = 29,
        UnableToConnect     = 30,
        UnableToSend        = 31,
        UnableToReceive     = 32,
        NotConnected        = 33,
        NoSuchProtocol      = 34,
        FakeError           = 35,
        CantSetIP           = 36,
        NotStarted          = 37;

};



# endif /* H_GRNETWORK_ERRORLIST */
