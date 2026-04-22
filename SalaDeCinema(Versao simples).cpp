#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>

float angulo = 0.0;
float zoom = 15.0;

void drawWallLamp(float y, float z) {
    glPushMatrix();
        glTranslatef(-9.85f, y, z);
        glColor3f(0.3f, 0.25f, 0.1f); // Marrom escuro
        glScalef(0.12f, 0.25f, 0.12f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-9.75f, y - 0.10f, z);
        glRotatef(90.0f, 0, 1, 0);   
        glColor3f(1.0f, 0.9f, 0.0f); // Amarelo brilhante (simulando luz acesa)
        GLUquadric* q = gluNewQuadric();
        gluCylinder(q, 0.12, 0.0, 0.20, 12, 4);  
        gluDeleteQuadric(q);
    glPopMatrix();
}

void drawRoom() {
    // chao
    glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f);
        glScalef(20.0f, 0.1f, 20.0f);
        glutSolidCube(1);
    glPopMatrix();

    // teto
    glPushMatrix();
        glColor3f(0.1f, 0.1f, 0.1f);
        glTranslatef(0, 8, 0);
        glScalef(20.0f, 0.1f, 20.0f);
        glutSolidCube(1);
    glPopMatrix();

    // parede frontal
    glPushMatrix();
        glColor3f(0.4f, 0.0f, 0.0f);
        glTranslatef(0, 4, -10);
        glScalef(20.0f, 8.0f, 0.1f);
        glutSolidCube(1);
    glPopMatrix();

    // parede esquerda 
    glPushMatrix();
        glColor3f(0.15f, 0.15f, 0.15f);
        glTranslatef(-10, 4, 0);
        glScalef(0.1f, 8.0f, 20.0f);
        glutSolidCube(1);
    glPopMatrix();
}

void drawWallLamps() {
    float zPositions[] = {-7.0f, -4.0f, -1.0f, 2.0f, 5.0f};
    for (int i = 0; i < 5; i++) {
        drawWallLamp(3.5f, zPositions[i]);
    }
}

void drawScreen() {
    glPushMatrix();
        glTranslatef(0, 4.2f, -9.5f);
        glColor3f(1.0f, 1.0f, 1.0f); // Branco puro
        glScalef(9.0f, 5.0f, 0.15f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 4.2f, -9.4f);
        glColor3f(0.0f, 0.0f, 0.0f); // Moldura preta
        glScalef(9.6f, 5.6f, 0.08f);
        glutSolidCube(1);
    glPopMatrix();
}

void drawStage() {
    glPushMatrix();
        glTranslatef(0, 0.5f, -8.0f);
        glColor3f(0.3f, 0.15f, 0.05f); // Madeira
        glScalef(14.0f, 1.0f, 3.0f);
        glutSolidCube(1);
    glPopMatrix();
}

void drawStep(float x, float y, float z, float w, float h, float d) {
    glPushMatrix();
        glTranslatef(x, y, z);
        glColor3f(0.25f, 0.15f, 0.05f);
        glScalef(w, h, d);
        glutSolidCube(1);
    glPopMatrix();
}

void drawBox(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b) {
    glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);
        glColor3f(r, g, b);
        glutSolidCube(1.0);
    glPopMatrix();
}

void drawDoor() {
    drawBox(-9.9f, 2.5f, 8.0f, 0.15f, 5.0f, 2.5f, 0.1f, 0.1f, 0.1f);//porta e placa de saida
    drawBox(-9.82f, 2.3f, 8.0f, 0.1f, 0.1f, 2.3f, 0.7f, 0.7f, 0.7f);
    drawBox(-9.85f, 5.3f, 8.0f, 0.12f, 0.6f, 1.3f, 0.0f, 0.0f, 0.0f);
    drawBox(-9.83f, 5.3f, 8.0f, 0.1f, 0.45f, 1.15f, 0.0f, 0.8f, 0.0f);
}

void drawChair(float x, float y, float z) {
    glPushMatrix();
        glTranslatef(x, y + 0.3f, z);
        
        // assento e encosto
        glColor3f(0.7f, 0.0f, 0.0f); 
        glPushMatrix();
            glScalef(0.75f, 0.35f, 0.75f);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0.45f, 0.30f);
            glScalef(0.75f, 0.75f, 0.18f);
            glutSolidCube(1);
        glPopMatrix();

        // pernas
        glColor3f(0.1f, 0.1f, 0.1f);
        float px[] = {-0.28f,  0.28f, -0.28f,  0.28f};
        float pz[] = {-0.28f, -0.28f,  0.28f,  0.28f};
        for (int k = 0; k < 4; k++) {
            glPushMatrix();
                glTranslatef(px[k], -0.18f, pz[k]);
                glRotatef(-90.0f, 1, 0, 0);
                GLUquadric* q = gluNewQuadric();
                gluCylinder(q, 0.04, 0.04, 0.32, 8, 2);
                gluDeleteQuadric(q);
            glPopMatrix();
        }
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        zoom * sin(angulo), 5.0f, zoom * cos(angulo),
        0, 2, -5,
        0, 1, 0
    );

    drawRoom();
    drawWallLamps();
    drawScreen();
    drawStage();
    drawDoor();

    float altDegrau = 0.40f;
    float profDegrau = 1.50f;

    for (int i = 0; i < 6; i++) {
        float yTopo = i * altDegrau;          
        float zPos = -5.0f + (i * profDegrau); 
        float alturaTotal = yTopo + altDegrau;
        drawStep(0, alturaTotal/2.0f, zPos, 14.0f, alturaTotal, profDegrau);

        for (int j = 0; j < 10; j++) {
            drawChair(-6.0f + j * 1.30f, yTopo + altDegrau, zPos);
        }
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': case 'A': angulo -= 0.08f; break;
        case 'd': case 'D': angulo += 0.08f; break;
        case 'w': case 'W': if (zoom > 3.0f) zoom -= 1.0f; break;
        case 's': case 'S': if (zoom < 30.0f) zoom += 1.0f; break;
        case 27: exit(0);
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.5, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cinema Sala");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
