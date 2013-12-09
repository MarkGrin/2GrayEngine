# ifndef H_ENGINE_COMPILE

# define H_ENGINE_COMPILE

bool compile (environment* en);

bool systemCommand (char* line, environment* en);
bool newCommand    (char* line, environment* en);
bool delCommand    (char* line, environment* en);

bool engineCommand (char* line, environment* en);

bool parseArgs   (environment* en, Function* fnc,
                  const char* argumentLine);

bool userArgument (const char* name, environment* en, Function* fnc,
                   int argsParsed);

bool TEXTargument (const char* name, environment* en);

void removeWhitespaces (char* str);

int  findObject (const char* name, ::std::vector<Object*>* pool);
bool addObject  (const char* name, int code, TypeList* typeList,
                 ::std::vector<Object*>* pool,
                 ::std::vector<::std::pair<char*, unsigned int>>* places);
                  
bool compile (environment* en)
{
    if ( !en )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }
    if ( !en->scpt        || !en->functions || !en->pool ||
         !en->placeInPool || !en->typeList )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }

    char line[256] = {};
    for (unsigned int index = 0; index < en->scpt->lines (); index++)
    {
        if ( !en->scpt->get (line, 256, index) )
        {
            OUTPUT_INTERNAL ("script holder hadn't wrote command");
            return false;
        }
        line[255] = 0;
        removeWhitespaces (line);

        if ( !line[0] )       /* empty */
            continue;

        if ( line[0] == '!' ) /* system command */
        {
            bool result = systemCommand (line + 1, en);
            if ( !result )
            {
                OUTPUT_INTERNAL ("bad result");
                OUTPUT_ERROR ("bad system command on line:%d", index);
                return false;
            }
            continue;
        }

        else                  /* engine command */
        {
            bool result = engineCommand (line, en);
            if ( !result )
            {
                OUTPUT_INTERNAL ("bad result");
                OUTPUT_ERROR ("bad system command on line:%d", index);
                return false;
            }
            continue;
        }

                              /* unknown command */
        OUTPUT_INTERNAL ("Unknow command");
        OUTPUT_ERROR ("unknow command on line:%d\ncommand:%s", index, line);
        return false;
    }
    return true;
}

bool systemCommand (char* line, environment* en)
{
    if ( !en || !line )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }
    if ( !en->scpt        || !en->functions || !en->pool ||
         !en->placeInPool || !en->typeList )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }

    if ( strstr (line, "new ") == line)
    {
        if ( !newCommand (line + 4, en) )
        {
            OUTPUT_INTERNAL ("bad command");
            OUTPUT_ERROR ("new command failure");
            return false;
        }
        return true;
    }

    if ( strstr (line, "del ") == line )
    {
        if ( !delCommand (line + 4, en) )
        {
            OUTPUT_INTERNAL ("bad command");
            OUTPUT_ERROR ("del command failure");
            return false;
        }
        return true;
    }

    OUTPUT_INTERNAL ("unknown command");
    OUTPUT_ERROR ("unknown system command:%s", line);
    return false;
}

bool newCommand    (char* line, environment* en)
{
    if ( !en || !line )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }
    if ( !en->scpt        || !en->functions || !en->pool ||
         !en->placeInPool || !en->typeList )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }

    Object* create = nullptr;
    char* pos = strchr (line, ' ');
    if ( !pos )
    {
        OUTPUT_INTERNAL ("cant find whitespace");
        OUTPUT_ERROR ("new must have type and object name");
        return false;
    }

    int size = pos - line;
    char buffer[size + 1]; /* un-initialised array */
    memcpy (buffer, line, size); /* initialised here */
    buffer[size] = 0;
    int code = en->typeList->find (buffer);

    if ( !code )
    {
        OUTPUT_INTERNAL ("cant find type");
        OUTPUT_ERROR ("type unknown:%s", buffer);
        return false;
    }

    if ( *(line + size + 1) == '\0' ||
         *(line + size + 2) == '\0')
    {
        OUTPUT_INTERNAL ("cant no name specified");
        OUTPUT_ERROR ("no name given");
        return false;
    }
    
    if ( !addObject (line + size + 1, code, en->typeList,
         en->pool, en->placeInPool) )
    {
        OUTPUT_INTERNAL ("error with adding object");
        return false;
    }

    try
    {
        en->execMem->push_back (CMD::NEW);
        en->execMem->push_back (en->pool->size () - 1);
    }
    catch (::std::bad_alloc)
    {
        OUTPUT_INTERNAL ("bytes wasn't pushed to vector");
        return false;
    }
    return true;
}

bool delCommand    (char* line, environment* en)
{
    if ( !en || !line )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }
    if ( !en->scpt        || !en->functions || !en->pool ||
         !en->placeInPool || !en->typeList )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }

    int delIndex = findObject (line, en->pool);
    if ( delIndex < 0 )
    {
        OUTPUT_INTERNAL ("unknown varible");
        OUTPUT_ERROR ("no such varible:%s", line);
        return false;
    }
    try
    {
        en->execMem->push_back (CMD::DEL);
        en->execMem->push_back (delIndex);
        return true;
    }
    catch (::std::bad_alloc)
    {
        OUTPUT_INTERNAL ("bytes wasn't pushed to vector");
        return false;
    }
    return true;
}
    
bool engineCommand (char* line, environment* en)
{
    if ( !en || !line )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }
    if ( !en->scpt        || !en->functions || !en->pool ||
         !en->placeInPool || !en->typeList )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }

    ::std::vector<Function*>* functions = en->functions;
    for (unsigned int i = 0; i < functions->size (); i++)
    {
        Function* fnc = functions->at (i);
        if ( !fnc )
        {
            OUTPUT_INTERNAL ("blank function %d", i);
            return false;
        }

        functionAttributes attribute = fnc->attributes();
        int nameSize = strlen (attribute.name);



        if ( strstr (line, attribute.name) == line )
        {
            if ( line[nameSize] != '\0' && line[nameSize] != ' ' )
            {
                continue;
            }
            try
            {
                en->execMem->push_back (CMD::CALL);
                en->execMem->push_back (i);
                en->execMem->push_back (attribute.argnum);
            }
            catch (::std::bad_alloc)
            {
                OUTPUT_INTERNAL ("bytes weren't pushed to vector");
                return false;
            }

            if ( !parseArgs (en, fnc, line + strlen (attribute.name) + 1) )
            {
                OUTPUT_INTERNAL ("was unable to parse args");
                OUTPUT_ERROR ("bad args");
                return false;
            }
            return true;
        }
    }
    OUTPUT_INTERNAL ("didn't find function:%s", line);
    OUTPUT_ERROR ("unknown command:%s", line);
    return false;
}

bool parseArgs   (environment* en, Function* fnc, 
                  const char* argumentLine)
{
    if ( !en )
    {
        OUTPUT_INTERNAL ("bad argument");
        return false;
    }
    if ( !en->execMem || !en->placeInPool || !fnc ||
         !en->pool    || !argumentLine )
    {
        OUTPUT_INTERNAL ("bad arguments");
        return false;
    }

    int argsParsed = 0;
    for (unsigned int i = 0; argumentLine[i] != '\0'; i++)
    {
        if ( argumentLine[i] == '"' )
        {
            if ( fnc->attributes ().args[argsParsed] != 12 )
            {
                OUTPUT_INTERNAL ("type doesn't match");
                OUTPUT_ERROR ("type doesn't match of %d argument",
                              argsParsed);
                return false;
            }


            char* ptr = strchr (argumentLine + i + 1, '"');
            if ( !ptr )
            {
                OUTPUT_INTERNAL ("unclosed string");
                OUTPUT_ERROR ("unclosed string");
                return false;
            }
            *(ptr) = 0; /* ... "Some string[\0] ... */
            if ( !TEXTargument  (argumentLine + i + 1, en) )
            {
                OUTPUT_ERROR ("bad argument:%d", argsParsed);
                return false;
            }
            argsParsed++;
            if ( ptr )
                i = ptr - argumentLine;
            *(ptr) = '"';
            continue;
        }
        else if ( argumentLine[i] == ' ' )
        {
            continue;
        }
        else
        {
            char* pos = strchr (argumentLine + i, ' ');
            if ( pos )
                *pos = 0;
            if ( !userArgument (argumentLine + i, en, fnc, argsParsed) )
            {
                return false;
            }
            i += strlen (argumentLine + i);
            if ( pos )
                *pos = ' ';
            i--;
            argsParsed++;
            continue;
        }
    }
    if ( argsParsed > fnc->attributes().argnum )
    {
        OUTPUT_ERROR ("Too many arguments");
        return false;
    }
    if ( argsParsed < fnc->attributes().argnum )
    {
        OUTPUT_ERROR ("Not enough arguments");
        return false;
    }
    return true;
}

bool userArgument (const char* name, environment* en, Function* fnc,
                   int argsParsed)
{
    if ( !en )
    {
        OUTPUT_INTERNAL ("bad argument");
        return false;
    }
    if ( !en->execMem || !en->placeInPool || !fnc ||
         !en->pool    || !name )
    {
        OUTPUT_INTERNAL ("bad arguments");
        return false;
    }

    int size = strlen (name);
    if ( !size )
    {
        OUTPUT_INTERNAL ("null argument");
        OUTPUT_ERROR ("bad argument:%d", argsParsed);
        return false;
    }
    for (unsigned int j = 0; j < en->placeInPool->size (); j++ )
    {
        if ( !strcmp (en->placeInPool->at (j).first, name) )
        {
            if ( fnc->attributes ().args[argsParsed] !=
                 en->pool->at(j)->typeCode() )
            {
                OUTPUT_INTERNAL ("wrong argument");
                OUTPUT_ERROR ("wrong argument");
                return false;
            }
            if ( argsParsed >= fnc->attributes ().argnum )
            {
                OUTPUT_ERROR ("too many args!");
                return false;
            }
            en->execMem->push_back (0);
            en->execMem->push_back ((en->placeInPool->at(j).second));
            return true;
        }
    }
    OUTPUT_INTERNAL ("unknown command");
    OUTPUT_ERROR ("unknown command");
    return false;
}

bool TEXTargument (const char* name, environment* en)
{
    if ( !en || !name )
    {
        OUTPUT_INTERNAL ("bad argument");
        return false;
    }
    if ( !en->execMem || !en->placeInPool || !en->pool ||
         !name )
    {
        OUTPUT_INTERNAL ("bad arguments");
        return false;
    }

    std::Text* obj = (std::Text*)std::TEXTcreateOn ();
    if ( !obj )
    {
        OUTPUT_INTERNAL ("Object wasn't created");
        return false;
    }
    if ( !obj->set (name) )
    {
        OUTPUT_INTERNAL ("Unable to set string:%s", name);
        return false;
    }
    try
    {
        en->execMem->push_back (0 | ARG_FLAG::DEL | ARG_FLAG::ALLOCED);
        unsigned char buff[sizeof (obj)] = {};
        memcpy (buff, &obj, sizeof (obj));
        for (int j = 0; j < sizeof (obj); j++)
            en->execMem->push_back (buff[j]);
    }
    catch (::std::bad_alloc)
    {
        OUTPUT_INTERNAL ("Cant push mem");
        return false;
    }
    return true;
}

void removeWhitespaces (char* str)
{
    if ( !str )
    {
        OUTPUT_INTERNAL ("bad argument");
        return ;
    }
    char* parsed = str;
    char* current = str - 1;
    bool spaceSequence = true;
    do
    {
        current++;
        if ( *current == ' ' || *current == 9 )
        {
            if ( spaceSequence )
            {
                continue;
            }
            spaceSequence = true;
        }
        else if ( *current != '(' &&
                  *current != ')' &&
                  *current != '!' )
        {
            spaceSequence = false;
        }
        *parsed = *current;
        parsed++;
    }
    while ( *current );
}


int findObject (const char* name, ::std::vector<Object*>* pool)
{
    try
    {
        for (int i = 0; i < pool->size (); i++)
        {
            Object* obj = pool->at (i);
            if ( !obj )
            {
                OUTPUT_INTERNAL ("blank element in pool!");
                return -2;
            }
            if ( obj->is (name) )
            {
                return i;
            }
        }
        return -1;
    }
    catch (::std::out_of_range)
    {
        OUTPUT_INTERNAL ("error when getting element!");
        return -2;
    }
    return -2;
}

bool addObject  (const char* name, int code, TypeList* typeList,
                 ::std::vector<Object*>* pool,
                 ::std::vector<::std::pair<char*, unsigned int>>* places)
{
    if ( !name || !pool || !places )
    {
        OUTPUT_INTERNAL ("bad args");
        return false;
    }
    if ( findObject (name, pool) >= 0 )
    {
        OUTPUT_INTERNAL ("Already have such varible");
        OUTPUT_ERROR ("Already have such varible");
        return false;
    }
    Object* obj = typeList->create (code);
    if ( !obj )
    {
        OUTPUT_INTERNAL ("typelist didn't create object");
        OUTPUT_ERROR ("object wasn't created LINE:");
        return nullptr;
    }
    if ( !obj->setName (name) )
    {
        OUTPUT_INTERNAL ("name wasn't set");
        return false;
    }

    try
    {
        pool->push_back (obj);
    }
    catch (::std::bad_alloc) 
    {
        OUTPUT_INTERNAL ("object wasn't pushed to pool");
        return false;
    }

    try
    {
        int size = strlen (name);
        char* pushName = new char[size + 1];
        memcpy (pushName, name, size);
        pushName[size] = 0;
        ::std::pair<char*, unsigned int> p = {pushName, pool->size () - 1};
        places->push_back (p);
    }
    catch (::std::bad_alloc)
    {
        OUTPUT_INTERNAL ("object wasn't pushed to vector");
        return false;
    }
    return true;
}

# endif /* H_ENGINE_COMPILE */
