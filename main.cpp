/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

//#include "./freeglut-3.4.0/include/GL/freeglut.h"
#include <GL/freeglut.h>

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = { 0,1,4,1 };
int windowWidth = 640, windowHeight = 480;
double xRot = 0;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
    // Original positions close to each quadrant's center
    double originalPositions[4][2] = {
        {-0.25, 0.25}, // Quadrant 1
        {0.25, 0.25},  // Quadrant 2
        {-0.25, -0.25},// Quadrant 3
        {0.25, -0.25}  // Quadrant 4
    };

    // axis pots
    double axisPositions[4][2] = {
        {0, 1},    // Top
        {1, 0},    // Right
        {-1, 0},   // Left
        {0, -1}    // Bottom
    };

    // Rotation angles for quadrant pots
    double anglesQuad[4] = {225, 135, 315, 45};

    // quadrant teapots
    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glTranslatef(originalPositions[i][0], originalPositions[i][1], 0.0f);
        glRotatef(anglesQuad[i], 0.0f, 0.0f, 1.0f);
        glutSolidTeapot(0.1); // Draw the teapot
        glPopMatrix();
    }

    double anglesAxis[4] = {180, 90, 270, 0};
    // axis teapots
    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glTranslatef(axisPositions[i][0], axisPositions[i][1], 0.0f);
        glRotatef(anglesAxis[i], 0.0f, 0.0f, 1.0f);
        glutSolidTeapot(0.1); // Draw the teapot
        glPopMatrix();
    }
}

void problem2() {
    int layers = 10;
    float scale = 4.0f; // base
    float scaleStep = 0.4f; // step per level
    float translateYStep = 0.1f; // Translation step per level

    // Draw the upper pyramid
    for (int i = 0; i < layers; ++i) {
        glPushMatrix();
        glTranslatef(0.0f, i * translateYStep, 0.0f); // Move up 
        glScalef(scale - i * scaleStep, scaleStep, scale - i * scaleStep); // Scale down 
        glutSolidCube(1.0);
        glPopMatrix();
    }

    // Draw the lower pyramid
    for (int i = 0; i < layers; ++i) {
        glPushMatrix();
        glTranslatef(0.0f, -i * translateYStep, 0.0f); // Move down
        glScalef(scale - i * scaleStep, scaleStep, scale - i * scaleStep); // Scale down
        glutSolidCube(1.0);
        glPopMatrix();
    }

}

void problem3() {
  int maxPots = 4; 
    float potSize = 0.5f;
    float spacing = 1.0f;

  //nested loop to draw diamond shape
    for (int row = 0; row < 2 * maxPots - 1; ++row) {
        int currPots;

        if (row < maxPots) {
            // upper
              currPots = row + 1;
        } else {
            // lower
              currPots = 2 * maxPots - row - 1;
        }

        for (int teapotNum = 0; teapotNum < currPots; ++teapotNum) {
            glPushMatrix();
            //calculate the x and y positions for the teapot
            float xPosition = (teapotNum - (currPots - 1) / 2.0f) * spacing;
            float yPosition = (row - maxPots + 1) * spacing;
            glTranslatef(xPosition, yPosition, 0.0f);
            glutSolidTeapot(potSize);
            glPopMatrix();
        }
    }
}

void problem4() {

  //its kinda cursed, face with teapot eyes
  //draw head
  glPushMatrix();
  glutSolidSphere(1.0, 32, 32); // Radius 1.0, with 32 slices and stacks for smoothness
  glPopMatrix();

  double eyeDistance = 0.5f;
  double eyeYPosition = 0.25f;
  double eyeZPosition = 1.0f;

  // raw left eye
  glPushMatrix();
  glTranslatef(-eyeDistance, eyeYPosition, eyeZPosition); // Position 
  glutSolidTeapot(0.2);
  glPopMatrix();

  //draw right eye
  glPushMatrix();
  glTranslatef(eyeDistance, eyeYPosition, eyeZPosition); // Position 
  glutSolidTeapot(0.2); 
  glPopMatrix();

  //draw upper lip
  glPushMatrix();
  glTranslatef(0.0f, -0.4f, eyeZPosition); 
  glRotatef(90, 1.0, 0.0, 0.0); 
  glutSolidTorus(0.2, 0.2, 10, 30); 
  glPopMatrix();

  //draw lower lip
  glPushMatrix();
  glTranslatef(0.0f, -0.6f, eyeZPosition); 
  glRotatef(90, 1.0, 0.0, 0.0); 
  glutSolidTorus(0.2, 0.2, 10, 30); 
  glPopMatrix();

}

void display()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x axis
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y axis
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z axis
    glEnd(/*GL_LINES*/);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, windowWidth, windowHeight);

    float ratio = (float)windowWidth / (float)windowHeight;
    gluPerspective(50, ratio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    if (curProblem == 1) problem1();
    if (curProblem == 2) problem2();
    if (curProblem == 3) problem3();
    if (curProblem == 4) problem4();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
    else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

    lastPos[0] = x;
    lastPos[1] = y;
}

void mouseMoved(int x, int y)
{
    if (leftDown) {
        xRot += (y - lastPos[1]) * .1;
        yRot += (x - lastPos[0]) * .1;
    }
    if (rightDown) {
        for (int i = 0; i < 3; i++)
            cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
    }


    lastPos[0] = x;
    lastPos[1] = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    curProblem = key - '0';
    if (key == 'q' || key == 'Q' || key == 27) {
        exit(0);
    }
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("HW2");

    glutDisplayFunc(display);
    glutMotionFunc(mouseMoved);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
