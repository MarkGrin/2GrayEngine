# ifndef H_ENGINE_FUNCTIONATTRIBUTESMETHODS

# define H_ENGINE_FUNCTIONATTRIBUTESMETHODS


/**
 *
 * this function verifies the object
 *
 * @return
 * {true}  - ok
 * {false} - broken
 */
bool FunctionAttributes :: verify () const
{
    if ( !this )
    {
        OUTPUT_INTERNAL ("this pointer - is nullptr");
        return false;
    }
    if ( !version_ )
    {
        OUTPUT_INTERNAL ("null version");
        return false;
    }
    if ( !code_ )
    {
        OUTPUT_INTERNAL ("null code");
        return false;
    }
    return true;
}

/**
 *
 * constructor
 *
 * @param code - unique code of this function
 * @param name - name of this function
 *
 */
FunctionAttributes :: FunctionAttributes (int code, const char* name)
    :
    version_ (ENGINE_VERSION),
    code_    (code),
    name_    (nullptr)
{
    try
    {
        unsigned int size = strlen (name);
        name_ = new char[size + 1];
        memcpy (name_, name, size);
        name_[size] = '\0';
    }
    catch (::std::bad_alloc)
    {
        OUTPUT_INTERNAL ("cant alloc");
    }
}

/**
 *
 * copy constructor
 * @param attr - what to copy
 *
 */
FunctionAttributes :: FunctionAttributes (FunctionAttributes& attr)
    :
    version_ (ENGINE_VERSION),
    code_    (attr.code ()),
    name_    (nullptr)
{
    try
    {
        unsigned int size = strlen (attr.name ());
        name_ = new char[size + 1];
        memcpy (name_, attr.name(), size);
        name_[size] = '\0';
    }
    catch (::std::bad_alloc)
    {
        OUTPUT_INTERNAL ("cant alloc");
    }
}

/**
 *
 * getter of unique code
 *
 * @return unique code
 *
 */
int FunctionAttributes :: code () const
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("bad object");
        return 0;
    }
    return code_;
}

/**
 *
 * getter of version 
 *
 * @return unique code
 *
 */
int FunctionAttributes :: version () const
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("bad object");
        return 0;
    }
    return version_;
}

/**
 *
 * getter of name
 *
 */
const char* FunctionAttributes :: name () const
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("bad object");
        return 0;
    }
    return name_;
}

/**
 *
 * this function returns number of arguments
 *
 * @return
 * {>=0} - number of arguments
 * {-1 } - error
 *
 */
int FunctionAttributes :: argnum () const
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("bad object");
        return -1;
    }
    return args_.size ();
}

/**
 *
 * this function returns type code of argument
 *
 * @param index - index of argument whose code will be returned
 *
 * @return
 * {!=0} - type code
 * { 0 } - error
 *
 */
int  FunctionAttributes :: arg (unsigned int index) const
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("bad object");
        return 0;
    }
    try
    {
        if ( args_.size () <= index )
            return 0;
        return args_.at (index);
    }
    catch (::std::out_of_range)
    {
        OUTPUT_INTERNAL ("bad index out of range index:%d size:%d", index,
                                                             args_.size ());
        return 0;
    }
    return 0;
}


/**
 *
 * this function adds argument.
 *
 * @param code - code of the argument
 *
 * @return success
 *
 */
bool FunctionAttributes :: pushArg (int code)
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("bad object");
        return false;
    }
    try
    {
        args_.push_back (code);
    }
    catch (::std::bad_alloc)
    {
        OUTPUT_INTERNAL ("cant push argument");
        return false;
    }
    return true;
}

/**
 *
 * destructor
 *
 */
FunctionAttributes :: ~FunctionAttributes ()
{
    code_ = 0;
    version_ = 0;
    if ( name_ )
        delete[] name_;
    name_ = nullptr;
}

# endif /* H_ENGINE_FUNCTIONATTRIBUTESMETHODS */

