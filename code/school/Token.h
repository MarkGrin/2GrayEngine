enum TOKEN
{
    COMMA    = 1,
    NUM      = 2,
    MATH_OP  = 3,
    BOOL_OP  = 4,
    SYS_MARK = 5,
    NAME     = 6,
    END      = 7,
    SCOPE    = 8,
    NEW_FUNC = 9,
    MAIN     = 10,
    EXIT     = 11,
    EQ       = 12
};

const char* MAIN_FUNC_NAME = "mainfunc";
const char* NEW_FUNC_NAME = "newfunc";

struct token_t
{
    int type;
    char data[256]; //* TODO:add dynamic memory
};
