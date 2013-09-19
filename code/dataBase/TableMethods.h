# ifndef H_DATABASE_TABLEMETHODS

# define H_DATABASE_TABLEMETHODS


Table :: Table (TypeRegistry* registry)
    :
    registry_ (registry)
{
}

Table :: ~Table ()
{
    START_FUNCTION
    int size = columns_.size ();
    for (int i = 0; i < size; i++)
    {
        try
        {
            if ( columns_.at (i) )
            {
                OUTPUT_DEBUG (PLACE, "DEBUG:Deleting [%u]:%p", i, columns_.at(i));
                delete (columns_.at (i));
            }
            columns_.at (i) = nullptr;
        }
        catch (...)
        {
            OUTPUT_DEBUG (PLACE, "ERROR:Access index:%d failure", i);
        }
    }
    columns_.clear ();
}

void Table :: destroy ()
{
    START_FUNCTION
    int size = columns_.size ();
    for (int i = 0; i < size; i++)
    {
        try
        {
            if ( columns_.at (i) )
            {
                OUTPUT_DEBUG (PLACE, "DEBUG:Deleting [%u]:%p", i, columns_.at(i));
                delete (columns_.at (i));
            }
            columns_.at (i) = nullptr;
        }
        catch (...)
        {
            OUTPUT_DEBUG (PLACE, "ERROR:Access index:%d failure", i);
        }
    }
    columns_.clear ();
}

bool Table :: ok () const
{
    START_FUNCTION
    if ( !registry_ )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok. NULL registry");
        return false;
    }

    int size = columns_.size ();
    unsigned int height = 0;
    for (int i = 0; i < size; i++)
    {
        try
        {
            Column* ptr = columns_.at (i);
            if ( !ptr )
            {
                OUTPUT_DEBUG (PLACE, "ERROR:Table not ok. Column index:%d missing", i);
                return false;
            }
            if ( i )
            {
                if ( height != ptr->height () )
                {
                    OUTPUT_DEBUG (PLACE, "ERROR:Table not ok. [%d]height:%d but [%d]height:%d", 
                                  i - 1, height, i, ptr->height ());
                    return false;
                }
            }
            height = ptr->height ();
        }
        catch (...)
        {
            OUTPUT_DEBUG (PLACE, "ERROR:Table not ok Access index:%d failure", i);
            return false;
        }
    }
    return true;
}

bool Table :: empty () const
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table ok object");
        return false;
    }
    if ( height() * columnNumber() )
    {
        return false;
    }
    return true;
}

unsigned int Table :: columnNumber () const
{
    START_FUNCTION
    return columns_.size ();
}

unsigned int Table :: height () const
{
    START_FUNCTION
    if ( columns_.size () )
    {
        if ( columns_.at (0) )
        {
            OUTPUT_DEBUG (PLACE, "DEBUG:HEIGHT:%d", columns_.at (0)->height () );
            return columns_.at (0)->height ();
        }
    }
    return 0;
}

unsigned int Table :: size () const
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok.");
        return 0;
    }

    unsigned int size   = Table::columnNumber ();
    unsigned int height = Table::height ();
    unsigned int result = 0;

    for (unsigned int i = 0; i < size; i++)
    {
        result += columns_.at(i)->size ()*height;
    }
    return result;
}

unsigned int Table :: size (unsigned int index) const
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok.");
        return 0;
    }
    unsigned int result = 0;
    try
    {
        result = columns_.at (index)->size ();
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant access:%d", index);
        return 0;
    }
    return result;
}

int Table :: code (unsigned int index) const
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok");
        return 0;
    }
    int code = 0;
    try
    {
        code = columns_.at (index)->code ();
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant access:%d", index);
        return 0;
    }
    return code;
}
bool Table :: addColumn (int code)
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok.");
        return false;
    }
    Column* ptr = nullptr;
    try
    {
        ptr = new Column (Table::height (), code, this);
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant create new column");
        return false;
    }
    if ( !ptr->ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Creation failure");
        delete ptr;
        return false;
    }
    try
    {
        columns_.push_back (ptr);
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant push back");
        delete ptr;
        return false;
    }
    return true;
}

bool Table :: expand ()
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok");
        return false;
    }
    unsigned int size = columns_.size ();
    for (unsigned int i = 0; i < size; i++)
    {
        if ( !columns_.at(i)->expand () )
        {
            OUTPUT_DEBUG (PLACE, "CRITICAL:Column:%d was not expanded", i);
            return false;
        }
    }
    return true;
}

bool Table :: delColumn (unsigned int index)
{
    START_FUNCTION;
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok");
        return false;
    }
    try
    {
        Column* toDelete = columns_.at (index);
        delete toDelete;
        std::vector<Column*>::iterator del = columns_.begin () + index;
        columns_.erase (del);
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant delete %d column", index);
        return false;
    }
    return true;
}

bool Table :: delLine   (unsigned int index)
{
    START_FUNCTION;
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok");
        return false;
    }
    if ( index >= Table::height () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Too big index");
        return false;
    }
    unsigned int size = columns_.size ();
    for (unsigned int x = 0; x < size; x++)
    {
        try
        {
            columns_.at (x)->delCell (index);
        }
        catch (...)
        {
            OUTPUT_DEBUG (PLACE, "CRITICAL ERROR:Cant delete %d cell in %d column", index, x);
            return false;
        }
    }
}

bool Table :: nullCell (unsigned int x, unsigned int y)
{
    START_FUNCTION;
    Element* nullElement = nullptr;
    if ( Table::put (x, y, nullElement) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:coudnt set null cell - x:%d y:%d", x, y);
        return false;
    }
    return true;
}

bool Table :: put (unsigned int x, unsigned int y, Element* element) const
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok");
        return false;
    }
    if ( !element )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:NULL element ptr given");
        return false;
    }
    if ( element->type_code_ != columns_.at(x)->code () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Wrong type. Need:%d. Have:%d.", element->type_code_, columns_.at(y)->code () );
        return false;
    }
    try
    {
        if (  !( (columns_.at (x))->put(y, element) )  )
        {
            OUTPUT_DEBUG (PLACE, "ERROR:Was unable to place in x:%d y:%d", x, y);
            return false;
        }
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Wanted column:%d but have only:%d", x, columns_.size());
        return false;
    }
    return true;
}

bool Table :: put (unsigned int x, unsigned int y, char* data) const
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok");
        return false;
    }
    if ( !data )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:NULL data ptr given");
        return false;
    }

    int code = Table::getCode (x);
    OUTPUT_DEBUG (PLACE, "DEBUG:Code:%d", code);

    Element* element = registry_->create (code, data);
    if ( !element)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Created null element");
        return false;
    }

    Table::put (x, y, element);

    return true;
}

int Table :: getCode (unsigned int index) const
{
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok.");
        return false;
    }
    try
    {
        Column* ptr = columns_.at (index);
        return ptr->code ();
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:No column:%d", index);
        return 0;
    }
    return 0;
}
Element* Table :: get (unsigned int x, unsigned int y) const
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Table not ok");
        return nullptr;
    }
    Element* result = nullptr;
    try
    {
        result = (columns_.at (x))->get(y);
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Wanted column:%d but have only:%d", x, columns_.size ());
        return nullptr;
    }
    if ( !result )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:x:%d y:%d element returned null", x, y);
        return nullptr;
    }
    return result;
}

# endif /* H_DATABASE_TABLEMETHODS */
