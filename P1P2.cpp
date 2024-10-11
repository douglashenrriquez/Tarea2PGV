#include <iostream>
#include "GL/glut.h"
#include <math.h>


using namespace std;

GLsizei ancho = 1024, alto = 768; 

void pintapixel(int cx, int cy, float red, float green, float blue, int tam);
void Ejes();
void mouse(int click, int estado, int cx, int cy);
void Pintalinea(int x1, int x2, int y1, int y2);

int cx1, cy1, cx2, cy2;

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(ancho, alto);
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("Dibujar una linea");
    glutMouseFunc(mouse);
    gluOrtho2D(-(ancho / 2), ancho / 2, -(alto / 2), alto / 2); 
    glutDisplayFunc(Ejes);
    glutMainLoop();
    return 0;
}

void Ejes() {
    for (int i = -(ancho / 2); i < ancho / 2; i++) {
        pintapixel(i, 0, 1, 1, 1, 2);
    }
    for (int i = -(alto / 2); i < alto / 2; i++) {
        pintapixel(0, i, 1, 1, 1, 2);
    }
}

void pintapixel(int cx, int cy, float red, float green, float blue, int tam) {
    glPointSize(tam);
    glBegin(GL_POINTS);
    glColor3f(red, green, blue);
    glVertex2d(cx, cy);
    glEnd();
    glFlush();
}

void mouse(int click, int estado, int cx, int cy) {
    if (click == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        cx1 = cx - (ancho / 2);
        cy1 = (alto / 2) - cy;
        pintapixel(cx1, cy1, 0, 0, 1, 5);
    }
    else if (click == GLUT_LEFT_BUTTON && estado == GLUT_UP) {
        cx2 = cx - (ancho / 2);
        cy2 = (alto / 2) - cy;
        cout << "cx:" << cx1 << endl;
        cout << "cy:" << cy1 << endl;
        cout << "cx2:" << cx2 << endl;
        cout << "cy2:" << cy2 << endl;
        pintapixel(cx2, cy2, 1, 0.5, 0, 5);
        Pintalinea(cx1, cx2, cy1, cy2);
    }
}

void Pintalinea(int x1, int x2, int y1, int y2) {
    int x, y, ini, fin, Dx, Dy;
    float m, b;
    Dx = x2 - x1;
    Dy = y2 - y1;

    if (Dx != 0) {
        m = (float)Dy / (float)Dx;
        b = y1 - m * x1;
        cout << "Dy:" << Dy << endl;
        cout << "Dx:" << Dx << endl;
        cout << "m:" << m << endl;
        cout << "\n" << endl;


        if (abs(Dx) >= abs(Dy)) {
            ini = (x1 <= x2) ? x1 : x2;
            fin = (x1 <= x2) ? x2 : x1;
            for (x = ini; x <= fin; x++) {
                y = m * x + b;
                pintapixel(x, y, 0, 1, 0, 3);
            }
        }
        else {
            ini = (y1 <= y2) ? y1 : y2;
            fin = (y1 <= y2) ? y2 : y1;
            for (y = ini; y <= fin; y++) {
                x = (y - b) / m;
                pintapixel(x, y, 1, 0, 0, 3);
            }
        }
    }
    else {
        ini = (y1 <= y2) ? y1 : y2;
        fin = (y1 <= y2) ? y2 : y1;
        for (y = ini; y <= fin; y++) {
            pintapixel(x1, y, 1, 0, 1, 3);
        }
    }
}
