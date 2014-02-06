# ifndef H_ENGINE_LIBINFO

# define H_ENGINE_LIBINFO


namespace LibInfoSize
{

const int MAX_NAME = 32;

};

class LibInfo
{

    LibInfo (LibInfo&);
    LibInfo& operator = (LibInfo&);

    
    char name_[LibInfoSize::MAX_NAME + 1];

    HMODULE*   handle_;
   
    public:

    LibInfo (const char* name, HMODULE* handle);

    const char* name () const;

    ~LibInfo ();

};



# endif /* H_ENGINE_LIBINFO */
