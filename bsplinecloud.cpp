#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;

class Point {        // this class is used to store the coordinates of the point
public:
    float x, y;
    void setxy(float x2, float y2)
    {
        x = x2; y = y2;
    }
    //operator overloading for '=' sign
    const Point & operator=(const Point &rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }

};

int factorial(int n)   // this function is used to calculate the factorial of a number
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);  // recursive call
    return n;
}

float binomial_coff(float n,float k)   // this function is used to calculate the binomial coefficient
{
    float ans;
    ans = factorial(n) / (factorial(k)*factorial(n-k));     // binomial coefficient is n!/k!*(n-k)!
    return ans;   // returns the coefficient value
}




Point abc[20];   // array storing points
int SCREEN_HEIGHT = 500;  // declaring screen height
int points = 0;
int clicks = 5;    // This variable is responsible for the no of clicks/points before drawing the spline curve.


void myInit() {
    glClearColor(1.0,1.0,1.0,0.0);    //clearing color buffer
    glColor3f(0.0,0.0,0.0);   //selection of color
    glPointSize(3); 
    glMatrixMode(GL_PROJECTION);  //selection of matrix mode
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,500.0);

}

void drawDot(int x, int y) {     // this function is used to draw a point wherever it is clicked
    glBegin(GL_POINTS);
     glVertex2i(x,y);    // vertex
    glEnd();
    glFlush();
}

void drawLine(Point p1, Point p2) {    // this function draws a line between two points
    glBegin(GL_LINES);
      glVertex2f(p1.x, p1.y);
      glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush();
}


//Calculate the bezier point
Point drawBezier(Point PT[], double t) {   // This function is responsible for calculating different beizer point
    Point P;
    P.x = (pow((1 - t), 3) * PT[0].x +  (3 *pow((t), 3) - 6*pow(t,2) + t)* PT[1].x + (-3* pow(t, 3)+3*pow(t,2)+3*t+1)* PT[2].x + pow (t, 3)* PT[3].x)/6.0;
    P.y = (pow((1 - t), 3) * PT[0].y+ (3 *pow((t), 3) - 6*pow(t,2) + t)* PT[1].y + (-3* pow(t, 3)+3*pow(t,2)+3*t+1)* PT[2].y + pow (t, 3)* PT[3].y)/6.0;

    return P;
}



Point drawBezierGeneralized(Point PT[], double t) {      // This function is responsible for calculating the generalized beizer point
    Point P;
    P.x = 0; P.y = 0;   
    for (int i = 0; i<clicks; i++)
    {
        P.x = P.x + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].x;
        P.y = P.y + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].y;
    }
    cout<<P.x<<endl<<P.y;
    cout<<endl<<endl;
    return P;
}



void myMouse(int button, int state, int x, int y) {    // This function is used for getting and setting the value of points got after clicking the mouse.
  
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    
    abc[points].setxy((float)x,(float)(SCREEN_HEIGHT - y));
    points++;

    drawDot(x, SCREEN_HEIGHT - y);   // draws a small dot wherever mouse is clicked

    for(int l=0;l<6;l++)
    {   if(points == clicks) 
    {
        glColor3f(0.2,1.0,0.0);   // selection of color
        
        //for(int k=0;k<clicks-1;k++)
          // drawLine(abc[k], abc[k+1]);

        Point p1 = abc[0];    // getting a point from the array
        
        for(double t = 0.0;t <= 1.0; t += 0.02)     // drawing the curve
        {
            Point p2 = drawBezierGeneralized(abc,t);
            //cout<<p1.x<<"  ,  "<<p1.y<<endl;
            //cout<<p2.x<<"  ,  "<<p2.y<<endl;
            //cout<<endl;
            drawLine(p1, p2);
            p1 = p2;
        }
        glColor3f(0.0,0.0,0.0);   // selection of color

        points = 0;
    }
    }
  }
}


void myDisplay() {   // Display function
    glClear(GL_COLOR_BUFFER_BIT);  // clearing color buffer
    glFlush();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,500);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Bezier Curve");
    glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();

    return 0;
}
