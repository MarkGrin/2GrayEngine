namespace CMD
{
    const unsigned char
    NEW  = 1, /* Allocate new varible */
    DEL  = 2, /* Delete alloced varible */
    CALL = 1  /* Call user function */
    ;
};
namespace ARG_FLAG
{
    const unsigned char
    DEL     = 1, /* Delete this argument after usage */
    ALLOCED = 2  /* Use direct pointer instead of pool */
    ;
};
