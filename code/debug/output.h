# ifndef H_DEBUG_OUTPUT

# define H_DEBUG_OUTPUT


bool OUTPUT_DEBUG (const char* file, const char* function, int line,
                              const char* text, ...)
{
    if ( !text )
        return false;

    char message [128] = "";
    char string  [128]  = "";

    va_list arguments;
    va_start (arguments, text);

    int n = vsnprintf (message, sizeof (message) - 2, text, arguments);

    va_end (arguments);

    sprintf (string, "%s File:%s Function:%s Line:%d", message, file, function, line);

    OutputDebugStringA (string);

    return (n > 0) ? true : false;
}

# define PLACE __FILE__, __FUNCTION__, __LINE__

# ifndef ALLOW_OUTPUT_DEBUG

# define OUTPUT_DEBUG(...) ;

# endif /* ALLOW_OUTPUT_DEBUG */




# endif /* H_DEBUG_OUTPUT */
