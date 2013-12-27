# ifndef H_DATABASE_SETTING

# define H_DATABASE_SETTING


class NonCopy
{
    NonCopy (NonCopy&);
    NonCopy operator = (NonCopy&);
    public:
    NonCopy (){}
    ~NonCopy (){}
};

namespace Setting
{
    const int DEBUG_OUTPUT_STRING_SIZE    = 512;
    const int DEBUG_OUTPUT_MESSAGE_SIZE   = 512;

    const int DATA_BASE_FILE_NUMBER_SIZE = 4 + 1;
    const char*        DATA_BASE_FILE_NAME        = "GRIN_DATABASE_FILE";
    const unsigned int DATA_BASE_FILE_NAME_LENGTH = 18;

    const unsigned int MAX_INPUT_DATABASE = 32;

    const int NETWORK_MESSAGE_SIZE  = 1024;
    const int NETWORK_FIRST_MESSAGE = 8;

    const short int THREAD_RUNNING    = 0;
    const short int THREAD_FORCE_EXIT = 1;
    const short int THREAD_STOPPED    = 2;
    const short int THREAD_STARTING   = 3;

    const wchar_t FONT_NAMEW[32] = {L"Lucida Console"};
    const char    FONT_NAMEA[32] = { "Lucida Console"};

# ifdef CSV
    const wchar_t* EXCEL_TYPE = L".csv";
# endif/*CSV*/
# ifdef XLS
    const wchar_t* EXCEL_TYPE = L".xls";
# endif/*XLS*/
    
    const wchar_t* DATABASE_TYPE = L".hug";

    const char INT     = 'I';
    const char WCHAR_T = 'W';
    const char CHAR    = 'C';

    const unsigned int BUTTON_IDLE    = 0;
    const unsigned int BUTTON_PRESSED = 1;
    const unsigned int BUTTON_POINTED = 2;

    const wchar_t BUTTON_IDLE_FILE_NAME    = 'I';

    const wchar_t BUTTON_PRESSED_FILE_NAME = 'S';
    const wchar_t BUTTON_POINTED_FILE_NAME = 'P';

    const unsigned int MAX_FILE_NAME_LENGTH = 32;
    const unsigned int MAX_ANSWER_SIZE = 256;

    const unsigned int BMP_TYPE = 5;

    const int DATA_TYPE = 127;

    const unsigned int PORT = 1985;

};

# endif /* H_DATABASE_SETTING */
