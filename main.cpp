#include "visuals.h"


int main(int argc, char* argv[])
{
    glutInit(&argc, const_cast<char**>(argv));
    stars s;
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    
    
    glutInitWindowSize(800,800);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2,(glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
    
    glutCreateWindow("Solar System");
    
    Setup();
    
    glutReshapeFunc(Resize);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Move);
    glutDisplayFunc(Render);
    glutIdleFunc(Idle);
    glViewport(0, 0, 800, 800);
    
   
    //Enter main event handling loop
    glutMainLoop();
    return 0;	
}  
