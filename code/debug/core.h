# ifndef H_DEBUG_CORE

# define H_DEBUG_CORE

namespace DEBUG
{

char* OUTPUT_DEBUG_FILE    = nullptr;
char* OUTPUT_ERROR_FILE    = nullptr;
char* OUTPUT_INTERNAL_FILE = nullptr;
/* TODO: Add critical section here */

bool SILENT = false;
# define OUT_INFO if ( !DEBUG::SILENT )\
    printf


# include "output.h"

};

# endif /* H_DEBUG_CORE */
