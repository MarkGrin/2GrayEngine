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

extern "C"
__declspec(export)
userlib::technicalData* technicalData ()
{
    userlib::technicalData* ret = new userlib::technicalData;
    ret->version = ENGINE_VERSION;
    return ret;
}

extern "C"
__declspec(export)
std::vector<logic::Function*>* funcs ()
{
    std::vector<logic::Function*>* funcsVector = nullptr;
    funcsVector = new std::vector<logic::Function*>;

    funcsVector->push_back (new userlib::Receive);
    funcsVector->push_back (new userlib::Send);
    funcsVector->push_back (new userlib::SetIP);
    funcsVector->push_back (new userlib::SetPort);
    funcsVector->push_back (new userlib::Connect);
    funcsVector->push_back (new userlib::Listen);

    return funcsVector;
}

extern "C"
__declspec(export)
std::vector<logic::TypeAttributes*>* types    ()
{
    std::vector<logic::TypeAttributes*>* typesVector = new std::vector<logic::TypeAttributes*>;
    logic::TypeAttributes* socket = nullptr;
    try
    {
        socket = new logic::TypeAttributes (777, "Socket", userlib::SOCKETcreate, userlib::SOCKETcreateOn);
        typesVector->push_back (socket);
    }
    catch (std::bad_alloc)
    {
    }
    return typesVector;
}
