# ifndef H_ENGINE_EXECUTE

# define H_ENGINE_EXECUTE


bool execute  (unsigned int size,
               ::std::vector<Function*>* functions,
               ::std::vector<Object*>* pool,
               ::std::vector<::std::pair<char*,unsigned int>>* placeInPool,
               ExecMem* mem_);

int  callCMD  (ExecMem* mem, unsigned int i,
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool);

int  delCMD   (ExecMem* mem, unsigned int i,
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool);


/**
 *
 * this function executes script that was compiled and stored i ExecMem.
 *
 * @param size        - size of program in ExecMem
 * @param functions   - vector of functions to use
 * @param pool        - vector of varibles
 * @param placeInPool - vector of pairs with names of varibles and their
 * places in pool vector
 * @param mem         - pointer to ExecMem class with program
 *
 * @return - success
 *
 */
bool execute (unsigned int size,
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool,
              ExecMem* mem
              )
{
    if ( !mem || !size || !functions || !pool || !placeInPool )
    {
        OUTPUT_INTERNAL ("bad arguments");
        return false;
    }
    mem->dump ("dump.txt");
    for (unsigned int i = 0; i < size; i++)
    {
        int rslt = 0;
        if ( mem->get(i) == CMD::CALL )
        {
            i++;
            rslt = callCMD (mem, i, functions, pool, placeInPool);
            if ( rslt < 0 )
            {
                OUTPUT_INTERNAL ("error when executing:%d", i);
                return false;
            }
            i = rslt;
            continue;
        }
        else if ( mem->get(i) == CMD::DEL )
        {
            i++;
            rslt = delCMD (mem, i, functions, pool, placeInPool);
            if ( rslt < 0 )
            {
                OUTPUT_INTERNAL ("error when executing:%d", i);
                return false;
            }
            i = rslt;
        
            continue;
        }
    }
    return true;
}

/**
 *
 * this function executes call command
 *
 * @param mem         - pointer to ExecMem class with program
 * @param i           - index of calling command in ExecMem class
 * @param functions   - availible functions
 * @param pool        - availible varible
 * @param placeInPool - names of varibles and their places in pool
 *
 * @return - succes
 *
 */
int callCMD  (ExecMem* mem, unsigned int i,
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool)
{
    if ( !mem || !functions || !pool || !placeInPool )
    {
        OUTPUT_INTERNAL ("bad args");
        return false;
    }
                            //TODO::Delete what was marked to be deleted
    int funcNum = mem->get(i);
    if ( funcNum >= functions->size () )
    {
        OUTPUT_INTERNAL ("calling unknown function:%d", funcNum);
        return -1;
    }
    Function* call = functions->at(funcNum);
    try
    {
        call = functions->at(mem->get(i));
    }
    catch (::std::out_of_range)
    {
        OUTPUT_INTERNAL ("unknown index:%d", mem->get(i));
        return -1;
    }
    if ( !call )
    {
        OUTPUT_INTERNAL ("unusable function");
        return -1;
    }
    i++;
    int argnum = mem->get(i);
    for (unsigned int j = 0; j < argnum; j++)
    {
        i++;
        Object* arg = nullptr;
        if ( mem->get(i) & ARG_FLAG::ALLOCED )
        {
            i++;
            if ( !mem->memcpy (i, (unsigned char*)(&arg), sizeof (arg)) )
            {
                OUTPUT_INTERNAL ("Cant copy");
            }
            i += sizeof (Object*) - 1;
            if ( !(call->pushArg (arg)) )
            {
                OUTPUT_INTERNAL ("bad arg:%d", arg);
                return -1;
            }
        OUTPUT_DEBUG ("TEXT_CALL_ARG:%p", arg);
        }
        else
        {
            i++;
            unsigned int argIndex = mem->get(i);
            if ( argIndex >= pool->size () )
            {
                OUTPUT_INTERNAL ("bad arg index:%d", argIndex);
                return -1;
            }
            arg = pool->at (argIndex);
            OUTPUT_DEBUG ("ARG_CALL Indx:%d Ptr:%p", argIndex, arg);
            if ( !(call->pushArg (arg)) )
            {
                OUTPUT_INTERNAL ("bad arg:%d", arg);
                return -1;
            }
        }
    }
    OUTPUT_DEBUG ("Calling:%p", call);
    call->execute ();
    OUTPUT_DEBUG ("Call successful");
    return i;
}

/**
 *
 * this function executes del command
 *
 * @param mem         - ponter to ExecMem class
 * @param i           - index of delCMD in ExecMem class
 * @param functions   - availible functions
 * @param pool        - availible varible
 * @param placeInPool - names of varibles and their places in pool
 *
 * @return - succes
 *
 */
int  delCMD   (ExecMem* mem, unsigned int i,
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool)
{
    if ( !mem || !functions || !pool || !placeInPool )
    {
        OUTPUT_INTERNAL ("bad args");
        return -1;
    }

    //Call destructor TODO::Add destructors
    try
    {
        if ( pool->at (mem->get(i)) )
            delete pool->at (mem->get(i));
        pool->at (mem->get(i)) = nullptr;
    }
    catch (::std::out_of_range sct)
    {
        OUTPUT_INTERNAL ("bad delete index:%d", mem->get(i));
        return -1;
    }
    return i;
}

/**
 *
 * this function dumps data to file
 *
 * @param data   - pointer to a buffer that will be dumped
 * @param amount - size of buffer that will be dumped
 *
 */
void dump        (unsigned char* data, int amount)
{
    FILE* file = fopen ("Dump.txt", "w");
    if ( !file )
        return;
    for (unsigned int i = 0; i < amount; i++)
    {
        int input = data[i];
        fprintf (file, "[%3d]:{%X}\n", i, input);
    }
    fclose (file);
}



# endif /* H_ENGINE_EXECUTE */
