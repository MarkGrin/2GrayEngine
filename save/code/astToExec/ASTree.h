class ASTree
{
    ASTree ();
    ASTree& operator = (ASTree&);
    ASTree (ASTree&);

    ASTNode* read (FILE* file, ASTNode* parent, int* index);
    void drawNode (ASTNode* node);

    std::map <int, int> funcJumps_;
    Memory mem_;

    ASTNode* root_;

    int buildNumber_;
    int personalCode_;
    std::map<int, char*> funcs_;
    std::map<int, char*> vars_;

    public:

    bool isOK () const;
    ASTree (const char* filename);
    void draw (const char* name);
    void toExec (const char* name);
    void toExec (ASTNode* node);

    ~ASTree ();
};
