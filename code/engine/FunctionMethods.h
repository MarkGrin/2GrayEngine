# ifndef H_ENGINE_FUNCTIONMETHODS

# define H_ENGINE_FUNCTIONMETHODS


/**
 *
 * this function checks if function class is ok
 *
 * @return -
 * {true}  - ok
 * {false} - broken
 *
 */
bool Function :: verify () const
{
    if ( !this )
        return false;
    return true;
}

/**
 *
 * blank constructor of function.
 *
 */
Function :: Function ()
{
}

/**
 *
 * adds argument to function
 *
 * @param Object - argument to push
 *
 * @return - success
 *
 */
bool     Function :: pushArg (Object* obj)
{
    if ( !verify () )
        return false;
    try
    {
        args_.push (obj);
        return true;
    }
    catch (std::bad_alloc)
    {
        return false;
    }
    return false;
}

/**
 *
 * returns arguments that was previously pushed in
 *
 * @retrun - pointer to a object that was pushed
 * nullptr - error
 *
 */
Object*  Function :: popArg  ()
{
    if ( !verify () )
        return nullptr;

    Object* result = nullptr;
    if ( args_.empty () )
    {
        OUTPUT_INTERNAL ("empty argument list");
        return nullptr;
    }
    result = args_.top ();
    args_.pop();
    return result;
}

/**
 *
 * user function that user must overload.
 *
 * @return - success
 *
 */
bool Function :: payLoadFunction ()
{
    if ( !verify () )
        return false;
    return true;
}

/**
 *
 * this function return valid attributes structure about this function
 *
 * @return - valid structure about this function
 *
 */
functionAttributes Function :: attributes () const
{
    functionAttributes attr = {};
    if ( !verify () )
        return attr;

    attr.size = sizeof (functionAttributes);
    attr.version = ENGINE_VERSION;
    attr.code = 0;

    attr.name[32 + 1] = 0;

    attr.argnum = 0;
    attr.args = nullptr;

}

/**
 *
 * this function checks if function is ready to be called and if it is
 * it calls it.
 *
 * @return - success
 *
 */
bool Function :: execute ()
{
    if ( this->attributes ().argnum != args_.size () )
    {
        return false;
    }

    return this->payLoadFunction ();
}



# endif /* H_ENGINE_FUNCTIONMETHODS */
