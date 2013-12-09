# ifndef H_ENGINE_EXECUTE

# define H_ENGINE_EXECUTE


bool execute  (unsigned char* data, unsigned int size,
               ::std::vector<Function*>* functions,
               ::std::vector<Object*>* pool,
               ::std::vector<::std::pair<char*,unsigned int>>* placeInPool,
               TypeList* typeList);

int  callCMD  (unsigned char* data, 
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool);

int  delCMD   (unsigned char* data, 
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool);

void dump        (unsigned char* data, int amount);

bool execute (unsigned char* mem, unsigned int size,
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool,
              TypeList* typeList
              )
{
    if ( !mem || !size || !functions || !pool || !placeInPool || !typeList )
    {
        OUTPUT_INTERNAL ("bad arguments");
        return false;
    }
    for (unsigned int i = 0; i < size; i++)
    {
        int rslt = 0;
        if ( mem[i] == CMD::CALL )
        {
            i++;
            rslt = callCMD (mem + i, functions, pool, placeInPool);
            if ( rslt < 0 )
            {
                OUTPUT_INTERNAL ("error when executing");
                return false;
            }
            i += rslt;
            continue;
        }
        else if ( mem[i] == CMD::DEL )
        {
            i++;
            rslt = delCMD (mem + i, functions, pool, placeInPool);
            if ( rslt < 0 )
            {
                OUTPUT_INTERNAL ("error when executing");
                return false;
            }
            i += rslt;
        
            continue;
        }
    }
    return true;
}

int callCMD  (unsigned char* mem, 
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool)
{
    if ( !mem || !functions || !pool || !placeInPool )
    {
        OUTPUT_INTERNAL ("bad args");
        return false;
    }
    int i = 0;
                            //TODO::Delete what was marked to be deleted
    int funcNum = mem[i];
    if ( funcNum >= functions->size () )
    {
        OUTPUT_INTERNAL ("calling unknown function:%d", funcNum);
        return -1;
    }
    Function* call = functions->at(mem[i]);
    try
    {
        call = functions->at(mem[i]);
    }
    catch (::std::bad_alloc)
    {
        OUTPUT_INTERNAL ("unknown index:%d", mem[i]);
        return -1;
    }
    if ( !call )
    {
        OUTPUT_INTERNAL ("unusable function");
        return -1;
    }
    i++;
    int argnum = mem[i];
    for (unsigned int j = 0; j < argnum; j++)
    {
        i++;
        Object* arg = nullptr;
        if ( mem[i] & ARG_FLAG::ALLOCED )
        {
            i++;
            char buff[sizeof (arg)] = {};
            for (int k = 0; k < sizeof (arg); k++)
            {
                buff[k] = mem[i + k];
            }
            memcpy (&arg, buff, sizeof (arg));
            i += sizeof (Object*) - 1;
            if ( !call->pushArg (arg) )
            {
                OUTPUT_INTERNAL ("bad arg:%d", arg);
                return -1;
            }
        }
        else
        {
            i++;
            unsigned int argIndex = mem[i];
            if ( argIndex >= pool->size () )
            {
                OUTPUT_INTERNAL ("bad arg index:%d", argIndex);
                return -1;
            }
            arg = pool->at (argIndex);
            if ( !call->pushArg (arg) )
            {
                OUTPUT_INTERNAL ("bad arg:%d", arg);
                return -1;
            }
        }
    }
    call->execute ();
    return i;
}

int  delCMD   (unsigned char* data, 
              ::std::vector<Function*>* functions,
              ::std::vector<Object*>* pool,
              ::std::vector<::std::pair<char*,unsigned int>>* placeInPool)
{
    if ( !data || !functions || !pool || !placeInPool )
    {
        OUTPUT_INTERNAL ("bad args");
        return -1;
    }

    //Call destructor TODO::Add destructors
    try
    {
        if ( pool->at (*data) )
            delete pool->at (*data);
        pool->at (*data) = nullptr;
    }
    catch (::std::out_of_range sct)
    {
        OUTPUT_INTERNAL ("bad delete index:%d", *data);
        return -1;
    }
    return 0;
}

void dump        (unsigned char* data, int amount)
{
    FILE* file = fopen ("dump.txt", "w");
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
