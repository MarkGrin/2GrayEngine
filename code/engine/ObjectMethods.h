# ifndef H_ENGINE_OBJECTMETHODS

# define H_ENGINE_OBJECTMETHODS


/**
 *
 * constructor
 *
 * @param typeCode - code of type of this object
 *
 */
Object :: Object (int typeCode)
    :
    typeCode_ (typeCode)
{
    memcpy (name_, "(no_name)", 10);
}

/**
 *
 * this function checks if name of this object and given are the same
 *
 * @param name - name to check identity
 *
 * @return
 * true - same names
 * false - names aren't same
 *
 */
bool Object :: is (const char* name)
{
    if ( !name )
        return false;
    return !(strcmp (name_, name));
}

/**
 *
 * this function sets object's name
 *
 * @param name - new name
 *
 * @return - success
 *
 */
bool Object :: setName (const char* name)
{
    if ( !name )
        return false;
    int size = strlen (name);
    size = (size > 32 ) ? 32 : size;
    memcpy (name_, name, size + 1);
    return true;
}

/**
 *
 * this function return typeCode of  this object
 *
 * @return - typeCode
 * 0 - errorCode
 *
 */
int Object :: typeCode ()
{
    return typeCode_;
}


# endif /* H_ENGINE_OBJECTMETHODS */
