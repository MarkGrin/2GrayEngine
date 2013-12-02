# ifndef H_ENGINE_STD_TYPES

# define H_ENGINE_STD_TYPES


class Text : public Object
{

    char* text_;

    public:

    void print ()
    {
        printf ("\nECHO:%s", text_);
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
        if ( this->text_ )
            delete[] this->text_;
        this->text_ = newText;
        //printf ("\nECHO:%s", text_);
        return true;
    }
    bool set (const char* smth)
    {
        unsigned int size = strlen (smth);

        char* newText = nullptr;
        try
        {
            newText = new char[size + 1];
            memcpy (newText, smth, size);
            newText[size] = 0;
        }
        catch (...)
        {
            return false;
        }
        if ( this->text_ )
            delete[] this->text_;
        this->text_ = newText;
        printf ("AAA");
        return true;
    }
    const char* get ()
    {
        return this->text_;
    }
    ~Text ()
    {
        if ( this->text_ )
            delete[] this->text_;
        this->text_ = nullptr;
    }

    Text ()
        :
        Object (12),
        text_ (nullptr)
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
        return nullptr;
    }
    return (Object*) result;
}

class Number
{
    public:
    int number_;
    explicit Number (int num)
        :
    number_ (num)
    {}
};

Object* NUMBERcreateOn ()
{
    Number* result = nullptr;
    try
    {
        result = new Number (0);
    }
    catch (...)
    {
    }
    return (Object*) result;
}

Object* NUMBERcreateOn (const char* text)
{
    Number* result = nullptr;
    try
    {
        result = new Number (atoi (text));
    }
    catch (...)
    {
    }
    return (Object*) result;
}


typeAttributes TEXTattributes   = {12, sizeof (Text)  ,
                                   "Text",  TEXTcreateOn, nullptr};
typeAttributes NUMBERattributes = {14, sizeof (Number),
                                   "Number",NUMBERcreateOn, nullptr};

# endif /* H_ENGINE_STD_TYPES */
