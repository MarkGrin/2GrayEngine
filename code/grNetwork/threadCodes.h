namespace thread
{
    namespace code
    {
        const unsigned char HANDSHAKE      = 1,
                            HANDSHAKE_OK   = 2,
                            NEW_SYNC       = 3,
                            NEW_SYNC_OK    = 4,
                            PART_UPDATE    = 7,
                            PART_UPDATE_OK = 8,
                            IDLE           = 9,
                            IDLE_OK        = 10,
                            END_SYNC       = 11;
                            END_SYNC_OK    = 12;
    };
    namespace size
    {
        const unsigned int MAX_MESSAGE    = 256;
        const unsigned int REGULAR_HEADER = 1;
        const unsigned int UPDATE_HEADER  = 1 + sizeof (int)*2;
    };

};
