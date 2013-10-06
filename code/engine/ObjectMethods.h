# ifndef H_ENGINE_OBJECTMETHODS

# define H_ENGINE_OBJECTMETHODS


Object :: Object (int typeCode)
    :
    typeCode_ (typeCode)
{}

int Object :: typeCode ()
{
    return typeCode_;
}


# endif /* H_ENGINE_OBJECTMETHODS */
