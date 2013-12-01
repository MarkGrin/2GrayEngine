# include <stdio.h>
# include <conio.h>
# include <vector>
# include <stack>
# include <map>
# include <utility>

# include <winsock2.h>
# include "ws2tcpip.h"
# include <windows.h>

# include "core.h"

void printHelp ();

int main (int argc, char** argv)
{
    if ( argc <= 1 )
    {
        printHelp ();
        return 0;
    }

    int fileIndex = -1;
    for (unsigned int i = 1; i < argc; i++)
    {
        if ( argv[i][0] == '-' )
            continue;
        fileIndex = i;
        break;
    }
    if ( fileIndex == - 1)
    {
        printHelp ();
        return 1;
    }
    for ( unsigned int i = 0; i < 1; i++ )
    {
        for (unsigned int j = 1; j < fileIndex; j++)
        {
            if ( argv[j][1] == 's' )
                DEBUG::SILENT = true;
            else
            {
                printHelp ();
                return 1;
            }
        }
    }
    if ( fileIndex + 2 < argc )
    {
        if ( argv[fileIndex + 1][0] == '-' &&
             argv[fileIndex + 1][1] == 'o' )
        {
            DEBUG::OUTPUT_FILE = argv[fileIndex + 2];
        }
    }
    OUTPUT_DEBUG ("debugging code");
    OUTPUT_ERROR ("user error info here");
    OUTPUT_DEBUG ("internal code error info here");
    grNetwork::Start ();
    printf ("\n");
    engine::run (argv[fileIndex]);
    getch ();
    grNetwork::Stop ();

    return 0;

}

void printHelp ()
{
    printf ("\n2grayEngine -s File.txt -o out.txt");
    printf ("\n[-s] - silent. No output");
    printf ("\n[Filename]  - File to run");
    printf ("\n[-0 fileName] - output file. If not specified ouput will");
    printf ("be printed on console");
    printf ("\n");
}
