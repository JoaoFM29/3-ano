#define GL_SILENCE_DEPRECATION

#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>   // Para a função time
#include <iostream>

#define MAX_TREES 500
#define RAIOCIRCULO 30
#define RAIOTEAPOT 25


float alfa_start = 0;
float beta_start = 0;

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

bool axis = false;

typedef struct {
    float x;
    float z;
} TreePosition;

TreePosition treePositions[MAX_TREES];

void generateTreePositions() {
    srand(time(NULL)); // start the random number sequence

    for (int i = 0; i < MAX_TREES; ++i) {
        float x, z;
        do {
            x = (float)(rand() % 200 - 100); // Coordenada x aleatória entre -100 e 100
            z = (float)(rand() % 200 - 100); // Coordenada z aleatória entre -100 e 100
        } while (sqrt(x * x + z * z) <= RAIOCIRCULO); // Verifica se as coordenadas estão dentro do círculo

        treePositions[i].x = x;
        treePositions[i].z = z;
    }
}

void drawTrees() {
    for (int i = 0; i < MAX_TREES; ++i) {
        glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.0f);
        glTranslatef(treePositions[i].x, 3.0f, treePositions[i].z);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        glutSolidCone(3.0f, 10.0f, 5, 20); // Desenha o cone da árvore
        glPopMatrix();

        glColor3f(0.6f, 0.3f, 0.0f);
        glPushMatrix();
        glTranslatef(treePositions[i].x, 0.0f, treePositions[i].z);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        glutSolidCone(1.0f, 5.0f, 15, 20); // Desenha o cone da árvore
        glPopMatrix();
    }
}

void drawTeapot(double raio1, double raio2, int quantidade){

    beta_start+= M_PI / 60 ;
    if ( beta_start == M_PI * 2)
        beta_start = 0;

    float step_beta = M_PI * 2 / quantidade;
    float current_beta = beta_start;

    for( int i = 0; i < quantidade ;++i ){

        float x = sin(current_beta) * raio1;
        float z = cos(current_beta) * raio1;
        float y = 2;
        float degrees = current_beta * (180.0/M_PI); // conversão para radianos

        glPushMatrix();
        glColor3f(0.5f, 0.0f, 0.0f);
        glTranslatef(x,y,z);
        glRotatef(degrees,0,1,0);
        glutSolidTeapot(1);
        glPopMatrix();

        current_beta+=step_beta;
    }

    alfa_start+= M_PI / 60 ;
    if ( alfa_start == M_PI * 2)
       alfa_start = 0;

    float step_apha = M_PI * 2 / quantidade;
    float current_alpha = alfa_start;

    for( int i = 0; i<quantidade ;++i ){

        float x = sin(current_alpha) * raio2;
        float z = cos(current_alpha) * raio2;
        float y = 2;
        float degrees = current_alpha * (180.0/M_PI); // conversão para radianos

        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.5f);
        glTranslatef(x,y,z);
        glRotatef(degrees - 90 ,0,1,0);
        glutSolidTeapot(1);
        glPopMatrix();

        current_alpha+=step_apha;
    }
    glutPostRedisplay();
}

void drawTorus(){
    glPushMatrix();
    glColor3f(0.6f, 0.0f, 0.6f); // Cor roxa (vermelho: 0.6, verde: 0.0, azul: 0.6)
    glutSolidTorus(1.0f, 1.5f, 10,10);
    glPopMatrix();
}

void drawCircle(double radius, int slices) {
    double sliceStep = 2.0 * M_PI / slices;
    double alfa = 0.0f;

    glColor3f(1.0f,1.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= slices; ++i) {
        glVertex3f(cos(alfa) * radius, 0.1f, sin(alfa) * radius);
        alfa += sliceStep;
    }
    glEnd();
}


void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();

    if (axis){
        glBegin(GL_LINES);
// X axis in red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(
                -100.0f, 0.0f, 0.0f);
        glVertex3f( 100.0f, 0.0f, 0.0f);
// Y Axis in Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f,
                   -100.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);
// Z Axis in Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f,
                   -100.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
        glEnd();
    }

    drawTrees();
    drawTeapot(RAIOTEAPOT, RAIOTEAPOT-20, 10);
    drawCircle(RAIOCIRCULO,10);
    drawTorus();

	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {

    switch (c) {
        case 'x':
            axis = !axis;
            glutPostRedisplay();
            break;
    }
}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {
    generateTreePositions(); // Gera as posições das árvores aleatoriamente

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
