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

void ASTree :: toExec (ASTNode* node)
{
    if ( !node )
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
            toExec (node->getChild(i));
    }
    else if ( code == USER_FUNC )
    {
        if ( node->getParent()->getCode() == ROOT )
        {
            ExecByte byte = {{COMMAND::MARK, 0, 0, 0}, 0};
            mem_.push_back (byte);
            funcJumps_[value] = mem_.size() - 1;
            for (int i = 0; i < node->getSize(); i++)
                toExec (node->getChild(i));
            ExecByte ret = {{COMMAND::RET, 0, 0, 0}, 0};
            mem_.push_back (ret);
        }
        else
        {
        }
    }
    else if ( code == NUMBER )
    {
        ExecByte byte = {{COMMAND::PUSH, PLACE::MEMORY, 0, 0}, value};
        mem_.push_back (byte);
    }
    else if ( code == VARIABLE )
    {
        ExecByte byte = {{COMMAND::PUSH, PLACE::REGISTER, value, 0}, 0};
        mem_.push_back (byte);
    }
    else if ( code == OPERATOR )
    {
        const char* OPERATORS[20] = {"=", "+", "-", "*", "/", "^", "==", "!=", "<", ">", ">=", "<=", "!", "||", "&&",
                                     "+=", "-=", "*=", "/=", "ERROR"};
        if ( value == 1 )
        {
            for (int i = 1; i < node->getSize(); i++)
                toExec(node->getChild(i));
            ExecByte byte = {{COMMAND::POP, PLACE::REGISTER, node->getChild(0)->getValue(), 0}, 0};
            mem_.push_back (byte);
        }
        if ( value == 16 )
        {
            ExecByte push = {{COMMAND::PUSH, PLACE::REGISTER, node->getChild(0)->getValue(), 0}, 0};
            mem_.push_back (push);
            for (int i = 1; i < node->getSize(); i++)
                toExec(node->getChild(i));
            ExecByte math = {{COMMAND::ADD, 0, 0, 0}, 0};
            mem_.push_back (math);
            ExecByte byte = {{COMMAND::POP, PLACE::REGISTER, node->getChild(0)->getValue(), 0}, 0};
            mem_.push_back (byte);
        }
        if ( value == 17 )
        {
            ExecByte push = {{COMMAND::PUSH, PLACE::REGISTER, node->getChild(0)->getValue(), 0}, 0};
            mem_.push_back (push);
            for (int i = 1; i < node->getSize(); i++)
                toExec(node->getChild(i));
            ExecByte math = {{COMMAND::SUB, 0, 0, 0}, 0};
            mem_.push_back (math);
            ExecByte byte = {{COMMAND::POP, PLACE::REGISTER, node->getChild(0)->getValue(), 0}, 0};
            mem_.push_back (byte);
        }
        if ( value == 18 )
        {
            ExecByte push = {{COMMAND::PUSH, PLACE::REGISTER, node->getChild(0)->getValue(), 0}, 0};
            mem_.push_back (push);
            for (int i = 1; i < node->getSize(); i++)
                toExec(node->getChild(i));
            ExecByte math = {{COMMAND::MUL, 0, 0, 0}, 0};
            mem_.push_back (math);
            ExecByte byte = {{COMMAND::POP, PLACE::REGISTER, node->getChild(0)->getValue(), 0}, 0};
            mem_.push_back (byte);
        }
        if ( value == 19 )
        {
            ExecByte push = {{COMMAND::PUSH, PLACE::REGISTER, node->getChild(0)->getValue(), 0}, 0};
            mem_.push_back (push);
            for (int i = 1; i < node->getSize(); i++)
                toExec(node->getChild(i));
            ExecByte math = {{COMMAND::DIV, 0, 0, 0}, 0};
            mem_.push_back (math);
            ExecByte byte = {{COMMAND::POP, PLACE::REGISTER, node->getChild(0)->getValue(), 0}, 0};
            mem_.push_back (byte);
        }
        else if ( value == 2 )
        {
            for (int i = 0; i < node->getSize(); i++)
                toExec(node->getChild(i));
            ExecByte byte = {{COMMAND::ADD, 0, 0, 0}, 0};
            mem_.push_back (byte);
        }
        else if ( value == 3 )
        {
            for (int i = 0; i < node->getSize(); i++)
                toExec(node->getChild(i));
            ExecByte byte = {{COMMAND::SUB, 0, 0, 0}, 0};
            mem_.push_back (byte);
        }
        else if ( value == 4 )
        {
            for (int i = 0; i < node->getSize(); i++)
                toExec(node->getChild(i));
            ExecByte byte = {{COMMAND::MUL, 0, 0, 0}, 0};
            mem_.push_back (byte);
        }
        else if ( value == 5 )
        {
            for (int i = 0; i < node->getSize(); i++)
                toExec(node->getChild(i));
            ExecByte byte = {{COMMAND::DIV, 0, 0, 0}, 0};
            mem_.push_back (byte);
        }
    }
    else if ( code == LOGIC )
    {
        const char* LOGICS[6] = {"if", "while", "else", "condition", "cond_met", "ERROR"};
        if ( value == 1 )
        {
            if ( node->getSize () <= 2 )
            {
                ASTNode* cond     = node->getChild(0);
                int command = 0;
                if ( cond->getChild(0)->getValue() == OPERATORS::GREATER )
                    command = COMMAND::J_NOT_AB;
                else if ( cond->getChild(0)->getValue() == OPERATORS::LOWER )
                    command = COMMAND::J_NOT_BE;
                else if ( cond->getChild(0)->getValue() == OPERATORS::EQUAL )
                    command = COMMAND::J_NOT_EQ;
                else if ( cond->getChild(0)->getValue() == OPERATORS::NOT_LOW )
                    command = COMMAND::J_ABOVE;
                else if ( cond->getChild(0)->getValue() == OPERATORS::NOT_GRE )
                    command = COMMAND::J_BELOW;
                else if ( cond->getChild(0)->getValue() == OPERATORS::BOOL_EQ )
                    command = COMMAND::J_NOT_EQ;

                ASTNode* sign = cond->getChild(0);
                toExec (sign->getChild(0));
                toExec (sign->getChild(1));
            printf ("\ncom:%d %d", command, cond->getChild(0)->getValue());
                ExecByte jmp = {{command, 0, 0, 0}, 0};
                mem_.push_back (jmp);
                int jumpIndex = mem_.size() - 1;

                ASTNode* cond_met = node->getChild(1);
                for (int i = 0; i < cond_met->getSize(); i++)
                    toExec (cond_met->getChild(i));

                ExecByte mark = {{COMMAND::MARK, 0, 0, 0}, 0};
                mem_.push_back (mark);
                mem_.at (jumpIndex).data = mem_.size() - 1;
            }
            else
            {
                ASTNode* cond     = node->getChild(0);
                int command = 0;
                if ( cond->getChild(0)->getValue() == OPERATORS::GREATER )
                    command = COMMAND::J_NOT_AB;
                else if ( cond->getChild(0)->getValue() == OPERATORS::LOWER )
                    command = COMMAND::J_NOT_BE;
                else if ( cond->getChild(0)->getValue() == OPERATORS::EQUAL )
                    command = COMMAND::J_NOT_EQ;
                else if ( cond->getChild(0)->getValue() == OPERATORS::NOT_LOW )
                    command = COMMAND::J_ABOVE;
                else if ( cond->getChild(0)->getValue() == OPERATORS::NOT_GRE )
                    command = COMMAND::J_BELOW;
                else if ( cond->getChild(0)->getValue() == OPERATORS::BOOL_EQ )
                    command = COMMAND::J_NOT_EQ;

                ASTNode* sign = cond->getChild(0);
                toExec (sign->getChild(0));
                toExec (sign->getChild(1));
            printf ("\ncom:%d %d", command, cond->getChild(0)->getValue());
                ExecByte jmp = {{command, 0, 0, 0}, 0};
                mem_.push_back (jmp);
                int jumpIndex = mem_.size() - 1;

                ASTNode* cond_met = node->getChild(1);
                for (int i = 0; i < cond_met->getSize(); i++)
                    toExec (cond_met->getChild(i));

                ExecByte endJump = {{COMMAND::JMP, 0, 0, 0}, 0};
                mem_.push_back (endJump);
                int endJumpIndex = mem_.size() - 1;

                ExecByte mark = {{COMMAND::MARK, 0, 0, 0}, 0};
                mem_.push_back (mark);
                mem_.at (jumpIndex).data = mem_.size() - 1;

                ASTNode* elseCond = node->getChild(2);
                for (int i = 0; i < elseCond->getSize(); i++)
                    toExec (elseCond->getChild(i));

                mem_.push_back (mark);
                mem_.at (endJumpIndex).data = mem_.size() - 1;
            }
        }
        if ( value == 2 )
        {
            ExecByte checkMark = {{COMMAND::MARK, 0, 0, 0}, 0};
            mem_.push_back (checkMark);
            int checkMarkIndex = mem_.size() - 1;
            ASTNode* cond     = node->getChild(0);
            int command = 0;
            if ( cond->getChild(0)->getValue() == OPERATORS::GREATER )
                command = COMMAND::J_NOT_AB;
            else if ( cond->getChild(0)->getValue() == OPERATORS::LOWER )
                command = COMMAND::J_NOT_BE;
            else if ( cond->getChild(0)->getValue() == OPERATORS::EQUAL )
                command = COMMAND::J_NOT_EQ;
            else if ( cond->getChild(0)->getValue() == OPERATORS::NOT_LOW )
                command = COMMAND::J_ABOVE;
            else if ( cond->getChild(0)->getValue() == OPERATORS::NOT_GRE )
                command = COMMAND::J_BELOW;
            else if ( cond->getChild(0)->getValue() == OPERATORS::BOOL_EQ )
                command = COMMAND::J_NOT_EQ;

            printf ("\ncom:%d %d", command, cond->getChild(0)->getValue());
            ASTNode* sign = cond->getChild(0);
            toExec (sign->getChild(0));
            toExec (sign->getChild(1));
            ExecByte jmp = {{command, 0, 0, 0}, 0};
            mem_.push_back (jmp);
            int jumpIndex = mem_.size() - 1;

            ASTNode* cond_met = node->getChild(1);
            for (int i = 0; i < cond_met->getSize(); i++)
                toExec (cond_met->getChild(i));

            ExecByte retJump = {{COMMAND::JMP, 0, 0, 0}, checkMarkIndex};
            mem_.push_back (retJump);

            ExecByte mark = {{COMMAND::MARK, 0, 0, 0}, 0};
            mem_.push_back (mark);
            mem_.at (jumpIndex).data = mem_.size() - 1;
        }
    }
    else if ( code == MAIN )
    {
        ExecByte byte = {{COMMAND::CALL, 0, 0, 0}, 0};
        mem_.push_back (byte);
        funcJumps_[-1] = mem_.size() - 1;
        for (int i = 0; i < node->getSize(); i++)
            toExec (node->getChild(i));
        ExecByte stop = {{COMMAND::STOP_PROC, 0, 0, 0}, 0};
        mem_.push_back (stop);
    }
    else if ( code == STANDARD_FUNC )
    {
        const char* STANDARD_FUNCS[11] = {"in", "out", "sin", "cos", "getch", "call", "dif", "sqrt", "max", "min", "ERROR"};
        if ( value == 1 )
        {
            ExecByte byte = {{COMMAND::IN, 0, node->getChild(0)->getValue(), 0}, 0};
            mem_.push_back (byte);
        }
        else if ( value == 2 )
        {
            for (int i = 0; i < node->getSize(); i++)
                toExec (node->getChild(i));
            ExecByte byte = {{COMMAND::OUT, 0, 0, 0}, 0};
            mem_.push_back (byte);
        }
        else if ( value == 6 )
        {
            ExecByte byte = {{COMMAND::CALL, 0, 0, 0}, funcJumps_[node->getChild(0)->getValue()]};
            mem_.push_back (byte);
        }
        else if ( value == 8 )
        {
            for (int i = 0; i < node->getSize(); i++)
                toExec (node->getChild(i));
            ExecByte byte = {{COMMAND::SQRT, 0, 0, 0}, 0};
            mem_.push_back (byte);
        }
        else if ( value == 9 )
        {
            for (int i = 0; i < node->getSize(); i++)
                toExec (node->getChild(i));
            ExecByte byte = {{COMMAND::MAX, 0, 0, 0}, 0};
            mem_.push_back (byte);
        }
        else if ( value == 10 )
        {
            for (int i = 0; i < node->getSize(); i++)
                toExec (node->getChild(i));
            ExecByte byte = {{COMMAND::MIN, 0, 0, 0}, 0};
            mem_.push_back (byte);
        }
        else if ( value == 11 )
        {
            for (int i = 0; i < node->getSize(); i++)
                toExec (node->getChild(i));
            ExecByte byte = {{COMMAND::SQRT, 0, 0, 0}, 0};
            mem_.push_back (byte);
        }
    }
    else if ( code == VAR_INIT )
    {
        ExecByte byte = {{COMMAND::MARK, 0, 0, 0}, 0};
        mem_.push_back (byte);
        for (int i = 0; i < node->getSize(); i++)
        {
            ASTNode* var = node->getChild(i);
            ASTNode* num = var->getChild(0);
            ExecByte push = {{COMMAND::PUSH, PLACE::MEMORY  , 0, 0}, num->getValue()};
            ExecByte pop  = {{COMMAND::POP,  PLACE::REGISTER, var->getValue(), 0}, 0};
            mem_.push_back (push);
            mem_.push_back (pop);
        }
        ExecByte ret = {{COMMAND::RET, 0, 0, 0}, 0};
        mem_.push_back (ret);
    }
}

void ASTree :: toExec (const char* name)
{
    FILE* file = fopen (name, "w");
    if ( !file )
        return;
    toExec (root_);
    fprintf (file, "%s\n", HEADER);
    fprintf (file, "%d\n", funcJumps_[-1]);
    fprintf (file, "%d\n", mem_.size());
    for (int i = 0; i < mem_.size(); i++)
    {
        ExecByte byte = mem_.at(i);
        int a = byte.head[0], b = byte.head[1], c = byte.head[2], d = byte.head[3],
            e = byte.data;
        fprintf (file, "%d %d %d %d %d\n", a, b, c, d, e);
    }
    fclose (file);
}

ASTree :: ~ASTree ()
{
    if ( root_ )
        delete root_;
    root_ = nullptr;
}
