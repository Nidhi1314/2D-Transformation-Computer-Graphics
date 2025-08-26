# 2D Transformations Visualizer

This project is a simple C++ application that visualizes basic 2D geometric transformations (translation, scaling, rotation, reflection, shearing) on a triangle using the SFML graphics library.

## How to Run

1. **Install SFML**
   - Download and install SFML from [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)
   - Make sure the SFML libraries are available in your compiler's library path.

2. **Compile the Code**
   - Open a terminal in the project directory.
   - Compile using:
     ```sh
     g++ main.cpp -o transforms -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system
     ```

3. **Run the Program**
   - Execute the compiled binary:
     ```sh
     ./transforms
     ```
    

4. **Usage**
   - Enter the coordinates for the three vertices of a triangle.
   - Choose a transformation and provide the required parameters.
   - The original triangle (white) and the transformed triangle (yellow) will be displayed in a window.
   - Close the window to exit.

## Code Overview

- **main.cpp**
  - Defines a `Point` struct for 2D points and a `Viewport` struct for display scaling.
  - Implements transformation functions: `translate`, `scale`, `rotate`, `reflect`, and `shear`.
  - Asks the user for triangle coordinates and transformation choice/parameters.
  - Applies the transformation and visualizes both the original and transformed triangles using SFML.
  - The window shows the original triangle in white and the transformed triangle in yellow.

---

This project is intended for educational purposes to demonstrate basic 2D transformations without using matrices.
