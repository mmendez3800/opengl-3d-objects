#include "OBJObject.h"

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

#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)


OBJObject::OBJObject(std::string filename) : Drawable()
{
    /*this->vertices = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
	this->colors = new std::vector<Vector3*>();
    this->faces = new std::vector<Face*>();*/
    
    parse(filename);
}

OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    
    /*deleteVector(Vector3*, vertices);
    deleteVector(Vector3*, normals);
	deleteVector(Vector3*, colors);
    deleteVector(Face*, faces);*/
}

void OBJObject::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_TRIANGLES);
    
    //Loop through the faces
    //For each face:
    //  Look up the vertices, normals (if they exist), and texcoords (if they exist)
    //  Draw them as triplets:
	for (unsigned int i = 0; i < faces.size(); i++) {
		Face face = faces.at(i);

		for (int j = 0; j < 3; j++) {
			glNormal3fv((normals.at(face.normalIndices[j] - 1)).ptr());

			if (hasColor) {
				glColor3fv((colors.at(face.colorIndices[j] - 1)).ptr());
			}

			else {
				glColor3f(0.75, 0.75, 0.75);
			}

			glVertex3fv((vertices.at(face.vertexIndices[j] - 1)).ptr());
		}
	}
    
    glEnd();
    
    glPopMatrix();
}

void OBJObject::update(UpdateData& data)
{
    //
}

void OBJObject::parse(std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens, f_1, f_2, f_3;
    std::string token;
    
    int lineNum = 0;
    
    
    std::cout << "Starting parse..." << std::endl;
    
    //While all your lines are belong to us
    while (std::getline(infile, line))
    {
        //Progress
        if(++lineNum % 10000 == 0)
            std::cout << "At line " << lineNum << std::endl;
        
        //Split a line into tokens by delimiting it on spaces
        //"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
        tokens.clear();
        tokens = split(line, ' ', tokens);
        
		if (tokens.empty()){
			continue;
		}
        //If first token is a v then it gots to be a vertex
        if (tokens.at(0).compare("v") == 0)
        {
			hasColor = false;

            //Parse the vertex line
            float x = std::stof(tokens.at(1));
            float y = std::stof(tokens.at(2));
            float z = std::stof(tokens.at(3));
            
            vertices.push_back(Vector3(x, y, z));

			if (tokens.size() > 4) {
				hasColor = true;

				float r = std::stof(tokens.at(4));
				float g = std::stof(tokens.at(5));
				float b = std::stof(tokens.at(6));

				colors.push_back(Vector3(r, g, b));
			}
        }
        else if(tokens.at(0).compare("vn") == 0)
        {
            //Parse the normal line
			float xn = std::stof(tokens.at(1));
			float yn = std::stof(tokens.at(2));
			float zn = std::stof(tokens.at(3));

			Vector3 norm = Vector3(xn, yn, zn);
			vertexNormals.push_back(norm);

			norm = norm.normalize();
			normals.push_back(norm);
        }
        else if(tokens.at(0).compare("f") == 0)
        {
            Face face;
            
            //Parse the face line
			f_1.clear();
			f_2.clear();
			f_3.clear();

			f_1 = split(tokens.at(1), '/', f_1);
			f_2 = split(tokens.at(2), '/', f_2);
			f_3 = split(tokens.at(3), '/', f_3);

			face.vertexIndices[0] = std::stof(f_1.at(0));
			face.colorIndices[0] = std::stof(f_1.at(0));
			face.normalIndices[0] = std::stof(f_1.at(2));

			face.vertexIndices[1] = std::stof(f_2.at(0));
			face.colorIndices[1] = std::stof(f_1.at(0));
			face.normalIndices[1] = std::stof(f_2.at(2));

			face.vertexIndices[2] = std::stof(f_3.at(0));
			face.colorIndices[2] = std::stof(f_1.at(0));
			face.normalIndices[2] = std::stof(f_3.at(2));
            
            faces.push_back(face);

			indices.push_back(face.vertexIndices[0] - 1);
			indices.push_back(face.vertexIndices[1] - 1);
			indices.push_back(face.vertexIndices[2] - 1);

			normIndices.push_back(face.normalIndices[0] - 1);
			normIndices.push_back(face.normalIndices[1] - 1);
			normIndices.push_back(face.normalIndices[2] - 1);
        }

		else if(tokens.at(0).compare("#") == 0)
        {
            //See the Wavefront Object format specification for details
			continue;
        }
        
    }
    
    std::cout << "Done parsing." << std::endl;
}

std::vector<Vector3>* OBJObject::getVertices()
{
	return &vertices;
}

std::vector<int>* OBJObject::getIndices()
{
	return &indices;
}

std::vector<Vector3>* OBJObject::getNormals()
{
	return &vertexNormals;
}

std::vector<int>* OBJObject::getNormIndices()
{
	return &normIndices;
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
