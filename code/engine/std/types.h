# ifndef H_ENGINE_STD_TYPES

# define H_ENGINE_STD_TYPES


class Text : public Object
{

    char* text_;

    public:

    void print ()
    {
        if ( !text_ )
            printf ("\nBLANK_ECHO!");
        else
            printf ("\nECHO:%s", text_);

        return;
    }


    bool readFromQuotes (const char* text)
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
    bool set (const char* smth)
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
    const char* get ()
    {
        OUTPUT_DEBUG ("Getting:%s", text_);
        return text_;
    }
    ~Text ()
    {
        if ( this->text_ )
            delete[] this->text_;
        this->text_ = nullptr;
    }

    Text ()
        :
        Object (12),
        text_ (nullptr)
    {
	    OUTPUT_DEBUG ("TEXT CREATED");
    }

};

Object* TEXTcreateOn ()
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
    return (Object*) result;
}

Object* TEXTcreateOn (const char* text)
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
    return (Object*) result;
}

class Number
{
    public:
    int number_;
    explicit Number (int num)
        :
    number_ (num)
    {}
};

Object* NUMBERcreateOn ()
{
    Number* result = nullptr;
    try
    {
        result = new Number (0);
    }
    catch (::std::bad_alloc)
    {
    }
    return (Object*) result;
}

Object* NUMBERcreateOn (const char* text)
{
    Number* result = nullptr;
    try
    {
        result = new Number (atoi (text));
    }
    catch (::std::bad_alloc)
    {
    }
    return (Object*) result;
}


class Socket : public Object
{
    grNetwork::Server server;
    grNetwork::Client client;

    public:

    Socket ()
        :
        Object (777)
    {
        client.setPort (97621);
        client.setIP ("127.0.0.1");
        server.setPort (97621);
        server.setIP (nullptr);
	OUTPUT_DEBUG ("SOCKET CREATED");
    }
    void send (const char* buff, int size)
    {
	if ( !server.start () )
		printf ("START FAILURE");
    OUTPUT_DEBUG ("LISTENING");
        if ( !server.listen () )
		printf ("LISTEN FAILURE:%d %d", server.getLastError ().lib (),
				                server.getLastError ().local ());
    OUTPUT_DEBUG ("SENDING");
        if ( !server.send (buff, size) )
		printf ("SEND FAILURE");
    OUTPUT_DEBUG ("SENDED");
    }
    void receive (Text* txt)
    {
        char array[256] = {};
	     if ( !client.start () )
		printf ("START FAILURE");
        OUTPUT_DEBUG ("Listen started");
        if ( !client.connect () )
		printf ("LISTEN FAILURE:%d %d", client.getLastError ().lib (),
				                client.getLastError ().local ());
        OUTPUT_DEBUG ("Listen complete");
        if ( !client.receive (array, 256) )
		printf ("SEND FAILURE");
        txt->set (array);
    }


};


Object* SOCKETcreateOn ()
{
    Socket* result = nullptr;
    try
    {
        result = new Socket ();
    }
    catch (::std::bad_alloc)
    {
    }
    return (Object*) result;
}

Object* SOCKETcreateOn (const char*)
{
    Socket* result = nullptr;
    try
    {
        result = new Socket ();
    }
    catch (::std::bad_alloc)
    {
    }
    return (Object*) result;
}


typeAttributes TEXTattributes   = {12, sizeof (Text)  ,
                                   "Text",  TEXTcreateOn, nullptr};
typeAttributes SOCKETattributes = {777, sizeof (Socket),
                                   "Socket",SOCKETcreateOn, SOCKETcreateOn};
typeAttributes NUMBERattributes = {14, sizeof (Number),
                                   "Number",NUMBERcreateOn, nullptr};


# endif /* H_ENGINE_STD_TYPES */
