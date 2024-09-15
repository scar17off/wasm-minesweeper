# WebAssembly Minesweeper 💣🕹️

![GitHub](https://img.shields.io/github/license/scar17off/wasm-minesweeper)
![JavaScript](https://img.shields.io/badge/language-JavaScript-yellow)
![Version](https://img.shields.io/badge/version-1.0-blue)
![GitHub stars](https://img.shields.io/github/stars/scar17off/wasm-minesweeper?style=social)
![GitHub forks](https://img.shields.io/github/forks/scar17off/wasm-minesweeper?style=social)
![GitHub issues](https://img.shields.io/github/issues/scar17off/wasm-minesweeper)
![GitHub pull requests](https://img.shields.io/github/issues-pr/scar17off/wasm-minesweeper)
![GitHub last commit](https://img.shields.io/github/last-commit/scar17off/wasm-minesweeper)
![GitHub repo size](https://img.shields.io/github/repo-size/scar17off/wasm-minesweeper)
![GitHub contributors](https://img.shields.io/github/contributors/scar17off/wasm-minesweeper)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/scar17off/wasm-minesweeper)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/scar17off/wasm-minesweeper)

A Minesweeper game implemented in C++ and compiled to WebAssembly for browser play.

## Features 📋

- 30x30 grid with 150 mines 🔢
- Left-click to reveal cells 🖱️
- Right-click to flag potential mines 🚩
- Game over detection 💀
- Win condition check 🏆

## Prerequisites 🛠️

- Emscripten SDK 🔧
- Web browser with WebAssembly support 🌐

## Building 🏗️

Run the build script:

```bash
emcc src/main.cpp src/minesweeper.cpp -o build/output.js -s WASM=1 -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap'] -s EXPORTED_FUNCTIONS=['_main'] -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=1 -s MODULARIZE=1 -s EXPORT_NAME="Module" --bind -std=c++17 -O3
```

## Usage 🚀

1. Build the project using the build script.
2. Open `index.html` in your browser.

## Contributing 🤝

Contributions are welcome! Please feel free to submit a PR.