#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif
#include <iostream>

class stars{
public:
    
    typedef struct star{
        float x, y, z, radius;
    }star;
    
    static std::vector<star> vstar;
    static int starsNum;
    
    stars();
    ~stars();
};

class Planet
{
    typedef struct point
    {
        float x,y,z;
    }point;
    
    typedef struct face
    {
        int vertex[3][2];
    }face;
    
    std::vector<point> v;
    std::vector<point> vn;
    std::vector<face> faces;
    
public:
    
    Planet(std::string);    //create vertices/faces
    ~Planet();  //destroy everything
    void DisplayPlanet();
};

//-------- Functions --------------------------------

void Render();
void Resize(int,int);
void Setup();
void Keyboard(unsigned char,int,int);
void Move(int,int,int);
void Idle();
