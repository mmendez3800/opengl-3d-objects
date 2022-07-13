# OpenGL 3D Objects
This project implements basic shape and object rendering using OpenGL

## General Info
When the user starts the project, they will be able to perform the below operations through the OpenGL window:
 * r - reset 3D scene
 * x - move object on the x-axis in the negative direction
 * X - move object on the x-axis in the positive direction
 * y - move object on the y-axis in the negative direction
 * Y - move object on the y-axis in the positive direction
 * z - move object on the z-axis in the negative direction
 * Z - move object on the z-axis in the positive direction
 * o - rotate object counterclockwise
 * O - rotabe object clockwise
 * s - zoom in on object
 * S - zoom out on object
 * c - change the spin direction
 * f - show frames-per-second (FPS)
 * e - rasterize image
 * (+) - decrease triangle rasterization count
 * (-) - increase triangle rasterization count
 * d - enable/disable box rasterization display
 * F1 - display box scene
 * F2 - display house scene
 * F3 - display house scene from an angle
 * F4 - display bunny object
 * F5 - display dragon object
 * F6 - display bear object

## Technologies
This project was run using the following:
* Visual Studio 2022
* GLUT 3.7.6

## Setup
After cloning or forking the repository, you can run the project in the below manner:
1. Make a folder called `glut` within the C drive
   - `C:\glut`
2. Download `glut-3.7.6-bin.zip` and extract the contents of the zip file
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
