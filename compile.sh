#	To compile the project, run this file:
#	./compile.sh

gcc `pkg-config' --cflags gtk+-3.0` -o pathfind.exe main.c `pkg-config --libs gtk+-3.0`
sudo chmod 766 pathfind.exe
