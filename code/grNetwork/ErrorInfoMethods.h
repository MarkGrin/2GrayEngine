# ifndef H_GRNETWORK_ERRORINFOMETHODS

# define H_GRNETWORK_ERRORINFOMETHODS


/**
 *
 * This is constructor that sets error codes.
 * 
 * @param local local error to be set.
 * @param lib error code that happened in library to be set.
 *
 */
ErrorInfo :: ErrorInfo (unsigned int local, unsigned int lib)
    :
    local_ (local),
    lib_   (lib)
{}

/**
 *
 * This is function that sets error code values.
 *
 * @param local local error to be set.
 * @param lib error code that happened in library to be set.
 *
 */
void ErrorInfo :: set (unsigned int local, unsigned int lib)
{
    local_ = local;
    lib_   = lib;

    return;
}

/**
 *
 * This function set error codes values by copying them from another ErrorInfo
 * class.
 *
 * @param ei ErrorInfo class that contains error codes to be copied.
 *
 */
void ErrorInfo :: set (const ErrorInfo& ei)
{
    local_ = ei.local ();
    lib_   = ei.lib   ();

    return;
}

/**
 *
 * This function returns local error.
 *
 * @return local error.
 *
 */
unsigned int ErrorInfo :: local () const
{
    return local_;
}

/**
 *
 * This function return lib error code.
 *
 * @return lib error.
 *
 */
unsigned int ErrorInfo :: lib () const
{
    return lib_;
}



# endif /* H_GRNETWORK_ERRORINFOMETHODS */
