g++ ./client/main.cpp -static-libgcc -lwsock32 -o ./client/main.exe
g++ ./server/main.cpp -static-libgcc -lwsock32 -o ./server/main.exe
g++ ./launcher/main.cpp -static-libgcc -lwsock32 -o ./launcher/main.exe
