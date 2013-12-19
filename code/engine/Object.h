# ifndef H_ENGINE_OBJECT

# define H_ENGINE_OBJECT


/**
 *
 * this is Object class, it's a base and abstract class. It represent an
 * abstract object in engine.
 *
 */
class Object
{

    protected:

    int typeCode_;
    char name_[32 + 1];

    private:

    Object ();

    public:

    bool verify () const;

    explicit Object (int typeCode);

    bool is (const char* name);
    bool setName (const char* name);

    int typeCode ();

};



# endif /* H_ENGINE_OBJECT */
