struct ExecByte /* Plain Old Data */
{
    unsigned char head[4];
    double        data;
};

typedef std::vector<ExecByte> Memory;

const int   MAX_DATA = 256;
const char* HEADER   = "MARKGRIN_EXECUTABLE_FILE";

namespace COMMAND
{
    enum COMMAND
    {
        STOP_PROC = 10,
        PUSH      = 11,
        POP       = 12,
        TOP       = 13,
        ADD       = 14,
        SUB       = 15,
        MUL       = 16,
        DIV       = 17,
        JMP       = 18,
        MARK      = 19,
        CALL      = 20,
        RET       = 21,
        IN        = 22,
        OUT       = 23,
        J_EQUAL   = 24,
        J_ABOVE   = 25,
        J_BELOW   = 26,
        J_NOT_EQ  = 27,
        J_NOT_AB  = 28,
        J_NOT_BE  = 29,
        MAX       = 30,
        MIN       = 31,
        SQRT      = 32,
    };
}

namespace PLACE
{
    enum PLACE
    {
        NOWHERE  = 0,
        REGISTER = 1,
        MEMORY   = 2,
    };
}
