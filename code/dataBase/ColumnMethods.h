# ifndef H_DATABASE_COLUMNMETHODS

# define H_DATABASE_COLUMNMETHODS


bool Column :: ok ()
{
    START_FUNCTION
    if ( !parentTable_ )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Null parent table given");
        return false;
    }
    if ( type_code_ == 0 )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Null code");
        return false;
    }
    if ( !parentTable_->ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Not ok table given");
        return false;
    }
    if ( !parentTable_->registry_->sizeOf (type_code_) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:parent table given not ok");
        return false;
    }
    if ( Column::height() != parentTable_->height() )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Column sized:%d but have to be:%d",
                      elements_.size (), parentTable_->height ());
        return false;
    }
    return true;
}
Column :: Column (unsigned int size, int code, Table* parentTable)
    :
    parentTable_ (parentTable),
    type_code_ (code)
{
    START_FUNCTION
    try
    {
        elements_.resize (size, nullptr);
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Column coded:%d parentTable:%p cant expand on:%d",
                      type_code_, parentTable, size);
        parentTable = nullptr;
        type_code_  = 0;
        elements_.clear ();
    }
}

Column :: ~Column ()
{
    START_FUNCTION
    int size = elements_.size ();
    for (int i = 0; i < size; i++)
    {
        if ( elements_.at (i) )
            delete elements_.at (i);
    }
    parentTable_ = nullptr;
    elements_.clear ();
    type_code_ = 0;
}

unsigned int Column :: height ()
{
    START_FUNCTION
    return elements_.size ();
}

unsigned int Column :: size ()
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Column not ok");
        return 0;
    }
    return parentTable_->registry_->sizeOf (type_code_);
}

int Column :: code ()
{
    START_FUNCTION
    return type_code_;
}

bool Column :: put (unsigned int index, Element* element)
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Column not ok");
        return nullptr;
    }
    try
    {
        elements_.at (index) = element;
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant access:%d", index);
        return false;
    }
    return true;
}

bool Column :: delCell (unsigned int index)
{
    START_FUNCTION;
    try
    {
        std::vector<Element*>::iterator toDelete;
        toDelete = elements_.begin () + index;
        elements_.erase (toDelete);
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant delete %d cell", index);
        return false;
    }
    return true;
}

Element* Column :: get (unsigned int index)
{
    START_FUNCTION
    if ( !ok () )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Column not ok");
        return nullptr;
    }
    Element* result = nullptr;
    try
    {
        result = elements_.at (index);
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant access:%d", index);
        return nullptr;
    }
    return result;
}

bool Column :: expand ()
{
    START_FUNCTION
    try
    {
        elements_.push_back (nullptr);
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant push back");
        return false;
    }
    return true;
}

# endif /* H_DATABASE_COLUMNMETHODS */
