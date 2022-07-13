#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <iostream>
#include "Vector3.h"
#include "Matrix4.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Material.h"
#include <float.h>
#include <math.h>
#include <vector>


class Drawable
{
    
public:
    
    Matrix4 toWorld;
    Material material;
    
    Drawable(void);
    ~Drawable(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);

	virtual std::vector<Vector3>* getVertices(void);
	virtual std::vector<int>* getIndices(void);
	virtual std::vector<Vector3>* getNormals(void);
	virtual std::vector<int>* getNormIndices(void);
};

#endif
