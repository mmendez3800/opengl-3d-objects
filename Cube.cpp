#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>
#include <cstring>

std::vector<Vector3> vertices;
std::vector<int> indices;

std::vector<Vector3> normals;
std::vector<int> normIndices;

Cube::Cube(float size) : Drawable()
{
    this->size = size;
	float halfSize = size / 2.0;

	vertices.push_back(Vector3(-halfSize, halfSize, halfSize));
	vertices.push_back(Vector3(halfSize, halfSize, halfSize));
	vertices.push_back(Vector3(halfSize, -halfSize, halfSize));
	vertices.push_back(Vector3(-halfSize, -halfSize, halfSize));
	vertices.push_back(Vector3(-halfSize, halfSize, -halfSize));
	vertices.push_back(Vector3(-halfSize, -halfSize, -halfSize));
	vertices.push_back(Vector3(halfSize, halfSize, -halfSize));
	vertices.push_back(Vector3(halfSize, -halfSize, -halfSize));

	normals.push_back(Vector3(0.0, 0.0, 1.0));
	normals.push_back(Vector3(-1.0, 0.0, 0.0));
	normals.push_back(Vector3(1.0, 0.0, 0.0));
	normals.push_back(Vector3(0.0, 0.0, -1.0));
	normals.push_back(Vector3(0.0, 1.0, 0.0));
	normals.push_back(Vector3(0.0, -1.0, 0.0));

	//Front face
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	normIndices.push_back(0);
	normIndices.push_back(0);
	normIndices.push_back(0);
	normIndices.push_back(0);
	normIndices.push_back(0);
	normIndices.push_back(0);

	//Left side
	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(3);

	normIndices.push_back(1);
	normIndices.push_back(1);
	normIndices.push_back(1);
	normIndices.push_back(1);
	normIndices.push_back(1);
	normIndices.push_back(1);

	//Right side
	indices.push_back(1);
	indices.push_back(7);
	indices.push_back(6);
	indices.push_back(1);
	indices.push_back(7);
	indices.push_back(2);

	normIndices.push_back(2);
	normIndices.push_back(2);
	normIndices.push_back(2);
	normIndices.push_back(2);
	normIndices.push_back(2);
	normIndices.push_back(2);

	//Back face
	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(6);
	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(5);

	normIndices.push_back(3);
	normIndices.push_back(3);
	normIndices.push_back(3);
	normIndices.push_back(3);
	normIndices.push_back(3);
	normIndices.push_back(3);

	//Top side
	indices.push_back(0);
	indices.push_back(6);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(6);
	indices.push_back(4);

	normIndices.push_back(4);
	normIndices.push_back(4);
	normIndices.push_back(4);
	normIndices.push_back(4);
	normIndices.push_back(4);
	normIndices.push_back(4);

	//Bottom side
	indices.push_back(5);
	indices.push_back(2);
	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(2);
	indices.push_back(3);

	normIndices.push_back(5);
	normIndices.push_back(5);
	normIndices.push_back(5);
	normIndices.push_back(5);
	normIndices.push_back(5);
	normIndices.push_back(5);
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}


void Cube::draw(DrawData& data)
{
    float halfSize = size/2.0;
    
    //Apply the material properties
    //From here forward anything drawn will be drawn with this material
    material.apply();
    
    //Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    //Make cube!
    glBegin(GL_QUADS);
    
    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);

    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);

    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);

    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);

    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);

    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);

    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);

    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);

    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);

    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);

    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);

    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);

    glEnd();
    
    //The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
    //glutSolidCube(size);
    
    //Pop the save state off the matrix stack
    //This will undo the multiply we did earlier
    glPopMatrix();
}


void Cube::update(UpdateData& data)
{
    //
}

void Cube::spin(float radians)
{
    Matrix4 rotation;
    rotation.makeRotateY(radians);
    
    toWorld = toWorld * rotation;
}

std::vector<Vector3>* Cube::getVertices()
{
	return &vertices;
}

std::vector<int>* Cube::getIndices()
{
	return &indices;
}

std::vector<Vector3>* Cube::getNormals()
{
	return &normals;
}

std::vector<int>* Cube::getNormIndices()
{
	return &normIndices;
}