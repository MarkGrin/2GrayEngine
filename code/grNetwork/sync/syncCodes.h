namespace code
{
    const unsigned char HANDSHAKE      = 1 ,
                        HANDSHAKE_OK   = 2 ,

                        DISCONNECT     = 3 ,
                        DISCONNECT_OK  = 4 ,

                        PART_UPDATE    = 5 ,
                        PART_UPDATE_OK = 6 ,

                        DATA_SEND      = 7 ,
                        DATA_SEND_OK   = 8 ,

                        IDLE           = 9 ,
                        IDLE_OK        = 10,

                        HASH_CHECK     = 11,
                        HASH_CHECK_OK  = 13,

                        CHECK_SIZE     = 14,
                        CHECK_SIZE_OK  = 15;

    const unsigned char USING_MD5       = 1,
                        USING_GRIN_HASH = 2;
};

namespace size
{
    const unsigned int MAX_MESSAGE    = 256;
    const unsigned int REGULAR_HEADER = 1 + sizeof (int) * 2;
};
