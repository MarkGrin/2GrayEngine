# ifndef H_GRNETWORK_ERRORINFOMETHODS

# define H_GRNETWORK_ERRORINFOMETHODS


<<<<<<< HEAD
/**
 *
 * This is constructor that sets error codes.
 * 
 * @param local local error to be set.
 * @param lib error code that happened in library to be set.
 *
 */
=======
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79
ErrorInfo :: ErrorInfo (unsigned int local, unsigned int lib)
    :
    local_ (local),
    lib_   (lib)
{}

<<<<<<< HEAD
/**
 *
 * This is function that sets error code values.
 *
 * @param local local error to be set.
 * @param lib error code that happened in library to be set.
 *
 */
=======
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79
void ErrorInfo :: set (unsigned int local, unsigned int lib)
{
    local_ = local;
    lib_   = lib;

    return;
}

<<<<<<< HEAD
/**
 *
 * This function set error codes values by copying them from another ErrorInfo
 * class.
 *
 * @param ei ErrorInfo class that contains error codes to be copied.
 *
 */
=======
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79
void ErrorInfo :: set (const ErrorInfo& ei)
{
    local_ = ei.local ();
    lib_   = ei.lib   ();

    return;
}

<<<<<<< HEAD
/**
 *
 * This function returns local error.
 *
 * @return local error.
 *
 */
=======
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79
unsigned int ErrorInfo :: local () const
{
    return local_;
}

<<<<<<< HEAD
/**
 *
 * This function return lib error code.
 *
 * @return lib error.
 *
 */
=======
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79
unsigned int ErrorInfo :: lib () const
{
    return lib_;
}



# endif /* H_GRNETWORK_ERRORINFOMETHODS */
