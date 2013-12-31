# ifndef H_ENGINE_STD_FUNCTIONS

# define H_ENGINE_STD_FUNCTIONS


class helloWorld : public Function
{
    public:

    virtual bool payLoadFunction ()
    {
        printf ("\n\nHELLO WORLD SUCCESS\n\n");
        return true;
    }

    virtual FunctionAttributes* attributes () const
    {
        try
        {
            return new FunctionAttributes (5,"HelloWorld");
        }
        catch (::std::bad_alloc)
        {
            OUTPUT_INTERNAL ("cant alloc attributes");
            return nullptr;
        }
    }
};

helloWorld HELLO_WORLD;


class echo : public Function
{
    public:

    virtual bool payLoadFunction ()
    {
        Text* text = (Text*) this->popArg ();
        if ( text )
            text->print ();
        else
            return false;
        return true;
    }

    virtual FunctionAttributes* attributes () const
    {
        try
        {
            FunctionAttributes* attr = new FunctionAttributes (7, "echo");
            attr->pushArg (12);
            return attr;
        }
        catch (::std::bad_alloc)
        {
            OUTPUT_INTERNAL ("cant alloc attributes");
            return nullptr;
        }
        return nullptr;
    }
};

echo ECHO;

class TextUserInput : public Function
{
    public:

    virtual bool payLoadFunction ()
    {
        OUTPUT_DEBUG ("PTR_SOCKET_USE:");
        Text* text = (Text*) this->popArg ();
        if ( text )
        {
            char buffer[256] = {};
            printf ("\nINPUT:");
            scanf ("%s", buffer);
            text->set (buffer);
            return true;
        }
        return false;
    }

    virtual FunctionAttributes* attributes () const
    {
        try
        {
            FunctionAttributes* attr = nullptr;
            attr = new FunctionAttributes (505,"TextUserInput");
            attr->pushArg (12);
            return attr;
        }
        catch (::std::bad_alloc)
        {
            OUTPUT_INTERNAL ("cant alloc attributes");
            return nullptr;
        }
        return nullptr;
    }
};

TextUserInput TEXTUSERINPUT;

class Send : public Function
{
    public:

    virtual bool payLoadFunction ()
    {
        OUTPUT_DEBUG ("PTR_SOCKET_USE:%p", socket);
        Text* text = (Text*) this->popArg ();
        Socket* socket = (Socket*) this->popArg ();
        OUTPUT_DEBUG ("PTR_SOCKET_USE:%p", socket);
        OUTPUT_DEBUG ("PTR__TEXT_USE:%p", text);
        const char* textbuff = text->get ();
        OUTPUT_DEBUG ("TEXT_USE:%s", textbuff);

        OUTPUT_DEBUG ("Reached, calling send");
        socket->send (textbuff, strlen (textbuff)+1);
        return false;
    }

    virtual FunctionAttributes* attributes () const
    {
        try
        {
            FunctionAttributes* attr = new FunctionAttributes (1012,"Send");
            attr->pushArg (777);
            attr->pushArg (12);
            return attr;
        }
        catch (::std::bad_alloc)
        {
            OUTPUT_INTERNAL ("cant alloc attributes");
            return nullptr;
        }
        return nullptr;
    }
};

Send SEND;


class Receive : public Function
{
    public:

    virtual bool payLoadFunction ()
    {
        Text* text = (Text*) this->popArg ();
        Socket* socket = (Socket*) this->popArg ();
        socket->receive (text);
        return false;
    }

    virtual FunctionAttributes* attributes () const
    {
        try
        {
            FunctionAttributes* attr = new FunctionAttributes (1015,"Receive");
            attr->pushArg (777);
            attr->pushArg (12);
            return attr;
        }
        catch (...)
        {
            OUTPUT_INTERNAL ("cant alloc attributes");
            return nullptr;
        }
        return nullptr;
    }
};

Receive RECEIVE;


# endif /* H_ENGINE_STD_FUNCTIONS */
