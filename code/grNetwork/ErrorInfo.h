# ifndef H_GRNETWORK_ERRORINFO

# define H_GRNETWORK_ERRORINFO


<<<<<<< HEAD
/**
 *
 *  This class provides information about error. It stores error in two
 *  parts. local - is error that happened in GrNetwork module. lib - is
 *  error that happened in socket library (winsock). Some winsock error
 *  can cause error in GrNetwork module, so ErrorInfo class can contain
 *  both of them.
 *
 */
=======
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79
class ErrorInfo
{
    unsigned int local_,
                 lib_;

    public:

    ErrorInfo (unsigned int local, unsigned int lib);

    void set (unsigned int local, unsigned int lib);
    void set (const ErrorInfo&);

    unsigned int local () const;
    unsigned int lib   () const;
};



# endif /* H_GRNETWORK_ERRORINFO */
