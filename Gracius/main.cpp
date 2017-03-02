#include "Game.h"

int main() {
    Game::i().init(1.0f / 60);
    Game::i().run();
    return 0;
}
