# include <stdio.h>
# include <string.h>
# include <vector>
# include <map>

# include "Token.h"
# include "Mem.h"
# include "ASTNode.h"
# include "ASTNodeMethods.h"
# include "ASTree.h"
# include "ASTreeMethods.h"

int main (int argv, char** argc)
{
    printf ("ASTree to Executable\n");
    if ( argv != 3 )
    {
        printf ("Please, provide 2 arguments:\n");
        printf ("1 - Name of ASTree file\n");
        printf ("2 - Name of output executable file\n");
        return argv;
    }
    ASTree tree(argc[1]);
    if ( !tree.isOK() )
    {
        printf ("Something wrong with the tree:%s", argc[1]);
        return 1;
    }
    tree.toExec (argc[2]);
    return 0;
}
