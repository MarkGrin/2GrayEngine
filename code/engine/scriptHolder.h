# ifndef H_ENGINE_SCRIPTHOLDER

# define H_ENGINE_SCRIPTHOLDER


class ScriptHolder
{

    ScriptHolder& operator = (ScriptHolder&);

    std::vector<char*> lines_;

    public:

    ScriptHolder (ScriptHolder&);

    unsigned int lines  () const;
    int length (unsigned int index) const;

    bool  pushBack (const char*  line , unsigned int length);
    bool  insert   (const char*  line , unsigned int length,
                    unsigned int index);

    char* get      (unsigned int index , unsigned int size) const;
    bool  get      (char*        buffer, unsigned int size,
                    unsigned int index ) const;

    bool remove    (unsigned int index);

    bool replace   (const char*  line , unsigned int length,
                    unsigned int index);

    ~ScriptHolder ();
};



# endif /* H_ENGINE_SCRIPTHOLDER */