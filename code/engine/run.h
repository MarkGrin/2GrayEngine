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
void dump        (unsigned char* data, int amount);

bool run (const char* fileName)
{
    try
    {
        ScriptHolder scpt;
        if ( !loadFile (fileName, &scpt) )
        {
            OUTPUT_INTERNAL ("Cant load file");
            OUTPUT_ERROR ("Script file wasn't loaded");
            return false;
        }

        ::std::vector<Function*> functions;
        ::std::vector<Object*> pool;
        ::std::vector<::std::pair<char*,unsigned int>> placeInPool;
        TypeList typeList;
        ::std::vector<unsigned char> execMem;

        unsigned char* execRam = compile (&scpt, &functions, &pool,
                                          &placeInPool, &typeList,
                                          &execMem);
        if ( !execRam )
        {
            OUTPUT_INTERNAL ("compile function didn't compile anything");
            OUTPUT_ERROR ("compile function didn't compile anything");
            return false;
        }

        unsigned int size = execMem.size ();
        if ( !size )
            return true;

        execute (execRam, size, &functions, &pool,
                 &placeInPool, &typeList);
        return true;
    }
    catch (...)
    {
        OUTPUT_INTERNAL ("unhandled exception");
        OUTPUT_ERROR ("during running file some unhandled exception caught");
        return false;
    }
    return false;
}

bool loadFile (const char* fileName, ScriptHolder* scpt)
{
    if ( !fileName || !scpt )
    {
        OUTPUT_INTERNAL ("bad arguments given");
        return false;
    }

    FILE* file = fopen (fileName, "r");

    if ( !file )
    {
        OUTPUT_INTERNAL ("cant open file:%s", fileName);
        OUTPUT_ERROR ("cant open file:%s", fileName);
        return false;
    }

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
    if ( !addStandard (functions, typeList) )
    {
        OUTPUT_INTERNAL ("cant add standard function and types");
        return nullptr;
    }


    char command[256] = {};
    char buffer[256] = {};
    bool successIteration = false;
    for ( unsigned int linesParsed = 0; linesParsed < scpt->lines (); linesParsed++ )
    {
        memset (command, 0, 256);
        memset (buffer, 0, 256);
        if ( !scpt->get (command, 256, linesParsed) )
        {
            OUTPUT_INTERNAL ("script holder hadn't wrote command");
        }

        if ( command[0] == '!' )/* Standard commands */
        {
            if ( strstr (command+1, "new") == command + 1 )
            {
                Object* obj = nullptr;
                char* pos = strchr (command + 5, ' ');
                if ( !pos )
                {
                    OUTPUT_INTERNAL ("cant find whitespace");
                    OUTPUT_ERROR ("new must have type and object name LINE:%d",
                                   linesParsed + 1);
                    return nullptr;
                }
                int size = pos - command - 5;
                memcpy (buffer, command + 5, size);
                buffer[size] = 0;
                int code = typeList->find (buffer);
                if ( !code )
                {
                    OUTPUT_INTERNAL ("cant find type");
                    OUTPUT_ERROR ("type unknown:%s LINE:%d",
                                  buffer, linesParsed + 1);
                    return nullptr;
                }
                int nameSize = strlen (command + 6 + size);
                if ( !nameSize )
                {
                    OUTPUT_INTERNAL ("cant no name specified");
                    OUTPUT_ERROR ("no name given LINE:%d",
                                  linesParsed);
                    return nullptr;
                }
                memcpy (buffer, command + 6 + size, nameSize);
                buffer[nameSize] = 0;
                
                for (unsigned int i = 0; i < pool->size (); i++)
                {
                    if ( pool->at (i)->is (buffer) )
                    {
                        OUTPUT_INTERNAL ("Already have such varible");
                        OUTPUT_ERROR ("Already have such varible LINE:%d",
                                       linesParsed);
                        return nullptr;
                    }
                }
                obj = typeList->create (code);
                if ( !obj )
                {
                    OUTPUT_INTERNAL ("typelist didn't create object");
                    OUTPUT_ERROR ("object wasn't created LINE:%d",
                                  linesParsed);
                    return nullptr;
                }
                if ( !obj->setName (buffer) )
                {
                    OUTPUT_INTERNAL ("name wasn't set");
                    return nullptr;
                }
                try
                {
                    pool->push_back (obj);
                }
                catch (...) 
                {
                    OUTPUT_INTERNAL ("object wasn't pushed to pool");
                    return nullptr;
                }
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
                    OUTPUT_INTERNAL ("object wasn't pushed to vector");
                    return nullptr;
                }
                try
                {
                    execMem->push_back (CMD::NEW);
                    execMem->push_back (pool->size () - 1);
                }
                catch (...)
                {
                    OUTPUT_INTERNAL ("bytes wasn't pushed to vector");
                    return nullptr;
                }
                successIteration = true;
                continue;
            }
            if ( strstr (command + 1, "delete") == command + 1 )
            {
                for (unsigned int i = 0; i < pool->size (); i++)
                {
                    if ( pool->at (i)->is (command + 8) )
                    {
                        try
                        {
                            execMem->push_back (CMD::DEL);
                            execMem->push_back (i);
                            successIteration = true;
                            continue;
                        }
                        catch (...)
                        {
                            OUTPUT_INTERNAL ("bytes wasn't pushed to vector");
                        }
                    }
                }
                OUTPUT_INTERNAL ("Unknown varible");
                OUTPUT_ERROR ("Unkown varible to delete %s LINE:%d",
                              command + 8, linesParsed);
            }
        }

        /* non standard functions */
        for (unsigned int i = 0; i < functions->size (); i++)
        {
            functionAttributes attribute = functions->at (i)->attributes();
            if ( strstr (command, attribute.name) == command )
            {
                try
                {
                    execMem->push_back (CMD::CALL);
                    execMem->push_back (i);
                    execMem->push_back (attribute.argnum);
                }
                catch (...)
                {
                    OUTPUT_INTERNAL ("bytes weren't pushed to vector");
                }
                if ( !parseArgs (execMem, placeInPool, functions->at (i),
                               pool, command + strlen (attribute.name) + 1) )
                {
                    OUTPUT_INTERNAL ("was unable to parse args");
                    OUTPUT_ERROR ("bad args LINE:%d", linesParsed);
                    return nullptr;
                }
                successIteration = true;
                continue;
            }
        }

        if ( successIteration )
            continue;

        OUTPUT_INTERNAL ("unknown command");
        OUTPUT_ERROR ("unknown command %s LINE:%d",
                      command, linesParsed);
        return nullptr;
    }

    unsigned char* mem = nullptr;
    try
    {
        mem = new unsigned char[execMem->size ()];
    }
    catch (...)
    {
        OUTPUT_INTERNAL ("Cant alloc such ram");
        OUTPUT_ERROR ("Compilation function cant alloc mem to execute");
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
    if ( !mem || !size || !functions || !pool || !placeInPool || !typeList )
    {
        OUTPUT_INTERNAL ("bad arguments");
        return false;
    }
    for (unsigned int i = 0; i < size; i++)
    {
        if ( mem[i] == CMD::CALL )
        {
            i++;//TODO::Delete what was marked to be deleted
            int funcNum = mem[i];
            if ( funcNum >= functions->size () )
            {
                OUTPUT_INTERNAL ("calling unknown function");
                return false;
            }
            Function* call = functions->at(mem[i]);
            if ( !call )
            {
                OUTPUT_INTERNAL ("unusable function");
                return false;
            }
            i++;
            dump (mem, size);
            int argnum = mem[i];
            for (unsigned int j = 0; j < argnum; j++)
            {
                i++;
                Object* arg = nullptr;
                if ( mem[i] & ARG_FLAG::ALLOCED )
                {
                    i++;
                    char buff[sizeof (arg)] = {};
                    for (int k = 0; k < sizeof (arg); k++)
                    {
                        buff[k] = mem[i + k];
                    }
                    memcpy (&arg, buff, sizeof (arg));
                    i += sizeof (Object*) - 1;
                    if ( !call->pushArg (arg) )
                    {
                        OUTPUT_INTERNAL ("bad arg:%d", arg);
                        return false;
                    }
                }
                else
                {
                    i++;
                    unsigned int argIndex = mem[i];
                    if ( argIndex >= pool->size () )
                    {
                        OUTPUT_INTERNAL ("bad arg index:%d", argIndex);
                        return false;
                    }
                    arg = pool->at (argIndex);
                    if ( !call->pushArg (arg) )
                    {
                        OUTPUT_INTERNAL ("bad arg:%d", arg);
                        return false;
                    }
                }
            }
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
    }
    return true;
}

bool addStandard (::std::vector<Function*>* functions, TypeList* typeList)
{
    if ( !functions || !typeList )
    {
        OUTPUT_INTERNAL ("bad arguments given");
        return false;
    }

    bool success = true;

    try
    {
        functions->push_back (&std::ECHO);
        success = success && typeList ->add (&std::TEXTattributes, 12);
        success = success && typeList ->add (&std::NUMBERattributes, 14);
    }
    catch (...)
    {
        OUTPUT_INTERNAL ("was unable to push function");
        return false;
    }

    if ( !success )
    {
        OUTPUT_INTERNAL ("was unable to add type");
        return false;
    }

    return true;
}

bool parseArgs   (::std::vector<unsigned char>* execMem,
                  ::std::vector<::std::pair<char*, unsigned int>>* places,
                  Function* fnc,
                  ::std::vector<Object*>* pool,
                  const char* argumentLine)
{
    if ( !execMem || !places || !fnc || !pool || !argumentLine )
    {
        OUTPUT_INTERNAL ("bad arguments");
        return false;
    }
    try
    {
        int argsParsed = 0;
        for (unsigned int i = 0; argumentLine[i] != '\0'; i++)
        {
            if ( argsParsed >= fnc->attributes ().argnum )
                return true;
            if ( argumentLine[i] == '"' )
            {
                if ( fnc->attributes ().args[argsParsed] != 12 )
                {
                    OUTPUT_INTERNAL ("type doesn't match");
                    OUTPUT_ERROR ("type doesn't match of %d argument",
                                  argsParsed);
                    return false;
                }

                std::Text* obj = (std::Text*)std::TEXTcreateOn (argumentLine + i);

                if ( !obj )
                {
                    OUTPUT_INTERNAL ("Object wasn't created");
                    return false;
                }
                char* ptr = strchr (argumentLine + i + 1, '"');
                if ( !ptr )
                {
                    OUTPUT_INTERNAL ("Unclosed string");
                    OUTPUT_ERROR ("Unclosed string");
                }
                i = argumentLine - ptr;
                try
                {
                    execMem->push_back (0 | ARG_FLAG::DEL | ARG_FLAG::ALLOCED);
                    unsigned char buff[sizeof (obj)] = {};
                    memcpy (buff, &obj, sizeof (obj));
                    for (int j = 0; j < sizeof (obj); j++)
                        execMem->push_back (buff[j]);
                }
                catch (...)
                {
                    OUTPUT_INTERNAL ("Cant push mem");
                    return false;
                }
                argsParsed++;
                continue;
            }
            else if ( argumentLine[i] == ' ' )
            {
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
                        break;
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

void dump        (unsigned char* data, int amount)
{
    FILE* file = fopen ("dump.txt", "w");
    if ( !file )
        return;
    for (unsigned int i = 0; i < amount; i++)
    {
        int input = data[i];
        fprintf (file, "[%3d]:{%X}\n", i, input);
    }
    fclose (file);
}

# endif /* H_ENGINE_METHODS */
