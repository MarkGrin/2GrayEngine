# ifndef H_ENGINE_SCRIPTHOLDERMETHODS

# define H_ENGINE_SCRIPTHOLDERMETHODS


/**
 *
 * copy constructor
 *
 * @param holder - scriptHolder to copy
 *
 */
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
        catch (::std::bad_alloc)
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
        catch (::std::bad_alloc)
        {
            delete[] ptr;
            continue;
        }

    }
}

/**
 *
 * standard constructor
 *
 */
ScriptHolder :: ScriptHolder ()
{}

/**
 *
 * this function return number of lines in script
 *
 * @return - number of lines
 *
 */
unsigned int ScriptHolder :: lines  () const
{
    return lines_.size ();
}

/**
 *
 * this function return length of string
 *
 * @param index - index of string to return it's length
 *
 * @return
 * {>= 0}  - length of string
 * { -1 }  - error
 *
 */
int ScriptHolder :: length (unsigned int index) const
{
    try
    {
        const char* ptr = lines_.at (index);
        if ( !ptr )
            return -1;
        return strlen (ptr);
    }
    catch ( ::std::out_of_range)
    {
    }
    return -1;
}

/**
 *
 * this function adds given string to the end of scripth
 *
 * @param line  - string to add
 * @param size_ - size of that string
 *
 * @return - success
 *
 */
bool ScriptHolder :: pushBack (const char* line, unsigned int size_)
{/* WTF why it's named size_ with underscore ??!! */
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
    catch (::std::bad_alloc)
    {
        return false;
    }

    try
    {
        lines_.push_back (ptr);
    }
    catch (::std::bad_alloc)
    {
        delete[] ptr;
        return false;
    }

    return true;
}

/**
 *
 * this function inserts string at given index
 *
 * @param line  - string to insert
 * @param size_ - size of the string
 * @param index - index of string when it will be placed
 *
 * @return - success
 *
 */
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
    catch (::std::bad_alloc)
    {
        return false;
    }

    try
    {
        std::vector<char*>::iterator it = lines_.begin ();
        it += index;
        lines_.insert (it, ptr);
    }
    catch (::std::out_of_range)
    {
        delete[] ptr;
        return false;
    }

    return true;

}

/**
 *
 * this function copies string and return pointer to it
 *
 * @param index - index of string to copy
 * @param size  - number of letters to copy from string
 *
 * @return
 * {  >=0  } - pointer to alloced string
 * {nullptr} - error
 *
 */
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
    catch (::std::bad_alloc)
    {
        return nullptr;
    }

    try
    {
        memcpy (ptr, lines_.at (index), size);
    }
    catch (::std::bad_alloc)
    {
        delete[] ptr;
        return nullptr;
    }

    return ptr;

}

/**
 *
 * this function writes string to buffer
 *
 * @param buffer - pointer to buffer to write in
 * @param size   - size of the buffer. (excess will be cut)
 * @param index  - index of string to get
 *
 * @return
 * {>=0} - number of copied letters
 * {-1}  - error
 *
 */
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
    catch (::std::bad_alloc)
    {
        return -1;
    }
    return size;
}

/**
 *
 * this function removes string from script
 *
 * @param index - index of string to remove
 *
 * @return - success
 *
 */
bool ScriptHolder :: remove  (unsigned int index)
{
    if ( index > lines_.size () )
        return false;
    try
    {
        std::vector<char*>::iterator it = lines_.begin () + index;
        if ( lines_.at (i) )
            delete[] lines_.at (i);
        lines_.erase (it);
    }
    catch (::std::out_of_range)
    {
        return false;
    }
    return true;
}

/**
 *
 * this function replaces one string by another in script
 *
 * @param line   - replacement string
 * @param length - size of replacement string
 * @param index  - index of string to replace
 *
 * @return - success
 *
 */
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
    catch (::std::bad_alloc)
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
    catch (::std::out_of_range)
    {
        delete[] ptr;
        return false;
    }

    return true;
}

/**
 *
 * destructor
 *
 */
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
        catch (::std::bad_alloc)
        {
        }
    }
}



# endif /* H_ENGINE_SCRIPTHOLDERMETHODS */
