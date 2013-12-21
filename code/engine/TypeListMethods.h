# ifndef H_ENGINE_TYPELISTMETHODS

# define H_ENGINE_TYPELISTMETHODS


/**
 *
 * this function checks if function class is ok
 *
 * @return -
 * {true}  - ok
 * {false} - broken
 *
 */
bool TypeList :: verify () const
{
    if ( !this )
        return false;
    return true;
}

/**
 *
 * this function adds type
 *
 * @param type      - type to add
 * @param type_code - type code of new type
 *
 * @return - success
 *
 */
bool TypeList :: add (typeAttributes* type, int type_code)
{
    if ( !verify () )
        return false;
    try
    {
        list_[type_code] = *type;
    }
    catch ( ::std::out_of_range)
    {
        //OUTPUT_DEBUG (PLACE, "Cant place code:%d", type_code);
        return false;
    }
    return true;
}

/**
 *
 * this function finds typeAttribute by it's type_code and creates an
 * single object of this type
 *
 * @param type_code - type code of object that will be created
 *
 * @return
 * {  >=0  } - newly created object with given type
 * {nullptr} - error
 *
 */
Object* TypeList :: create (int type_code)
{
    if ( !verify () )
        return nullptr;
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
    catch ( ::std::out_of_range)
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

/**
 *
 * this function finds typeAttribute by it's type_code and creates an
 * single object of this type by calling create function with
 * given argument
 *
 * @param type_code - type code of object that will be created
 * @param what      - argument to create function
 *
 * @return
 * {  >=0  } - newly created object with given type
 * {nullptr} - error
 *
 */
Object* TypeList :: create (int type_code, const char* what)
{
    if ( !verify () )
        return nullptr;
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
    catch ( ::std::out_of_range)
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


/**
 *
 * return number of types that are stored
 *
 * @return - size
 *
 */
unsigned int TypeList :: size () const
{
    if ( !verify () )
        return false;
    return list_.size ();
}

/**
 *
 * this function finds a type with given name
 *
 * @param what - name to look for
 *
 * @return
 * {!=0} - type code of type with given name
 * { 0 } - error code
 *
 */
int TypeList :: find (const char* what)
{
    if ( !verify () )
        return false;
    std::map<int, typeAttributes>::iterator it;
    for (it = list_.begin () ; it != list_.end (); it++)
    {
        if ( !strcmp (it->second.name, what) )
            return it->first;
    }
    return 0;
}



# endif /* H_ENGINE_TYPELISTMETHODS */
