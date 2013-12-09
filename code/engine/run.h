# ifndef H_ENGINE_RUN

# define H_ENGINE_RUN


bool run         (const char* fileName);
bool loadFile    (const char* fileName, ScriptHolder* scpt);

bool addStandard (::std::vector<Function*>* functions, TypeList* typeList);

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

        if ( !addStandard (&functions, &typeList) )
        {
            OUTPUT_INTERNAL ("add standard failed");
            return false;
        }
        environment en = {&scpt, &functions, &pool, &placeInPool, &typeList, &execMem};


        if ( !compile (&en) )
        {
            OUTPUT_INTERNAL ("compile function didn't compile anything");
            OUTPUT_ERROR ("compile function didn't compile anything");
            return false;
        }

        unsigned int size = execMem.size ();
        unsigned char* mem = nullptr;
        try
        {
            mem = new unsigned char[size];
        }
        catch (::std::bad_alloc)
        {
            OUTPUT_INTERNAL ("compile function didn't compile anything");
            OUTPUT_ERROR ("compile function didn't compile anything");
            return false;
        }
        for (unsigned int i = 0; i < size; i++)
            mem[i] = execMem.at (i);
        if ( !size )
            return true;

        execute (mem, size, &functions, &pool,
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
    catch (::std::bad_alloc)
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



# endif /* H_ENGINE_RUN */
