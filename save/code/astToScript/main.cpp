# include <stdio.h>
# include <string.h>
# include <map>
# include <vector>

# include "Token.h"
# include "ASTNode.h"
# include "ASTNodeMethods.h"
# include "ASTree.h"
# include "ASTreeMethods.h"

int main (int argv, char** argc)
{
    printf ("ASTree to Script\n");
    if ( argv != 3 )
    {
        printf ("Please, provide 2 arguments:\n");
        printf ("1 - Name of ASTree file\n");
        printf ("2 - Name of outpit script file\n");
        return argv;
    }
    ASTree tree(argc[1]);
    if ( !tree.isOK() )
    {
        printf ("Something wrong with the tree:%s", argc[1]);
        return 1;
    }
    tree.toScript (argc[2]);
    return 0;
}
