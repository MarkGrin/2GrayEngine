# ifndef H_ENGINE_ENVIRONMENT

# define H_ENGINE_ENVIRONMENT


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

