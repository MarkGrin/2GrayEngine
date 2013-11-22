# ifndef H_ENGINE_OBJECT

# define H_ENGINE_OBJECT


class Object
{

    protected:

    int typeCode_;
    char name_[32 + 1];

    private:

    Object ();

    public:

    explicit Object (int typeCode);

    bool is (const char* name);
    bool setName (const char* name);

    int typeCode ();

};



# endif /* H_ENGINE_OBJECT */
