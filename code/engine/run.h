# ifndef H_ENGINE_METHODS

# define H_ENGINE_METHODS


/* General */
bool run         (const char* fileName);
bool loadFile    (const char* fileName, ScriptHolder* scpt);
unsigned char* compile (
               ScriptHolder* scpt,
               ::std::vector<Function*>* functions,
               ::std::vector<Object*>* pool,
               ::std::vector<::std::pair<char*,unsigned int>>* placeInPool,
               TypeList* typeList,
               ::std::vector<unsigned char>* execMem);

bool execute  (unsigned char* data, unsigned int size,
               ::std::vector<Function*>* functions,
               ::std::vector<Object*>* pool,
               ::std::vector<::std::pair<char*,unsigned int>>* placeInPool,
               TypeList* typeList);

/* Compile */
bool addStandard (::std::vector<Function*>* functions, TypeList* typeList);
bool parseArgs   (::std::vector<unsigned char>* execMem,
                  ::std::vector<::std::pair<char*, unsigned int>>* places,
                  Function* fnc,
                  ::std::vector<Object*>* pool,
                  const char* argumentLine);
bool checkArgs   (functionAttributes* attr, ::std::vector<Object*>* args);

/* Misc */
void dump        (char* data, int amount);

bool run (const char* fileName)
{
    try
    {
        ScriptHolder scpt;
        if ( !loadFile (fileName, &scpt) )
            return false;

        ::std::vector<Function*> functions;
        ::std::vector<Object*> pool;
        ::std::vector<::std::pair<char*,unsigned int>> placeInPool;
        TypeList typeList;
        ::std::vector<unsigned char> execMem;

        unsigned char* execRam = compile (&scpt, &functions, &pool,
                                          &placeInPool, &typeList,
                                          &execMem);
        if ( !execRam )
            return false;

        unsigned int size = execMem.size ();
        if ( !size )
            return true;

        execute (execRam, size, &functions, &pool,
                 &placeInPool, &typeList);
    }
    catch (...)
    {
    }
    return false;
}

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

unsigned char* compile (
           ScriptHolder* scpt,
           ::std::vector<Function*>* functions,
           ::std::vector<Object*>* pool,
           ::std::vector<::std::pair<char*,unsigned int>>* placeInPool,
           TypeList* typeList,
           ::std::vector<unsigned char>* execMem)
{
    addStandard (functions, typeList);


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
                    return nullptr;
                int size = pos - command - 5;
                memcpy (buffer, command + 5, size);
                buffer[size] = 0;
                int code = typeList->find (buffer);
                if ( !code )
                    return nullptr;
                int nameSize = strlen (command + 6 + size);
                if ( !nameSize )
                    return nullptr;
                memcpy (buffer, command + 6 + size, nameSize);
                buffer[nameSize] = 0;
                
                for (unsigned int i = 0; i < pool->size (); i++)
                {
                    if ( pool->at (i)->is (buffer) )
                        return nullptr;
                }
                obj = typeList->create (code);
                if ( !obj )
                    return nullptr;
                obj->setName (buffer);
                pool->push_back (obj);
                try
                {
                    char* pushName = new char[nameSize + 1];
                    memcpy (pushName, buffer, nameSize);
                    pushName[nameSize] = 0;
                    ::std::pair<char*, unsigned int> p = {pushName, pool->size () - 1};
                    placeInPool->push_back (p);
                }
                catch (...)
                {
                }
                execMem->push_back (CMD::NEW);
                execMem->push_back (pool->size () - 1);
            }
            if ( strstr (command + 1, "delete") == command + 1 )
            {
                 for (unsigned int i = 0; i < pool->size (); i++)
                {
                    if ( pool->at (i)->is (buffer) )
                    {
                        execMem->push_back (CMD::DEL);
                        execMem->push_back (i);
                    }
                }
            }
        }

        for (unsigned int i = 0; i < functions->size (); i++)
        {
            functionAttributes attribute = functions->at (i)->attributes();
            printf ("attribute.name:%s\ncommand:%s\n-------\n", attribute.name, command);
            if ( strstr (command, attribute.name) == command )
            {
                execMem->push_back (CMD::CALL);
                execMem->push_back (i);
                execMem->push_back (attribute.argnum);
                parseArgs (execMem, placeInPool, functions->at (i),
                           pool, command + strlen (attribute.name));
            }
        }
        scpt->remove (0);
    }

    unsigned char* mem = nullptr;
    try
    {
        mem = new unsigned char[execMem->size ()];
    }
    catch (...)
    {
        return nullptr;
    }
    for (unsigned int i = 0; i < execMem->size (); i++)
    {
        mem[i] = execMem->at (i);
    }
    
    return mem;
}

bool execute (unsigned char* mem, unsigned int size,
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool,
              TypeList* typeList
              )
{
    for (unsigned int i = 0; i < size; i++)
    {
       if ( mem[i] == CMD::CALL )
        {
            printf ("\nCALLING");
            i++;//TODO::Delete what was marked to be deleted
            printf ("\nCALLNUM:%d", mem[i]);
            Function* call = functions->at(mem[i]);
            i++;
            int argnum = mem[i];
            printf ("\nARGNUM:%d", argnum);
            for (unsigned int j = 0; j < argnum; j++)
            {
                i++;
                Object* arg = nullptr;
                if ( mem[i] & ARG_FLAG::ALLOCED )
                {
                    i++;
                    arg = (Object*)(mem + i);
                    i += sizeof (Object*) - 1;
                    call->pushArg (arg);
                }
                else
                {
                    i++;
                    arg = pool->at (mem[i] - 1);
                    call->pushArg (arg);
                }
            }
            printf ("EXEC");
            call->execute ();
            continue;
        }
        if ( mem[i] == CMD::CALL )
        {
            //Call constructor TODO::Add constructors
            i++;
            continue;
        }
        if ( mem[i] == CMD::DEL )
        {
            //Call destructor TODO::Add destructors
            i++;
            if ( pool->at (i) )
                delete pool->at (i);
            pool->at (i) = nullptr;
            continue;
        }
        printf ("mem[%d]:%d\nCMD::CALL:%d",i, mem[i], CMD::CALL);
    }
    return true;
}

bool addStandard (::std::vector<Function*>* functions, TypeList* typeList)
{
    functions->push_back (&std::ECHO);
    typeList ->add (&std::TEXTattributes, 12);
    typeList ->add (&std::NUMBERattributes, 14);
}

bool parseArgs   (::std::vector<unsigned char>* execMem,
                  ::std::vector<::std::pair<char*, unsigned int>>* places,
                  Function* fnc,
                  ::std::vector<Object*>* pool,
                  const char* argumentLine)
{
    try
    {
        unsigned int argsParsed = 0;
        for (unsigned int i = 0; argumentLine[i] != '\0'; i++)
        {
            if ( argumentLine[i] == '"' )
            {
                if ( fnc->attributes ().args[argsParsed] != 12 )
                    return false;

                std::Text* obj = (std::Text*)std::TEXTcreateOn (argumentLine + i);

                if ( !obj )
                    return false;
                i = argumentLine - strchr (argumentLine + i + 1, '"');
                execMem->push_back (0 | ARG_FLAG::DEL | ARG_FLAG::ALLOCED);
                char buff[sizeof (obj)] = {};
                printf ("DATA::%d", sizeof (obj));
                memcpy (buff, obj, sizeof (obj));
                for (unsigned int j = 0; j < sizeof (obj); j++)
                    execMem->push_back (buff[j]);
                argsParsed++;
                continue;
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
                for (unsigned int j = 0; j < places->size (); j++ )
                {
                    if ( !strcmp (places->at (j).first, buffer) )
                    {
                        if ( fnc->attributes ().args[j] !=
                             pool->at(j)->typeCode() )
                            return false;
                        execMem->push_back (0);
                        execMem->push_back ((places->at(j).second));
                        printf ("REEEEET:%d",places->at(j).second);
                    }
                }
                i+=size;
                argsParsed++;
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
