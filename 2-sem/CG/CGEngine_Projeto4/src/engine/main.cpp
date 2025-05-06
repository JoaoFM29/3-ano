#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include <chrono>
#include <stack>
#define _USE_MATH_DEFINES
#include <tuple>
#include <vector>
#include "animations.hpp"
#include "parser.hpp"
#include "ponto.hpp"
#include "algebra.hpp"
#include <IL/il.h>
using namespace std;


// Camera parameters
float alpha = 0.0;
float beta_ang = 0;
float radius = 0;

float xt,yt,zt = 0.0f;
float lx,ly,lz = 0.0f;
float rx, ry, rz;

bool axis = false;

bool fillModel = true;

bool showFps = false;

bool showO = false;

bool cinema = false;

Cena c;

int timebase;
float frame;
float fps;

GLuint *buffers;
GLuint *normals;
GLuint *textures;
GLuint *texIds;

int loadTexture(std::string s) {

    unsigned int t,tw,th;
    unsigned char *texData;
    unsigned int texID;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1,&t);
    ilBindImage(t);
    ilLoadImage((ILstring)s.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1,&texID);

    glBindTexture(GL_TEXTURE_2D,texID);
    glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;

}

// Function to convert spherical coordinates to Cartesian coordinates
void sphericalToCartesian(float alpha_, float beta_, float radius_, float &px, float &py, float &pz) {
    pz = radius_ * cos(beta_) * sin(alpha_);
    py = radius_ * sin(beta_);
    px = radius_ * (cos(beta_)) * cos(alpha_);
}

float getRadius(float x1, float y1, float z1, float x2, float y2, float z2) {
    // Calculate the differences in coordinates
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;

    // Calculate the distance using the Euclidean distance formula
    float distance = sqrt(dx * dx + dy * dy + dz * dz);

    return distance;
}

void initializeCamera(float eyeX, float eyeY, float eyeZ, float lookAtX, float lookAtY, float lookAtZ) {
    xt = eyeX;
    yt = eyeY;
    zt = eyeZ;
    lx = lookAtX - xt;
    ly = lookAtY - yt;
    lz = lookAtZ - zt;
    radius = getRadius(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ);
    alpha = atan2(lz, lx);
    beta_ang = asin(ly / radius);

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
    gluPerspective(c.getCamara()["projection"][0] ,ratio,c.getCamara()["projection"][1],c.getCamara()["projection"][2] );

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

int bindModel(std::vector<float> modelo,std::vector<float> modelon,std::vector<float> modelot, GLuint vbo,GLuint lvbo,GLuint tvbo,GLuint tid,std::string path) {
    std::vector<float> vfm = modelo;
    std::vector<float> vfmn = modelon;
    std::vector<float> vft = modelot;
    if (path.compare("") == 0){
        tid = 0;
    }else{
        tid = loadTexture(path);
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vfm.size() * sizeof(float), vfm.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,lvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vfmn.size(), vfmn.data(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, tvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * vft.size(), vft.data(), GL_STATIC_DRAW);
    return tid;
}

void renderModel(std::vector<float> modelo,std::vector<float> modelon,std::vector<float> modelot,Color cor,GLuint vbo,GLuint vbon,GLuint vbot,GLuint tid,std::string path) {
    std::vector<float> vfm = modelo;
    std::vector<float> vfmn = modelon;
    std::vector<float> vft = modelot;
    if (vfmn.size()>0){
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,vbon);
    glNormalPointer(GL_FLOAT,0,0);
    //glBufferData(GL_ARRAY_BUFFER, vfm.size() * sizeof(float), vfm.data(), GL_STATIC_DRAW);
    if (path.compare("") != 0){

        glBindTexture(GL_TEXTURE_2D,tid);

        glBindBuffer(GL_ARRAY_BUFFER,vbot);
        glTexCoordPointer(2,GL_FLOAT,0,0);


    }
    glEnableClientState(GL_VERTEX_ARRAY);

    if (fillModel){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cor.ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cor.difuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cor.specular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,cor.emissive);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, cor.shininess);

    glDrawArrays(GL_TRIANGLES, 0, vfm.size());
    glBindTexture(GL_TEXTURE_2D,0);
    glDisableClientState(GL_VERTEX_ARRAY);
    }else{
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexPointer(3,GL_FLOAT,0,0);
        //glBufferData(GL_ARRAY_BUFFER, vfm.size() * sizeof(float), vfm.data(), GL_STATIC_DRAW);
        glEnableClientState(GL_VERTEX_ARRAY);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        glColor3f(1.0f, 1.0f, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, vfm.size());
        glDisableClientState(GL_VERTEX_ARRAY);

    }
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void printMatrix(GLenum matrixName) {
    GLfloat matrix[16];
    glGetFloatv(matrixName, matrix);
    std::cout << "Matrix " << matrixName << ":\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
}

void printModelviewMatrix() {
    printMatrix(GL_MODELVIEW_MATRIX);
}
void renderCatmullRomCurve(int t,int p, std::vector<Ponto> points) {

    float pos[3];
    float deriv[3];
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < t; ++i) {

        getGlobalCatmullRomPoint(static_cast<float>(i)/static_cast<float>(t),pos,deriv,p,points);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}

void traverseDepthFirst(Node& node, int* i, int level = 0) {
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glPushMatrix();
    std::vector<Matrix4x4> mx;
    int t = 0;
    int a = 0;
    for (char w : node.indices){
        if (w == 't'){
            mx.push_back(node.matrices[t]);
            t++;
        }
        else{
            if (mx.size() > 0){
                Matrix4x4 f = multiplyMatrices(mx);
                GLfloat glMatrix[]{
                        1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f
                };

                matrix4x4ToGLfloat(f,glMatrix);

                //std::cout << "Processing node at level " << level << std::endl;
                glMultMatrixf(glMatrix);
                mx.clear();
            }
            Animation anim = node.animations[a];
            a++;
            int timemili = anim.time * 1000;
            if (anim.type == 't'){
                if (showO){
                    renderCatmullRomCurve(timemili,anim.points.size(),anim.points);
                }
                if (anim.align){

                    float pos[3] = {0.0f};
                    float deriv[3] = {0.0f};
                    float z[3] = {0.0f};
                    float gt = static_cast<float>(glutGet(GLUT_ELAPSED_TIME) % timemili) / static_cast<float>(timemili);
                    getGlobalCatmullRomPoint(gt,pos,deriv,anim.points.size(),anim.points);
                    glTranslatef(pos[0],pos[1],pos[2]);
                    normalize(deriv);
                    float tempy[3] = {anim.y[0], anim.y[1], anim.y[2]};
                    cross(deriv,tempy,z);
                    normalize(z);
                    cross(z,deriv,tempy);
                    normalize(tempy);
                    float m[16];
                    buildRotMatrix(deriv,tempy,z,m);
                    glMultMatrixf(m);


                    for(int k = 0; k < 3; k++) {
                        anim.y[k] = tempy[k];
                    }


                } else {
                    float pos[3] = {0.0f};
                    float deriv[3] = {0.0f};
                    float z[3] = {0.0f};
                    float gt = static_cast<float>(glutGet(GLUT_ELAPSED_TIME) % timemili) / static_cast<float>(timemili);
                    getGlobalCatmullRomPoint(gt,pos,deriv,anim.points.size(),anim.points);
                    glTranslatef(pos[0],pos[1],pos[2]);

                }
            }else if(anim.type == 'r'){
                float gt = static_cast<float>(glutGet(GLUT_ELAPSED_TIME) % timemili) / static_cast<float>(timemili);
                std::vector<Matrix4x4> mr;
                Matrix4x4 mtemp{};
                float angle = 360.0f * gt;
                float ang = angle * (M_PI / 180); // converter para radianos
                if (anim.y[0] == 1){

                    mtemp.data[0][0] = 1;mtemp.data[0][1] = 0;mtemp.data[0][2] = 0;mtemp.data[0][3] = 0;
                    mtemp.data[1][0] = 0;mtemp.data[1][1] = cosf(ang);mtemp.data[1][2] = -sinf(ang);mtemp.data[1][3] = 0;
                    mtemp.data[2][0] = 0;mtemp.data[2][1] = sinf(ang);mtemp.data[2][2] = cosf(ang);mtemp.data[2][3] = 0;
                    mtemp.data[3][0] = 0;mtemp.data[3][1] = 0;mtemp.data[3][2] = 0;mtemp.data[3][3] = 1;

                } else if(anim.y[1] == 1){
                    mtemp.data[0][0] = cosf(ang);mtemp.data[0][1] = 0;mtemp.data[0][2] = sinf(ang);mtemp.data[0][3] = 0;
                    mtemp.data[1][0] = 0;mtemp.data[1][1] = 1;mtemp.data[1][2] = 0;mtemp.data[1][3] = 0;
                    mtemp.data[2][0] = -sinf(ang);mtemp.data[2][1] = 0;mtemp.data[2][2] = cosf(ang);mtemp.data[2][3] = 0;
                    mtemp.data[3][0] = 0;mtemp.data[3][1] = 0;mtemp.data[3][2] = 0;mtemp.data[3][3] = 1;

                }else if(anim.y[2]){
                    mtemp.data[0][0] = cosf(ang);mtemp.data[0][1] = -sinf(ang);mtemp.data[0][2] =0;mtemp.data[0][3] = 0;
                    mtemp.data[1][0] = sinf(ang);mtemp.data[1][1] = cosf(ang);mtemp.data[1][2] = 0;mtemp.data[1][3] = 0;
                    mtemp.data[2][0] = 0;mtemp.data[2][1] = 0;mtemp.data[2][2] = 1;mtemp.data[2][3] = 0;
                    mtemp.data[3][0] = 0;mtemp.data[3][1] = 0;mtemp.data[3][2] = 0;mtemp.data[3][3] = 1;
                }
                mr.push_back(mtemp);
                Matrix4x4 f = multiplyMatrices(mr);
                GLfloat glMatrix[]{
                        1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f
                };

                matrix4x4ToGLfloat(f,glMatrix);
                glMultMatrixf(glMatrix);
            }
        }
    }

    if (mx.size() > 0){
        Matrix4x4 f = multiplyMatrices(mx);
        GLfloat glMatrix[]{
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        };

        matrix4x4ToGLfloat(f,glMatrix);

        //std::cout << "Processing node at level " << level << std::endl;
        glMultMatrixf(glMatrix);
        mx.clear();
    }

    for (auto &child: node.children) {
        traverseDepthFirst(child,i, level + 1);

    }

    if (node.modelsf.size() > 0) {
        for (int j = 0; j < node.modelsf.size(); (*i)++,j++) {
           // std::cout << "Rendering model " << j << " of node at level " << level <<" with id: "<<*i<<std::endl;
            renderModel(node.modelsf[j],node.normalsf[j],node.modelst[j],node.colors[j], buffers[*i],normals[*i],textures[*i],texIds[*i],node.texVector[j]);

        }
    }
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glPopMatrix();

    // Print other information of the node as needed
}

void traverseDepthFirstBind(const Node& node, int* i, int level = 0) {

    for (const auto &child : node.children) {
        traverseDepthFirstBind(child, i, level + 1);
    }

    if (node.modelsf.size() > 0) {
        for (int j = 0; j < node.modelsf.size(); (*i)++,j++) {
            texIds[*i] = bindModel(node.modelsf[j],node.normalsf[j],node.modelst[j], buffers[*i],normals[*i],textures[*i],texIds[*i],node.texVector[j]);

        }
    }

    // Print other information of the node as needed
}


void renderScene(void) {

    // clear buffers
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    //gluLookAt
    float ux = c.getCamara()["up"][0], uy = c.getCamara()["up"][1], uz = c.getCamara()["up"][2];
    if (!cinema){
        sphericalToCartesian(alpha, beta_ang, radius, rx, ry, rz);
        // set the camera

        // Up vector


        gluLookAt(xt, yt, zt, rx + xt, ry + yt, rz + zt, ux, uy, uz);
    }else{

        CinemaMode cm = c.getCinemaMode();
        float pos[3] = {0.0f};
        float deriv[3] = {0.0f};
        int timemili = cm.time * 1000;
        float gt = static_cast<float>(glutGet(GLUT_ELAPSED_TIME) % timemili) / static_cast<float>(timemili);
        getGlobalCatmullRomPoint(gt,pos,deriv,cm.points.size(),cm.points);
        gluLookAt(pos[0], pos[1], pos[2], cm.lookAt[0],cm.lookAt[1], cm.lookAt[2], ux, uy, uz);
    }
    for (int i = 0; i < c.getLuz().size();++i){
        Light l = c.getLuz()[i];

        if (l.tipo =='p'){

            float pos[4];
            pos[0] = l.pos[0];
            pos[1] = l.pos[1];
            pos[2] = l.pos[2];
            pos[3] = 1;
            glLightfv(GL_LIGHT0 + i, GL_POSITION, pos);

        }
        if (l.tipo =='d'){

            float pos[4];
            pos[0] = l.dir[0];
            pos[1] = l.dir[1];
            pos[2] = l.dir[2];
            pos[3] = 0;
            glLightfv(GL_LIGHT0 + i, GL_POSITION, pos);

        }
        if (l.tipo =='s'){

            float pos[4];
            pos[0] = l.pos[0];
            pos[1] = l.pos[1];
            pos[2] = l.pos[2];
            pos[3] = 1;
            float dir[3];
            dir[0] = l.dir[0];
            dir[1] = l.dir[1];
            dir[2] = l.dir[2];
            glLightfv(GL_LIGHT0 + i, GL_POSITION, pos);
            glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, dir);
            glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF,l.cutoff);

        }

    }


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
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnd();
    }
    int i =0;
    traverseDepthFirst(c.getRaizes()[0],&i);



    frame++;
    int time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        fps = frame*1000.0/(time-timebase);
        timebase = time;
        frame = 0;
    }
    char buffer [50];
    sprintf(buffer,"%.2f",fps);
    if(showFps)
        cout<<buffer<<"\n";

    // End of frame
    glutSwapBuffers();
}


float speed = 0.01f; // Velocidade de andamento

void computePos(float deltaMove) {
    xt += deltaMove * rx;
    yt += deltaMove * ry;
    zt += deltaMove * rz;
}

void computePos2(float deltaMove) {
    // Objetivo desta função é calcular uma perpendicular
    float cx = rx, cy = ry, cz = rz; // Direções da camara
    float ux = c.getCamara()["up"][0], uy = c.getCamara()["up"][1], uz = c.getCamara()["up"][2]; // Up vector

    float px, py, pz; // Calcular a direção perpendicular
    px = cy * uz - uy * cz;
    py = cz * ux - uz * cx;
    pz = cx * uy - ux * cy;

    // Normalizar a perpendicular
    float length = sqrt(px * px + py * py + pz * pz);
    px /= length;
    pz /= length;

    xt += deltaMove * px;
    zt += deltaMove * pz;
}

void processKeys(unsigned char key, int xx, int yy) {

    switch (key) {
        case 'w':
            computePos(speed);
            break;
        case 's':
            computePos(-speed);
            break;
        case 'a':
            computePos2(-speed*4);
            break;
        case 'd':
            computePos2(+speed*4);
            break;
        case 'f':
            yt += speed*4;
            break;
        case 'g':
            yt -= speed*4;
            break;
        case 'x':
            if (axis)
                axis = false;
            else
                axis = true;
            break;
        case 'c':
            if (cinema)
                cinema = false;
            else{
                if (!c.getCinemaMode().points.empty()){
                    cout<<"Cinema Mode On\n";
                    cinema = true;
                }

            }
            break;
        case 'z':
            if (showFps)
                showFps = false;
            else
                showFps = true;
            break;
        case 'o':
            if (showO)
                showO = false;
            else
                showO = true;
            break;
        case 'l':
            if (fillModel)
                fillModel = false;
            else
                fillModel = true;
            break;
    }
    glutPostRedisplay();
}

// Define variables to hold the last mouse position
int lastMouseX = -1;
int lastMouseY = -1;

void processMouseMotion(int x, int y) {
    if (lastMouseX == -1 || lastMouseY == -1) {
        lastMouseX = x;
        lastMouseY = y;
        return;
    }

    // Compute the change in mouse position
    float deltaX = x - lastMouseX;
    float deltaY = y - lastMouseY;

    float rotationSpeed = 0.01f;

    // Update camera alpha and beta_ang based on mouse movement
    alpha += deltaX * rotationSpeed;
    beta_ang -= deltaY * rotationSpeed;  // Invert the Y-axis here

    // Clamp the vertical angle to prevent flipping
    if (beta_ang > M_PI / 2.0f) beta_ang = M_PI / 2.0f;
    if (beta_ang < -M_PI / 2.0f) beta_ang = -M_PI / 2.0f;

    // Update the camera look direction based on alpha and beta_ang
    sphericalToCartesian(alpha, beta_ang, radius, rx, ry, rz);

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
    float rotationSpeed = 0.02f;

    switch (key) {
        case GLUT_KEY_LEFT:
            alpha -= rotationSpeed;
            break;
        case GLUT_KEY_RIGHT:
            alpha += rotationSpeed;
            break;
        case GLUT_KEY_UP:
            beta_ang += rotationSpeed;
            if (beta_ang > M_PI / 2.0)
                beta_ang = M_PI / 2.0;
            break;
        case GLUT_KEY_DOWN:
            beta_ang -= rotationSpeed;
            if (beta_ang < -M_PI / 2.0)
                beta_ang = -M_PI / 2.0;
            break;

    }


    if (alpha > 2 * M_PI)
        alpha -= 2 * M_PI;
    else if (alpha < 0)
        alpha += 2 * M_PI;

    glutPostRedisplay();
}

void initLight(int num) {
    glEnable(GL_LIGHTING);
    glEnable(GL_RESCALE_NORMAL);
    float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

    // Ativar luzes todas
    for (int i = 0; i < num; ++i) {
        glEnable(GL_LIGHT0 + i);

        float dark[4] = {1, 1, 1, 1.0};
        float white[4] = {1.0, 1.0, 1.0, 1.0};
        float black[4] = {0.0f, 0.0f, 0.0f, 0.0f};
// light colors
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, dark);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, white);
// controls global ambient light
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
        // glLightfv definir
    }

}

int main(int argc, char **argv) {

    c = fromXml(argv[1]);
// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(get<0>(c.getJanela()),get<1>(c.getJanela()));
    glutCreateWindow(argv[1]);
    initializeCamera(c.getCamara()["position"][0] + xt,c.getCamara()["position"][1] + yt,c.getCamara()["position"][2]+zt,
                     c.getCamara()["lookAt"][0] + xt,c.getCamara()["lookAt"][1] + yt,c.getCamara()["lookAt"][2] + zt);

// Required callback registry
    timebase = glutGet(GLUT_ELAPSED_TIME);
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutMotionFunc(processMouseMotion);
    glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    #ifndef __APPLE__
        glewInit();
    #endif
    int num_models = c.getTotalModelsInTree();
    buffers = new GLuint[num_models];
    normals = new GLuint[num_models];
    textures = new GLuint[num_models];
    texIds = new GLuint[num_models];
    glGenBuffers(num_models, buffers);  // Generate VBOs
    glGenBuffers(num_models, normals);  // Generate VBOs
    glGenBuffers(num_models, textures);  // Generate VBOs

    if (c.getLuz().size() == 0){

    }else{
        initLight(c.getLuz().size());

    }
    glEnable(GL_TEXTURE_2D);



    int i = 0;
    traverseDepthFirstBind(c.getRaizes()[0],&i);


// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
