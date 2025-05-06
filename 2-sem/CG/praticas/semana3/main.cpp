#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

GLfloat angle = 0.0f; // Ângulo de rotação inicial
GLfloat tX = 0.0f; // Translação inicial em X
GLfloat tY = 0.0f; // Translação inicial em Y
GLfloat tZ = 0.0f; // Translação inicial em Z
GLfloat teapotSize = 1.0f; // Tamanho inicial do cilindro

void changeSize(int w, int h) {
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);
}

void drawCylinder(float radius, float height, int slices) {
    glPushMatrix();
    glTranslatef(tX, tY, tZ);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glScalef(teapotSize, teapotSize, teapotSize);

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < slices; ++i) {
        float theta1 = (2.0f * M_PI * i) / slices;
        float theta2 = (2.0f * M_PI * (i + 1)) / slices;

        // Topo
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, height / 2.0f, 0.0f);
        glVertex3f(radius * cos(theta1), height / 2.0f, radius * sin(theta1));
        glVertex3f(radius * cos(theta2), height / 2.0f, radius * sin(theta2));

        // Base
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, -height / 2.0f, 0.0f);
        glVertex3f(radius * cos(theta2), -height / 2.0f, radius * sin(theta2));
        glVertex3f(radius * cos(theta1), -height / 2.0f, radius * sin(theta1));

        // Lateral
        glNormal3f(cos(theta1 + theta2), 0.0f, sin(theta1 + theta2));
        glVertex3f(radius * cos(theta1), height / 2.0f, radius * sin(theta1));
        glVertex3f(radius * cos(theta2), height / 2.0f, radius * sin(theta2));
        glVertex3f(radius * cos(theta2), -height / 2.0f, radius * sin(theta2));

        glVertex3f(radius * cos(theta2), -height / 2.0f, radius * sin(theta2));
        glVertex3f(radius * cos(theta1), -height / 2.0f, radius * sin(theta1));
        glVertex3f(radius * cos(theta1), height / 2.0f, radius * sin(theta1));
    }

    glEnd();

    glPopMatrix();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

    drawCylinder(1, 2, 10);

    glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) {
    switch (key) {
    case 'd':
        angle += 5.0f;
        glutPostRedisplay();
        break;
    case 'a':
        angle -= 5.0f;
        glutPostRedisplay();
        break;
    case 27: // Código ASCII para a tecla ESC
        exit(0);
        break;
    }
}

void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
    case GLUT_KEY_LEFT:
        tX -= 0.5f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        tZ += 0.5f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        tX += 0.5f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        tZ -= 0.5f;
        glutPostRedisplay();
        break;
    case 27: // Código ASCII para a tecla ESC
        exit(0);
        break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glutMainLoop();

    return 0;
}
