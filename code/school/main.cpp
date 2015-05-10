# include <stdio.h>
# include <stdlib.h>
# include <vector>
# include <stdexcept>
# include <string.h>

# include "Token.h"

# include "Tokenizer.h"
# include "TokenizerMethods.h"

# include "ASTree.h"
# include "ASTreeMethods.h"

# include "ASTNode.h"
# include "ASTNodeMethods.h"

# include "toTree.h"

void check (std::vector<token_t*>* tokens)
{
    for (int i = 0; i < tokens->size(); i++)
    {
        token_t token = *(tokens->at(i));
        int type = token.type;
        if ( type == TOKEN::COMMA )
        {
            printf ("\n[%d]={,}", i);
        }
        else if ( type == TOKEN::NUM )
        {
            printf ("\n[%d]={NUM}(%s)", i, token.data);
        }
        else if ( type == TOKEN::MATH_OP )
        {
            printf ("\n[%d]={MATH}(%c)", i, token.data[0]);
        }
        else if ( type == TOKEN::BOOL_OP )
        {
            printf ("\n[%d]={BOOL}(%c)", i, token.data[0]);
        }
        else if ( type == TOKEN::SYS_MARK )
        {
            printf ("\n[%d]={SYS_MARK}(!)", i);
        }
        else if ( type == TOKEN::NAME )
        {
            printf ("\n[%d]={NAME}(%s)", i, token.data);
        }
        else if ( type == TOKEN::END )
        {
            printf ("\n[%d]={END}(;)", i);
        }
        else if ( type == TOKEN::SCOPE )
        {
            printf ("\n[%d]={SCOPE}(%c)", i, token.data[0]);
        }
        else if ( type == TOKEN::NEW_FUNC )
        {
            printf ("\n[%d]={NEW_FUNC}", i);
        }
        else if ( type == TOKEN::MAIN )
        {
            printf ("\n[%d]={MAIN}", i);
        }
        else if ( type == TOKEN::EXIT )
        {
            printf ("\n[%d]={EXIT}($)", i);
        }
        else if ( type == TOKEN::EQ )
        {
            printf ("\n[%d]={EQUALITY}(=)", i);
        }
    }
}

int main (int argv, char** argc)
{

    printf ("AST builder\n");
    if ( argv != 3 )
    {
        printf ("Please provide 2 arguments:\n");
        printf ("1-Name of the script file\n");
        printf ("2-Name of outpit AST file\n");
        return 1;
    }
    FILE* file = fopen (argc[1], "r");
    std::vector<token_t*>* tokens = tokenize (file);
    fclose (file);
    printf ("Tokenizing done\n");
    file = fopen (argc[2], "w");
    toTree tree (*tokens);
    ASTNode* root = tree.getProg ();


    fprintf (file, "1 11\nFUNCS ");
    fprintf (file, "%d", tree.getFuncSize());
    for (int i = 0; i < tree.getFuncSize(); i++)
        fprintf (file, "\n%s", tree.getFunc (i));
    fprintf (file, "\nVARS ");
    fprintf (file, "%d", tree.getVarSize());
    for (int i = 0; i < tree.getVarSize(); i++)
        fprintf (file, "\n%s", tree.getVar (i));
    fprintf (file, "\n");
    root->write(file);
    fclose (file);
    printf ("AST tree built and saved:%s", argc[2]);

    printf ("\nEXITING");
    printf ("\n");
    return 0;
}
