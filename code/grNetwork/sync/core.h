# ifndef H_GRNETWORK_SYNC_CORE

# define H_GRNETWORK_SYNC_CORE


namespace sync
{

class  DeltaManager
{
    public:
    bool verify ();
    bool changeAll ();
    bool changed   ();
    unsigned int hash ();
    unsigned int hashFuncCode ();
    unsigned int size ();
    unsigned int deltaPartSize();
    unsigned int deltaPartIndex();
    unsigned int getDelta (char*, unsigned int size);
    unsigned int updateDelta (unsigned int index, unsigned int size);

};

# include "syncCodes.h"
# include "threadInfo.h"
# include "codes.h"
# include "threadMethods.h"
/*# include "serverThreadMethods.h"
# include "clientThreadMethods.h"
*/
};



# endif /* H_GRNETWORK_SYNC_CORE */
