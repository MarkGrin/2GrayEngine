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

    public:

    bool verify ();

    bool push_back (const unsigned char* data, unsigned int size = 1);
    bool memcpy    (unsigned int indexFrom, unsigned char* to,
                    unsigned int size);
};



# endif /* H_ENGINE_EXECMEM */
