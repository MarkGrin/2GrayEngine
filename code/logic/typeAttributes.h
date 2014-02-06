# ifndef H_LOGIC_TYPEATTRIBUTES

# define H_LOGIC_TYPEATTRIBUTES


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

    bool verify () const;

    TypeAttributes (int typeCode, const char* name,
                    createFunc*, createOnFunc*);
    TypeAttributes (TypeAttributes&);

    int typeCode     () const;
    int version      () const;
    const char* name () const;
    Object* create   () const;
    Object* createOn (const char*) const;
    createFunc*   createPtr   () const;
    createOnFunc* createOnPtr () const;

    ~TypeAttributes ();

};



# endif /* H_LOGIC_TYPEATTRIBUTES */
