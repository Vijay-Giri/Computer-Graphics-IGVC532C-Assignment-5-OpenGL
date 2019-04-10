#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

float _angle=45.5;


GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // white light
GLfloat  sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };  //source light
GLfloat     lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };   // declaring position of light source


void RenderScene(void)
{
    static float fMoonRot = 0.0f;  
    static float fEarthRot = 0.0f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clearing buffer bits
    glMatrixMode(GL_MODELVIEW);  //selection of matrix mode
    glPushMatrix();
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glTranslatef(0.0f, 0.0f, -300.0f);   //translating to the position where sun should be present
    glColor3ub(255, 100, 0);  //selection of color of sun
    glutSolidSphere(35.0f, 800, 800);  //declaring a sphere representing a sun
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glRotatef(_angle, 0.0f, 1.0f, 0.0f);  //rotating sun
    glColor3ub(0,50,255);   //selection of color of earth
    glTranslatef(105.0f,0.0f,0.0f);   //translating to the position where earth should be present
    glutSolidSphere(15.0f, 800, 800);  //declaring a sphere representing a earth.
    glColor3ub(200,200,200);    //selection of color of moon
    glRotatef(_angle,0.0f, 1.0f, 0.0f);   // rotating moon
    glTranslatef(30.0f, 0.0f, 0.0f);   //translating to the position where moon should be present
    fMoonRot+= 35.0f;  // angle of rotation of moon
    if(fMoonRot > 360.0f)   // if angle covered by moon is >360 degree the reinitialize it to 0 degrees
        fMoonRot = 0.0f;
    glutSolidSphere(6.0f, 800, 800);  // declaring a sphere representing a moon
    glPopMatrix();
    fEarthRot += 5.0f;
    if(fEarthRot > 360.0f)   // if angle covered by earth is >360 degree then reinitialize it to 0 degrees
        fEarthRot = 0.0f;
    glutSwapBuffers();
}



void SetupRC()   // this function is responsible for displaying the entire setup of solar system.
{
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}


void TimerFunc(int value)  // this function is to set timer of rotation.
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void ChangeSize(int w, int h) // this function is responsible for changing the size of viewport
{
    GLfloat fAspect;
    if(h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w/(GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, fAspect, 1.0, 425.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mySpecialFunc(int key, int x, int y){    //this function deals with the rotation of house to see the 3d view whenever RIGHT or LEFT key is pressed
        switch (key) {
    case GLUT_KEY_RIGHT:
        _angle += 1;    // at each click of RIGHT button it rotates the image with +1 degree in the right direction.
        if (_angle > 360) _angle = 0.0;   // if angle becomes 360 degree so it gets reinitialized to 0 so as to complete one complete rotation of the house
                break;
    case GLUT_KEY_LEFT:
        _angle -= 1;   // at each click of LEFT click it roatates 1 degree in the left direction
        if (_angle > 360) _angle = 0.0;  // if angle becomes 360 degrees it gets reinitialized to 0 so as to complete one complete rotation.
            break;
        }
        glutPostRedisplay();
}


int main(int argc, char* argv[])  // main function
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Earth/Moon/Sun System");  // title of the display window
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(mySpecialFunc);
    glutDisplayFunc(RenderScene);  //call to renderscene
    glutTimerFunc(500, TimerFunc, 1); // timer function
    SetupRC();
    glutMainLoop();

    return 0;
}
                      
