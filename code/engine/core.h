# ifndef H_ENGINE_CORE

# define H_ENGINE_CORE


namespace engine
{

/* structures */
struct typeAttributes;
struct functionAttributes;

/* classes */
class Object;
class Function;
class TypeList;
class ScriptHolder;

/* # include "methods.h" | not written yet */

/* structure files */
# include "typeAttributes.h"
# include "functionAttributes.h"

/* class files */
# include "Object.h"
# include "Function.h"
# include "TypeList.h"
# include "ScriptHolder.h"

/* class methods */
# include "ObjectMethods.h"
# include "TypeListMethods.h"
# include "ScriptHolderMethods.h"

/* modules */
# include "std/core.h"

};



# endif /* H_ENGINE_CORE */
