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

    virtual functionAttributes attributes () const
    {
        functionAttributes attr = {};
        attr.size = sizeof (functionAttributes);
        attr.version = 2;
        attr.code = 5;

        attr.argnum = 0;
        attr.args = nullptr;

        memcpy (attr.name, "helloWorld", strlen ("helloWorld") + 1);

        return attr;
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

    virtual functionAttributes attributes () const
    {
        functionAttributes attr = {};
       attr.size = sizeof (functionAttributes);
        attr.version = 2;
        attr.code = 7;

        attr.argnum = 1;
        attr.args = new int[1];
        attr.args[0] = 12;

        memcpy (attr.name, "echo", strlen ("echo") + 1);

        return attr;
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

    virtual functionAttributes attributes () const
    {
        functionAttributes attr = {};
        attr.size = sizeof (functionAttributes);
        attr.version = 2;
        attr.code = 505;

        attr.argnum = 1;
        attr.args = new int[1];
        attr.args[0] = 12;

        memcpy (attr.name, "TextUserInput", strlen ("TextUserInput") + 1);

        return attr;
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

    virtual functionAttributes attributes () const
    {
        functionAttributes attr = {};
        attr.size = sizeof (functionAttributes);
        attr.version = 2;
        attr.code = 1012;

        attr.argnum = 2;
        attr.args = new int[2];
        attr.args[0] = 777;
        attr.args[1] = 12;

        memcpy (attr.name, "Send", strlen ("Send") + 1);

        return attr;
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

    virtual functionAttributes attributes () const
    {
        functionAttributes attr = {};
        attr.size = sizeof (functionAttributes);
        attr.version = 2;
        attr.code = 1015;

        attr.argnum = 2;
        attr.args = new int[2];
        attr.args[0] = 777;
        attr.args[1] = 12;

        memcpy (attr.name, "Receive", strlen ("Receive") + 1);

        return attr;
    }
};

Receive RECEIVE;


# endif /* H_ENGINE_STD_FUNCTIONS */
