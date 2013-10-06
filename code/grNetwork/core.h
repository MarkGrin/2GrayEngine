# ifndef H_GRNETWORK_CORE

# define H_GRNETWORK_CORE


namespace grNetwork
{

class  ErrorInfo;
class  Socket;
class  Server;
class  Client;

struct SocketData;


/* Settings and lists */
# include "errorList.h"

/* Methods */
# include "methods.h"

/* Structures */
# include "socketData.h"

/* Classes */
# include "ErrorInfo.h"

/* Classes' methods */
# include "ErrorInfoMethods.h"

/* Modules */
# include "Socket/core.h"
# include "RawSocket/core.h"

};



# endif /* H_GRNETWORK_CORE */
