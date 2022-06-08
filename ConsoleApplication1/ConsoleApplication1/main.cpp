
#include "axis.h"
#include "constants.h"
#include "Face.h"
#include "filereader.h"
#include "illumination.h"
#include "info.h"
#include "renderer.h"
#include "rotation.h"
#include "scale.h"
#include "vector2.h"
#include "vector3.h"
#include <GL/glut.h>
#include <iostream>

Mesh mesh;
Axis axis = { false, false, true };
bool illumination[] = { true, false, false };




void pressLightSwitch() {
    (illumination[AMBIENT]) ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);
    (illumination[DIFFUSE]) ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);
    (illumination[SPECULAR]) ? glEnable(GL_LIGHT2) : glDisable(GL_LIGHT2);
}

void initIllumination() {
    // Material 
    GLfloat ambient[] = { 1.0, 1.0, 1.0, 0.4 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

    GLint specularityIntensity = 50;
    glMateriali(GL_FRONT, GL_SHININESS, specularityIntensity);

    // Light 
    GLfloat ambientLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);

    GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    pressLightSwitch();
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    initIllumination();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -30.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);
    {
        render(mesh);
    }
    glEnd();

    glPointSize(4.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < mesh.vertices.size(); i++) {
            glVertex3f(mesh.vertices[i].x, mesh.vertices[i].y, mesh.vertices[i].z);
        }

        glVertex3f(mesh.position.x, mesh.position.y, mesh.position.z);
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    if (height == 0) {
        height = 1;
    }

    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void redisplay(int value) {
    glutPostRedisplay();
    glutTimerFunc(REDISPLAY_DELAY, redisplay, 0);
}

void mouse(int button, int state, int x, int y) {
    float rotation = 10.0f;

    if (state != GLUT_UP) {
        switch (button) {
        case 3: // Scroll up (clockwise)
            mesh.rotateBy(-rotation, axis);
            break;
        case 4: // Scroll down (anti-clockwise)
            mesh.rotateBy(rotation, axis);
            break;
        default:
            break;
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    float speed = 1.0f;
    float scale = 2.0f;

    switch (key) {
    case 'w': // Up
        mesh.translateBy({ 0.0f, speed, 0.0f });
        break;
    case 'a': // Left
        mesh.translateBy({ -speed, 0.0f, 0.0f });
        break;
    case 's': // Down
        mesh.translateBy({ 0.0f, -speed, 0.0f });
        break;
    case 'd': // Right
        mesh.translateBy({ speed, 0.0f, 0.0f });
        break;
    case 'q': // Back
        mesh.translateBy({ 0.0f, 0.0f, -speed });
        break;
    case 'e': // Forward
        mesh.translateBy({ 0.0f, 0.0f, speed });
        break;

    case '1': // X-scale decrease
        mesh.scaleBy({ 1 / scale, 1, 1 });
        break;
    case '2': // X-scale increase
        mesh.scaleBy({ scale, 1, 1 });
        break;
    case '4': // Y-scale decrease
        mesh.scaleBy({ 1, 1 / scale, 1 });
        break;
    case '5': // Y-scale increase
        mesh.scaleBy({ 1, scale, 1 });
        break;
    case '7': // Z-scale decrease
        mesh.scaleBy({ 1, 1, 1 / scale });
        break;
    case '8': // Z-scale increase
        mesh.scaleBy({ 1, 1, scale });
        break;

    case 'x': // Set x-axis rotation
        axis = { true, false, false };
        break;
    case 'y': // Set y-axis rotation
        axis = { false, true, false };
        break;
    case 'z': // Set z-axis rotation
        axis = { false, false, true };
        break;

    case 'j': // Set ambient light
        illumination[AMBIENT] = !illumination[AMBIENT];
        pressLightSwitch();
        break;
    case 'k': // Set diffuse light
        illumination[DIFFUSE] = !illumination[DIFFUSE];
        pressLightSwitch();
        break;
    case 'l': // Set specular light
        illumination[SPECULAR] = !illumination[SPECULAR];
        pressLightSwitch();
        break;
    }
}




int main(int argc, char** argv) {
    srand(1);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE);

    glutInitWindowSize(800, 720);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("M2");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(REDISPLAY_DELAY, redisplay, 0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    loadOBJ("M:/CienciaDaComputacao/Computacao Grafica/ConsoleApplication1/ConsoleApplication1/Stone.obj", mesh);

    initGL();
    glutMainLoop();
    return 0;
}
