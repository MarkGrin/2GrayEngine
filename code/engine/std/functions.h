# ifndef H_ENGINE_STD_FUNCTIONS

# define H_ENGINE_STD_FUNCTIONS


class helloWorld : public Function
{
    public:

    bool execute ()
    {
        printf ("\n\nHELLO WORLD SUCCESS\n\n");
    }

    functionAttributes attributes ()
    {
        functionAttributes attr = {};
        attr.size = sizeof (functionAttributes);
        attr.version = 1;
        attr.code = 5;

        memcpy (attr.name, "helloWorld", strlen ("helloWorld") + 1);

        return attr;
    }
};

helloWorld HELLO_WORLD;

# endif /* H_ENGINE_STD_FUNCTIONS */
