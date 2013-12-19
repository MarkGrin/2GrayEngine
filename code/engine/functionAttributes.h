# ifndef H_ENGINE_FUNCTIONATTRIBUTES

# define H_ENGINE_FUNCTIONATTRIBUTES


/**
 *
 * this is functionAttributes structure that contain information about
 * function.
 *
 */
struct functionAttributes
{

    unsigned int size;
    unsigned int version;
    unsigned int code;
    char name[32 + 1];

    unsigned int argnum;
    int* args;

};

# endif /* H_ENGINE_FUNCTIONATTRIBUTES */
