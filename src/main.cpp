#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "minesweeper.h"

Minesweeper* game = nullptr;

void initGame(emscripten::val canvasContext) {
    if (game) delete game;
    game = new Minesweeper(30, 30, 150, canvasContext);
    game->drawBoard();
}

bool revealCell(int x, int y) {
    if (!game) return false;
    bool result = game->revealCell(x, y);
    game->drawBoard();
    return result;
}

void flagCell(int x, int y) {
    if (!game) return;
    game->flagCell(x, y);
    game->drawBoard();
}

bool isGameOver() {
    return game ? game->isGameOver() : false;
}

bool isGameWon() {
    return game ? game->isGameWon() : false;
}

EMSCRIPTEN_BINDINGS(minesweeper) {
    emscripten::function("initGame", &initGame);
    emscripten::function("revealCell", &revealCell);
    emscripten::function("flagCell", &flagCell);
    emscripten::function("isGameOver", &isGameOver);
    emscripten::function("isGameWon", &isGameWon);
}

int main() {
    return 0;
}