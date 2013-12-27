# ifndef H_DATABASE_LOADTWO

# define H_DATABASE_LOADTWO


struct Header
{
    unsigned int columnNumber;
    unsigned int height;

    int* codes;
    unsigned int* sizes;
};

char*         load          (char*   fileName     );
unsigned int  extractHeader (Header* header       , char*  file );
bool          checkHeader   (char*   headerToCheck);
bool          extractData   (Header* header       , char*  file , Table* table);
bool          applyHeader   (Header* header       , Table* table);

bool load (Table* table, char* fileName);

char* load (char* fileName)
{
    START_FUNCTION;
    FILE* file = fopen (fileName, "r");
    if ( !file )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:No file:%s", fileName);
        return nullptr;
    }

    fseek (file, 0, SEEK_END);
    unsigned int loadSize = ftell (file);
    rewind (file);

    char* load = nullptr;
    try
    {
        load = new char[loadSize + 1];
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Cant alloc file buffer");
        return nullptr;
    }

    if ( !fread (load, loadSize, sizeof (char), file) )
    {
        OUTPUT_DEBUG  (PLACE, "ERROR:With reading file");
        delete[] load;
        return nullptr;
    }
    return load;
}

unsigned int extractHeader (Header* header, char* file)
{
    START_FUNCTION;
    if ( !file || !header )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Null ptr given");
        return 0;
    }

    if ( !checkHeader (file) )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Bad file given");
        return 0;
    }

    unsigned int index = Setting::DATA_BASE_FILE_NAME_LENGTH + 1;

    sscanf (file + index, "%4d", &(header->height) );
    index += 5;

    sscanf (file + index, "%4d", &(header->columnNumber) );
    index += 5;

    if ( header->sizes )
    {
        delete[] header->sizes;
        header->sizes = nullptr;
    }
    if ( header->codes )
    {
        delete[] header->codes;
        header->sizes = nullptr;
    }

    try
    {
        header->sizes = new unsigned int[header->columnNumber];
        header->codes = new          int[header->columnNumber];
    }
    catch (...)
    {
        if ( header->codes )
            delete[] header->sizes;
        OUTPUT_DEBUG (PLACE, "ERROR:Cant alloc sizes or codes");
        return 0;
    }

    for (unsigned int i = 0; i < header->columnNumber; i++)
    {
        sscanf (file + index, "%4d", header->codes + i);
        index += 5;
        sscanf (file + index, "%4d", header->sizes + i);
        index += 5;
    }
    return index;
}

bool checkHeader (char* headerToCheck)
{
    START_FUNCTION;
    for (unsigned int i = 0; i < Setting::DATA_BASE_FILE_NAME_LENGTH; i++)
    {
        if ( Setting::DATA_BASE_FILE_NAME[i] != headerToCheck[i] )
        {
            OUTPUT_DEBUG (PLACE, "ERROR:Bad %d letter", i);
            return false;
        }
    }
    return true;
}

bool extractData (Header* header, char* file, Table* table)
{
    START_FUNCTION;
    if ( !header || !file || !table )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Null ptr given");
        return false;
    }

    unsigned int index = 0;
    for (unsigned int x = 0; x < header->columnNumber; x++)
    {
        for (unsigned int y = 0; y < header->height; y++)
        {
            if ( !table->put (x, y, file + index) )
            {
                OUTPUT_DEBUG (PLACE, "ERROR:Cant place x:%d y:%d", x, y);
                return false;
            }
            index += header->sizes[x];
        }
    }
    return true;
}

bool applyHeader (Header* header, Table* table)
{
    START_FUNCTION;
    if ( !header || !table )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Null ptr given");
        return false;
    }

    for (unsigned int i = 0; i < header->columnNumber; i++)
    {
        if ( !table->addColumn (header->codes[i]) )
        {
            OUTPUT_DEBUG (PLACE, "ERROR:Cant add %d column with %d code", i, header->codes[i]);
            return false;
        }
    }
    for (unsigned int i = 0; i < header->height; i++)
    {
        if ( !table->expand () )
        {
            OUTPUT_DEBUG (PLACE, "ERROR:Cant expand on %d itiration", i);
            return false;
        }
    }
    return true;
}

bool load (Table* table, char* fileName)
{
    START_FUNCTION;
    Header header;

    char* file = nullptr;
    file = load (fileName);
    if ( !file )
    {
        OUTPUT_DEBUG (PLACE, "ERROR:Load gave null ptr");
        return false;
    }

    unsigned int data_index = extractHeader (&header, file);
    if ( !data_index )
    {
        delete[] file;
        OUTPUT_DEBUG (PLACE, "ERROR:Cant extract header");
        return false;
    }
    file += data_index;
    if ( !applyHeader (&header, table) )
    {
        file -= data_index;
        delete[] file;
        delete[] header.codes;
        delete[] header.sizes;
        OUTPUT_DEBUG (PLACE, "ERROR:Cant apply header");
        return false;
    }

    if ( !extractData (&header, file, table) )
    {
        file -= data_index;
        delete[] file;
        delete[] header.codes;
        delete[] header.sizes;
        OUTPUT_DEBUG (PLACE, "ERROR:Cant extract data");
        return false;
    }
    file -= data_index;
    delete[] file;
    delete[] header.codes;
    delete[] header.sizes;
    
    return true;
}

# endif /* H_DATABASE_LOADTWO */
