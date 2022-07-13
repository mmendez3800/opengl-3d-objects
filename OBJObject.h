#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Drawable.h"

struct Face
{
    int vertexIndices[3];
    int normalIndices[3];
	int colorIndices[3];
    //Add more members as necessary
};

class OBJObject : public Drawable
{
    
protected:
	bool hasColor;

    //Storage vectors
    std::vector<Vector3> vertices;
    std::vector<Vector3> normals;
	std::vector<Vector3> colors;
    std::vector<Face> faces;
    
	std::vector<Vector3> vertexNormals;
	std::vector<int> indices;
	std::vector<int> normIndices;

    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    
    //Parse
    void parse(std::string&);
    
public:
    
    OBJObject(std::string);
    virtual ~OBJObject(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);

	std::vector<Vector3> * getVertices(void);
	std::vector<int> *  getIndices(void);
	std::vector<Vector3> * getNormals(void);
	std::vector<int> * getNormIndices(void);
};

#endif
