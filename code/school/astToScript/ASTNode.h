class ASTNode
{
    /* data */
    bool destructed_;
    int code_;
    double value_;
    ASTNode* parent_;
    std::vector<ASTNode*> child_;
    int index_;

    /* default constructors block */
    ASTNode ();
    ASTNode& operator = (ASTNode&);
    ASTNode (ASTNode&);

    public:

    /* constructor&destructor */
    ASTNode  (int code, double value, int index);
    ~ASTNode ();

    /* getters */
    ASTNode* getParent ()              const;
    ASTNode* getChild  (const int n)   const;
    int      getCode   ()              const;
    double   getValue  ()              const;
    int      getSize   ()              const;
    int      getIndex  ()              const;
    int      getIndex  (ASTNode*  node) const;


    /* setters */
    void setCode  (const int    code);
    void setValue (const double value);

    /* child handling */
    bool remove      (const int n);
    bool add         (ASTNode* child, const int n);
    bool add         (ASTNode* child);
    bool setParent   (ASTNode* parent);
    bool forceParent (ASTNode* parent);

    /* read/write handling */
    void write (FILE* file) const;

    /* safety */
    bool isOK () const;
    void kill ();
};
