# ifndef H_DATABASE_ELEMENT

# define H_DATABASE_ELEMENT

struct Element
{
    int type_code_;
    Element (int type_code, int size);
    virtual bool get (char* data) = 0;

    private:

    Element ();
};

Element :: Element (int type_code, int size)
    :
    type_code_ (type_code)
{}

# endif /* H_DATABASE_ELEMENT */
