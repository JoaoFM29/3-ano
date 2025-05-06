#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>



#define TOTAL_TREE 1000
#define TOTAL_COWBOY 8
#define TOTAL_INDIO 16
float alfa_start = 0;
float beta_start = M_PI / 2;
float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

int seed = rand();

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
	
	// put code to draw scene in here
    srand(seed);

    // arvores com tronco rosa
    for(int i = 0; i<TOTAL_TREE;++i){

        int randx = (rand() % 100) * pow(-1,rand());
        int randz = (rand() % 100) * pow(-1,rand());
        if (randx * randx + randz * randz < 40 * 40){
            --i;
            continue;
        }

        glPushMatrix();
        glTranslatef(randx,0,randz);
        glPushMatrix();
        glTranslatef(0,1,0);
        glRotatef(270,1,0,0);
        glColor3f(0.54f, 0.27f, 0.07f);
        glutSolidCone(1,3,10,10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,4,0);
        glRotatef(270,1,0,0);
        glColor3f(0.0f, 0.5f, 0.0f);
        glutSolidCone(3,5,10,10);
        glPopMatrix();
        glPopMatrix();
    }

    beta_start+= M_PI / 60 ;
    if ( beta_start == M_PI * 2)
        beta_start = 0;

    float step_beta = M_PI * 2 / TOTAL_INDIO;
    float big_radius = 25;
    float current_beta = beta_start;

    for( int i = 0; i<TOTAL_INDIO ;++i ){

        float x = sin(current_beta) * big_radius;
        float z = cos(current_beta) * big_radius;
        float y = 2;

        glPushMatrix();
        glColor3f(0.5f, 0.0f, 0.0f);
        float radians = current_beta;
        float degrees = radians * (180.0/M_PI);
        glTranslatef(x,y,z);
        glRotatef(degrees,0,1,0);
        glutSolidTeapot(1);
        glPopMatrix();
        current_beta+=step_beta;

    }

    alfa_start+= M_PI / 80 ;
    if ( alfa_start == M_PI * 2)
        alfa_start = 0;

    float step_apha = M_PI * 2 / TOTAL_COWBOY;
    float small_radius = 5;
    float current_alpha = alfa_start;

    for( int i = 0; i<TOTAL_COWBOY ;++i ){

        float x = sin(current_alpha) * small_radius;
        float z = cos(current_alpha) * small_radius;
        float y = 2;

        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.5f);

        float radians = current_alpha;
        float degrees = radians * (180.0/M_PI);
        // (x,0,z)
        glTranslatef(x,y,z);
        glRotatef(degrees + 270,0,1,0);
        glutSolidTeapot(1);
        glPopMatrix();
        current_alpha+=step_apha;

    }

    glPushMatrix();
    glColor3f(0.5f, 0.0f, 0.5f);
    glutSolidTorus(1, 2, 10,10);
    glPopMatrix();

	
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

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

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
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
