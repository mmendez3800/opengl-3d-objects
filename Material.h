#ifndef MATERIAL_H
#define MATERIAL_H

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
