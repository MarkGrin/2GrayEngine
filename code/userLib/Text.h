# ifndef H_USERLIB_TEXT

# define H_USERLIB_TEXT


/**
 *
 * this class is representing a text string
 *
 */
class Text : public logic::Object
{

    char* text_;

    public:

    void print ();

    bool readFromQuotes (const char* text);
    bool set            (const char* smth);

    const char* get ();

    ~Text ();
    Text  ();

};


logic::Object* TEXTcreateOn (const char*);
logic::Object* TEXTcreate   ();

logic::TypeAttributes TEXTattributes (12 , "Text",  TEXTcreate, TEXTcreateOn);


# endif /* H_USERLIB_TEXT */
