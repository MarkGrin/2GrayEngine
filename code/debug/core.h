# ifndef H_DEBUG_CORE

# define H_DEBUG_CORE

namespace DEBUG
{

char* OUTPUT_FILE = nullptr;
/* TODO: Add critical section here */

bool SILENT = false;
# define OUT_INFO if ( !DEBUG::SILENT )\
    printf

# define ALLOW_OUTPUT_DEBUG
# define ALLOW_OUTPUT_ERROR
# define ALLOW_OUTPUT_INTERNAL

# include "output.h"

};

# endif /* H_DEBUG_CORE */
