# ifndef H_GRNETWORK_CORE

# define H_GRNETWORK_CORE


namespace grNetwork
{

class  ErrorInfo;
<<<<<<< HEAD
=======
class  Socket;
class  Server;
class  Client;
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79

struct SocketData;


/* Settings and lists */
# include "errorList.h"

/* Methods */
<<<<<<< HEAD
# include "Methods.h"
# include "headerGen.h"
=======
# include "methods.h"
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79

/* Structures */
# include "socketData.h"

/* Classes */
# include "ErrorInfo.h"
<<<<<<< HEAD

/* Classes' methods */
# include "ErrorInfoMethods.h"

/* Modules */
# include "Socket/core.h"
# include "RawSocket/core.h"
=======
# include "Socket.h"
# include "Server.h"
# include "Client.h"

/* Classes' methods */
# include "ErrorInfoMethods.h"
# include "SocketMethods.h"
# include "ServerMethods.h"
# include "ClientMethods.h"
>>>>>>> d156b06435bc4c498dd25db7087b6d375c534a79

};



# endif /* H_GRNETWORK_CORE */
