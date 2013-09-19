# ifndef 
//INCLUDE GUARD
# define 


bool Column :: ok ()
{
    START_FUNCTION
    return true;
}
Column :: Column (unsigned int size, int code, Table* parentTable)
{
    START_FUNCTION
}

Column :: ~Column ()
{
    START_FUNCTION
}

unsigned int Column :: height ()
{
    START_FUNCTION
    return elements_.size ();
}

unsigned int Column :: size ()
{
    START_FUNCTION
    return 0;
}

int Column :: code ()
{
    START_FUNCTION
    return type_code_;
}

bool Column :: put (unsigned int index, Element* element)
{
    START_FUNCTION
    return true;
}

bool Column :: put (unsigned int index, char* data)
{
    START_FUNCTION
    return true;
}

Element* Column :: get (unsigned int index)
{
    START_FUNCTION
    return nullptr;
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


# endif/ifndef /
       //INCLUDE_GUARD
