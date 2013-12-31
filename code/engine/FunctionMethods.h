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
    :
    attributes_ (nullptr)
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
    OUTPUT_INTERNAL ("abstract class attribtues called");
    return false;
}

/**
 *
 * this function return valid attributes structure about this function
 *
 * @return - valid pointer to FunctionAttrubute class
 *
 */
FunctionAttributes* Function :: attributes () const
{
    OUTPUT_INTERNAL ("abstract class attribtues called");
    return nullptr;
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
    if ( !attributes_ )
    {
        try
        {
            attributes_ = this->attributes ();
            if ( !(attributes_->verify ()) )
            {
                OUTPUT_INTERNAL ("bad alloced attributes");
                return false;
            }
        }
        catch (::std::bad_alloc)
        {
            OUTPUT_INTERNAL ("cant alloc attributes");
            return false;
        }
    }
    if ( attributes_->argnum () != args_.size () )
    {
        return false;
    }

    return this->payLoadFunction ();
}



# endif /* H_ENGINE_FUNCTIONMETHODS */
