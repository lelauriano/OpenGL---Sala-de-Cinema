#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>

float angulo = 0.0;
float zoom = 15.0;

GLuint texturaPoltrona;

void criarTextura() {
    const int size = 64;
    GLubyte data[size][size][3];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int checker = ((i / 8) % 2) ^ ((j / 8) % 2);
            if (checker) {
                data[i][j][0] = 180; data[i][j][1] = 0; data[i][j][2] = 0;
            } else {
                data[i][j][0] = 120; data[i][j][1] = 0; data[i][j][2] = 0;
            }
        }
    }
    glGenTextures(1, &texturaPoltrona);
    glBindTexture(GL_TEXTURE_2D, texturaPoltrona);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void setupLighting() {
    glEnable(GL_LIGHTING);

    // Luz ambiente geral 
    GLfloat ambiente[] = {0.12f, 0.08f, 0.08f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente);

    // Luz frontal/teto (principal)
    glEnable(GL_LIGHT0);
    GLfloat pos0[]  = {0.0f,  7.5f, -5.0f, 1.0f};
    GLfloat dif0[]  = {0.55f, 0.50f, 0.50f, 1.0f};
    GLfloat spec0[] = {0.3f,  0.3f,  0.3f,  1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

    //Luz lateral
    glEnable(GL_LIGHT1);
    GLfloat pos1[]  = {-9.0f, 3.0f, -2.0f, 1.0f};
    GLfloat dif1[]  = {0.55f, 0.35f, 0.10f, 1.0f};  // âmbar quente
    GLfloat spec1[] = {0.1f,  0.05f, 0.0f,  1.0f};
    GLfloat atten1  = 0.04f;
    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  dif1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
    glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION, atten1);

    glEnable(GL_LIGHT2);
    GLfloat pos2[]  = {-9.0f, 3.0f,  4.0f, 1.0f};
    GLfloat dif2[]  = {0.50f, 0.30f, 0.08f, 1.0f};
    GLfloat spec2[] = {0.0f,  0.0f,  0.0f,  1.0f};
    glLightfv(GL_LIGHT2, GL_POSITION, pos2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  dif2);
    glLightf (GL_LIGHT2, GL_QUADRATIC_ATTENUATION, atten1);

    //Luz de borda do palco/tela 
    glEnable(GL_LIGHT3);
    GLfloat pos3[]  = {0.0f, 1.5f, -9.2f, 1.0f};
    GLfloat dif3[]  = {0.20f, 0.25f, 0.50f, 1.0f};
    GLfloat spec3[] = {0.1f,  0.1f,  0.2f,  1.0f};
    glLightfv(GL_LIGHT3, GL_POSITION, pos3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE,  dif3);
    glLightfv(GL_LIGHT3, GL_SPECULAR, spec3);
    glLightf (GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.06f);
}

void setMaterial(float r, float g, float b,
                 float amb_factor,
                 float spec_r, float spec_g, float spec_b,
                 float shininess) {
    GLfloat amb[]  = {r*amb_factor, g*amb_factor, b*amb_factor, 1.0f};
    GLfloat dif[]  = {r, g, b, 1.0f};
    GLfloat spec[] = {spec_r, spec_g, spec_b, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  spec);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, shininess);
} 
void drawWallLamp(float y, float z) {
    glPushMatrix();
        glTranslatef(-9.85f, y, z);
        setMaterial(0.25f, 0.20f, 0.10f, 0.4f, 0.4f, 0.35f, 0.25f, 40.0f);
        glColor3f(0.25f, 0.20f, 0.10f);
        glScalef(0.12f, 0.25f, 0.12f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-9.75f, y - 0.10f, z);
        glRotatef(90.0f, 0, 1, 0);   
        setMaterial(0.90f, 0.70f, 0.20f, 0.5f, 0.8f, 0.7f, 0.3f, 60.0f);
        glColor3f(0.90f, 0.70f, 0.20f);
        GLUquadric* q = gluNewQuadric();
        gluCylinder(q, 0.12, 0.0, 0.20, 12, 4);  
        gluDeleteQuadric(q);
    glPopMatrix();
}
void drawRoom() {
    glDisable(GL_TEXTURE_2D);

    setMaterial(0.18f, 0.18f, 0.18f, 0.3f, 0.05f, 0.05f, 0.05f, 10.0f);//chao
    glPushMatrix();
        glColor3f(0.18f, 0.18f, 0.18f);
        glScalef(20.0f, 0.1f, 20.0f);
        glutSolidCube(1);
    glPopMatrix();

    setMaterial(0.06f, 0.06f, 0.06f, 0.3f, 0.0f, 0.0f, 0.0f, 5.0f);//teto
    glPushMatrix();
        glColor3f(0.06f, 0.06f, 0.06f);
        glTranslatef(0, 8, 0);
        glScalef(20.0f, 0.1f, 20.0f);
        glutSolidCube(1);
    glPopMatrix();

    //parede avermelhada onde fica a tela 
    setMaterial(0.50f, 0.04f, 0.04f, 0.35f, 0.15f, 0.05f, 0.05f, 20.0f);
    glPushMatrix();
        glColor3f(0.50f, 0.04f, 0.04f);
        glTranslatef(0, 4, -10);
        glScalef(20.0f, 8.0f, 0.1f);
        glutSolidCube(1);
    glPopMatrix();

    // parede esquerda 
    setMaterial(0.14f, 0.11f, 0.11f, 0.3f, 0.05f, 0.05f, 0.05f, 10.0f);
    glPushMatrix();
        glColor3f(0.14f, 0.11f, 0.11f);
        glTranslatef(-10, 4, 0);
        glScalef(0.1f, 8.0f, 20.0f);
        glutSolidCube(1);
    glPopMatrix();
}
void drawWallLamps() {
    // luminárias na parede esquerda
    float zPositions[] = {-7.0f, -4.0f, -1.0f, 2.0f, 5.0f};
    int n = 5;
    for (int i = 0; i < n; i++) {
        drawWallLamp(3.5f, zPositions[i]);
    }
}
//tela
void drawScreen() {
    // emissor branco — simula tela iluminada
    GLfloat emissao[] = {0.95f, 0.95f, 1.0f, 1.0f};
    GLfloat sem[]     = {0.0f,  0.0f,  0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, emissao);

    glPushMatrix();
        glTranslatef(0, 4.2f, -9.5f);
        glColor3f(1, 1, 1);
        glScalef(9.0f, 5.0f, 0.15f);
        glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, sem);

    // moldura preta ao redor da tela
    setMaterial(0.05f, 0.05f, 0.05f, 0.3f, 0.0f, 0.0f, 0.0f, 5.0f);
    glPushMatrix();
        glTranslatef(0, 4.2f, -9.4f);
        glColor3f(0.05f, 0.05f, 0.05f);
        glScalef(9.6f, 5.6f, 0.08f);
        glutSolidCube(1);
    glPopMatrix();
}
//palco abaixo da tela
void drawStage() {
    // Cor amadeirada marrom
    setMaterial(0.45f, 0.25f, 0.08f, 0.35f, 0.25f, 0.15f, 0.05f, 30.0f);
    glPushMatrix();
        glTranslatef(0, 0.5f, -8.0f);
        glColor3f(0.45f, 0.25f, 0.08f);
        glScalef(14.0f, 1.0f, 3.0f);
        glutSolidCube(1);
    glPopMatrix();
}
void drawStep(float x, float y, float z, float w, float h, float d) {
    setMaterial(0.42f, 0.22f, 0.07f, 0.35f, 0.20f, 0.12f, 0.04f, 25.0f);
    glPushMatrix();
        glTranslatef(x, y, z);
        glColor3f(0.42f, 0.22f, 0.07f);
        glScalef(w, h, d);
        glutSolidCube(1);
    glPopMatrix();
}
void drawBox(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b, float emission = 0.0f) {
    GLfloat e[] = {0, emission, 0, 1};
    glMaterialfv(GL_FRONT, GL_EMISSION, e);
    setMaterial(r, g, b, 0.3f, 0.2f, 0.2f, 0.2f, 20.0f);
    glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);
        glColor3f(r, g, b);
        glutSolidCube(1.0);
    glPopMatrix();
    GLfloat none[] = {0, 0, 0, 1};
    glMaterialfv(GL_FRONT, GL_EMISSION, none);
}
void drawDoor() {
    //porta saida
    drawBox(-9.9f, 2.5f, 8.0f, 0.15f, 5.0f, 2.5f, 0.05f, 0.05f, 0.05f);
    drawBox(-9.82f, 2.3f, 8.0f, 0.1f, 0.1f, 2.3f, 0.7f, 0.7f, 0.7f);

    //placa exit
    drawBox(-9.85f, 5.3f, 8.0f, 0.12f, 0.6f, 1.3f, 0.0f, 0.0f, 0.0f);
    drawBox(-9.83f, 5.3f, 8.0f, 0.1f, 0.45f, 1.15f, 0.0f, 0.9f, 0.0f, 1.0f);
    drawBox(-9.81f, 5.3f, 7.6f, 0.05f, 0.15f, 0.15f, 1.0f, 0.0f, 0.0f, 0.5f);
}
//poltronas vermelhas
void drawChair(float x, float y, float z) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaPoltrona);

    GLfloat amb[]  = {0.25f, 0.02f, 0.02f, 1.0f};
    GLfloat dif[]  = {0.80f, 0.05f, 0.05f, 1.0f};
    GLfloat spec[] = {0.30f, 0.10f, 0.10f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  spec);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 35.0f);

    glPushMatrix();
        glTranslatef(x, y + 0.3f, z);
        glColor3f(1, 1, 1);  // cor modulada pela textura

        // assento
        glPushMatrix();
            glScalef(0.75f, 0.35f, 0.75f);
            glutSolidCube(1);
        glPopMatrix();

        // encosto
        glPushMatrix();
            glTranslatef(0, 0.45f, 0.30f);
            glScalef(0.75f, 0.75f, 0.18f);
            glutSolidCube(1);
        glPopMatrix();

        // pernas 
        glDisable(GL_TEXTURE_2D);
        setMaterial(0.20f, 0.18f, 0.16f, 0.3f, 0.5f, 0.5f, 0.5f, 60.0f);
        glColor3f(0.20f, 0.18f, 0.16f);

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

    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        zoom * sin(angulo), 5.0f, zoom * cos(angulo),
        0, 2, -5,
        0, 1, 0
    );

    setupLighting();

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
    	float yCentro = alturaTotal / 2.0f;
    	drawStep(0, yCentro, zPos, 14.0f, alturaTotal, profDegrau);

    for (int j = 0; j < 10; j++) {
        drawChair(-6.0f + j * 1.30f, yTopo + altDegrau, zPos);
    }
}

    glutSwapBuffers();
}

// controles da sala
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': case 'A': 
		angulo -= 0.08f; 
			break;
        case 'd': case 'D': 
		angulo += 0.08f; 
			break;
        case 'w': case 'W': 
		if (zoom > 3.0f) zoom -= 1.0f; 
			break;
        case 's': case 'S': 
		if (zoom < 30.0f) zoom += 1.0f; 
			break;
        case 27: exit(0);
    }
    glutPostRedisplay();
}
void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//fundo branco
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    criarTextura();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 0.5, 150.0);

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
