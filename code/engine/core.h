# ifndef H_ENGINE_CORE

# define H_ENGINE_CORE


namespace engine
{

# define ENGINE_VERSION 2

/* structures */
struct functionAttributes;

/* classes */
class TypeAttributes;
class Object;
class Function;
class TypeList;
class ScriptHolder;


/* lists */
# include "CommandList.h"

/* structure files */
# include "typeAttributes.h"
# include "functionAttributes.h"

/* class files */
# include "Object.h"
# include "Function.h"
# include "TypeList.h"
# include "ScriptHolder.h"
# include  "ExecMem.h"

/* class methods */
# include "TypeAttributesMethods.h"
# include "ObjectMethods.h"
# include "FunctionMethods.h"
# include "TypeListMethods.h"
# include "ScriptHolderMethods.h"
# include "ExecMemMethods.h"

/* modules */
# include "std/core.h"

# include "environment.h"

/* methods */
# include "compile.h"
# include "execute.h"
# include "run.h"

};



# endif /* H_ENGINE_CORE */
