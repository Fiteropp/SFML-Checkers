#include "Game.h"
#include <windows.h>


int main() {
    Game game;
    game.run();
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    return main();
}
