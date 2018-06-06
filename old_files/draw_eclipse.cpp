//
// Created by Hython on 2018/3/19.
//

#include<GLUT/glut.h>
#include<iostream>
#include<cmath>
using namespace std;

//The main algorithm to draw a ellipse without calculation of float number
void Bresenham(int cx, int cy, int a, int b);
//glut initialization
void init(void);
//Callback function when window size changed
void ChangeSize(GLsizei w, GLsizei h);
//Draw a point
void setPixel(int x, int y);
//Using the symmetry of ellipse to draw four points at a time
void Ellipsepot(int x0, int y0, int x, int y);
//glutDisplayFunc will call the following function to draw the ellipse
void display(void);

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("MidEllipse");
    glutDisplayFunc(display);
    glutReshapeFunc(ChangeSize);
    init();
    glutMainLoop();
    return 0;
}

void init(void)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // Set display-window color to white.
    glMatrixMode(GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void setPixel(int x, int y)
{
    glColor3f(1.0f, 0.5f, 0.2f);       // 蓝色
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}
void Ellipsepot(int x0, int y0, int x, int y)
{
    setPixel((x0 + x), (y0 + y));
    setPixel((x0 + x), (y0 - y));
    setPixel((x0 - x), (y0 - y));
    setPixel((x0 - x), (y0 + y));
}

void ChangeSize(GLsizei w, GLsizei h)
{

    if (h == 0)     h = 1;
    // Project to the screen
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Clipping Region
    if (w <= h)
        glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h / w, 1.0, -1.0);
    else
        glOrtho(0.0f, 250.0f*w / h, 0.0f, 250.0f, 1.0, -1.0);

}

void display(void)
{
    // Clear the screen with current background color
    glClear(GL_COLOR_BUFFER_BIT);

    int x0 = 120, y0 = 100, a = 100, b = 60;
    Bresenham(x0, y0, a, b);
}

void Bresenham(int cx, int cy, int a, int b){
    int squa=a*a;
    int squb=b*b;

    int xi=0;
    int yi=b;
    int di=2*squb-2*b*squa+squa;
    int X_Range=round((double)squa/sqrt((double)(squa+squb)));

    while(xi<=X_Range){
        Ellipsepot(cx,cy,xi,yi);
//        canvas[yi+cy][xi+cx]=1;
//        canvas[-yi+cy][xi+cx]=1;
//        canvas[-yi+cy][-xi+cx]=1;
//        canvas[yi+cy][-xi+cx]=1;
        if(di<0){
            di+=2*squb*(2*xi+3);
        }else{
            di+=2*squb*(2*xi+3)-4*squa*(yi-1);
            yi=yi-1;
        }
        xi=xi+1;

    }
    di=squb*(xi*xi+xi)+squa*(yi*yi-yi)-squa*squb;
    while(yi>=0){
        Ellipsepot(cx,cy,xi,yi);
//        canvas[yi+cy][xi+cx]=1;
//        canvas[-yi+cy][xi+cx]=1;
//        canvas[-yi+cy][-xi+cx]=1;
//        canvas[yi+cy][-xi+cx]=1;
        if(di<0){
            xi++;
            di=di-2*squa*yi-squa+2*squb*xi+2*squb;
        }else{
            di=di-2*squa*yi-squa;
        }
        yi=yi-1;
    }
}
