# ifndef H_ENGINE_CORE

# define H_ENGINE_CORE


namespace engine
{


struct environment;

/* classes */
class TypeList;
class ScriptHolder;
class ExecMem;
class LibHolder;
class LibInfo;


/* lists */
# include "CommandList.h"

/* class files */
# include "TypeList.h"
# include "ScriptHolder.h"
# include "ExecMem.h"
# include "LibHolder.h"
# include "LibInfo.h"

/* structures */
# include "environment.h"

/* class methods */
# include "TypeListMethods.h"
# include "ScriptHolderMethods.h"
# include "ExecMemMethods.h"
# include "LibInfoMethods.h"
# include "LibHolderMethods.h"


/* methods */
# include "compile.h"
# include "execute.h"
# include "run.h"

};



# endif /* H_ENGINE_CORE */
