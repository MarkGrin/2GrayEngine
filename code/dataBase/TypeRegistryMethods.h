# ifndef H_DATABASE_TYPEREGISTRYMETHODS

# define H_DATABASE_TYPEREGISTRYMETHODS


bool TypeRegistry :: add (type_* type, int type_code)
{
    START_FUNCTION
    try
    {
        registry[type_code] = *type;
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "Cant place code:%d", type_code);
        return false;
    }
    return true;
}

Element* TypeRegistry :: create (int type_code)
{
    START_FUNCTION
    Element* result = NULL;
    try
    {
        if ( !registry.count (type_code) )
        {
            OUTPUT_DEBUG (PLACE, "ERROR: NO code:%d in map", type_code);
            return NULL;
        }
        if ( !registry[type_code].create )
        {
            OUTPUT_DEBUG (PLACE, "ERROR:NO function to call on code:%d", type_code);
            return NULL;
        }
        result = registry[type_code].create ();
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR: Cant access code:%d", type_code);
        return NULL;
    }
    if ( result )
    {
        return result;
    }
    OUTPUT_DEBUG (PLACE, "Bad creation of type:%d", type_code);
    return NULL;
}

Element* TypeRegistry :: create (int type_code, char* what)
{
    START_FUNCTION
    $ Element* result = NULL;
    try
    {
        if ( !registry.count (type_code) )
        {
            OUTPUT_DEBUG (PLACE, "ERROR: NO code:%d in map", type_code);
            return NULL;
        }
        $ if ( !registry[type_code].createOn )
        {
            OUTPUT_DEBUG (PLACE, "ERROR:NO function to call on code:%d", type_code);
            return NULL;
        }
        $ result = registry[type_code].createOn (what);
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR: Cant access code:%d", type_code);
        return NULL;
    }
    if ( result )
    {
        $ return result;
    }
    OUTPUT_DEBUG (PLACE, "Bad creation of type:%d", type_code);
    $ return NULL;
}

int TypeRegistry :: sizeOf (int type_code)
{
    START_FUNCTION

    return registry[type_code].size;
}

# endif /* H_DATABASE_TYPEREGISTRYMETHODS */
