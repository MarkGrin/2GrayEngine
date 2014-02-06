# ifndef H_ENGINE_STD_FUNCTIONS

# define H_ENGINE_STD_FUNCTIONS


class echo : public logic::Function
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

    virtual logic::FunctionAttributes* attributes () const
    {
        try
        {
            logic::FunctionAttributes* attr = new logic::FunctionAttributes (7, "echo");
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

class TextUserInput : public logic::Function
{
    public:

    virtual bool payLoadFunction ()
    {
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

    virtual logic::FunctionAttributes* attributes () const
    {
        try
        {
            logic::FunctionAttributes* attr = nullptr;
            attr = new logic::FunctionAttributes (505,"TextUserInput");
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

class Send : public logic::Function
{
    public:

    virtual bool payLoadFunction ()
    {
        Text* num  = (Text*) this->popArg ();
        Text* text = (Text*) this->popArg ();
        Socket* socket = (Socket*) this->popArg ();

        int size = atoi (num->get());
        const char* textbuff = text->get ();

        if ( size > strlen (textbuff) )
            size = strlen (textbuff);

        socket->send (textbuff, size);
        return false;
    }

    virtual logic::FunctionAttributes* attributes () const
    {
        try
        {
            logic::FunctionAttributes* attr = new logic::FunctionAttributes (1012,"Send");
            attr->pushArg (777);
            attr->pushArg (12);
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


class Receive : public logic::Function
{
    public:

    virtual bool payLoadFunction ()
    {
        Text* num = (Text*) this->popArg ();
        Text* text = (Text*) this->popArg ();
        char buffer[256] = "";
        int size = atoi (num->get());
        Socket* socket = (Socket*) this->popArg ();
        socket->receive (buffer, size);
        text->set (buffer);
        return false;
    }

    virtual logic::FunctionAttributes* attributes () const
    {
        try
        {
            logic::FunctionAttributes* attr = new logic::FunctionAttributes (1015,"Receive");
            attr->pushArg (777);
            attr->pushArg (12);
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


class Connect : public logic::Function
{
    public:

    virtual bool payLoadFunction ()
    {
        Socket* socket = (Socket*) this->popArg ();
        socket->connect ();
        return false;
    }

    virtual logic::FunctionAttributes* attributes () const
    {
        try
        {
            logic::FunctionAttributes* attr = new logic::FunctionAttributes (1016,"Connect");
            attr->pushArg (777);
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

Connect CONNECT;

class Listen : public logic::Function
{
    public:

    virtual bool payLoadFunction ()
    {
        Socket* socket = (Socket*) this->popArg ();
        socket->listen ();
        return false;
    }

    virtual logic::FunctionAttributes* attributes () const
    {
        try
        {
            logic::FunctionAttributes* attr = new logic::FunctionAttributes (1017,"Listen");
            attr->pushArg (777);
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

Listen LISTEN;

class SetPort : public logic::Function
{
    public:

    virtual bool payLoadFunction ()
    {
        Text* num  = (Text*) this->popArg ();
        Socket* socket = (Socket*) this->popArg ();

        socket->setPort (num->get());
        return false;
    }

    virtual logic::FunctionAttributes* attributes () const
    {
        try
        {
            logic::FunctionAttributes* attr = new logic::FunctionAttributes (1020,"SetPort");
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

SetPort SETPORT;


class SetIP : public logic::Function
{
    public:

    virtual bool payLoadFunction ()
    {
        Text* ip  = (Text*) this->popArg ();
        Socket* socket = (Socket*) this->popArg ();

        socket->setIP (ip->get());
        return false;
    }

    virtual logic::FunctionAttributes* attributes () const
    {
        try
        {
            logic::FunctionAttributes* attr = new logic::FunctionAttributes (1021,"SetIP");
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

SetIP SETIP;


# endif /* H_ENGINE_STD_FUNCTIONS */
