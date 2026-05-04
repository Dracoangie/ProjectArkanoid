# Project Arkanoid

A classic Arkanoid implementation developed in **C++** using the **SDL2** library. This project focuses on a clean, object-oriented architecture and efficient memory management.

## Features
*   **Scene System:** Independent management for menus, game levels, and transitions.
*   **Entity Component Logic:** Robust base for game objects with a full lifecycle: `start`, `update`, and `render`.
*   **Memory Optimization:** Strict use of `std::unique_ptr` to prevent memory leaks and static members for shared texture management.
*   **Brick Pooling:** Pre-instantiated brick repository to optimize performance and reduce runtime allocations.
*   **Data-Driven Levels:** Level layouts loaded from matrices, allowing for easy map creation without modifying the source code.

## Setup and Execution
1.  **Environment:** Designed for **Visual Studio 2022 (x64)**.
2.  **Dependencies:** SDL2 and SDL2_image (included in the `external/` folder for immediate compilation).
3.  **Compilation:**
    *   Open `ProjectArkanoid.sln`.
    *   Set configuration to `x64` (Debug or Release).
    *   Press `F5` to build and run.

## Project Structure
*   `src/`: Source code files.
*   `include/`: Header files.
*   `assets/`: Visual game resources (textures, etc.).
*   `external/`: Third-party libraries and headers.

## Author
*   **Dracoangie** - [GitHub](https://github.com/Dracoangie)