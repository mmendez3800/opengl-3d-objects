#ifndef CSE167_Rasterizer_h
#define CSE167_Rasterizer_h

#include "Matrix4.h"
#include "Drawable.h"
#include "Vector3.h"
#include "Vector4.h"
#include "OBJObject.h"

class Rasterizer
{

protected:
	Matrix4 P;
	Matrix4 D;

public:
	static Drawable * toDrawOBJ;
	static int part;
	static int box;

	float alpha, beta, gamma;

	Rasterizer();
	~Rasterizer();

	void loadData();
	void clearBuffer();
	void drawPoint(int, int, float, float, float);

	Vector4 rasterizeVertex(Vector3);
	bool baryCoordinates(Vector3, Vector3, Vector3, Vector3);
	void drawBox(int, int, int, int);
	void rasterizeTriangle(Vector3, Vector3, Vector3);
	void rasterizeTriangleNormals(Vector3, Vector3, Vector3, Vector3, Vector3, Vector3);
	void rasterize();
	bool checkBoundary(Vector4);
	void reshape(int, int);

	void keyboard(unsigned char, int, int);
	void display();
};

#endif