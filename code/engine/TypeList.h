# ifndef H_ENGINE_TYPELIST

# define H_ENGINE_TYPELIST


class TypeList
{
    std::map<int, typeAttributes> list_;

    public:

    bool add (typeAttributes* type, int typeCode);

    Object* create (int typeCode);
    Object* create (int typeCode, const char* what);

    unsigned int size ();
    int find (const char* what);
};



# endif /* H_DATABASE_TYPELIST */
