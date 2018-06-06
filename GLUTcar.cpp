#include "GLUT/glut.h"
#include <math.h>
#include <cstdlib>

float light_radius = 0.5;

void window();

GLfloat ctrlpoints_side1r[4][4][3] = {//车门右侧
        {{-4.0, 1.2, -0.5},
                {-3.9, 1.5, 2.2},
                {-2.0, 1.5, 1.6},
                {-1.5, 1.5, 1.6}},
        {{-4.0, 1.3, -0.5},
                {-3.9, 2.2, 2.4},
                {-2.0, 2.2, 2.2},
                {-1.5, 2.2, 1.3}},
        {{-4.0, 1.4, -0.5},
                {-3.9, 2.3, 1.6},
                {-2.0, 2.3, 1.4},
                {-1.5, 2.3, 1.2}},
        {{-4.0, 1.5, -0.5},
                {-3.9, 2.4, 1.0},
                {-2.0, 2.4, 1.0},
                {-1.5, 2.5, 0.6}}
};
GLfloat ctrlpoints_side1l[4][4][3] = {//车门左侧
        {{-4.0, -1.2, -0.5},
                {-3.9, -1.5, 2.2},
                {-2.0, -1.5, 1.6},
                {-1.5, -1.5, 1.6}},
        {{-4.0, -1.3, -0.5},
                {-3.9, -2.2, 2.4},
                {-2.0, -2.2, 2.2},
                {-1.5, -2.2, 1.3}},
        {{-4.0, -1.4, -0.5},
                {-3.9, -2.3, 1.6},
                {-2.0, -2.3, 1.4},
                {-1.5, -2.3, 1.2}},
        {{-4.0, -1.5, -0.5},
                {-3.9, -2.4, 1.0},
                {-2.0, -2.4, 1.0},
                {-1.5, -2.5, 0.6}}
};
GLfloat ctrlpoints_side2r[4][4][3] = {//右前轮前侧
        {{-1.5, 1.5, 1.6},
                {-0.5, 1.5, 6.0},
                {6.0, 1.5, 4.0},
                {7.0, 1.5, -0.5}},
        {{-1.5, 2.2, 1.4},
                {-0.5, 2.2, 4.0},
                {6.0, 2.2, 3.0},
                {6.0, 2.2, -0.5}},
        {{-1.5, 2.2, 1.0},
                {-0.5, 2.2, 1.0},
                {6.0, 2.2, 1.0},
                {7.0, 2.2, -0.5}},
        {{-1.5, 2.0, -0.5},
                {-0.5, 2.0, -0.5},
                {6.0, 2.0, -0.5},
                {7.0, 2.0, -0.5}}
};
GLfloat ctrlpoints_side2l[4][4][3] = {//左前轮前前侧
        {{-1.5, -1.5, 1.6},
                {-0.5, -1.5, 6.0},
                {6.0, -1.5, 4.0},
                {7.0, -1.5, -0.5}},
        {{-1.5, -2.2, 1.4},
                {-0.5, -2.2, 4.0},
                {6.0, -2.2, 3.0},

                {6.0, -2.2, -0.5}},
        {{-1.5, -2.2, 1.0},
                {-0.5, -2.2, 1.0},
                {6.0, -2.2, 1.0},
                {7.0, -2.2, -0.5}},
        {{-1.5, -2.0, -0.5},
                {-0.5, -2.0, -0.5},
                {6.0, -2.0, -0.5},
                {7.0, -2.0, -0.5}}
};
GLfloat ctrlpoints_side3l[4][4][3] = {//左侧车轮后侧
        {{-1.5, -1.5, 1.6},
                {-1.0, -1.5, 1.4},
                {-0.8, -1.5, 0.8},
                {-0.5, -1.5, -0.5}},
        {{-1.5, -2.2, 1.3},
                {-1.0, -2.2, 1.0},
                {-0.8, -2.2, 0.6},
                {-0.5, -2.2, -0.5}},
        {{-1.5, -2.3, 1.2},
                {-1.0, -2.4, 1.0},
                {-0.8, -2.4, 0.6},
                {-0.5, -2.3, -0.5}},
        {{-1.5, -2.5, 0.6},
                {-1.0, -2.6, -0.5},
                {-0.8, -2.6, -0.5},
                {-0.5, -2.5, -0.5}}
};
GLfloat ctrlpoints_side3r[4][4][3] = {//右侧车轮后侧
        {{-1.5, 1.5, 1.6},
                {-1.0, 1.5, 1.4},
                {-0.8, 1.5, 0.8},
                {-0.5, 1.5, -0.5}},
        {{-1.5, 2.2, 1.3},
                {-1.0, 2.2, 1.0},
                {-0.8, 2.2, 0.6},
                {-0.5, 2.2, -0.5}},

        {{-1.5, 2.3, 1.2},
                {-1.0, 2.4, 1.0},
                {-0.8, 2.4, 0.8},
                {-0.5, 2.3, -0.5}},
        {{-1.5, 2.5, 0.6},
                {-1.0, 2.6, 0.3},
                {-0.8, 2.6, 0.0},
                {-0.5, 2.5, -0.5}}
};
GLfloat ctrlpoints_side4r[4][4][3] = {//右后轮前侧
        {{3.4, 1.5, -0.5},
                {3.5, 1.5, 2.0},
                {5.0, 1.5, 1.8},
                {6.0, 1.5, 1.6}},
        {{3.4, 2.3, -0.5},
                {3.5, 2.3, 1.8},
                {5.0, 2.3, 1.4},
                {6.0, 2.3, 1.3}},
        {{3.4, 2.3, -0.5},
                {3.5, 2.6, 1.6},
                {5.0, 2.6, 1.3},
                {6.0, 2.4, 1.2}},
        {{3.4, 2.4, -0.5},
                {3.5, 2.7, 1.0},
                {5.0, 2.7, 0.8},
                {6.0, 2.5, 0.6}}
};
GLfloat ctrlpoints_side4l[4][4][3] = {//左后轮前侧
        {{3.4, -1.5, -0.5},
                {3.5, -1.5, 2.0},
                {5.0, -1.5, 1.8},
                {6.0, -1.5, 1.6}},
        {{3.4, -2.3, -0.5},
                {3.5, -2.3, 1.6},
                {5.0, -2.3, 1.4},
                {6.0, -2.3, 1.3}},
        {{3.4, -2.3, -0.5},
                {3.5, -2.6, 1.8},

                {5.0, -2.6, 1.4},
                {6.0, -2.4, 1.2}},
        {{3.4, -2.4, -0.5},
                {3.5, -2.7, 1.0},
                {5.0, -2.7, 0.8},
                {6.0, -2.5, 0.6}}
};


GLfloat ctrlpoints_top[4][4][3] = {
        {{-1.5, -2.2, 1.6},
                {-0.5, -2.2, 6.0},
                {6.0, -2.2, 4.0},
                {7.0, -2.7, -0.5}},
        {{-1.5, -0.5, 1.6},
                {-0.5, -0.5, 6.0},
                {6.0, -0.5, 4.0},
                {7.0, -0.5, -0.5}},
        {{-1.5, 0.5,  1.6},
                {-0.5, 0.5,  6.0},
                {6.0, 0.5,  4.0},
                {7.0, 0.5,  -0.5}},
        {{-1.5, 2.2,  1.6},
                {-0.5, 2.2,  6.0},
                {6.0, 2.2,  4.0},
                {7.0, 2.7,  -0.5}}
};

GLfloat ctrlpoints_front[4][4][3] = {
        {{-4.0, -2.2, -0.5},
                {-3.9, -2.2, 2.2},
                {-2.0, -2.2, 1.6},
                {-1.5, -2.2, 1.6}},
        {{-4.0, -0.5, -0.5},
                {-3.9, -0.5, 2.2},
                {-2.0, -0.5, 1.6},
                {-1.5, -0.5, 1.6}},
        {{-4.0, 0.5,  -0.5},
                {-3.9, 0.5,  2.2},
                {-2.0, 0.5,  1.6},
                {-1.5, 0.5,  1.6}},
        {{-4.0, 2.2,  -0.5},
                {-3.9, 2.2,  2.2},
                {-2.0, 2.2,  1.6},
                {-1.5, 2.2,  1.6}}
};


void wheel_material() {
    GLfloat specular_color[] = {0.0, 0.0, 0.0, 0.0};//设置镜面反射颜色为黑色
    GLfloat shininess_degree[] = {0.0};
    GLfloat diffuse_color[] = {0.0, 0.0, 0.0, 0.0};//设置漫反射颜色为黑色
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);//设置正面镜面反射颜色
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess_degree);//设置正面镜面指数
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_color);//设置正面漫反射颜色
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, diffuse_color);//设置全局环境光照强度
}

void wheel() {
    const int segments = 200;
    const GLfloat pi = 3.14f;
    int i, j;
    GLfloat r1, r2;
    r1 = 0.9;
    r2 = 0.6;
    GLfloat tmp1, tmp2;
    glPushMatrix();
    glTranslatef(-2.3, 2.7, -0.4);
    glLineWidth(1.0);
    wheel_material();
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < segments; ++i)//把车轮处看作一个圆
    {
        tmp1 = 2 * pi * i / segments;
        for (j = 0; j < segments; ++j) {
            tmp2 = 2 * pi * j / segments;
            glVertex3f((r1 + r2 * sin(tmp2)) * cos(tmp1), r2 * cos(tmp2),
                       (r1 + r2 * sin(tmp2)) * sin(tmp1));
//以圆上每个点作为圆心画圆
        }
    }
    glEnd();
    glTranslatef(0.0, -5.4, 0.0);
    wheel_material();
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < segments; ++i) {
        tmp1 = 2 * pi * i / segments;
        for (j = 0; j < segments; ++j) {
            tmp2 = 2 * pi * j / segments;
            glVertex3f((r1 + r2 * sin(tmp2)) * cos(tmp1), r2 * cos(tmp2),
                       (r1 + r2 * sin(tmp2)) * sin(tmp1));
        }
    }
    glEnd();
    glTranslatef(7.5, 0.0, 0.0);
    wheel_material();
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < segments; ++i) {
        tmp1 = 2 * pi * i / segments;
        for (j = 0; j < segments; ++j) {
            tmp2 = 2 * pi * j / segments;
            glVertex3f((r1 + r2 * sin(tmp2)) * cos(tmp1), r2 * cos(tmp2),
                       (r1 + r2 * sin(tmp2)) * sin(tmp1));
        }
    }

    glEnd();
    glTranslatef(0.0, 5.4, 0.0);
    wheel_material();
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < segments; ++i) {
        tmp1 = 2 * pi * i / segments;
        for (j = 0; j < segments; ++j) {
            tmp2 = 2 * pi * j / segments;
            glVertex3f((r1 + r2 * sin(tmp2)) * cos(tmp1), r2 * cos(tmp2),
                       (r1 + r2 * sin(tmp2)) * sin(tmp1));
        }
    }
    glEnd();
    glPopMatrix();
}


void top_material() {
    GLfloat specular_color[] = {1.0, 0.0, 0.0, 1.0};//设置镜面反射的颜色为红色
    GLfloat shininess_degree[] = {55.0};//设置镜面反射指数
    GLfloat diffuse_color[] = {1.0, 0.0, 0.0, 1.0};//设置漫反射颜色为红色
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);//设置正面镜面反射颜色
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess_degree);//设置正面镜面指数
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_color);//设置正面漫反射颜色
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, diffuse_color);//设置全局环境光照强度
}

void dick_material() {
    GLfloat specular_color[] = {1.0, 1.0, 0.0, 1.0};//设置镜面反射的颜色为红色
    GLfloat shininess_degree[] = {55.0};//设置镜面反射指数
    GLfloat diffuse_color[] = {1.0, 1.0, 0.0, 1.0};//设置漫反射颜色为红色
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);//设置正面镜面反射颜色
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess_degree);//设置正面镜面指数
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_color);//设置正面漫反射颜色
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, diffuse_color);//设置全局环境光照强度
}

void front_material() {
    GLfloat specular_color[] = {0.0, 1.0, 0.0, 1.0};//设置镜面反射的颜色为红色
    GLfloat shininess_degree[] = {55.0};//设置镜面反射指数
    GLfloat diffuse_color[] = {0.0, 1.0, 0.0, 1.0};//设置漫反射颜色为红色
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);//设置正面镜面反射颜色
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess_degree);//设置正面镜面指数
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_color);//设置正面漫反射颜色
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, diffuse_color);//设置全局环境光照强度
}

void top() {
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_top[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    dick_material();
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
}

void front() {
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_front[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    front_material();
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
}


void LightPosition() {
    float x, y, z;//光源方向
    x = 3.0;
    y = light_radius * 1;
    z = light_radius * 0;
    float light_position[] = {x, y, z, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);//设置0号光源的位置属性为之前所设的向

}

void side() {
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_side1r[0][0][0]);//画车门右侧
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(0, 0.7, 0.0);
    top_material();
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_side1l[0][0][0]);//画车门左侧
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    top_material();
    glTranslatef(0, -0.7, 0.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_side2l[0][0][0]);//画车左前轮前侧
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    dick_material();
    glTranslatef(0, -0.7, 0.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_side2r[0][0][0]);//画右前轮前侧
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    dick_material();
    glTranslatef(0, 0.7, 0.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_side3l[0][0][0]);//画左前车轮后侧
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    top_material();
    glTranslatef(0, -0.7, 0.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);//画左前车轮后侧
    glTranslatef(7.5, 0.0, 0.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);//画左后车轮后侧
    glPopMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_side3r[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    top_material();
    glTranslatef(0, 0.7, 0.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);//画右前车轮后侧
    glTranslatef(7.5, 0.0, 0.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);//画右后车轮后侧
    glPopMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_side4r[0][0][0]);//画右后轮前侧
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    top_material();
    glTranslatef(0, 0.7, 0.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_side4l[0][0][0]);//画左后轮前侧
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(0, -0.7, 0.0);
    top_material();

    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
}

GLfloat xo = -200, yo = -35, zo = 40, xref = 0, yref = 0, zref = 0, Vx = 4, Vy = 1, Vz = 0;
static float xwMin = -20, xwMax = 20, ywMin = -20, ywMax = 20, dnear = 200, dfar = 10000;


void CarDisplay() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xo, yo, zo, xref, yref, zref, Vx, Vy, Vz);
    //CarPosition();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    top();//画车顶
    front();//画车前盖
    side();//画车侧面
    wheel();//画车轮
    window();//画窗户
    glFlush();
    glutSwapBuffers();
}

GLfloat ctrlpoints_frontWin[4][4][3] = {
        {{-1.5, -2.0, 1.6},
                {-1.1, -2.0, 3.6},
                {0, -2.0, 3.8},
                {0.2, -2.0, 3.9}},
        {{-1.5, -0.5, 1.6},
                {-1.1, -0.5, 3.6},
                {0, -0.5, 3.8},
                {0.2, -0.5, 3.9}},
        {{-1.5, 0.5,  1.6},
                {-1.1, 0.5,  3.6},
                {0, 0.5,  3.8},
                {0.2, 0.5,  3.9}},
        {{-1.5, 2.0,  1.6},
                {-1.1, 2.0,  3.6},
                {0, 2.0,  3.8},
                {0.2, 2.0,  3.9}}
};
//右侧车窗
GLfloat ctrlpoints_sidewinr[4][4][3] = {
        {{-1.1, 2.0, 1.6},
                {-0.5, 1.7, 5.5},
                {4.8, 1.7, 3.0},
                {5.0, 2.0, 1.6}},
        {{-1.1, 2.0, 1.6},
                {-0.5, 2.2, 4.0},
                {4.8, 2.2, 2.0},
                {5.0, 2.0, 1.6}},
        {{-1.1, 2.0, 1.6},
                {-0.5, 2.2, 1.5},
                {4.8, 2.2, 1.0},
                {5.0, 2.0, 1.6}},
        {{-1.1, 2.0, 1.6},
                {-0.5, 2.0, 1.0},
                {4.8, 2.0, 1.6},
                {5.0, 2.0, 1.6}}
};
//左侧车窗
GLfloat ctrlpoints_sidewinl[4][4][3] = {
        {{-1.1, -2.0, 1.6},
                {-0.5, -1.7, 5.5},
                {4.8, -1.7, 3.0},
                {5.0, -2.0, 1.6}},
        {{-1.1, -2.0, 1.6},
                {-0.5, -2.2, 4.0},
                {4.8, -2.2, 2.0},

                {5.0, -2.0, 1.6}},
        {{-1.1, -2.0, 1.6},
                {-0.5, -2.2, 1.5},
                {4.8, -2.2, 1.0},
                {5.0, -2.0, 1.6}},
        {{-1.1, -2.0, 1.6},
                {-0.5, -2.0, 1.0},
                {4.8, -2.0, 1.6},
                {5.0, -2.0, 1.6}}
};

void win_material() {
    GLfloat specular_color[] = {0.0, 0.0, 0.0, 0.0};//设置镜面反射的颜色为黑色
    GLfloat shininess_degree[] = {50.0};//设置镜面反射指数
    GLfloat diffuse_color[] = {0.0, 0.0, 0.0, 0.0};//设置漫反射颜色为黑色
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);//设置正面镜面反射颜色
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess_degree);//设置正面镜面指数
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_color);//设置正面漫反射颜色
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, diffuse_color);//设置全局环境光照强度
}


void window() {
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_frontWin[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    win_material();
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_sidewinr[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(0, 0.7, 0.0);
    win_material();
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints_sidewinl[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(0, -0.7, 0.0);
    win_material();
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    LightPosition();
    glShadeModel(GL_SMOOTH);//渐变色效果
    glEnable(GL_LIGHTING);//开启灯光
    glEnable(GL_LIGHT0);//选择 0 号光源
    glEnable(GL_DEPTH_TEST);//使近距离物体遮挡远距离物体
    glEnable(GL_COLOR_MATERIAL);//使开启灯光后依然可以给物体上色
}


void reshape(int w, int h);

void keyboard(unsigned char key, int x, int y);

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Forced to use Bezier to Draw Car T_T");
    init();
    glutDisplayFunc(CarDisplay);
    //glutIdleFunc(&Solar_systemIdle);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    //glutPassiveMotionFunc(&Solar_systemMouse);
    glutMainLoop();
    return 0;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
                4.0 * (GLfloat) h / (GLfloat) w, -4.0, 4.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
                4.0 * (GLfloat) w / (GLfloat) h, -4.0, 4.0, -4.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}