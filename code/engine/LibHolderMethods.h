# ifndef H_ENGINE_LIBHOLDERMETHODS

# define H_ENGINE_LIBHOLDERMETHODS

LibHolder :: LibHolder ()
{
}
bool LibHolder :: add (environment* en, const char* name)
{
    if ( !en || !name )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }
    if ( !en->scpt        || !en->functions || !en->pool ||
         !en->placeInPool || !en->typeList )
    {
        OUTPUT_INTERNAL ("bad arg");
        return false;
    }
    HMODULE dll = LoadLibrary (name);
    if ( !dll )
    {
        OUTPUT_INTERNAL ("can't find:%s", name);
        OUTPUT_ERROR ("can't load:\"%s\" dll", name);
        return false;
    }

    typedef userlib::technicalData*         getTechData ();
    typedef ::std::vector<logic::Function*>*       getFuncs    ();
    typedef ::std::vector<logic::TypeAttributes*>* getTypes    ();
    getTechData* techData = (getTechData*) GetProcAddress (dll, "technicalData");
    getFuncs   * funcs    = (getFuncs*   ) GetProcAddress (dll, "funcs");
    getTypes   * types    = (getTypes*   ) GetProcAddress (dll, "types");
    if ( !techData || !funcs || !types)
    {
        OUTPUT_INTERNAL ("bad dll %s", name);
        OUTPUT_ERROR    ("dll %s is bad, check it", name);
        return false;
    }
    userlib::technicalData* check = techData ();
    if ( !check )
    {
        OUTPUT_INTERNAL ("no technical data");
        OUTPUT_ERROR    ("technical data function works uncorrectly");
        return false;
    }
    if ( check->version < ENGINE_VERSION_SUPPORT )
    {
        OUTPUT_INTERNAL ("is too old");
        OUTPUT_ERROR    ("version of dll%s is not supported, dll%d support%d",
                         name, ENGINE_VERSION, ENGINE_VERSION_SUPPORT);
        return false;
    }
    ::std::vector<logic::Function*>*       addFuncs = funcs ();
    ::std::vector<logic::TypeAttributes*>* addTypes = types ();
    if ( !addFuncs || !addTypes )
    {
        OUTPUT_INTERNAL ("no user functions or types");
        OUTPUT_ERROR    ("no user functions or types");
        return false;
    }
    for (unsigned int i = 0; i < addFuncs->size(); i++)
    {
        try
        {
            if ( !addFuncs->at (i) )
            {
                OUTPUT_INTERNAL ("blank function");
                return false;
            }
            en->functions->push_back (addFuncs->at (i));
        }
        catch (::std::bad_alloc)
        {
            OUTPUT_INTERNAL ("cant add function");
            return false;
        }
        catch (::std::out_of_range)
        {
            OUTPUT_INTERNAL ("cant add function");
            return false;
        }
    }
    for (unsigned int i = 0; i < addTypes->size(); i++)
    {
        try
        {
            if ( !addTypes->at (i) )
            {
                OUTPUT_INTERNAL ("blank type");
                return false;
            }
            if ( ! (en->typeList->add (addTypes->at (i),
                    addTypes->at(i)->typeCode ())) )
            {
                OUTPUT_INTERNAL ("cant add type");
                return false;
            }
        }
        catch (::std::out_of_range)
        {
            OUTPUT_INTERNAL ("cant add type");
            return false;
        }
    }
    try
    {
        libs_.push_back (new LibInfo (name, &dll));
    }
    catch (std::bad_alloc)
    {
        OUTPUT_INTERNAL ("cant add lib to lib vector");
        return false;
    }
    return true;
}

bool LibHolder :: clear ()
{
    for (unsigned int i = 0; i < libs_.size (); i++)
    {
        try
        {
            if ( libs_.at (i) )
                delete libs_.at (i);
        }
        catch (std::out_of_range)
        {
        }
    }
    libs_.clear ();
}

LibHolder :: ~LibHolder ()
{
    this->clear ();
}

# endif /* H_ENGINE_LIBHOLDERMETHODS */
