# ifndef H_ENGINE_SCRIPTHOLDERMETHODS

# define H_ENGINE_SCRIPTHOLDERMETHODS


ScriptHolder :: ScriptHolder (ScriptHolder& holder)
{
    for (unsigned i = 0; i < holder.lines (); i++)
    {
        char* ptr = nullptr;
        unsigned int size = holder.length (i) + 1;

        try
        {
            ptr = new char[size];
        }
        catch (...)
        {
            continue;
        }
        
        if ( !holder.get (ptr, size, i) )
        {
            delete[] ptr;
            continue;
        }
        ptr[size] = 0;

        try
        {
            lines_.push_back (ptr);
        }
        catch (...)
        {
            delete[] ptr;
            continue;
        }

    }
}

ScriptHolder :: ScriptHolder ()
{}

unsigned int ScriptHolder :: lines  () const
{
    return lines_.size ();
}

int ScriptHolder :: length (unsigned int index) const
{
    try
    {
        const char* ptr = lines_.at (index);
        if ( !ptr )
            return -1;
        return strlen (ptr);
    }
    catch (...)
    {
    }
    return -1;
}

bool ScriptHolder :: pushBack (const char* line, unsigned int size_)
{
    if ( !line )
        return false;

    unsigned int size = size_;
    if ( !size )
       size = strlen (line); 
    if ( !size )
        return false;

    char* ptr = nullptr;

    try
    {
        ptr = new char[size + 1];
        memcpy (ptr, line, size);
        ptr[size] = 0;
    }
    catch (...)
    {
        return false;
    }

    try
    {
        lines_.push_back (ptr);
    }
    catch (...)
    {
        delete[] ptr;
        return false;
    }

    return true;
}

bool ScriptHolder :: insert (const char* line, unsigned int size_, unsigned int index)
{
    if ( !line )
        return false;

    unsigned int size = size_;
    if ( !size )
       size = strlen (line); 
    if ( !size )
        return false;

    char* ptr = nullptr;

    try
    {
        ptr = new char[size + 1];
        ptr[size] = 0;
    }
    catch (...)
    {
        return false;
    }

    try
    {
        std::vector<char*>::iterator it = lines_.begin ();
        it += index;
        lines_.insert (it, ptr);
    }
    catch (...)
    {
        delete[] ptr;
        return false;
    }

    return true;

}

char* ScriptHolder :: get (unsigned int index, unsigned int size) const
{
    if ( !size || size > this->length(index) )
        return nullptr;
    if ( index > lines_.size () )
        return nullptr;

    char* ptr = nullptr;

    try
    {
        ptr = new char[size + 1];
        ptr[size] = 0;
    }
    catch (...)
    {
        return nullptr;
    }

    try
    {
        memcpy (ptr, lines_.at (index), size);
    }
    catch (...)
    {
        delete[] ptr;
        return nullptr;
    }

    return ptr;

}

int  ScriptHolder :: get (char*        buffer, unsigned int size,
                          unsigned int index ) const
{
    if ( index > lines_.size () )
        return -1;
    if ( !size )
        return -1;
    if ( size > this->length (index) )
        size = this->length (index);

    try
    {
        memcpy (buffer, lines_.at (index), size);
        buffer[size] = 0;
    }
    catch (...)
    {
        return -1;
    }
    return size;
}

bool ScriptHolder :: remove  (unsigned int index)
{
    if ( index > lines_.size () )
        return false;
    try
    {
        std::vector<char*>::iterator it = lines_.begin () + index;
        lines_.erase (it);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool ScriptHolder :: replace (const char*  line , unsigned int length,
                              unsigned int index)
{
     if ( !line )
        return false;

    unsigned int size = length;
    if ( !size )
       size = strlen (line); 
    if ( !size )
        return false;

    char* ptr = nullptr;

    try
    {
        ptr = new char[size + 1];
        ptr[size] = 0;
    }
    catch (...)
    {
        return false;
    }

    try
    {
        std::vector<char*>::iterator it = lines_.begin ();
        it += index;
        lines_.insert (it, ptr);

        it = lines_.begin () + size + 1;
        char* replaced = lines_.at (size + 1);
        if ( replaced )
            delete[] replaced;/* No data leak */
        lines_.erase (it);
    }
    catch (...)
    {
        delete[] ptr;
        return false;
    }

    return true;
}

ScriptHolder :: ~ScriptHolder ()
{
    unsigned int size = lines_.size ();
    for (unsigned int i = 0; i < size; i++)
    {
        try
        {
            char* ptr = lines_.at (i);
            if ( ptr )
                delete[] ptr;
            ptr = nullptr;
        }
        catch (...)
        {
        }
    }
}



# endif /* H_ENGINE_SCRIPTHOLDERMETHODS */
