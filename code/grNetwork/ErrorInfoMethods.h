# ifndef H_GRNETWORK_ERRORINFOMETHODS

# define H_GRNETWORK_ERRORINFOMETHODS


ErrorInfo :: ErrorInfo (unsigned int local, unsigned int lib)
    :
    local_ (local),
    lib_   (lib)
{}

void ErrorInfo :: set (unsigned int local, unsigned int lib)
{
    local_ = local;
    lib_   = lib;

    return;
}

void ErrorInfo :: set (const ErrorInfo& ei)
{
    local_ = ei.local ();
    lib_   = ei.lib   ();

    return;
}

unsigned int ErrorInfo :: local () const
{
    return local_;
}

unsigned int ErrorInfo :: lib () const
{
    return lib_;
}



# endif /* H_GRNETWORK_ERRORINFOMETHODS */
