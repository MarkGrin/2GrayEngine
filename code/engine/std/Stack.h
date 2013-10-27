# ifndef H_ENGINE_STD_STACK

# define H_ENGINE_STD_STACK


template <class _dataType>
class Stack
{
    Stack (Stack&);
    Stack& operator= (Stack&);

    Vector<_dataType> data_;

    public:

    bool verify ();

    Stack ();

    bool push (_dataType& obj);
    bool pop  ();

    unsigned int size ();

    _dataType& top ();

    void Dump ();

    ~Stack ();
};



# endif /* H_ENGINE_STD_STACK */
