# ifndef H_ENGINE_OBJECTMETHODS

# define H_ENGINE_OBJECTMETHODS


Object :: Object (int typeCode)
    :
    typeCode_ (typeCode)
{
    memcpy (name_, "(no_name)", 10);
}

bool Object :: is (const char* name)
{
    if ( !name )
        return false;
    return !(strcmp (name_, name));
}

bool Object :: setName (const char* name)
{
    if ( !name )
        return false;
    int size = strlen (name);
    size = (size > 32 ) ? 32 : size;
    memcpy (name_, name, size + 1);
}

int Object :: typeCode ()
{
    return typeCode_;
}


# endif /* H_ENGINE_OBJECTMETHODS */
