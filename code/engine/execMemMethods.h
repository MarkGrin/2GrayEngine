# ifndef H_ENGINE_EXECMEMMETHODS

# define H_ENGINE_EXECMEMMETHODS


/**
 *
 * empty constructor
 *
 */
ExecMem :: ExecMem ()
{
}

/**
 *
 * this function checks if ExecMem class is ok
 *
 * @return
 * {true}  - ok
 * {false} - broken
 *
 */
bool ExecMem :: verify () const
{
    if ( !this )
        return false;
    return true;
}

/**
 *
 * this function returns size of memory in ExecMem in bytes
 *
 * @return
 * {true}  - ok
 * {false} - broken
 *
 */
unsigned int ExecMem :: size () const
{
    if ( !verify () )
        return false;
    return mem_.size ();
}

/*
 *
 * this function adds to the end of memory another memory.
 *
 * @param data - data to add to the end
 * @param size - size of data to add
 *
 * @return - succes
 *
 */
bool ExecMem :: push_back (const unsigned char* data,
                           unsigned int size/* = 1 */)
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("bad object");
        return false;
    }
    if ( !data )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }

    for (unsigned int i = 0; i < size; i++)
    {
        try
        {
            mem_.push_back (data[i]);
        }
        catch (::std::bad_alloc)
        {
            OUTPUT_INTERNAL ("exec mem can't alloc %d step", i);
            return false;
        }
    }
    return true;
}

/**
 *
 * this function copies memory from ExecMem to buffer
 *
 * @param indexFrom - index of the first memory piece to copied.
 * @param to        - buffer to be filled with data from ExecMem
 * @param size      - size of memory to be copied
 *
 * @return success
 *
 */
bool ExecMem :: memcpy    (unsigned int indexFrom, unsigned char* to,
                    unsigned int size) const
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("bad object");
        return false;
    }
    if ( indexFrom + size > mem_.size () )
    {
        OUTPUT_INTERNAL ("asked too much, actual size:%d, asked:%d",
                         mem_.size (), indexFrom + size);
        return false;
    }
    if ( !to )
    {
        OUTPUT_INTERNAL ("bad argument");
        return false;
    }
    unsigned int forbidenIndex = indexFrom + size;
    unsigned int src = indexFrom;
    for (unsigned int dst = 0; dst < size; dst++)
    {
        try
        {
            to[dst] = mem_.at (src);
        }
        catch (::std::out_of_range)
        {
            OUTPUT_INTERNAL ("cant access %d, size:%d", src, mem_.size ());
            return false;
        }
        src++;
    }
    return true;
}

/**
 *
 * this function get byte by it's index
 *
 * @param index - index of byte, that you want to get
 *
 * @return
 * byte that was stored by this index
 *
 */
unsigned char ExecMem :: get (unsigned int index) const
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("bad object");
        return CMD::BAD;
    }
    if ( index >= mem_.size () )
    {
        OUTPUT_INTERNAL ("bad parametr:%d size:%d", index, mem_.size ());
        return CMD::BAD;
    }
    return mem_.at (index);
}

/*
 *
 * undocumented, evil laugh
 *
 */
void ExecMem :: dump (const char* fileName) const
{
    if ( !verify () )
        return ;
    FILE* file = fopen (fileName, "w");
    if ( !file )
        return;
    for (unsigned int i = 0; i < mem_.size (); i++)
    {
        int input = mem_.at(i);
        fprintf (file, "[%3d]:{%X}\n", i, input);
    }
    fclose (file);
}

/**
 *
 * Blank destructor
 *
 */
ExecMem :: ~ExecMem()
{
}



# endif /* H_ENGINE_EXECMEMMETHODS */
