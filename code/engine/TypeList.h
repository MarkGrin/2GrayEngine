# ifndef H_ENGINE_TYPELIST

# define H_ENGINE_TYPELIST


/**
 *
 * this is typeList class. It contain typeAttribute structures and it 
 * povides easy acces to them by code or name.
 *
 */
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
