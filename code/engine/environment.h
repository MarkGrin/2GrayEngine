# ifndef H_ENGINE_ENVIRONMENT

# define H_ENGINE_ENVIRONMENT


/**
 *
 * this is environment struct and it contains things that are used in
 * compilation and execution. They are created before compilation
 * and destructed after execution. So it's logical to place them
 * in one structure that can be described as environment of engine
 *
 */
struct environment
{
    ScriptHolder* scpt;
    ::std::vector<Function*>* functions;
    ::std::vector<Object*>* pool;
    ::std::vector<::std::pair<char*,unsigned int>>* placeInPool;
    TypeList* typeList;
    ::std::vector<unsigned char>* execMem;
};


# endif /* H_ENGINE_ENVIRONMENT */

