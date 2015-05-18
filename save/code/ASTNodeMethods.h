ASTNode :: ASTNode (int code, double value)
    :
    destructed_ (false),
    code_       (code),
    value_      (value),
    parent_     (nullptr)
{
}

ASTNode :: ~ASTNode ()
{
    if ( this == nullptr )
        return ;
    if ( !isOK () )
        return ;
    for (int i = 0; i < child_.size(); i++)
    {
        if ( child_.at(i) )
            delete child_.at(i);
    }
    kill();
    child_.clear();
    this->setParent(nullptr);
}

/* getters */
int      ASTNode :: getCode   ()            const
{
    return code_;
}

double   ASTNode :: getValue  ()            const
{
    return value_;
}

ASTNode* ASTNode :: getParent ()            const
{
    return parent_;
}

ASTNode* ASTNode :: getChild  (const int n) const
{
    if ( n >= child_.size() )
        return nullptr;
    try
    {
        return child_.at (n);
    }
    catch (std::out_of_range)
    {
        return nullptr;
    }
    return nullptr;
}

int  ASTNode :: getSize   ()            const
{
    if ( !isOK () )
        return -1;
    return child_.size ();
}

int ASTNode :: getIndex  (ASTNode* node) const
{
    if ( !isOK () )
        return -2;
    if ( !node )
        return -2;

    for (int i = 0; i < child_.size(); i++)
    {
        if ( child_.at(i) == node )
            return i;
    }
    return -1;
}

void ASTNode :: setCode  (const int    code)
{
    code_ = code;
}

void ASTNode :: setValue (const double value)
{
    value_ = value;
}

bool ASTNode :: remove    (const int n)
{
    if ( !isOK () )
        return false;
    if ( n >= child_.size () )
        return false;

    ASTNode* child = child_.at (n);
    child->setParent (nullptr);

    std::vector<ASTNode*>::iterator it = child_.begin();
    it += n;
    child_.erase (it);

    return true;
}

bool ASTNode :: add       (ASTNode* child, const int n)
{
    if ( !child )
        return false;
    if ( child == this )
        return false;
    if ( !isOK () )
        return false;
    if ( n > child_.size () )
        return false;
    if ( n == child_.size () )
    {
        return add (child);
    }

    std::vector<ASTNode*>::iterator it = child_.begin();
    it += n;
    child_.insert (it, child);

    child->setParent(this);
    return true;
}

bool ASTNode :: add       (ASTNode* child)
{
    if ( !child )
        return false;
    if ( child == this )
        return false;
    if ( !isOK () )
        return false;

    try
    {
        child_.push_back (child);
    }
    catch (std::bad_alloc)
    {
        return false;
    }
    child->setParent (this);
    return true;
}

bool ASTNode :: setParent (ASTNode* parent)
{
    if ( !parent )
        return false;
    if ( parent == this )
        return false;
    if ( !isOK () )
        return false;

    if ( parent_ )
    {
        int thisParentIndex = parent_->getIndex (this);
        if ( thisParentIndex >= 0 )
            parent_->remove (thisParentIndex);
    }
    parent_ = parent;
    return true;
}

bool ASTNode :: forceParent (ASTNode* parent)
{
    if ( !parent )
        return false;
    if ( parent == this )
        return false;
    if ( !isOK () )
        return false;

    parent_ = parent;
    return true;
}

void ASTNode :: write (FILE* file) const
{
    if ( !file )
        return ;
    if ( !isOK() )
        return ;

    int value = value_;
    fprintf (file, "[ %d %d ", code_, value);

    for (int i = 0; i < child_.size(); i++)
        child_.at(i)->write (file);

    fprintf (file, "NULL ] ");

    return ;
}

bool ASTNode :: isOK () const
{
    if ( !this )
        return false;
    if ( destructed_ )
    {
        return false;
    }
    for (int i = 0; i < child_.size(); i++)
        if ( child_.at (i) == nullptr)
            return false;
   return true;
}

void ASTNode :: kill ()
{
    destructed_ = true;
}
