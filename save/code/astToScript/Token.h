const int MAX_MEM = 256;

namespace TOKEN
{
    enum TOKEN
    {
        COMMA      = 1,
        NUM        = 2,
        MATH_OP    = 3,
        BOOL_OP    = 4,
        SYS_MARK   = 5,
        NAME       = 6,
        END        = 7,
        SCOPE      = 8,
        NEW_FUNC   = 9,
        MAIN       = 10,
        EXIT       = 11,
        EQ         = 12,
        NEW_VAR    = 13,
        MATH_SCOPE = 14,
    };
}

namespace TREE
{
    enum TREE
    {
        ROOT      = 0,
        USER_FUNC = 1,
        NUMBER    = 2,
        VARIABLE  = 3,
        OPERATOR  = 4,
        LOGIC     = 5,
        MAIN      = 6,
        STD_FUNC  = 7,
        VAR_INIT  = 8
    };
}

namespace OPERATORS
{
    enum OPERATORS
    {
        EQUAL   = 1,
        PLUS    = 2,
        MINUS   = 3,
        MUL     = 4,
        DIV     = 5,
        LOWER   = 9,
        GREATER = 10,
    };
}
namespace LOGIC
{
    enum LOGIC
    {
        IF       = 1,
        WHILE    = 2,
        ELSE     = 3,
        COND     = 4,
        COND_MET = 5
    };
}

namespace STD_FUNC
{
    enum STD_FUNC
    {
        IN      = 1,
        OUT     = 2,
        CALL    = 6
    };
}
const char* MAIN_FUNC_NAME = "mainfunc";
const char* NEW_FUNC_NAME  = "newfunc";
const char* NEW_VAR_NAME   = "newvar";

struct token_t /* Plain Old Data */
{
    int type;
    char data[MAX_MEM]; // TODO:add dynamic memory
};
