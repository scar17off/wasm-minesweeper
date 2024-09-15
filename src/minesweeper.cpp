#include "minesweeper.h"
#include <algorithm>
#include <random>
#include <emscripten/bind.h>

Minesweeper::Minesweeper(int width, int height, int mineCount, emscripten::val canvasContext)
    : width(width), height(height), mineCount(mineCount), gameOver(false), ctx(canvasContext) {
    initializeBoard();
}

void Minesweeper::initializeBoard() {
    mines.resize(height, std::vector<bool>(width, false));
    revealed.resize(height, std::vector<int>(width, -1));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, width - 1);
    std::uniform_int_distribution<> disY(0, height - 1);

    int placedMines = 0;
    while (placedMines < mineCount) {
        int x = disX(gen);
        int y = disY(gen);
        if (!mines[y][x]) {
            mines[y][x] = true;
            placedMines++;
        }
    }
}

bool Minesweeper::revealCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || revealed[y][x] != -1) {
        return false;
    }

    if (mines[y][x]) {
        revealed[y][x] = -2;
        gameOver = true;
        return true;
    }

    int adjacentMines = countAdjacentMines(x, y);
    revealed[y][x] = adjacentMines;

    if (adjacentMines == 0) {
        revealAdjacentCells(x, y);
    }

    return true;
}

void Minesweeper::flagCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || revealed[y][x] >= 0) {
        return;
    }
    revealed[y][x] = (revealed[y][x] == -1) ? -3 : -1;
}

int Minesweeper::getCellState(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return -1;
    }
    return revealed[y][x];
}

bool Minesweeper::isGameWon() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (!mines[y][x] && revealed[y][x] == -1) {
                return false;
            }
        }
    }
    return true;
}

int Minesweeper::countAdjacentMines(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && mines[ny][nx]) {
                count++;
            }
        }
    }
    return count;
}

void Minesweeper::revealAdjacentCells(int x, int y) {
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                revealCell(nx, ny);
            }
        }
    }
}

void Minesweeper::drawBoard() {
    ctx.call<void>("clearRect", 0, 0, width * 20, height * 20);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            drawCell(x, y);
        }
    }
}

void Minesweeper::drawCell(int x, int y) {
    int state = getCellState(x, y);
    int cellSize = 20;

    // Draw cell background
    ctx.set("fillStyle", state == -1 ? "#ccc" : "#fff");
    ctx.call<void>("fillRect", x * cellSize, y * cellSize, cellSize, cellSize);
    ctx.call<void>("strokeRect", x * cellSize, y * cellSize, cellSize, cellSize);

    if (state > 0) {
        // Draw number
        std::string color;
        switch (state) {
            case 1: color = "#0000FF"; break; // Blue
            case 2: color = "#008000"; break; // Green
            case 3: color = "#FF0000"; break; // Red
            case 4: color = "#000080"; break; // Navy
            case 5: color = "#800000"; break; // Maroon
            case 6: color = "#008080"; break; // Teal
            case 7: color = "#000000"; break; // Black
            case 8: color = "#808080"; break; // Gray
            default: color = "#000000"; break;
        }
        ctx.set("fillStyle", color);
        ctx.set("font", "14px Arial");
        ctx.set("textAlign", "center");
        ctx.set("textBaseline", "middle");
        ctx.call<void>("fillText", std::to_string(state), x * cellSize + cellSize / 2, y * cellSize + cellSize / 2);
    } else if (state == -2) {
        // Draw mine
        ctx.set("fillStyle", "#f00");
        ctx.call<void>("beginPath");
        ctx.call<void>("arc", x * cellSize + cellSize / 2, y * cellSize + cellSize / 2, cellSize / 4, 0, 2 * M_PI);
        ctx.call<void>("fill");
    } else if (state == -3) {
        // Draw flag
        ctx.set("fillStyle", "#FF0000");
        ctx.call<void>("beginPath");
        ctx.call<void>("moveTo", x * cellSize + 5, y * cellSize + 5);
        ctx.call<void>("lineTo", x * cellSize + 15, y * cellSize + 10);
        ctx.call<void>("lineTo", x * cellSize + 5, y * cellSize + 15);
        ctx.call<void>("closePath");
        ctx.call<void>("fill");
    }
}