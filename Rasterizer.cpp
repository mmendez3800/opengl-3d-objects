#include "Rasterizer.h"
#include "Globals.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <ctime>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static float* zbuffer = new float[window_width * window_height];
static float zValue;

Drawable * Rasterizer::toDrawOBJ = &Globals::cube;
int Rasterizer::part = 0;
int Rasterizer::box = 1;

Rasterizer::Rasterizer()
{
	P.makePerspectiveProjection(60.0, (float)window_width, (float)window_height, 1.0, 1000.0);
	D.makeViewport(0.0, (float)window_width, 0.0, (float)window_height);
}


Rasterizer::~Rasterizer()
{
}

/*struct Color    // generic color
{
	float r, g, b;
};*/

void Rasterizer::loadData()
{
	// put code to load data model here
}

// Clear frame buffer
void Rasterizer::clearBuffer()
{
	Color clearColor = { 0.0, 0.0, 0.0 };   // clear color: black
	for (int i = 0; i < window_width * window_height; ++i)
	{
		pixels[i * 3] = clearColor[0];
		pixels[i * 3 + 1] = clearColor[1];
		pixels[i * 3 + 2] = clearColor[2];
		zbuffer[i] = 1.0;
	}
}

// Draw a point into the frame buffer
void Rasterizer::drawPoint(int x, int y, float r, float g, float b)
{
	int offset = y * window_width * 3 + x * 3;

	if (part == 0) {
		pixels[offset] = r;
		pixels[offset + 1] = g;
		pixels[offset + 2] = b;
	}

	if (zValue < zbuffer[y * window_width + x] && zValue > 0) {
		pixels[offset] = r;
		pixels[offset + 1] = g;
		pixels[offset + 2] = b;

		if (part == 2 || part == 3)
			zbuffer[y * window_width + x] = zValue;
	}
}

Vector4 Rasterizer::rasterizeVertex(Vector3 p)
{
	Vector4 p_prime = p.toVector4(1.0);

	p_prime = toDrawOBJ->toWorld * p_prime;
	p_prime = Globals::camera.getInverseMatrix() * p_prime;
	p_prime = P * p_prime;
	p_prime = p_prime.dehomogenize();
	p_prime = D * p_prime;

	return p_prime;
}
bool Rasterizer::baryCoordinates(Vector3 a, Vector3 b, Vector3 c, Vector3 p)
{
	Vector3 v0 = a - p;
	Vector3 v1 = b - p;
	Vector3 v2 = c - p;
	Vector3 v3 = a - b;
	Vector3 v4 = c - b;

	Vector3 Va = v1.cross(v2);
	Vector3 Vb = v2.cross(v0);
	Vector3 Vc = v0.cross(v1);
	Vector3 V = v4.cross(v3);

	float Aa = Va.magnitude() / 2;
	float Ab = Vb.magnitude() / 2;
	float Ac = Vc.magnitude() / 2;
	float A = V.magnitude() / 2;

	alpha = (Aa / A) * (Va.dot(V) / (Va.magnitude() * V.magnitude()));
	beta = (Ab / A) * (Vb.dot(V) / (Vb.magnitude() * V.magnitude()));
	gamma = (Ac / A) * (Vc.dot(V) / (Vc.magnitude() * V.magnitude()));

	zValue = alpha * a[2] + beta * b[2] + gamma * c[2];

	if (alpha >= 0 && beta >= 0 && gamma >= 0 && alpha <= 1 && beta <= 1 && gamma <= 1)
		return true;

	return false;
}

void Rasterizer::drawBox(int xMin, int xMax, int yMin, int yMax)
{
	for (int i = xMin; i <= xMax; i++) {
		drawPoint(i, yMin, 1.0, 0.0, 0.0);
		drawPoint(i, yMax, 1.0, 0.0, 0.0);
	}

	for (int j = yMin; j <= yMax; j++) {
		drawPoint(xMin, j, 1.0, 0.0, 0.0);
		drawPoint(xMax, j, 1.0, 0.0, 0.0);
	}
}

void Rasterizer::rasterizeTriangle(Vector3 x, Vector3 y, Vector3 z)
{
	int minX = min(min(x[0], y[0]), z[0]);
	int minY = min(min(x[1], y[1]), z[1]);
	int maxX = max(max(x[0], y[0]), z[0]);
	int maxY = max(max(x[1], y[1]), z[1]);

	minX = max(minX, 0);
	minX = min(minX, window_width - 1);

	minY = max(minY, 0);
	minY = min(minY, window_height - 1);

	maxX = min(maxX, window_width - 1);
	maxX = max(maxX, 0);

	maxY = min(maxY, window_height - 1);
	maxY = max(maxY, 0);

	if (box == -1)
		drawBox(minX, maxX, minY, maxY);

	float R = (float)(rand()) / (float)(RAND_MAX);
	float G = (float)(rand()) / (float)(RAND_MAX);
	float B = (float)(rand()) / (float)(RAND_MAX);

	for (int i = minX; i <= maxX; i++) {
		for (int j = minY; j <= maxY; j++) {
			Vector3 p(i, j, 0);

			if (baryCoordinates(x, y, z, p)) {
				drawPoint(i, j, R, G, B);
			}
		}
	}
}

void Rasterizer::rasterizeTriangleNormals(Vector3 x, Vector3 y, Vector3 z, Vector3 xn, Vector3 yn, Vector3 zn)
{
	int minX = min(min(x[0], y[0]), z[0]);
	int minY = min(min(x[1], y[1]), z[1]);
	int maxX = max(max(x[0], y[0]), z[0]);
	int maxY = max(max(x[1], y[1]), z[1]);

	minX = max(minX, 0);
	minY = max(minY, 0);

	maxX = min(maxX, window_width - 1);
	maxX = max(maxX, 0);

	maxY = min(maxY, window_height - 1);
	maxY = max(maxY, 0);

	if (box == -1)
		drawBox(minX, maxX, minY, maxY);

	for (int i = minX; i <= maxX; i++) {
		for (int j = minY; j <= maxY; j++) {
			Vector3 p(i, j, 0);

			xn = xn.normalize();
			yn = yn.normalize();
			zn = zn.normalize();

			if (baryCoordinates(x, y, z, p)) {
				Vector3 color(xn.scale(alpha) + yn.scale(beta) + zn.scale(gamma));
				color = color.multiply(0.5);
				color = color.add(Vector3(0.5, 0.5, 0.5));

				drawPoint(i, j, color[0], color[1], color[2]);
			}
		}
	}
}

void Rasterizer::rasterize()
{
	// Put your main rasterization loop here
	// It should go over the data model and call rasterizeTriangle for every triangle in it

	// example: draw diagonal line:

	std::vector<Vector3>* vertex = toDrawOBJ->getVertices();
	std::vector<int>* index = toDrawOBJ->getIndices();
	std::vector<int>::iterator it = index->begin();

	std::vector<Vector3>* normal = toDrawOBJ->getNormals();
	std::vector<int>* normIndex = toDrawOBJ->getNormIndices();
	std::vector<int>::iterator itn = normIndex->begin();

	if (part == 0) {
		for (; it != index->end(); ++it) {
			Vector4 p = rasterizeVertex(vertex->at(*it));
			if (checkBoundary(p))
			{
				drawPoint((int)p[0], (int)p[1], 1.0, 1.0, 1.0);
			}
		}
	}

	else {
		while (it != index->end()) {
			Vector4 a = rasterizeVertex(vertex->at(*it++));
			Vector4 b = rasterizeVertex(vertex->at(*it++));
			Vector4 c = rasterizeVertex(vertex->at(*it++));

			if (part == 3) {
				int a_itn = *itn++;
				int b_itn = *itn++;
				int c_itn = *itn++;

				rasterizeTriangleNormals(a.toVector3(), b.toVector3(), c.toVector3(), normal->at(a_itn), normal->at(b_itn), normal->at(c_itn));
			}

			else {
				rasterizeTriangle(a.toVector3(), b.toVector3(), c.toVector3());
			}
		}
	}
}

bool Rasterizer::checkBoundary(Vector4 p)
{
	return !(p[0] < 0 || p[1] < 0 || p[0] >= window_width || p[1] >= window_height);
}

// Called whenever the window size changes
void Rasterizer::reshape(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;
	delete[] pixels;
	pixels = new float[window_width * window_height * 3];
	zbuffer = new float[window_width * window_height];

	P.makePerspectiveProjection(60.0, (float)new_width, (float)new_height, 1.0, 1000.0);
	D.makeViewport(0.0, (float)new_width, 0.0, (float)new_height);
}

void Rasterizer::keyboard(unsigned char key, int, int)
{
	std::cerr << "Key pressed: " << key << std::endl;
}

void Rasterizer::display()
{
	srand(1);

	clearBuffer();
	rasterize();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

	glutSwapBuffers();
}

/*int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("CSE 167 Project 3");

	loadData();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutMainLoop();
}*/