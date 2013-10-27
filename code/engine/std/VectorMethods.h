# ifndef H_ENGINE_STD_VECTORMETHODS

# define H_ENGINE_STD_VECTORMETHODS


template <class _dataType>
bool Vector<_dataType> :: verify ()
{
    if ( size_ < 0 )
        return false;

    return true;
}

template <class _dataType>
Vector<_dataType> :: Vector  ()
    :
    size_ (0),
    data_ (nullptr)
{
}

template <class _dataType>
Vector<_dataType> :: Vector (unsigned int size)
    :
    size_ (0),
    data_ (0)
{
    try
    {
        data_ = new _dataType[size];
        size_ = size;
    }
    catch (...)
    {
        size_ = -1;
        data_ = nullptr;
    }
}

template <class _dataType>
unsigned int Vector<_dataType> :: size ()
{
    return size_;
}

template <class _dataType>
_dataType& Vector<_dataType> :: at (unsigned int index)
{
    if ( !verify () )
        throw "Bad object";
    if ( index >= size_ )
        throw "Bad argument";

    return data_[index];
}

template <class _dataType>
_dataType& Vector<_dataType> :: operator [] (unsigned int index)
{
    if ( !verify () )
        throw "Bad object";
    if ( index >= size_ )
    {
        try
        {
            this->resize (index + 1);
        }
        catch (...)
        {
            throw "Cant expand object";
        }
    }

    if ( !verify () )
        throw "Object was broken";

    return data_[index];

}

template <class _dataType>
bool Vector<_dataType> :: erase   (unsigned int from, unsigned int to)
{
    if ( !verify () )
        throw "Bad object";
    if ( from >= size_ || to >= size_ || from > to)
        throw "Bad argument";
    if ( from == 0 && to == size_ - 1)
    {
        if ( data_ )
            delete[] data_;
        data_ = nullptr;
        size_ = 0;
        return true;
    }

    try
    {
        _dataType* replace = new _dataType[size_ + from - to - 1];
        memcpy (replace, data_, from*sizeof(_dataType));
        memcpy (replace + from, data_ + to + 1,
               (size_ - to - 1) * sizeof(_dataType) );


        if ( data_ )
        delete[] data_;

        data_ = replace;
        size_ = size_ + from - to - 1;
    }
    catch (...)
    {
        throw "Cant resize";
    }

    if ( !verify () )
        throw "Object was broken";

    return true;
}

template <class _dataType>
bool Vector<_dataType> :: erase   (unsigned int what)
{
    return erase (what, what);/* wat */
}

template <class _dataType>
bool Vector<_dataType> :: resize  (unsigned int to)
{
    if ( !verify () )
        throw "Bad object";
    if ( to == size_ )
        return true;
    if ( to == 0 )
    {
        if ( data_ )
            delete[] data_;
        data_ = nullptr;
        size_ = 0;

        return true;
    }

    try
    {
        _dataType* replace = new _dataType[to];
        unsigned int copySize = (( to >= size_ ) ? size_ : to);
        memcpy (replace, data_, copySize*sizeof (_dataType));

        if ( data_ )
        delete[] data_;

        data_ = replace;
        size_ = to;
    }
    catch (...)
    {
        throw "Cant resize";
    }

    if ( !verify () )
        throw "Object was broken";

    return true;
}

template <class _dataType>
void Vector<_dataType> :: Dump ()
{
    printf ("\nThis is Vector dump");
    printf ("\nData pointer:%p", data_);
    printf ("\nSize is:%d\n\n", size_);
    for (unsigned int i = 0; i < size_; i++)
    {
        printf ("  [%d]:%d\n", i, data_[i]);
    }
    printf ("\nEND\n");
}

template <class _dataType>
Vector<_dataType> :: ~Vector ()
{
    if ( data_ )
        delete[] data_;

    data_ = nullptr;
    size_ = -1;
}



# endif /* H_ENGINE_STD_VECTORMETHODS */
