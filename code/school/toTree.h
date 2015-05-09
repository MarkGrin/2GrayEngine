class toTree
{
    std::vector<token_t*>& tokens_;
    std::vector<char*> funcs_;
    std::vector<char*> vars_;
    int index_;
    ASTNode* root_;
    ASTNode* varsInit_;
    ASTNode* main_;


    public:

    toTree (std::vector<token_t*>& tokens)
    :
        index_  (0),
        tokens_ (tokens)
    {
    }

    bool next ()
    {
        if ( index_ < tokens_.size() )
        {
            return true;
        }
        return false;
    }
    token_t* getToken ()
    {
        if ( next () )
            return tokens_.at (index_);
        return nullptr;
    }

    ASTNode* getProg ()
    {
        root_         = new ASTNode (TREE::ROOT, 0);
        varsInit_     = new ASTNode (TREE::VAR_INIT, 0);
        main_         = new ASTNode (TREE::MAIN, 0);
        while ( true )
        {
            int res = getSysCom ();
            if ( res < 0 )
            {
                if ( getToken()->type == TOKEN::EXIT )
                {
                    res = 1;
                }
            }
            if ( res > 0 )
            {
                printf ("EXITING");
                root_->add (varsInit_);
                root_->add (main_);
                return root_;
            }
        }
        return nullptr;
    }
    int getSysCom ()
    {
        if ( next () )
        {
            if ( getToken()->type != TOKEN::SYS_MARK )
                return -1;
            index_++;
        }
        if ( next() )
        {
            if ( getToken()->type == TOKEN::MAIN )
            {
                index_++;
                index_++;
                getFunc (main_);
                if ( getToken()->type != TOKEN::SCOPE ||
                     getToken()->data[0] != '}' )
                {
                    return -1;
                } 
                index_++;
                return 1;
            }
            if ( getToken()->type == TOKEN::NEW_VAR )
            {
                index_++;
                char* name = new char[MAX_MEM];
                memcpy (name, getToken()->data, MAX_MEM);
                vars_.push_back (name);
                ASTNode* node = new ASTNode (TREE::VARIABLE, vars_.size() - 1);
                index_++;
                index_++;
                ASTNode* number = new ASTNode (TREE::NUMBER, atof (getToken()->data));
                node->add(number);
                varsInit_->add(node);
                index_++;
                return 0;
            }
            if ( getToken()->type == TOKEN::NEW_FUNC )
            {
                index_++;
                char* name = new char[MAX_MEM];
                memcpy (name, getToken()->data, MAX_MEM);
                funcs_.push_back (name);
                ASTNode* node = new ASTNode (TREE::USER_FUNC, funcs_.size() - 1);
                index_++;
                index_++;
                getFunc (node);
                root_->add (node);
                return 0;
            }
        }
        return -1;
    }
    void getFunc (ASTNode* func)
    {
        ASTNode* result = getTerm();
        while ( result )
        {
            printf ("\n|%d %s", getToken()->type, getToken()->data);
            func->add (result);
            result = getTerm();
        }
        index_++;
    }

    ASTNode* getTerm ()
    {
        if ( getToken()->type != TOKEN::NAME )
            return nullptr;
        if ( getVar (getToken()->data) >= 0 )
        {
            ASTNode* node = getAssigment();
            index_++;
            return node;
        }
        if ( getFunc (getToken()->data) >= 0 )
        {
            ASTNode* node = new ASTNode (TREE::STD_FUNC, STD_FUNC::CALL);
            ASTNode* child = new ASTNode (TREE::USER_FUNC, getFunc(getToken()->data));
            node->add (child);
            index_++;
            index_++;
            return node;
        }
        if ( !strcmp (getToken()->data, "while") )
        {
            ASTNode* node = getCond (LOGIC::WHILE);
            return node;
        }
        if ( !strcmp (getToken()->data, "if") )
        {
            ASTNode* node = getCond (LOGIC::IF);
            return node;
        }
        if ( !strcmp (getToken()->data, "in") )
        {
            ASTNode* node = new ASTNode (TREE::STD_FUNC, STD_FUNC::IN);
            index_++;
            ASTNode* son = new ASTNode (TREE::VARIABLE, getVar (getToken()->data));
            index_++;
            index_++;
            node->add (son);
            return node;
        }
        if ( !strcmp (getToken()->data, "out") )
        {
            ASTNode* node = new ASTNode (TREE::STD_FUNC, STD_FUNC::OUT);
            index_++;
            ASTNode* son = new ASTNode (TREE::VARIABLE, getVar (getToken()->data));
            index_++;
            node->add (son);
            return node;
        }
        printf ("unknown term");
        return nullptr;
    }
    ASTNode* getCond (const int type)
    {
        ASTNode* node = new ASTNode  (TREE::LOGIC, type);
        ASTNode* left  = new ASTNode (TREE::LOGIC, LOGIC::COND);
        ASTNode* right = new ASTNode (TREE::LOGIC, LOGIC::COND_MET);
        node->add (left);
        node->add (right);
        index_++;
        printf ("\n1:%d %s", getToken()->type, getToken()->data);
        ASTNode* leftOp  = getArythm ();
        printf ("\n2:%d", getToken()->type);
        ASTNode* midOp   = getLogic ();
        printf ("\n3:%d", getToken()->type);
        ASTNode* rightOp = getArythm ();
        printf ("\n4%d:%p %p %p", getToken()->type, leftOp, midOp, rightOp);
        midOp->add(leftOp);
        midOp->add(rightOp);
        left->add(midOp);
        index_++;
        index_++;
        getFunc (right);
        return node;
    }

    ASTNode* getAssigment()
    {
        int var_index = getVar(getToken()->data);
        ASTNode* variable = new ASTNode(TREE::VARIABLE, var_index);
        ASTNode* equal    = new ASTNode(TREE::OPERATOR, OPERATORS::EQUAL);
        index_++;
        index_++;
        equal->add(variable);
        equal->add(getArythm());
        return equal;
    }

    ASTNode* getArythm()
    {
        ASTNode* element = getComponent();
        if ( !element )
        {
            printf ("\nbad math");
            return nullptr;
        }
        bool minused = false;
        bool extended = false;
        ASTNode* plus  = new ASTNode (TREE::OPERATOR, OPERATORS::PLUS);
        ASTNode* minus = new ASTNode (TREE::OPERATOR, OPERATORS::PLUS);
        plus->add (element);
        if ( !( getToken()->data[0] == '+' ||
                getToken()->data[0] == '-'   ) ||
             getToken()->type != TOKEN::MATH_OP)
            return element;
        while (true)
        {
            printf ("\nCURR:%d %s", getToken()->type, getToken()->data);
            if ( !next () )
            {
                printf ("\nmath reached end unfinished");
                return nullptr;
            }
            if ( getToken()->type != TOKEN::MATH_OP )
            {
                printf ("\nCIVIL END");
                if ( plus->getSize () == 1 )
                {
                    printf ("swapping");
                    ASTNode* del = plus;
                    plus = plus->getChild(0);
                    del->remove (0);
                    //delete del;
                }
                if ( minus->getSize() == 0 )
                {
                    return plus;
                }
                else if ( minus->getSize() == 1 )
                {
                    printf ("\nGOTCHA");
                    ASTNode* root = new ASTNode (TREE::OPERATOR, OPERATORS::MINUS);
                    root->add (plus);
                    root->add (minus->getChild(0));
                    delete minus;
                    return root;
                }
                else if ( minus->getSize() > 1 )
                {
                    ASTNode* root = new ASTNode (TREE::OPERATOR, OPERATORS::MINUS);
                    root->add (plus);
                    root->add (minus);
                    return root;
                }
            }
            if ( getToken()->data[0] == '+' )
            {
                index_++;
                ASTNode* result = getComponent();
                if ( !result )
                {
                    return nullptr;
                }
                plus->add (result);
            }
            else if ( getToken()->data[0] == '-' )
            {
                index_++;
                ASTNode* result = getComponent();
                if ( !result )
                {
                    return nullptr;
                }
                minus->add (result);
            }
            else
            {
                return nullptr;
            }
        }
    }

    ASTNode* getComponent()
    {
        ASTNode* element = getElement();
        if ( !element )
        {
            printf ("\nbad comp math");
            return nullptr;
        }
        bool minused = false;
        bool extended = false;
        ASTNode* plus  = new ASTNode (TREE::OPERATOR, OPERATORS::MUL);
        ASTNode* minus = new ASTNode (TREE::OPERATOR, OPERATORS::MUL);
        plus->add (element);
        if ( !( getToken()->data[0] == '*' ||
                getToken()->data[0] == '/'   ) ||
             getToken()->type != TOKEN::MATH_OP)
            return element;
        while (true)
        {
            printf ("\nCURR:%d %s", getToken()->type, getToken()->data);
            if ( !next () )
            {
                printf ("\nmath reached end unfinished");
                return nullptr;
            }
            if ( getToken()->type != TOKEN::MATH_OP )
            {
                printf ("\nCIVIL END");
                if ( plus->getSize () == 1 )
                {
                    printf ("swapping");
                    ASTNode* del = plus;
                    plus = plus->getChild(0);
                    del->remove (0);
                    //delete del;
                }
                if ( minus->getSize() == 0 )
                {
                    return plus;
                }
                else if ( minus->getSize() == 1 )
                {
                    printf ("\nGOTCHA");
                    ASTNode* root = new ASTNode (TREE::OPERATOR, OPERATORS::DIV);
                    root->add (plus);
                    root->add (minus->getChild(0));
                    delete minus;
                    return root;
                }
                else if ( minus->getSize() > 1 )
                {
                    ASTNode* root = new ASTNode (TREE::OPERATOR, OPERATORS::DIV);
                    root->add (plus);
                    root->add (minus);
                    return root;
                }
            }
            if ( getToken()->data[0] == '*' )
            {
                index_++;
                ASTNode* result = getElement();
                if ( !result )
                {
                    return nullptr;
                }
                plus->add (result);
            }
            else if ( getToken()->data[0] == '/' )
            {
                index_++;
                ASTNode* result = getElement();
                if ( !result )
                {
                    return nullptr;
                }
                minus->add (result);
            }
            else
            {
                return nullptr;
            }
        }
    }

    ASTNode* getElement ()
    {
        if ( !next() )
        {
            return nullptr;
            printf ("\nelement reached end unfinished");
        }
        if ( getToken()->type == TOKEN::NUM )
        {
            ASTNode* num = new ASTNode(TREE::NUMBER, atof (getToken()->data));
            index_++;
            return num;
        }
        if ( getToken()->type == TOKEN::NAME )
        {
            int var = getVar (getToken()->data);
            if ( var >= 0 )
            {
                ASTNode* res = new ASTNode (TREE::VARIABLE, var);
                index_++;
                return res;
            }
            printf ("Unknown name:%s", getToken()->data);
            return nullptr;
        }
        if ( getToken()->type == TOKEN::MATH_SCOPE )
        {
            if ( getToken()->data[0] == ')' )
            {
                return nullptr;
            }
            else
            {
                index_++;
                ASTNode* node = getArythm();
                index_++;
                return node;
            }
        }
    }
    ASTNode* getLogic ()
    {
        if ( !next () )
        {
            printf ("\nreached end on unfinished logic");
            return nullptr;
        }
        int logic = 0;
        if ( getToken()->data[0] == '=' )
            logic = OPERATORS::EQUAL;
        else if ( getToken()->data[0] == '>' )
            logic = OPERATORS::GREATER;
        else if ( getToken()->data[0] == '<' )
            logic = OPERATORS::LOWER;
        else
            return nullptr;

        ASTNode* result = new ASTNode (TREE::OPERATOR, logic);
        index_++;
        return result;
    }
    int getVar (const char* name)
    {
        for (int i = 0; i < vars_.size(); i++)
            if ( !strcmp(vars_.at (i), name) )
                return i;
        return -1;
    }
    int getFunc (const char* name)
    {
        for (int i = 0; i < funcs_.size(); i++)
            if ( !strcmp(funcs_.at (i), name) )
                return i;
        return -1;
    }

    const char* getVar (const int index)
    {
        if ( index >= vars_.size() )
            return nullptr;
        return vars_.at(index);
    }
    const char* getFunc (const int index)
    {
        if ( index >= funcs_.size() )
            return nullptr;
        return funcs_.at(index);
    }
    int getVarSize ()
    {
        return vars_.size();
    }
    int getFuncSize ()
    {
        return funcs_.size();
    }
};

