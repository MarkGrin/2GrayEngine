# ifndef H_ENGINE_METHODS

# define H_ENGINE_METHODS


bool loadFile    (const char* fileName, ScriptHolder* scpt);
bool execute     (ScriptHolder* scpt);
bool execute     (const char* file);
bool addStandard (::std::vector<Function*>* functions, TypeList* typeList);
bool parseArgs   (::std::vector<Object*>* args,
                  ::std::vector<Object*>* pool, const char* argumentLine);
bool checkArgs   (functionAttributes* attr, ::std::vector<Object*>* args);

bool loadFile (const char* fileName, ScriptHolder* scpt)
{
    if ( !fileName || !scpt )
        return false;

    FILE* file = fopen (fileName, "r");

    if ( !file )
        return false;

    char line[256] = {};

    for (unsigned int lineCount = 0; !feof (file); lineCount++)
    {
        for (unsigned int letterCount = 0; letterCount <= 80; letterCount++)
        {
            if ( !fread (line + letterCount, 1, 1, file) )
                continue;

            line[letterCount + 1] = 0;

            if ( line[letterCount] == '\n' || feof (file) )
            {
                line[letterCount] = 0;
                scpt->pushBack (line, letterCount);
                break;
            }
        }
        line[0] = 0;
    }

    return true;
}

bool execute  (ScriptHolder* scpt)
{
    ::std::vector<Function*> functions;
    ::std::vector<Object*> pool;
    TypeList typeList;

    addStandard (&functions, &typeList);


    char command[256] = {};
    char buffer[256] = {};
    while ( scpt->lines () )
    {
        memset (command, 0, 256);
        memset (buffer, 0, 256);
        scpt->get (command, 256, 0);

        if ( command[0] == '!' )
        {
            if ( strstr (command+1, "new") == command + 1 )
            {
                Object* obj = nullptr;
                char* pos = strchr (command + 5, ' ');
                if ( !pos )
                    return false;
                int size = pos - command - 5;
                memcpy (buffer, command + 5, size);
                buffer[size] = 0;
                int code = typeList.find (buffer);
                if ( !code )
                    return false;
                int nameSize = strlen (command + 6 + size);
                if ( !nameSize )
                    return false;
                memcpy (buffer, command + 6 + size, nameSize);
                buffer[nameSize] = 0;
                
                for (unsigned int i = 0; i < pool.size (); i++)
                {
                    if ( pool.at (i)->is (buffer) )
                        return false;
                }
                obj = typeList.create (code);
                if ( !obj )
                    return false;
                obj->setName (buffer);
                pool.push_back (obj);
            }
            if ( strstr (command+1, "delete") == command + 1 )
            {
                 for (unsigned int i = 0; i < pool.size (); i++)
                {
                    if ( pool.at (i)->is (buffer) )
                    {
                        ::std::vector<Object*>::iterator it = pool.begin () + i;
                        delete pool.at (i);
                        pool.erase (it);
                    }
                }
            }
        }

        for (unsigned int i = 0; i < functions.size (); i++)
        {
            functionAttributes attribute = functions.at (i)->attributes();
            if ( strstr (command, attribute.name) == command )
            {
                ::std::vector<Object*> args;
                parseArgs (&args, &pool, command + strlen (attribute.name));
                if ( checkArgs (&attribute, &args) )
                {
                    for (unsigned int argIndex = 0;
                         argIndex < attribute.argnum;
                         argIndex++)
                    {
                        functions.at (i)->pushArg (args.at (argIndex));
                    }
                    functions.at (i)->execute ();
                }
            }
        }
        scpt->remove (0);
    }
    return true;
}

bool execute (const char* fileName)
{
    ScriptHolder scpt;
    if ( !loadFile (fileName, &scpt) )
        return false;

    return execute (&scpt);
}

bool addStandard (::std::vector<Function*>* functions, TypeList* typeList)
{
    functions->push_back (&std::ECHO);
    typeList ->add (&std::TEXTattributes, 12);
    typeList ->add (&std::NUMBERattributes, 14);
}

bool parseArgs   (::std::vector<Object*>* args,
                  ::std::vector<Object*>* pool, const char* argumentLine)
{
    try
    {
        for (unsigned int i = 0; argumentLine[i] != '\0'; i++)
        {
            if ( argumentLine[i] == '"' )
            {
                std::Text* obj = (std::Text*)std::TEXTcreateOn ();
                if ( obj )
                {
                    if ( obj->readFromQuotes (argumentLine + i) )
                    {
                        args->push_back ((Object*)obj);
                    }
                    else
                        return false;
                }
                else
                {
                    return false;
                }
                i = argumentLine - strchr (argumentLine + i + 1, '"');
            }
            else
            {
                char* pos = strchr (argumentLine + i, ' ');
                int size = 0;
                if ( !pos )
                    size = strlen (argumentLine + i);
                else
                    size = pos - argumentLine - i;
                char buffer[80] = {};
                memcpy (buffer, argumentLine + i, size);
                buffer[size] = 0;
                for (unsigned int i = 0; i < pool->size (); i++ )
                {
                    if ( pool->at (i)->is (buffer) )
                        args->push_back (pool->at (i));
                }
                i+=size;
            }
        }
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool checkArgs   (functionAttributes* attr, ::std::vector<Object*>* args)
{
    for (unsigned int i = 0; i < attr->argnum; i++)
    {
        try
        {
            if ( attr->args[i] != args->at(i)->typeCode () )
                return false;
        }
        catch (...)
        {
            return false;
        }
    }
    return true;
}

# endif /* H_ENGINE_METHODS */
