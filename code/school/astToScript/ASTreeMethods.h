ASTree :: ASTree (const char* filename)
    :
    root_ (nullptr)
{
    FILE* file = fopen (filename, "r");
    if ( !file )
    {
        printf ("\nCant open file:%s", filename);
        return;
    }
    char str[256]={};
    fscanf (file, "%d %d", &buildNumber_, &personalCode_);

    int funcNum = 0;
    fscanf (file, "%s %d", str, &funcNum);
    for (int i = 0; i < funcNum; i++)
    {
        fscanf (file, "%s", str);
        char* putStr = new char[256];
        memcpy (putStr, str, 256);
        funcs_[i] = putStr;
    }

    int varNum = 0;
    fscanf (file, "%s %d", str, &varNum);
    for (int i = 0; i < varNum; i++)
    {
        fscanf (file, "%s", str);
        char* putStr = new char[256];
        memcpy (putStr, str, 256);
        vars_[i] = putStr;
    }
    char input = 0;

    while ( input != '[')
    {
        fscanf (file, "%c", &input);
        if ( feof(file) || ferror (file) )
        {
            printf ("\nError");
            return ;
        }
    }
    int index = 0;
    root_ = read (file, nullptr, &index);
    fclose (file);
    return ;
}
ASTNode* ASTree :: read (FILE* file, ASTNode* parent, int* index)
{
    int code = 0, value = 0;
    fscanf(file, "%d %d", &code, &value);
    ASTNode* node = new ASTNode(code,value, *index);
    (*index)++;
    if ( parent )
    {
        parent->add (node);
    }
    while (true)
    {
        char input = 0;
        fscanf (file, "%c", &input);
        if ( feof(file) || ferror(file) )
        {
            printf ("\nIncorrect tree. Probably missing ending ] or NULL");
            return nullptr;
        }
        while ( input == ' ' )
        {
            fscanf (file, "%c", &input);
            if ( feof(file) || ferror(file) )
            {
                printf ("\nIncorrect tree. Probably missing ending ] or NULL");
                return nullptr;
            }
        }
        if ( input == 'N' )
        {
            while ( input != ']')
            {
                fscanf (file, "%c", &input);
                if ( feof(file) || ferror(file) )
                {
                     printf ("\nIncorrect tree. Probably NULL incorrectly written");
                     return nullptr;
                }
            }
            break;
        }
        if ( !read (file, node, index) )
        {
            return nullptr;
        }
    }
    return node;
}

bool ASTree :: isOK () const
{
    if (!this)
        return false;
    return true;
}

void ASTree :: toScript (FILE* file, ASTNode* node, int indent)
{
    if ( !node || !file)
        return ;
    int code = node->getCode();
    int value = node->getValue();

    const int ROOT = 0,
              USER_FUNC = 1,
              NUMBER = 2,
              VARIABLE = 3,
              OPERATOR = 4,
              LOGIC = 5,
              MAIN = 6,
              STANDARD_FUNC = 7,
              VAR_INIT = 8,
              SERVICE = 9;
    if ( code == ROOT )
    {
        for (int i = 0; i < node->getSize(); i++)
            toScript (file, node->getChild(i), 0);
    }
    else if ( code == USER_FUNC )
    {
        if ( node->getParent()->getCode() == ROOT )
        {
            fprintf (file, "!newfunc %s\n{\n", funcs_[value]);
            indent++;
            for (int i = 0; i < node->getSize(); i++)
                toScript (file, node->getChild(i), indent);
            indent--;
            fprintf (file, "}\n\n");
        }
        else
        {
            fprintf (file, "%s", funcs_[value]);
        }
    }
    else if ( code == NUMBER )
    {
        fprintf (file, "%d ", value);
    }
    else if ( code == VARIABLE )
    {
        fprintf (file, "%s ", vars_[value]);
    }
    else if ( code == OPERATOR )
    {
        const char* OPERATORS[20] = {"=", "+", "-", "*", "/", "^", "==", "!=", "<", ">", ">=", "<=", "!", "||", "&&",
                                     "!=", "-=", "*=", "/=", "ERROR"};
        if ( value == 1 )
        {
            for (int i = 0; i < indent; i++)
                fprintf (file, "    ");
            toScript (file, node->getChild(0), indent);
            fprintf (file, "= ");
            for (int i = 1; i < node->getSize(); i++)
                toScript(file, node->getChild(i), indent);
            fprintf (file, ";\n");
        }
        else
        {
            bool scoped = false;
            if ( 
                 ( !strcmp (OPERATORS[value-1],"+") || !strcmp (OPERATORS[value-1], "-") )
                                                    
                                                    &&
                 
                 ( !strcmp (OPERATORS[(int)node->getParent()->getValue()-1], "*")
                                                    ||
                   !strcmp (OPERATORS[(int)node->getParent()->getValue()-1], "/") )
               )
                scoped = true;
            if ( scoped )
                fprintf (file, "( ");
            toScript (file, node->getChild(0), indent);
            fprintf (file, "%s ", OPERATORS[value-1]);
            toScript (file, node->getChild(1), indent);
            if ( scoped )
                fprintf (file, ") ");
        }
    }
    else if ( code == LOGIC )
    {
        const char* LOGICS[6] = {"if", "while", "else", "condition", "cond_met", "ERROR"};
        if ( value <= 3 )
        {
            for (int i = 0; i < indent; i++)
                fprintf (file, "    ");
            fprintf (file, "%s ", LOGICS[value-1]);
            for (int i = 0; i < node->getSize(); i++)
                toScript (file, node->getChild(i), indent);
        }
        if ( value == 4 )
        {
            for (int i = 0; i < node->getSize(); i++)
                toScript (file, node->getChild(i), indent);
            fprintf (file, ";\n");
        }
        if ( value == 5 )
        {
            for (int i = 0; i < indent; i++)
                fprintf (file, "    ");
            fprintf (file, "{\n");
            indent++;
            for (int i = 0; i < node->getSize(); i++)
                toScript (file, node->getChild(i), indent);
            indent--;
            for (int i = 0; i < indent; i++)
                fprintf (file, "    ");
            fprintf (file, "}\n\n");

        }
    }
    else if ( code == MAIN )
    {
        fprintf (file, "!mainfunc\n{\n");
        indent++;
        for (int i = 0; i < node->getSize(); i++)
            toScript (file, node->getChild(i), indent);
        indent++;
        fprintf (file, "}\n$");
    }
    else if ( code == STANDARD_FUNC )
    {
        const char* STANDARD_FUNCS[11] = {"in", "out", "sin", "cos", "getch", "call", "dif", "sqrt", "max", "min", "ERROR"};
        if ( value == 1 || value == 2 || value == 6 )
        {
            for (int i = 0; i < indent; i++)
                fprintf (file, "    ");
            fprintf (file, "%s ", STANDARD_FUNCS[value-1]);
            toScript (file, node->getChild(0), indent);
            fprintf (file, ";\n");
        }
        else
        {
            fprintf (file, "%s ( ", STANDARD_FUNCS[value-1]);
            for (int i = 0; i < node->getSize(); i++)
                toScript (file, node->getChild(i), indent);
            fprintf (file, ") ");
        }
    }
    else if ( code == VAR_INIT )
    {
        for (int i = 0; i < node->getSize(); i++)
        {
            fprintf (file, "!newvar ");
            ASTNode* var = node->getChild(i);
            toScript (file, var, indent);
            fprintf (file, "= ");
            ASTNode* num = var->getChild(0);
            toScript (file, num, indent);
            fprintf (file, "\n");
        }
        fprintf (file, "\n");
    }
}

void ASTree :: toScript (const char* name)
{
    FILE* file = fopen (name, "w");
    if ( !file )
        return;
    toScript (file, root_, 0);
    fclose (file);
}

ASTree :: ~ASTree ()
{
    if ( root_ )
        delete root_;
    root_ = nullptr;
}
