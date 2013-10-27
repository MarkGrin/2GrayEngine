# ifndef H_ENGINE_STD_VECTOR

# define H_ENGINE_STD_VECTOR


template <typename _dataType>
class Vector
{

    Vector (Vector&);
    Vector& operator = (Vector&);

    _dataType* data_;
    int size_;


    public:

    bool verify ();

    Vector ();
    explicit Vector (unsigned int size);

    unsigned int size ();

    _dataType& at          (unsigned int index);
    _dataType& operator [] (unsigned int index);

    bool erase   (unsigned int from, unsigned int to);
    bool erase   (unsigned int what);
    bool resize  (unsigned int to);

    void Dump ();

    ~Vector ();

};



# endif /* H_ENGINE_STD_VECTOR */
