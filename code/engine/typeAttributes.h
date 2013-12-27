# ifndef H_ENGINE_TYPEATTRIBUTES

# define H_ENGINE_TYPEATTRIBUTES


typedef Object* createFunc ();
typedef Object* createOnFunc (const char*);

/**
 *
 * this is typeAttributes class. It contains attribtues of type(Captain
 * obvious)
 *
 */
class TypeAttributes
{
    TypeAttributes& operator = (TypeAttributes&);
    TypeAttributes ();

    protected:

    int typeCode_;
    int version_;
    char* name_;
    Object* (*create_)();
    Object* (*createOn_)(const char*);

    public:

    bool verify ();

    TypeAttributes (int typeCode, const char* name,
                    createFunc*, createOnFunc*);
    TypeAttributes (TypeAttributes&);

    int typeCode     ();
    int version      ();
    const char* name ();
    Object* create   ();
    Object* createOn (const char*);
    createFunc*   createPtr   ();
    createOnFunc* createOnPtr ();

};



# endif /* H_ENGINE_TYPEATTRIBUTES */
