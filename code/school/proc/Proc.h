class Proc
{
    CallStack callStack_;
    Memory    memory_;
    Stack     stack_;

    double reg_[16];

    int startPoint_;

    public:

    bool loadMem (const char* filename);
    bool execute ();
};
