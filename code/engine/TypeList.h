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
    std::map<int, logic::TypeAttributes*> list_;

    public:

    bool verify () const;

    bool add (logic::TypeAttributes* type, int typeCode);

    logic::Object* create (int typeCode);
    logic::Object* create (int typeCode, const char* what);

    unsigned int size () const;
    int find (const char* what);
};



# endif /* H_DATABASE_TYPELIST */
