# ifndef H_ENGINE_CORE

# define H_ENGINE_CORE


namespace engine
{

# define ENGINE_VERSION 2

/* structures */
struct typeAttributes;
struct functionAttributes;

/* classes */
class Object;
class Function;
class TypeList;
class ScriptHolder;


# include "CommandList.h"

/* structure files */
# include "typeAttributes.h"
# include "functionAttributes.h"
# include "environment.h"

/* class files */
# include "Object.h"
# include "Function.h"
# include "TypeList.h"
# include "ScriptHolder.h"

/* class methods */
# include "ObjectMethods.h"
# include "FunctionMethods.h"
# include "TypeListMethods.h"
# include "ScriptHolderMethods.h"

/* modules */
# include "std/core.h"

/* methods */
# include "compile.h"
# include "execute.h"
# include "run.h"

};



# endif /* H_ENGINE_CORE */
