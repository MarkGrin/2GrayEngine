# ifndef H_ENGINE_METHODS

# define H_ENGINE_METHODS


bool loadFile (const char* fileName, ScriptHolder* scpt);
bool execute  (ScriptHolder* scpt);
bool execute  (const char* file);

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

            if ( line[letterCount] == '\n' )
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

    functions.push_back (&std::HELLO_WORLD);


    char command[256] = {};
    while ( scpt->lines () )
    {
        scpt->get (command, 256, 0);

        for (unsigned int i = 0; i < functions.size (); i++)
        {
            functionAttributes attribute = functions.at (i)->attributes();
            if ( !strcmp (command, attribute.name) )
            {
                functions.at (i)->execute ();
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

# endif /* H_ENGINE_METHODS */
