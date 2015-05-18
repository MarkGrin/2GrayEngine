void equality (FILE* file, std::vector<token_t*>* tokens, char& input);

std::vector<token_t*>* tokenize (FILE* file)
{
    std::vector<token_t*>* tokens = nullptr;
    try
    {
        tokens = new std::vector<token_t*>;
    }
    catch (std::bad_alloc)
    {
        return nullptr;
    }
    try
    {
        char input = fgetc (file);
        while ( !feof (file) )
        {
            if ( input == EOF )
                break;
            if ( input == ' ' )
            {
            }
            else if ( input == '=' )
            {
                equality (file, tokens, input);
                continue;
            }
            else if ( input == '!' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::SYS_MARK;
                tokens->push_back (current);
            }
            else if ( input == ';' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::END;
                tokens->push_back (current);
            }
            else if ( input == '(' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::MATH_SCOPE;
                current->data[0] = '(';
                tokens->push_back (current);
            }
            else if ( input == ')' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::MATH_SCOPE;
                current->data[0] = ')';
                tokens->push_back (current);
            }
            else if ( input == '{' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::SCOPE;
                current->data[0] = '{';
                tokens->push_back (current);
            }
            else if ( input == '}' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::SCOPE;
                current->data[0] = '}';
                tokens->push_back (current);
            }
            else if ( input == ',' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::COMMA;
                tokens->push_back (current);
            }
            else if ( input == '$' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::EXIT;
                tokens->push_back (current);
            }
            else if ( input == '+' || input == '-' || input == '/' ||
                 input == '*' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::MATH_OP;
                current->data[0] = input;
                tokens->push_back (current);
            }
            else if ( input == '>' || input == '<' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::BOOL_OP;
                current->data[0] = input;
                input = fgetc (file);
                if ( input == '=' )
                {
                    current->data[1] = input;
                    tokens->push_back (current);
                }
                else
                {
                    current->data[1] = 0;
                    tokens->push_back (current);
                    continue;
                }
            }
            else if ( input >= '0' && input <= '9' )
            {
                token_t* current = new token_t;
                current->type = TOKEN::NUM;
                int i = 0;
                while ( input >= '0' && input <= '9' )
                {
                    current->data[i] = input;
                    i++;
                    input = fgetc (file);
                }
                current->data[i] = 0;
                tokens->push_back (current);
                continue;
            }
            else if ( input >= 'a' && input <= 'z' )
            {
                token_t* current = new token_t;
                int i = 0;
                while ( input >= 'a' && input <= 'z' )
                {
                    current->data[i] = input;
                    i++;
                    input = fgetc (file);
                }
                current->data[i] = 0;
                if ( !strcmp (current->data, MAIN_FUNC_NAME) )
                    current->type = TOKEN::MAIN;
                else if ( !strcmp (current->data, NEW_FUNC_NAME) )
                    current->type = TOKEN::NEW_FUNC;
                else if ( !strcmp (current->data, NEW_VAR_NAME) )
                    current->type = TOKEN::NEW_VAR;
                else
                    current->type = TOKEN::NAME;

                tokens->push_back (current);
                continue;
            }
            input = fgetc (file);
            if ( input == EOF )
                break;
        }
    }
    catch (std::bad_alloc)
    {
        return nullptr;
    }
    return tokens;
}

void equality (FILE* file, std::vector<token_t*>* tokens, char& input)
{
    if ( !file || !tokens )
        return ;
    input = fgetc (file);
    if ( input == '=' )
    {
        token_t* current = new token_t;
        current->type = TOKEN::BOOL_OP;
        current->data[1] = input;
        current->data[0] = input;
        tokens->push_back (current);
        input = fgetc (file);
    }
    else
    {
        token_t* current = new token_t;
        current->type = TOKEN::EQ;
        tokens->push_back (current);
    }
}


