# ifndef H_ENGINE_STD_STACKMETHODS

# define H_ENGINE_STD_STACKMETHODS


template <class _dataType>
bool Stack<_dataType> :: verify ()
{
    if ( !data_.verify () )
        return false;
    return true;
}

template <class _dataType>
Stack<_dataType> :: Stack ()
{}

template <class _dataType>
bool Stack<_dataType> :: push (_dataType& obj)
{
    if ( !verify () )
        throw "Object is bad";

    try
    {
        data_[data_.size()] = obj;
    }
    catch (...)
    {
        throw "Cant expand object";
    }
    
    if ( !verify () )
        throw "Object was broken";

    return true;
}

template <class _dataType>
bool Stack<_dataType> :: pop ()
{
    if ( !verify () )
        throw "Object is bad";

    try
    {
        data_.erase (data_.size()-1);
    }
    catch (...)
    {
        throw "Cant pop";
    }
    
    if ( !verify () )
        throw "Object was broken";

    return true;
}

template <class _dataType>
unsigned int Stack<_dataType> :: size ()
{
    if ( verify () )
        return data_.size ();
    throw "Bad object";
}

template <class _dataType>
_dataType& Stack<_dataType> :: top ()
{
    if ( !verify () )
        throw "Object is bad";

    try
    {
        return data_.at (data_.size() - 1);
    }
    catch (...)
    {
        throw "Cant return it";
    }
};

template <class _dataType>
void Stack<_dataType> :: Dump ()
{
    printf ("\nThis is Stack dump, calling my vector dump");
    data_.Dump ();
}


template <class _dataType>
Stack<_dataType> :: ~Stack ()
{
}


# endif /* H_ENGINE_STD_STACKMETHODS */
