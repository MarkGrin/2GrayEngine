# ifndef H_DATABASE_SAVE

# define H_DATABASE_SAVE


bool save (Table* table, char* filename)
{
    START_FUNCTION

    int height = table->height ();;;
    int width  = table->columnNumber  ();;;//;;;

    if ( !(height*width) )
    {
        OUTPUT_DEBUG (PLACE, "Empty table");
        return false;
    }
    FILE* file = fopen (filename, "w");
    if ( !file )
    {
        OUTPUT_DEBUG (PLACE, "Cant open file:%s", filename);
        return false;
    }
                 //header + height + width + all widths and codes + binary
    int saveSize = 18 + 1 + 4 + 1 + 4 + 1 + 4 + 1 + table->columnNumber() * 10 + table->size () + 1;
    char* save = NULL;
    try
    {
        save = new char[saveSize + 1];
        memset (save, 0, saveSize);
    }
    catch (...)
    {
        OUTPUT_DEBUG (PLACE, "Cant create buffer sized:%d", saveSize);
        return false;
    }
    strcpy (save, "GRIN_DATABASE_FILE");
    int index = 0 + 18 + 1;
    //sprintf (save + index, "%-4d", saveSize);
    //index += 4 + 1;
    sprintf (save + index, "%-4d", table->height ());
    index += 4 + 1;
    sprintf (save + index, "%-4d", table->columnNumber ());
    index += 4 + 1;
    for (unsigned int i = 0; i < table->columnNumber (); i++)
    {
        sprintf (save + index, "%-4d", table->code (i));
        index += 4 + 1;
        sprintf (save + index, "%-4d", table->size (i));
        index += 4 + 1;

    }
    for (unsigned int x = 0; x < table->columnNumber (); x++)
    {
        for (unsigned int y = 0; y < table->height (); y++)
        {
            OUTPUT_DEBUG (PLACE, "DEBUG: Cycle:%d Cycle:%d", x, y);
            Element* element = table->get (x, y);

            if ( !element )
            {
                OUTPUT_DEBUG (PLACE, "ERROR element is NULL");
            }
            if ( !element->get (save + index) )
            {
                OUTPUT_DEBUG (PLACE, "Cant get at x:%d y:%d", x, y);
                delete[] save;
                return false;
            }
            index += table->size (x);
        }
    }
    
    int written = fwrite (save, sizeof (char), saveSize, file);
    if ( written != saveSize )
    {
        OUTPUT_DEBUG (PLACE, "Cant write:%d only %d", saveSize, written);
        return false;
    }
    fclose (file);
    return true;
}

# endif /* H_DATABASE_SAVE */
