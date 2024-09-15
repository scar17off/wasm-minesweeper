#pragma once
#include <vector>
#include <random>
#include <emscripten/val.h>

class Minesweeper {
public:
    Minesweeper(int width, int height, int mineCount, emscripten::val canvasContext);
    bool revealCell(int x, int y);
    void flagCell(int x, int y);
    int getCellState(int x, int y) const;
    bool isGameOver() const { return gameOver; }
    bool isGameWon() const;
    void drawBoard();

private:
    int width, height, mineCount;
    std::vector<std::vector<bool>> mines;
    std::vector<std::vector<int>> revealed;
    bool gameOver;
    emscripten::val ctx;

    void initializeBoard();
    int countAdjacentMines(int x, int y) const;
    void revealAdjacentCells(int x, int y);
    void drawCell(int x, int y);
};