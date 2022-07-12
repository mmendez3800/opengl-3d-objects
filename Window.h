#ifndef CSE167_Window_h
#define CSE167_Window_h

#include "Matrix4.h"

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void calculateFPS(void);
	static void moveObject(Matrix4);
	static void scaleObject(Matrix4);
	static void keyboard(unsigned char, int, int);
	static void specialKeyboard(int, int, int);
};

#endif

