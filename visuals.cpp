#include "visuals.h"

int stars::starsNum;
std::vector<stars::star> stars::vstar;
Planet planetobj("planet.obj");
bool rise = true,stop = false;
float angleX = 0.0,angleY = 0.0;
int rotateX,rotateY;
float zoom = 0.5f;
float opacity = 0.2;
float rotation[4] = {0,0,0,360};

stars::stars(){
    starsNum = 1000;
    for(int i = 0; i < starsNum;i++)
    {
        star s;
        s.x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1000))-500;
        s.y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1000))-500;
        s.z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1000))-500;
        s.radius = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.8));
        vstar.push_back(s);
    }
}

stars::~stars(){
    
    vstar.clear();
}

Planet::Planet(std::string filename)
{
    std::fstream fplanet(filename);
    std::string line;
    char fx[20],fy[20],fz[20],*token;
    float x,y,z;
    //read v,vn,f
    while(getline(fplanet,line))
    {
        switch (line[0]){
            case '#':
                continue;
            case 'v':
            {
                std::istringstream iss(&line[2]);
                while(iss >> x >> y >> z)
                {
                    Planet::point p;
                    p.x = x;
                    p.y = y;
                    p.z = z;
                    if (line[1] == ' ')
                        this->v.emplace_back(p);
                    else
                        this->vn.emplace_back(p);
                }
                iss.str("");
                break;
            }
            case 'f':
            {
                Planet::face f;
                std::istringstream iss(&line[2]);
                while(iss >> fx >> fy >> fz)
                {
                    token = strtok(fx,"//");
                    f.vertex[0][0] = atoi(token);
                    f.vertex[0][1] = atoi(strtok(NULL,"//"));
                    token = strtok(fy,"//");
                    f.vertex[1][0] = atoi(token);
                    f.vertex[1][1] = atoi(strtok(NULL,"//"));
                    token = strtok(fz,"//");
                    f.vertex[2][0] = atoi(token);
                    f.vertex[2][1] = atoi(strtok(NULL,"//"));
                    this->faces.emplace_back(f);
                }
                iss.str("");
                break;
            }
            default:
                break;
        }
    }
}

void Planet::DisplayPlanet()
{
    //Planet Mars
    glPushMatrix();
    glColor3f(0.6, 0.223,0.3);
    glTranslatef(0,0, -200);
    glRotatef(rotation[0], 0.0, 1.0, 0.0);
    glTranslatef(50,0, 0);
    glScalef(0.02f,0.02f,0.02f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < planetobj.faces.size(); i++)
    {
        glVertex3f(planetobj.v[faces[i].vertex[0][0]-1].x,planetobj.v[faces[i].vertex[0][0]-1].y,planetobj.v[faces[i].vertex[0][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[0][1]-1].x,planetobj.vn[faces[i].vertex[0][1]-1].y,planetobj.vn[faces[i].vertex[0][1]-1].z);
        glVertex3f(planetobj.v[faces[i].vertex[1][0]-1].x,planetobj.v[faces[i].vertex[1][0]-1].y,planetobj.v[faces[i].vertex[1][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[1][1]-1].x,planetobj.vn[faces[i].vertex[1][1]-1].y,planetobj.vn[faces[i].vertex[1][1]-1].z);
        glVertex3f(planetobj.v[faces[i].vertex[2][0]-1].x,planetobj.v[faces[i].vertex[2][0]-1].y,planetobj.v[faces[i].vertex[2][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[2][1]-1].x,planetobj.vn[faces[i].vertex[2][1]-1].y,planetobj.vn[faces[i].vertex[2][1]-1].z);
    }
    glEnd();
    glPopMatrix();
    
    //Planet Venus
    glPushMatrix();
    glColor3f(0, 0.223,0.3);
    glTranslatef(0,0, -200.0);
    glRotatef(rotation[1], 0.0, 1.0, 0.0);
    glTranslatef(100,0, 0.0);
    glScalef(0.02f,0.02f,0.02f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < planetobj.faces.size(); i++)
    {
        glVertex3f(planetobj.v[faces[i].vertex[0][0]-1].x,planetobj.v[faces[i].vertex[0][0]-1].y,planetobj.v[faces[i].vertex[0][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[0][1]-1].x,planetobj.vn[faces[i].vertex[0][1]-1].y,planetobj.vn[faces[i].vertex[0][1]-1].z);
        glVertex3f(planetobj.v[faces[i].vertex[1][0]-1].x,planetobj.v[faces[i].vertex[1][0]-1].y,planetobj.v[faces[i].vertex[1][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[1][1]-1].x,planetobj.vn[faces[i].vertex[1][1]-1].y,planetobj.vn[faces[i].vertex[1][1]-1].z);
        glVertex3f(planetobj.v[faces[i].vertex[2][0]-1].x,planetobj.v[faces[i].vertex[2][0]-1].y,planetobj.v[faces[i].vertex[2][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[2][1]-1].x,planetobj.vn[faces[i].vertex[2][1]-1].y,planetobj.vn[faces[i].vertex[2][1]-1].z);
    }
    glEnd();
    glPopMatrix();
    
    //Planet Earth
    glPushMatrix();
    glColor3f(0.25, 0.1,0.5);
    glTranslatef(0,0, -200.0);
    glRotatef(rotation[2], 1.0, 0.0, 0.0);
    glTranslatef(0,75, 0.0);
    glScalef(0.02f,0.02f,0.02f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < planetobj.faces.size(); i++)
    {
        glVertex3f(planetobj.v[faces[i].vertex[0][0]-1].x,planetobj.v[faces[i].vertex[0][0]-1].y,planetobj.v[faces[i].vertex[0][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[0][1]-1].x,planetobj.vn[faces[i].vertex[0][1]-1].y,planetobj.vn[faces[i].vertex[0][1]-1].z);
        glVertex3f(planetobj.v[faces[i].vertex[1][0]-1].x,planetobj.v[faces[i].vertex[1][0]-1].y,planetobj.v[faces[i].vertex[1][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[1][1]-1].x,planetobj.vn[faces[i].vertex[1][1]-1].y,planetobj.vn[faces[i].vertex[1][1]-1].z);
        glVertex3f(planetobj.v[faces[i].vertex[2][0]-1].x,planetobj.v[faces[i].vertex[2][0]-1].y,planetobj.v[faces[i].vertex[2][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[2][1]-1].x,planetobj.vn[faces[i].vertex[2][1]-1].y,planetobj.vn[faces[i].vertex[2][1]-1].z);
    }
    glEnd();
    glPopMatrix();
    
    //Planet Pluto
    glPushMatrix();
    glColor3f(1.0, 0.0,0.0);
    glTranslatef(0,0, -200.0);
    glRotatef(rotation[3], 1.0, 0.0, 0.0);
    glTranslatef(0,125, 0.0);
    glScalef(0.015f,0.015f,0.015f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < planetobj.faces.size(); i++)
    {
        glVertex3f(planetobj.v[faces[i].vertex[0][0]-1].x,planetobj.v[faces[i].vertex[0][0]-1].y,planetobj.v[faces[i].vertex[0][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[0][1]-1].x,planetobj.vn[faces[i].vertex[0][1]-1].y,planetobj.vn[faces[i].vertex[0][1]-1].z);
        glVertex3f(planetobj.v[faces[i].vertex[1][0]-1].x,planetobj.v[faces[i].vertex[1][0]-1].y,planetobj.v[faces[i].vertex[1][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[1][1]-1].x,planetobj.vn[faces[i].vertex[1][1]-1].y,planetobj.vn[faces[i].vertex[1][1]-1].z);
        glVertex3f(planetobj.v[faces[i].vertex[2][0]-1].x,planetobj.v[faces[i].vertex[2][0]-1].y,planetobj.v[faces[i].vertex[2][0]-1].z);
        glNormal3f(planetobj.vn[faces[i].vertex[2][1]-1].x,planetobj.vn[faces[i].vertex[2][1]-1].y,planetobj.vn[faces[i].vertex[2][1]-1].z);
    }
    glEnd();
    glPopMatrix();
}


Planet::~Planet()
{
    this->v.clear();
    this->vn.clear();
    this->faces.clear();
}

//function for setting the sun in the centre of our "universe"
void setSun()
{
    glPushMatrix();
    glTranslatef(0, 0, -200);
    glColor3f( 0.255, 0.255, 0.0);
    glutSolidSphere(20.0, 30.0, 30.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0, -200);
    glColor4f(0.255, 0.255, 0.0, opacity);
    glutSolidSphere(25.0, 30.0, 30.0);
    glPopMatrix();
}

//function for setting stars in our "universe"
void setStars()
{
    for (int i = 0 ; i < stars::starsNum;i++)
    {
        glPushMatrix();
        glTranslatef(stars::vstar[i].x,stars::vstar[i].y,stars::vstar[i].z);
        glColor3f( 1, 1, 1);
        glutSolidSphere(stars::vstar[i].radius, 30.0, 30.0);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(stars::vstar[i].x,stars::vstar[i].y, stars::vstar[i].z);
        glColor4f(1, 1, 1, opacity);
        glutSolidSphere(stars::vstar[i].radius+0.3, 30.0, 30.0);
        glPopMatrix();
    }
}

void Render()
{
    glEnable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -200);
    glScalef(zoom,zoom,zoom);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glTranslatef(0, 0, 200);
    
    setSun();
    setStars();
    planetobj.DisplayPlanet();
    glutSwapBuffers();
    glFlush();
}

void Keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 'q' : exit(0);
            break;
        case ' ' :
            if (stop)
                stop = false;
            else
                stop = true;
            break;
        case '+' :
            if (zoom < 0.95)
                zoom += 0.01;
            break;
        case '-' :
            if (zoom > 0.26)
                zoom -= 0.01;
            break;
        default : break;
    }
    glutPostRedisplay();
}



void Move(int key,int x,int y)
{
    glutIgnoreKeyRepeat(false);
    switch(key)
    {
        case GLUT_KEY_RIGHT:
        {
            angleY -= 2;
            rotateX = 0;
            rotateY = 1;
            break;
        }
        case GLUT_KEY_LEFT:  {
            angleY += 2;
            rotateX = 0;
            rotateY = 1;
            break;
        }
        case GLUT_KEY_UP:    {
            angleX += 2;
            rotateX = 1;
            rotateY = 0;
            break;
        }
        case GLUT_KEY_DOWN:  {
            angleX -= 2;
            rotateX = 1;
            rotateY = 0;
            break;
        }
    }
    glutPostRedisplay();
}


void Idle()
{
    //opacity change
    if (!stop)
    {
        if (rise)
        {
            if (opacity < 1)
                opacity += 0.01;
            else
            {
                opacity -= 0.01;
                rise = false;
            }
        }
        else
        {
            if (opacity > 0.2)
                opacity -= 0.01;
            else
            {
                opacity += 0.01;
                rise = true;
            }
        }
        //Planet Positions
        for (int i = 0 ; i < 3; i++)
        {
            rotation[i] += 0.5*(i+1);
            if(rotation[i]>360.0)
                rotation[i]-=360.0;
            if(rotation[i]<0.0)
                rotation[i]+=360.0;
        }
        rotation[3] -= 0.75;
        if(rotation[3]>360.0)
            rotation[3]-=360.0;
        if(rotation[3]<0.0)
            rotation[3]+=360.0;
    }
    glutPostRedisplay();
}

void Resize(int w, int h)
{
    if (h==0) h=1;
    glViewport(0,0,w,h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    
    float aspect = (float)w/(float)h;             /// aspect ratio
    gluPerspective(60.0, aspect, 1.0, 500.0);
}

void Setup()
{
    
    glShadeModel (GL_SMOOTH);
    glEnable(GL_RESCALE_NORMAL);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    glEnable(GL_NORMALIZE);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    
    GLfloat light_position[] = { 0.0, 0.0, 50.0, 0.0 };
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    
    GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
    
	   
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
    
    glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
    GLfloat specref[4];
    specref[0] = 0.247; specref[1] = 0.225; specref[2] = 0.065; specref[3] = 1.0;
    glMaterialfv(GL_FRONT,GL_AMBIENT,specref);
    specref[0] = 0.346; specref[1] = 0.314; specref[2] = 0.090; specref[3] = 1.0;
    glMaterialfv(GL_FRONT,GL_DIFFUSE,specref);
    specref[0] = 0.797; specref[1] = 0.724; specref[2] = 0.208; specref[3] = 1.0;
    glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
    
    glMaterialf(GL_FRONT,GL_SHININESS,4.0);
    
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glFrontFace(GL_CCW);
    
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Black background
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
}





