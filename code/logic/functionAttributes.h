# ifndef H_LOGIC_FUNCTIONATTRIBUTES

# define H_LOGIC_FUNCTIONATTRIBUTES


/**
 *
 * this is functionAttributes structure that contain information about
 * function.
 *
 */
class FunctionAttributes
{

    FunctionAttributes& operator = (FunctionAttributes&);
    FunctionAttributes ();

    protected:

    unsigned int version_;
    int code_;
    char* name_;

    ::std::vector<int> args_;

    public:

    bool verify () const;

    FunctionAttributes (int code, const char* name);
    FunctionAttributes (FunctionAttributes&);

    int code         () const;
    int version      () const;
    const char* name () const;

    int argnum ()                            const;
    int arg             (unsigned int index) const;

    bool pushArg (int code);

    ~FunctionAttributes ();
};

# endif /* H_LOGIC_FUNCTIONATTRIBUTES */
