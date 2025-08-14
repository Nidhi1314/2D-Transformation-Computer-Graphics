


# Computer Graphics Lab Assignment: 2D Transformations

## 📁 Folder Contents

- `src/transformations_with_graphics.c`  
   This program shows 2D transformations (like translation, scaling, rotation, reflection, and shearing) on a triangle using graphics. You’ll see the original and transformed triangle in a graphics window.  
   **Needs WinBGIm setup (`graphics.h`, `winbgim.h`, `libbgi.a`) to run.**

- `src/transformations.c`  
   This is a simple C program that does the same transformations, but only prints the new coordinates in the console.  
   **No graphics needed!**

- `include/graphics.h`, `include/winbgim.h`, `lib/libbgi.a`  
   These files are only needed if you want to run the graphics version.

---

## 🚀 How to Run

### 1. To run the graphics version (`transformations_with_graphics.c`):
1. Copy `graphics.h` and `winbgim.h` to your compiler’s `include` folder (like `C:/MinGW/include`).
2. Copy `libbgi.a` to your compiler’s `lib` folder (like `C:/MinGW/lib`).
3. Open `src/transformations_with_graphics.c` in Code::Blocks or any C IDE.
4. In your project’s linker settings, add:
    ```
    -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
    ```
5. Build and run. You’ll get a graphics window showing both triangles.

> **If you get errors about missing types or C++ headers, your WinBGIm might not be fully C-compatible. Try a different version or ask your teacher for help.**

### 2. To run the console version (`transformations.c`):
1. Open `src/transformations.c` in any C IDE or just use GCC.
2. Build and run the program.
3. Enter the triangle’s coordinates and pick a transformation. The new coordinates will print in the console.

---

## ℹ️ Notes
- The graphics version needs WinBGIm and a C-compatible setup.
- The console version is pure C and works anywhere—no graphics needed.



