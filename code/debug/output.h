# ifndef H_DEBUG_OUTPUT

# define H_DEBUG_OUTPUT


bool OUTPUT_DEBUG (const char* file, int line,
                              const char* text, ...)
{
    if ( !text )
        return false;

    char message [128] = "";
    char string  [128]  = "";

    va_list arguments;
    va_start (arguments, text);

    int n = vsnprintf (message, sizeof (message) - 2, text, arguments);
    if ( n < 0 )
        return false;

    va_end (arguments);

    n = sprintf (string, "%s:%d\n%s\n", file, line, message);
    if ( n < 0 )
        return false;

    if ( OUTPUT_FILE )
    {
        FILE* file = fopen (OUTPUT_FILE, "a");
        if ( !file )
            file = fopen (OUTPUT_FILE, "w");
        if ( !file )
            return false;
        n = fprintf (file, "\n%s", string);
        if ( n < 0 )
            return false;
        fclose ( file );
        return true;
    }
    n = printf ("\n%s", string);
    if ( n < 0 )
        return false;

    return true;
}

bool OUTPUT_ERROR (const char* file, int line,
                              const char* text, ...)
{
    if ( !text )
        return false;

    char message [128]  = "";
    char string  [128]  = "";

    va_list arguments;
    va_start (arguments, text);

    int n = vsnprintf (message, sizeof (message) - 2, text, arguments);
    if ( n < 0 )
        return false;

    va_end (arguments);

    n = sprintf (string, "_ERROR_\n%s\n",  message);
    if ( n < 0 )
        return false;

    if ( OUTPUT_FILE )
    {
        FILE* file = fopen (OUTPUT_FILE, "a");
        if ( !file )
            file = fopen (OUTPUT_FILE, "w");
        if ( !file )
            return false;
        n = fprintf (file, "\n%s", string);
        if ( n < 0 )
            return false;
        fclose ( file );
        return true;
    }
    n = printf ("\n%s", string);
    if ( n < 0 )
        return false;

    return true;
}


bool OUTPUT_INTERNAL (const char* file, int line,
                              const char* text, ...)
{
    if ( !text )
        return false;

    char message [128]  = "";
    char string  [128]  = "";

    va_list arguments;
    va_start (arguments, text);

    int n = vsnprintf (message, sizeof (message) - 2, text, arguments);
    if ( n < 0 )
        return false;

    va_end (arguments);

    n = sprintf (string, "_ERROR_INTERNAL_\n%s:%d\n%s\n", file, line, message);
    if ( n < 0 )
        return false;

    if ( OUTPUT_FILE )
    {
        FILE* file = fopen (OUTPUT_FILE, "a");
        if ( !file )
            file = fopen (OUTPUT_FILE, "w");
        if ( !file )
            return false;
        n = fprintf (file, "\n%s", string);
        if ( n < 0 )
            return false;
        fclose ( file );
        return true;
    }
    n = printf ("\n%s", string);
    if ( n < 0 )
        return false;

    return true;
}



# define PLACE __FILE__, __LINE__

# ifndef ALLOW_OUTPUT_DEBUG

# define OUTPUT_DEBUG(...) ;

# endif

# ifdef ALLOW_OUTPUT_DEBUG

# define OUTPUT_DEBUG(...)\
    if(!DEBUG::SILENT)DEBUG::OUTPUT_DEBUG(PLACE,__VA_ARGS__)

# endif /* ALLOW_OUTPUT_DEBUG */



# ifndef ALLOW_OUTPUT_ERROR

# define OUTPUT_ERROR(...) ;

# endif /* ALLOW_OUTPUT_ERROR */

# ifdef ALLOW_OUTPUT_ERROR

# define OUTPUT_ERROR(...)\
    if ( !DEBUG::SILENT )DEBUG::OUTPUT_ERROR (PLACE, __VA_ARGS__)

# endif /* ALLOW_OUTPUT_ERROR */



# ifndef ALLOW_OUTPUT_INTERNAL

# define OUTPUT_ERROR(...) ;

# endif /* ALLOW_OUTPUT_ERROR */

# ifdef ALLOW_OUTPUT_INTERNAL

# define OUTPUT_INTERNAL(...)\
    if ( !DEBUG::SILENT )DEBUG::OUTPUT_INTERNAL (PLACE, __VA_ARGS__)

# endif /* ALLOW_OUTPUT_ERROR */



# endif /* H_DEBUG_OUTPUT */
