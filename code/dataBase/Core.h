# ifndef H_DATABASE_CORE

# define H_DATABASE_CORE


namespace DataBase
{

    class Table;
    class Column;
    class TypeRegistry;
    class Element;

# include "setting.h"

# include "table.h"
# include "column.h"
# include "typeRegistry.h"
# include "element.h"

# include "typeRegistryMethods.h"
# include "columnMethods.h"
# include "tableMethods.h"

# include "save.h"
# include "load.h"

# include "network\Frontend.h" /*under active development*/
};

# endif /* ifndef H_DATABASE_CORE */
