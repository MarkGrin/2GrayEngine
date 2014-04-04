# ifndef H_GRNETWORK_CORE

# define H_GRNETWORK_CORE


namespace grNetwork
{

class  ErrorInfo;
class  DeltaManager
{
    public:
    bool verify ();
    bool changeAll ();
    bool changed   ();
    unsigned int hash ();
    unsigned int hashFuncCode ();

};

struct SocketData;


/* Settings and lists */
# include "errorList.h"

/* Methods */
# include "Methods.h"

/* Structures */
# include "socketData.h"

/* Classes */
# include "ErrorInfo.h"

/* Classes' methods */
# include "ErrorInfoMethods.h"

/* Modules */
# include "Socket/core.h"
# include "RawSocket/core.h"
# include "sync/core.h"

};



# endif /* H_GRNETWORK_CORE */
