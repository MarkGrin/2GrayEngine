# ifndef H_ENGINE_STD_TYPES

# define H_ENGINE_STD_TYPES


class Text : public Object
{

    char* text;

    public:

    void print ()
    {
        printf ("\nECHO:%s", text);
    }


    bool readFromQuotes (const char* text)
    {
        char* end = strchr (text + 1, '"');
        if ( !end )
            return false;
        unsigned int size = end - text - 1;

        char* newText = nullptr;
        try
        {
            newText = new char[size + 1];
            memcpy (newText, text + 1, size);
            newText[size] = 0;
        }
        catch (...)
        {
            return false;
        }
        this->text = newText; /* FUCK MEMORY LEAKS! */
        return true;
    }

    Text ()
        :
        Object (12)
    {}

};

Object* TEXTcreateOn ()
{
    Text* result = nullptr;
    try
    {
        result = new Text ();
        result->readFromQuotes ("\"DEFAULT\"");
    }
    catch (...)
    {
    }
    return (Object*) result;
}

Object* TEXTcreateOn (const char* text)
{
    Text* result = nullptr;
    try
    {
        result = new Text ();
        result->readFromQuotes (text);
    }
    catch (...)
    {
    }
    return (Object*) result;
}

typeAttributes TEXTattributes = {12, sizeof (Text), "Text", TEXTcreateOn, nullptr};

# endif /* H_ENGINE_STD_TYPES */
