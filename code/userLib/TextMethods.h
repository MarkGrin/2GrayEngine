# ifndef H_USERLIB_TEXTMETHODS

# define H_USERLIB_TEXTMETHODS


/**
 *
 * this function prints out what text contains
 *
 */
void Text :: print ()
{
    if ( !text_ )
        printf ("\nBLANK_ECHO!");
    else
        printf ("\nECHO:%s", text_);

    return;
}

/**
 *
 * this function sets Text class to contain text between quotes
 *
 * @param text - text with quotes outsied
 *
 * @return success
 *
 */
bool Text :: readFromQuotes (const char* text)
{
    char* end = strchr (text + 1, '"');
    if ( !end )
        return false;
    unsigned int size = end - text - 1;


    char* newText = nullptr;
    try
    {
        newText = new char[size + 1];
        memcpy (newText, text + 1, size);
        newText[size] = 0;
    }
    catch (::std::bad_alloc)
    {
        return false;
    }
    if ( this->text_ )
        delete[] this->text_;
    this->text_ = newText;
    return true;
}

/**
 *
 * this function makes Text class to contain string
 *
 * @param smth - string to contain
 *
 * @return - success
 *
 */
bool Text :: set (const char* smth)
{
    unsigned int size = strlen (smth);

    char* newText = nullptr;
    try
    {
        newText = new char[size + 1];
        memcpy (newText, smth, size);
        newText[size] = 0;
    }
    catch (::std::bad_alloc)
    {
        return false;
    }
    if ( this->text_ )
        delete[] this->text_;
    this->text_ = newText;
    printf ("AAA");
    printf ("\nNEW:%s", text_);
    return true;
}


/**
 *
 * this function return what Text class contain
 *
 * @return
 * {nullptr} - error
 * {>=0}     - string that is contained by Text class
 *
 */
const char* Text :: get ()
{
    OUTPUT_DEBUG ("Getting:%s", text_);
    return text_;
}


/**
 *
 * destructor
 *
 */
Text :: ~Text ()
{
    if ( this->text_ )
        delete[] this->text_;
    this->text_ = nullptr;
}

/**
 *
 * constructor
 *
 */
Text :: Text ()
    :
    Object (12),
    text_ (nullptr)
{
}

/**
 *
 * this function creates TEXT class element
 *
 */
logic::Object* TEXTcreate ()
{
    Text* result = nullptr;
    try
    {
        result = new Text ();
	    char name[256] = {};
	    sprintf (name,"\"%p\"", result);
        result->readFromQuotes (name);
    }
    catch (::std::bad_alloc)
    {
    }
    return (logic::Object*) result;
}

/**
 *
 * function creates Text class from text string
 *
 * @param text - text string
 *
 * @return
 * {nullptr} - error
 * {>=0}     - pointer to newly created Text class
 *
 */
logic::Object* TEXTcreateOn (const char* text)
{
    Text* result = nullptr;
    try
    {
        result = new Text ();
        result->readFromQuotes (text);
    }
    catch (::std::bad_alloc)
    {
        return nullptr;
    }
    return (logic::Object*) result;
}


# endif /* H_USERLIB_TEXTMETHODS */
