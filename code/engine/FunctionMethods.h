# ifndef H_ENGINE_FUNCTIONMETHODS

# define H_ENGINE_FUNCTIONMETHODS

Function :: Function ()
{
}

bool     Function :: pushArg (Object* obj)
{
    try
    {
        args_.push (obj);
        return true;
    }
    catch (...)
    {
        return false;
    }
    return false;
}

Object*  Function :: popArg  ()
{
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

bool Function :: payLoadFunction ()
{
    return true;
}

functionAttributes Function :: attributes ()
{
    functionAttributes attr = {};

    attr.size = sizeof (functionAttributes);
    attr.version = ENGINE_VERSION;
    attr.code = 0;

    attr.name[32 + 1] = 0;

    attr.argnum = 0;
    attr.args = nullptr;

}

bool Function :: execute ()
{
    if ( this->attributes ().argnum != args_.size () )
    {
        return false;
    }

    return this->payLoadFunction ();
}



# endif /* H_ENGINE_FUNCTIONMETHODS */
