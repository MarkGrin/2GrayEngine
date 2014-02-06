# ifndef H_LOGIC_OBJECT

# define H_LOGIC_OBJECT


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

    bool is (const char* name) const;
    bool setName (const char* name);

    int typeCode () const;

};



# endif /* H_LOGIC_OBJECT */
