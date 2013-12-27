# ifndef H_DATABASE_TYPEREGISTRY

# define H_DATABASE_TYPEREGISTRY


struct type_
{
    int type_code_;
    int size;
    Element* (*create)();
    Element* (*createOn)(char*);
};

class TypeRegistry
{
    std::map<int, type_> registry;

    public:

    bool add (type_* type, int type_code);

    int sizeOf (int type_code);

    Element* create (int type_code);
    Element* create (int type_code, char* what);
};



# endif /* H_DATABASE_TYPEREGISTRY */
