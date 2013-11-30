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

    virtual functionAttributes attributes ()
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

    virtual functionAttributes attributes ()
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

# endif /* H_ENGINE_STD_FUNCTIONS */
