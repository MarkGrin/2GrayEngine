# ifndef H_ENGINE_LIBINFOMETHODS

# define H_ENGINE_LIBINFOMETHODS


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

const char* LibInfo :: name () const
{
    return name_;
}

LibInfo :: ~LibInfo ()
{
    if ( handle_ )
        FreeLibrary (*handle_);
    handle_ = 0;
    name_[0] = 0;
}


# endif /* H_ENGINE_LIBINFOMETHODS */
