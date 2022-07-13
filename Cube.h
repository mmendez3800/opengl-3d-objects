#ifndef CUBE_H
#define CUBE_H

#include "Drawable.h"
#include "Vector3.h"
#include <iostream>
#include <vector>
#include <string>

class Cube : public Drawable
{
    
public:
    
    float size;
    
    Cube(float);
    virtual ~Cube(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
    void spin(float);

	std::vector<Vector3> * getVertices(void);
	std::vector<int> * getIndices(void);
	std::vector<Vector3> * getNormals(void);
	std::vector<int> * getNormIndices(void);
};

#endif

