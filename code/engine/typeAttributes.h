# ifndef H_ENGINE_TYPEATTRIBUTES

# define H_ENGINE_TYPEATTRIBUTES


struct typeAttributes
{
    int type_code_;
    int size;
    char name[32 + 1];
    Object* (*create)();
    Object* (*createOn)(const char*);
};



# endif /* H_ENGINE_TYPEATTRIBUTES */
