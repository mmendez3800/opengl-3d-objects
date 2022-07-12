#ifndef CSE167_House_h
#define CSE167_House_h

#include "Drawable.h"

class House : public Drawable
{
public:

	House();
	virtual ~House(void);

	virtual void draw(DrawData&);

	std::vector<Vector3> * getVertices(void);
	std::vector<int> *  getIndices(void);
	std::vector<Vector3> * getNormals(void);
	std::vector<int> * getNormIndices(void);
};

#endif