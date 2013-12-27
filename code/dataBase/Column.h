# ifndef H_DATABASE_COLUMN

# define H_DATABASE_COLUMN


class Column
{
    Table* parentTable_;
    int type_code_;
    std::vector<Element*> elements_;

    Column ();//Do not use it
    Column (Column&);
    Column operator = (Column&);

    public:

    bool ok ();

    Column  (unsigned int size, int code, Table* parentTable);
    ~Column ();

    unsigned int height ();
    unsigned int size   ();
             int code   ();

    bool put (unsigned int index, Element* element);

    bool delCell (unsigned int index);

    Element* get (unsigned int index);

    bool expand ();
};

# endif /* H_DATABASE_COLUMN */
