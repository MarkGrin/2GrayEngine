# ifndef H_ENGINE_LIBINFOMETHODS

# define H_ENGINE_LIBINFOMETHODS


/**
 *
 * this function vefifies if LibInfo is ok
 *
 * @return is okay
 * {true}  - ok
 * {false} - error
 *
 */
bool LibInfo :: verify ()
{
    if ( !this )
        return false;
    if ( !handle_ )
        return false;
    return true;
}

/**
 *
 * constructor, all params MUST BE VALID
 *
 * @param name   - name of lib not bigger than LibSizeInfo::MAX_SIZE
 * @param handle - handle to lib
 *
 */
LibInfo :: LibInfo (const char* name, HMODULE* handle)
    :
    handle_ (nullptr)
{
    if ( !name )
        return ;
    int size = strlen (name);
    if ( size > LibInfoSize::MAX_NAME )
        return;
    memcpy (name_, name, size);
    name_[size] = 0;
}

/**
 *
 * this function returns name of the lib
 *
 * @param pointer to the name
 *
 */
const char* LibInfo :: name () const
{
    return name_;
}

/**
 *
 * this is destructor, it frees library
 *
 */
LibInfo :: ~LibInfo ()
{
    if ( handle_ )
        FreeLibrary (*handle_);
    handle_ = 0;
    name_[0] = 0;
}


# endif /* H_ENGINE_LIBINFOMETHODS */
