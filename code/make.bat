g++ -o ../bin/2grayEngine -static-libstdc++ -std=c++0x -D "ALLOW_OUTPUT_DEBUG" -D "ALLOW_OUTPUT_ERROR" -D "ALLOW_OUTPUT_INTERNAL" main.cpp -lws2_32 2> out.gco
g++ -o ../bin/lib.dll -static-libstdc++ -std=c++0x -D "ALLOW_OUTPUT_DEBUG" -D "ALLOW_OUTPUT_ERROR" -D "ALLOW_OUTPUT_INTERNAL" -shared lib.cpp -lws2_32 2>> out.gco
