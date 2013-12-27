# ifndef H_DEBUG_CORE

# define H_DEBUG_CORE

<<<<<<< HEAD
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
=======

# define ALLOW_GRIN_FUNCTION_TRACE
# define ALLOW_OUTPUT_DEBUG
# define ALLOW_REPORT_EXCEPTION

# include "output.h"
# include "functionTrace.h"

>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79

# endif /* H_DEBUG_CORE */
