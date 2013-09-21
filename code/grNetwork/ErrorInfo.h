# ifndef H_GRNETWORK_ERRORINFO

# define H_GRNETWORK_ERRORINFO


class ErrorInfo
{
    unsigned int local_,
                 lib_;

    public:

    ErrorInfo (unsigned int local, unsigned int lib);

    void set (unsigned int local, unsigned int lib);
    void set (const ErrorInfo&);

    unsigned int local () const;
    unsigned int lib   () const;
};



# endif /* H_GRNETWORK_ERRORINFO */
