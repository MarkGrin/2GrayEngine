# ifndef H_ENGINE_FUNCTION

# define H_ENGINE_FUNCTION


/**
 *
 * this is Function class. It is base abstract class that represent user
 * function in engine. How to inherit and use it read in docs.
 *
 * To call it you must read what arguments it need by calling
 * attrutes function. Then you must push all the arguments.
 * Then call payLoadFunction that is overloaded by user. And user will pop
 * all arguments you pushed.
 *
 */
class Function
{
    Function  (Function&);
    Function& operator = (Function&);

    ::std::stack<Object*> args_;

    protected:

    Object* popArg  ();

    public:

    bool verify () const;

    Function ();

    bool pushArg (Object*);

    virtual bool payLoadFunction () = 0; 

    virtual functionAttributes attributes () const = 0;

    bool execute ();

};


# endif /* H_ENGINE_FUNCTION */
