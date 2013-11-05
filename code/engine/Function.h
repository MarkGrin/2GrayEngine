# ifndef H_ENGINE_FUNCTION

# define H_ENGINE_FUNCTION


class Function
{
    Function  (Function&);
    Function& operator = (Function&);

    ::std::stack<Object*> args_;

    protected:

    Object* popArg  ();

    public:

    Function ();

    bool pushArg (Object*);

    virtual bool payLoadFunction () = 0; 

    virtual functionAttributes attributes () = 0;

    bool execute ();

};


# endif /* H_ENGINE_FUNCTION */
