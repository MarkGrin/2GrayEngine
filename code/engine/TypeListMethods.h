# ifndef H_ENGINE_TYPELISTMETHODS

# define H_ENGINE_TYPELISTMETHODS


bool TypeList :: add (typeAttributes* type, int type_code)
{
    try
    {
        list_[type_code] = *type;
    }
    catch (...)
    {
        //OUTPUT_DEBUG (PLACE, "Cant place code:%d", type_code);
        return false;
    }
    return true;
}

Object* TypeList :: create (int type_code)
{
    Object* result = nullptr;
    try
    {
        if ( !list_.count (type_code) )
        {
            //OUTPUT_DEBUG (PLACE, "ERROR: NO code:%d in map", type_code);
            return nullptr;
        }
        typeAttributes check = list_[type_code];
        if ( !(check.create) )
        {
            ////OUTPUT_DEBUG (PLACE, "ERROR:NO function to call on code:%d", type_code);
            return nullptr;
        }
        result = check.create ();
    }
    catch (...)
    {
        //OUTPUT_DEBUG (PLACE, "ERROR: Cant access code:%d", type_code);
        return nullptr;
    }
    if ( result )
    {
        return result;
    }
    //OUTPUT_DEBUG (PLACE, "Bad creation of type:%d", type_code);
    return nullptr;
}

Object* TypeList :: create (int type_code, const char* what)
{
    Object* result = nullptr;
    try
    {
        if ( !list_.count (type_code) )
        {
            //OUTPUT_DEBUG (PLACE, "ERROR: NO code:%d in map", type_code);
            return nullptr;
        }
        if ( !list_[type_code].createOn )
        {
            //OUTPUT_DEBUG (PLACE, "ERROR:NO function to call on code:%d", type_code);
            return nullptr;
        }
        result = list_[type_code].createOn (what);
    }
    catch (...)
    {
        //OUTPUT_DEBUG (PLACE, "ERROR: Cant access code:%d", type_code);
        return nullptr;
    }
    if ( result )
    {
        return result;
    }
    //OUTPUT_DEBUG (PLACE, "Bad creation of type:%d", type_code);
    return nullptr;
}


unsigned int TypeList :: size ()
{
    return list_.size ();
}

int TypeList :: find (const char* what)
{
    std::map<int, typeAttributes>::iterator it;
    it = list_.begin ();
    for ( ; it != list_.end (); it++)
    {
        if ( !strcmp (it->second.name, what) )
            return it->first;
    }
    return 0;
}



# endif /* H_ENGINE_TYPELISTMETHODS */
