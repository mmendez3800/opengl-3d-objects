# OpenGL 3D Scenes
This project implements basic shape and object rendering using OpenGL

## General Info

## Technologies
This project was run using the following:
* Visual Studio 2022
* GLUT 3.7.6

## Setup
After cloning or forking the repository, you can run the project in the below manner:
1. Make a folder called `glut` within the C drive
  - `C:\glut`
2. Download `glut-3.7.6-bin.zip` and extract the contents of the zip fie
3. Place the folder `glut-3.7.6-bin` into `C:\glut`
  - Verify that you see the following five files: `glut.def`, `glut.h`, `glut32.dll`, `glut32.lib`, `README-win32.txt`
4. Move `glut32.dll` to `C:\Windows\System32` or `C:\Windows\SysWOW64` (depending on your operating system)
5. Create a new directory under `C:\glut\glut-3.7.6-bin` and name it `GL`
6. Move `glut.h` to `C:\glut\glut-3.7.6-bin\GL`
7. Double click file `Cube.sln` to open Visual Studio
8. Go to the Solution Explorer window and right-click **Cube** (not **Solution 'Cube'**)
9. Select **Properties** and left-click **C/C++**
10. At **Additional Include Directories**, add `C:\glut\glut-3.7.6-bin`
11. Left-click **Linker**
12. At **Additional Library Directories** add `C:\glut\glut-3.7.6-bin`

## Execution
If seup is completed successfully, simply build the project by either clicking the green **Start** button
* You can also press **F5** or **Ctrl + F5**
