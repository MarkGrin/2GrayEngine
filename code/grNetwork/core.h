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
# include "Socket.h"
# include "Server.h"
# include "Client.h"

/* Classes' methods */
# include "ErrorInfoMethods.h"
# include "SocketMethods.h"
# include "ServerMethods.h"
# include "ClientMethods.h"

};



# endif /* H_GRNETWORK_CORE */
