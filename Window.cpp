#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include "math.h"

#include "Window.h"
#include "House.h"
#include "Cube.h"
#include "OBJObject.h"
#include "Matrix4.h"
#include "Globals.h"
#include "Rasterizer.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

float spinDirection = 1;    //Changes the direction of the cube
int flag = 0;               //Indicates when to switch from cube to house
int rendering = 1;          //Indicates which rendering engine to use

int frame = 0, gtime = 0, timebase = 0, showFPS = 1;   //Used in calculating frame rate
float fps = 0;							  //Used in calculating frame rate

void Window::initialize(void)
{
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.02;
    
    //Initialize cube matrix:
    Globals::cube.toWorld.identity();
    
    //Setup the cube's material properties
    Color color(0x23ff27ff);
    Globals::cube.material.color = color;
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
	//Calculates the frame rate of an object 
	calculateFPS();

    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //Rotate cube; if it spins too fast try smaller values and vice versa
    Globals::cube.spin(spinDirection * 0.0005);
    
    //Call the update function on cube
    Globals::cube.update(Globals::updateData);
    
    //Call the display routine to draw the cube
	if (rendering == -1) {
		Globals::rasterizer.display();
	}
	else {
		displayCallback();
	}
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum

	Globals::rasterizer.reshape(w, h);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	Globals::camera.update();

    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);
    
    //Draw cube or house
	switch (flag) {
	case 0:
		Globals::cube.draw(Globals::drawData);
		break;

	case 1:
		Globals::house.draw(Globals::drawData);
		break;

	case 2:
		Globals::bunny.draw(Globals::drawData);
		break;

	case 3:
		Globals::dragon.draw(Globals::drawData);
		break;

	case 4:
		Globals::bear.draw(Globals::drawData);
		break;
	}
    
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}

//Calculates frame rate of object in Window
void Window::calculateFPS()
{
	//  Increase frame count
	frame++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	gtime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = gtime - timebase;

	if (timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frame / (timeInterval / 1000.0f);

		//  Set time
		timebase = gtime;

		//  Reset frame count
		frame = 0;
	}

	if (showFPS == -1)
		std::cout << "FPS: " << fps << std::endl;
}

//TODO: Keyboard callbacks!
void Window::keyboard(unsigned char key, int x, int y) {
	Matrix4 trans;

	switch (key) {
	case 'c':
		if (flag == 0)
			spinDirection = -spinDirection;

		break;

	case 'x':
		trans.makeTranslate(-1, 0, 0);
		moveObject(trans);
		break;

	case 'X':
		trans.makeTranslate(1, 0, 0);
		moveObject(trans);
		break;

	case 'y':
		trans.makeTranslate(0, -1, 0);
		moveObject(trans);
		break;

	case 'Y':
		trans.makeTranslate(0, 1, 0);
		moveObject(trans);
		break;

	case 'z':
		trans.makeTranslate(0, 0, -1);
		moveObject(trans);
		break;

	case 'Z':
		trans.makeTranslate(0, 0, 1);
		moveObject(trans);
		break;

	case 'r':
		switch (flag) {
		case 0:
			Globals::cube.toWorld.identity();
			spinDirection = 1;
			break;

		case 2:
			Globals::bunny.toWorld.identity();
			break;

		case 3:
			Globals::dragon.toWorld.identity();
			break;

		case 4:
			Globals::bear.toWorld.identity();
			break;
		}

		break;

	case 'o':
		trans.makeRotateZ(10 * M_PI / 180);
		moveObject(trans);
		break;

	case 'O':
		trans.makeRotateZ(-10 * M_PI / 180);
		moveObject(trans);
		break;

	case 's':
		trans.makeScale(.9);
		scaleObject(trans);
		break;

	case 'S':
		trans.makeScale(1.1);
		scaleObject(trans);
		break;

	case 'e':
		rendering = -rendering;
		break;

	case '+':
		if (rendering == -1 && Globals::rasterizer.part < 3)
			Globals::rasterizer.part++;

		break;

	case '-':
		if (rendering == -1 && Globals::rasterizer.part > 0)
			Globals::rasterizer.part--;
		
		break;

	case 'd':
		if (rendering == -1 && Globals::rasterizer.part != 0)
			Globals::rasterizer.box = -Globals::rasterizer.box;

		break;

	case 'f':
		showFPS = -showFPS;
		break;
	}

	if (flag == 0) {
		Vector3 position(Globals::cube.toWorld.get(3, 0), Globals::cube.toWorld.get(3, 1),
			Globals::cube.toWorld.get(3, 2));

		position.print("Position of Cube");
	}
}

//Moves the object in Window depeding on which key is pressed
void Window::moveObject(Matrix4 translate) {
	switch (flag) {
	case 0:
		Globals::cube.toWorld = translate * Globals::cube.toWorld;
		break;

	case 2:
		Globals::bunny.toWorld = translate * Globals::bunny.toWorld;
		break;

	case 3:
		Globals::dragon.toWorld = translate * Globals::dragon.toWorld;
		break;

	case 4:
		Globals::bear.toWorld = translate * Globals::bear.toWorld;
		break;
	}
}

//Scales the object in Window
void Window::scaleObject(Matrix4 scale) {
	switch (flag) {
	case 0:
		Globals::cube.toWorld = Globals::cube.toWorld * scale;
		break;

	case 2:
		Globals::bunny.toWorld = Globals::bunny.toWorld * scale;
		break;

	case 3:
		Globals::dragon.toWorld = Globals::dragon.toWorld * scale;
		break;

	case 4:
		Globals::bear.toWorld = Globals::bear.toWorld * scale;
		break;
	}
}

//TODO: Function Key callbacks!
void Window::specialKeyboard(int key, int x, int y) {
	Vector3 e, d, up;

	switch (key) {
	case GLUT_KEY_F1:
		e.set(0.0, 0.0, 20.0);
		d.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		Globals::camera.set(e, d, up);
		flag = 0;
		Globals::rasterizer.toDrawOBJ = &Globals::cube;
		break;

	case GLUT_KEY_F2:
		e.set(0.0, 24.14, 24.14);
		d.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		Globals::camera.set(e, d, up);
		flag = 1;
		Globals::rasterizer.toDrawOBJ = &Globals::house;
		break;

	case GLUT_KEY_F3:
		e.set(-28.33, 11.66, 23.33);
		d.set(-5.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.5);
		Globals::camera.set(e, d, up);
		flag = 1;
		Globals::rasterizer.toDrawOBJ = &Globals::house;
		break;

	case GLUT_KEY_F4:
		e.set(0.0, 0.0, 20.0);
		d.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		Globals::camera.set(e, d, up);
		flag = 2;
		Globals::rasterizer.toDrawOBJ = &Globals::bunny;
		break;

	case GLUT_KEY_F5:
		e.set(0.0, 0.0, 20.0);
		d.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		Globals::camera.set(e, d, up);
		flag = 3;
		Globals::rasterizer.toDrawOBJ = &Globals::dragon;
		break;

	case GLUT_KEY_F6:
		e.set(0.0, 0.0, 20.0);
		d.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		Globals::camera.set(e, d, up);
		flag = 4;
		Globals::rasterizer.toDrawOBJ = &Globals::bear;
		break;
	}
}
//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!
