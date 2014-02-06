# ifndef H_ENGINE_LIBHOLDER

# define H_ENGINE_LIBHOLDER


class LibHolder
{

    LibHolder (LibHolder&);
    LibHolder& operator = (LibHolder&);

    std::vector<LibInfo*> libs_;

    public:

    bool verify ();

    LibHolder ();

    bool add   (environment* en, const char* name);
    bool clear ();

    ~LibHolder ();

};



# endif /* H_ENGINE_LIBHOLDER */
