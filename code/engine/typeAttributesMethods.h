# ifndef H_ENGINE_TYPEATTRIBUTESMETHODS

# define H_ENGINE_TYPEATTRIBUTESMETHODS


/**
 *
 * This function verifies if TypeAttributes class is ok
 *
 * @return
 * {true} - ok
 * {false} - broken
 *
 */
bool TypeAttributes :: verify () const
{
    if ( !this )
        return false;
    if ( typeCode_ == 0 )
        return false;
    if ( !name_ )
        return false;
    if ( !create_ )
        return false;
    if ( !createOn_ )
        return false;
    return true;
}

/**
 *
 * The only constructor.
 *
 * @param typeCode - type code of this type
 * @param name     - name of this type
 * @param create   - function that creates single object of this type
 * @param createOn - function that creates single object of this type with
 *                   argument
 *
 */
TypeAttributes :: TypeAttributes (int typeCode, const char* name,
                                  createFunc* create, createOnFunc* createOn)
    :
    typeCode_ (typeCode),
    version_  (ENGINE_VERSION),
    name_     (nullptr),
    create_   (create),
    createOn_ (createOn)
{
    if ( !name )
    {
        name_ = nullptr;
        return ;
    }
    unsigned int size = strlen (name) + 1;
    try
    {
        name_ = new char[size];
        memcpy (name_, name, size);
        name_[size - 1] = 0;
    }
    catch (::std::bad_alloc)
    {
        name_ = nullptr;
    }
}

/**
 *
 * copy constructor of TypeAttributes class
 *
 * @param cpy - class to make copy of
 *
 */
TypeAttributes :: TypeAttributes (TypeAttributes& cpy)
    :
    typeCode_ (cpy.typeCode()),
    version_  (ENGINE_VERSION),
    name_     (nullptr),
    create_   (cpy.createPtr()),
    createOn_ (cpy.createOnPtr ())
{
    if ( !cpy.name() )
    {
        name_ = nullptr;
        return ;
    }
    unsigned int size = strlen (cpy.name()) + 1;
    try
    {
        name_ = new char[size];
        memcpy (name_, cpy.name(), size);
        name_[size - 1] = 0;
    }
    catch (::std::bad_alloc)
    {
        name_ = nullptr;
    }
}


/**
 *
 * getter of typeCode
 *
 * @return typeCode
 *
 */
int         TypeAttributes :: typeCode () const
{
    return typeCode_;
}

/**
 *
 * getter of version
 *
 * @return version
 *
 */
int         TypeAttributes :: version  () const
{
    return version_;
}

/**
 *
 * getter of name
 *
 * @return name of this type
 *
 */
const char* TypeAttributes :: name     () const
{
    return name_;
}

/**
 *
 * creates object with creare function 
 *
 * @return
 * {nullptr} - error
 * {>0}      - created object
 *
 */
Object*     TypeAttributes :: create   () const
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("broken object");
        return nullptr;
    }
    return create_ ();
}

/**
 *
 * creates object with createOn function with given arg 
 *
 * @param data - data that will be given to createOn function
 *
 * @return
 * {nullptr} - error
 * {>0}      - created object
 *
 */
Object*     TypeAttributes :: createOn (const char* data) const
{
    if ( !verify () )
    {
        OUTPUT_INTERNAL ("broken object");
        return nullptr;
    }
    return createOn_ (data);
}

/**
 *
 * getter of createPtr
 *
 * @return pointer to create function
 *
 */

createFunc* TypeAttributes :: createPtr () const
{
    return create_;
}

/**
 *
 * getter of createOnPtr
 *
 * @return pointer to createOn function
 *
 */
createOnFunc* TypeAttributes :: createOnPtr () const
{
    return createOn_;
}

TypeAttributes :: ~TypeAttributes ()
{
    if ( name_ )
        delete[] name_;

    /* My poison is null */
    name_     = nullptr;
    create_   = nullptr;
    createOn_ = nullptr;
    typeCode_ = 0;
}


# endif /* H_ENGINE_TYPEATTRIBUTESMETHODS */
