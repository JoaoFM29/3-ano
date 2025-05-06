#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

GLfloat angle = 0.0f; // Initial rotation angle
GLfloat tX = 0.0f; // Initial translation angle
GLfloat tY = 0.0f; // Initial translation angle
GLfloat tZ = 0.0f; // Initial scale angle
GLfloat eZ = 1.0f; // Initial scale angle
int prevY = 0;   // Variable to store the previous y-coordinate


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
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

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


// put the geometric transformations here
    glTranslatef(tX, tY, tZ); // moves the object
    glRotatef(angle, 0.0f, 1.0f, 0.0f); // rotação sobre o eixo verde
    glScalef(1.0,eZ,1.0); // scale factors for each axis
    glColor3f(1,0,0); // color in RGB. Each component varies between 0 and 1. (1,1,1) is white, (0,0,0) is black.
    //gluLookAt(0.0,1.0,0.0,0.0,1.0,0.0, 0.0,1.0,0.0);
    // px,py,pz – camera position
    // lx,ly,lz – look at point
    // ux,uy,uz – camera tilt, by default use (0.0, 1.0, 0.0)

// put pyramid drawing instructions here
    glBegin(GL_TRIANGLES);

    // Front face
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);//eixo vermelho
    glVertex3f(0.0f, 0.0f, 1.0f);//eixo azul
    glVertex3f(0.0f, 2.0f, 0.0f);//eixo verde

    //Left face
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);//eixo vermelho
    glVertex3f(0.0f, 0.0f, 1.0f);//eixo azul
    glVertex3f(0.0f, 2.0f, 0.0f);//eixo verde

    //Rigth face
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);//eixo vermelho
    glVertex3f(0.0f, 0.0f, -1.0f);//eixo azul
    glVertex3f(0.0f, 2.0f, 0.0f);//eixo verde

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);//eixo vermelho
    glVertex3f(0.0f, 0.0f, -1.0f);//eixo azul
    glVertex3f(0.0f, 2.0f, 0.0f);//eixo verde

    glEnd();

	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events
void function_rot(unsigned char key, int x, int y){
    switch (key) {
    case 'd':
        angle += 5.0f; // Increase the rotation angle by 5 degrees
        glutPostRedisplay(); // Trigger a redraw to reflect the changes
        break;
    case 'a':
        angle -= 5.0f; // Increase the rotation angle by 5 degrees
        glutPostRedisplay(); // Trigger a redraw to reflect the changes
        break;
    case 27: // ASCII code for escape key
        break;
    }
}

void function_trans(int key_code, int x, int y){
    switch (key_code) {
        case GLUT_KEY_LEFT:
            tX -= 0.5f; // Increase the rotation angle by 5 degrees
            glutPostRedisplay(); // Trigger a redraw to reflect the changes
            break;
        case GLUT_KEY_UP:
            tZ += 0.5f; // Increase the rotation angle by 5 degrees
            glutPostRedisplay(); // Trigger a redraw to reflect the changes
            break;
        case GLUT_KEY_RIGHT:
            tX += 0.5f; // Increase the rotation angle by 5 degrees
            glutPostRedisplay(); // Trigger a redraw to reflect the changes
            break;
        case GLUT_KEY_DOWN:
            tZ -= 0.5f; // Increase the rotation angle by 5 degrees
            glutPostRedisplay(); // Trigger a redraw to reflect the changes
            break;
        case 27: // ASCII code for escape key
            break;
    }
}



void motionFunction(int x, int y) {
    // Increase the growth variable based on the change in mouse coordinates
    eZ += 0.005f *(prevY - y); // Adjust the multiplier for a suitable rate
    prevY = y; // Update the previous y-coordinate
    glutPostRedisplay(); // Trigger a redraw to reflect the changes
}
void passiveMotionFunction(int x, int y) {
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
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
    glutKeyboardFunc(function_rot);
    glutSpecialFunc(function_trans);
    //glutMouseFunc(function_mouse);
    glutMotionFunc(motionFunction);
    glutPassiveMotionFunc(passiveMotionFunction);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
