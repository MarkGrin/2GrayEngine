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

void error (const char* message, grNetwork::RawSocket*);

int main (int argc, char** argv)
{
    grNetwork::Start ();

    if ( argc == 1 )
        engine::run ("Script.txt");
    else if ( argc == 2 )
    {
        engine::run (argv[1]);
    }
    else
    {
        printf ("\nERROR\nTo many arguments\n\n");
        getch ();
        return 1;
    }


    printf ("\n");
    getch ();
    grNetwork::Stop ();

    return 0;

}

void error (const char* message, grNetwork::RawSocket* sock)
{
    printf ("\n\nERROR:");
    printf ("\n%s", message);

    printf ("\nWin:%d,\nLib:%d", sock->GetLastError ().local (),
            sock->GetLastError ().lib ());

    printf ("\n");
    getch ();
    exit (0);
}
