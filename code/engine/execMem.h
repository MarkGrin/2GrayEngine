# ifndef H_ENGINE_EXECMEM

# define H_ENGINE_EXECMEM



/**
 *
 * this is ExecMem class. It is interface that helps to work with
 * executable memory
 *
 */
class ExecMem
{
    ::std::vector<unsigned char> mem_;

    ExecMem (ExecMem&);
    ExecMem& operator = (ExecMem&);

    public:

    bool verify () const;

    ExecMem ();

    unsigned int size () const;

    bool push_back (const unsigned char* data, unsigned int size = 1);
    bool memcpy    (unsigned int indexFrom, unsigned char* to,
                    unsigned int size) const;
    unsigned char get (unsigned int index) const;

    void dump (const char* fileName) const;

    ~ExecMem ();
};



# endif /* H_ENGINE_EXECMEM */
