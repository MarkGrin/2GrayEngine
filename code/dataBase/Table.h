# ifndef H_DATABASE_TABLE

# define H_DATABASE_TABLE


class Table
{
    std::vector<Column*> columns_;

    Table ();//Do not use it!
    Table (Table& table);
    Table operator = (Table& table);

    public:

    TypeRegistry* registry_;

    Table  (TypeRegistry*);
    ~Table (             );

    void destroy ();

    bool ok    () const;
    bool empty () const;

    unsigned int columnNumber (                  ) const;
    unsigned int height       (                  ) const;
    unsigned int size         (                  ) const;
    unsigned int size         (unsigned int index) const;
             int code         (unsigned int index) const;

    bool addColumn (int type_code);
    bool expand    (             );

    bool delColumn (unsigned int index);
    bool delLine   (unsigned int index);
    bool nullCell  (unsigned int x, unsigned int y);

    bool put (unsigned int x, unsigned int y, Element* element) const;
    bool put (unsigned int x, unsigned int y, char* data      ) const;

    int getCode (unsigned int columnNum) const;

    Element* get (unsigned int x, unsigned int y) const;
};


# endif /* H_DATABASE_TABLE */
