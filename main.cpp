#include <iostream>
#include "Game.h"
using namespace std;
//int main()
//{
//    Game game; 
//    game.run();
//
//}
#include <Windows.h>
//#include "Game.h" // include your game header if needed

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Game game;
    game.run();
    return 0;
}


