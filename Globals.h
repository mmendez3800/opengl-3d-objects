#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "House.h"
#include "Cube.h"
#include "OBJObject.h"
#include "Rasterizer.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"

class Globals
{
    
public:
    
    static Camera camera;

	static House house;

    static Cube cube;

	static OBJObject bunny, dragon, bear;

	static Rasterizer rasterizer;

    static Light light;

    static DrawData drawData;
    static UpdateData updateData;
    //Feel free to add more member variables as needed
    
};

#endif
