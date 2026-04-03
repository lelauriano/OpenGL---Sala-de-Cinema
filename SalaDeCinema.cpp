#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>

float angulo = 0.0;
float zoom = 15.0;

void drawRoom() {

    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(0, 0, 0);
        glScalef(20, 0.1, 20);
        glutSolidCube(1);
    glPopMatrix();//chão

    glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(0, 8, 0);
        glScalef(20, 0.1, 20);
        glutSolidCube(1);
    glPopMatrix();//teto

    glPushMatrix(); // parede esq
        glColor3f(0.15, 0.15, 0.15);
        glTranslatef(-10, 4, 0);
        glScalef(0.1, 8, 20);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); // parede fundo
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(0, 4, -10);
        glScalef(20, 8, 0.1);
        glutSolidCube(1);
    glPopMatrix();
}

void drawScreen() { //tela branca
    glPushMatrix();
        glTranslatef(0, 4, -9.5);
        glColor3f(1, 1, 1);
        glScalef(8, 4, 0.2);
        glutSolidCube(1);
    glPopMatrix();
}

void drawStage() { // palco marrom 
    glPushMatrix();
        glTranslatef(0, 1, -8);
        glColor3f(0.4, 0.2, 0.1);
        glScalef(8, 0.5, 2);
        glutSolidCube(1);
    glPopMatrix();
}

void drawChair(float x, float y, float z) {
    glPushMatrix();
        glTranslatef(x, y + 0.5, z);
        glRotatef(180, 0, 1, 0);

        // base da poltrona
        glColor3f(1, 0, 0);
        glPushMatrix();
            glScalef(0.8, 0.4, 0.8);
            glutSolidCube(1);
        glPopMatrix();

        // encosto da poltrona
        glPushMatrix();
            glTranslatef(0, 0.5, -0.3);
            glScalef(0.8, 0.8, 0.2);
            glutSolidCube(1);
        glPopMatrix();

        // detalhe em amarelo
        glPushMatrix();
            glTranslatef(0, 1.0, -0.3);
            glColor3f(1, 1, 0);
            glutSolidSphere(0.1, 20, 20);
        glPopMatrix();

    glPopMatrix();
}

void drawStep(float z, float largura, float altura){
	glPushMatrix();
		glTranslatef(0, 0, z);
		glScalef(largura,altura,1.5);
		glColor3f(0.2, 0.2, 0.2);
		glutSolidCube(1);
	glPopMatrix();
}


void drawLights() {
    GLUquadric *q = gluNewQuadric();

    for (float z = 5; z > -8; z -= 2.0) {

        // suporte em forma decilindro
        glPushMatrix();
            glTranslatef(-9.5, 3, z);
            glRotatef(90, 1, 0, 0);
            glColor3f(0.3, 0.3, 0.3);
            gluCylinder(q, 0.1, 0.1, 0.5, 10, 10);
        glPopMatrix();

        // luz lateral
        glPushMatrix();
            glTranslatef(-9.5, 3, z);
            glColor3f(1, 1, 0.5);
            glutSolidSphere(0.2, 20, 20);
        glPopMatrix();
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        zoom * sin(angulo), 5, zoom * cos(angulo),
        0, 2, -5,
        0, 1, 0
    );

    drawRoom();
    drawScreen();
    drawStage();
    drawLights();

    // poltronas
    for(int fil = 0; fil < 6; fil++){
    	drawStep(-5+(1.5*fil),6*1.5,0.5+fil);
    	for(int col = 0; col < 6; col++){
    		drawChair(-4+(1.5*col), 0.5*fil, -5+(1.5*fil));
		}
	}

    glutSwapBuffers();
}

// controle da sala 
void keyboard(unsigned char key, int x, int y) {
    
    // Verifica qual tecla foi pressionada
    switch (key) {

        case 'a': // gira a câmera para a esq
            angulo -= 0.1;
            break;

        case 'd': //gira a câmera para a dir
            angulo += 0.1;
            break;

        case 'w'://aproxima a câmera (entra na cena)
            zoom -= 1.0;
            break;

        case 's': // Aumenta o zoom, afasta a câmera (sai da cena)
            zoom += 1.0;
            break;

        case 27:
            exit(0);
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutCreateWindow("Sala de Cinema");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
