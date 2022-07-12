#ifndef CSE167_Material_h
#define CSE167_Material_h

#include <iostream>
#include "Color.h"

class Material
{
    
public:
    
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    Color emissionColor;
    
    float shininess;
    
    //A color variable
    Color color;
    
public:
    
    Material(void);
    ~Material(void);
    
    virtual void apply(void);
    
};

#endif
