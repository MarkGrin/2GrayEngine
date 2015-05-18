# include <stdio.h>
# include <string.h>
# include <stack>
# include <vector>

# include "Mem.h"
# include "Proc.h"
# include "ProcMethods.h"

int main (int argv, char** argc)
{
    printf ("Proc executer\n");
    if ( argv != 2 )
    {
        printf ("Please provide 1 argument:\n");
        printf ("1 - Name of executable file\n");
        return 1;
    }
    Proc proc;
    if ( !proc.loadMem (argc[1]) )
    {
        printf ("Error at reading file\n");
        return 1;
    }
    printf ("Executable file read\n");
    proc.execute();
    printf ("EXITING\n");
}
