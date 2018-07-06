#include "pieza.h"
#include "ofGraphics.h"

using namespace tuio;

piezas::piezas (float _angle, std::vector<DirectPoint> * _centros, pieza * _p) {
    angle = _angle;
    centros = _centros;
    p = _p;
}

void piezas::Draw() {
    glPushMatrix();
    glRotatef(angle,0.0f,0.0f,1.0f);
    for(int i = 0; i < centros->size(); i++) {
        glPushMatrix();
        glTranslatef((*centros)[i].getX(),(*centros)[i].getY(),0);
        p->Draw();
        glPushMatrix();
    }
    glPushMatrix();
}

void pieza::Draw() {
    glColor3d(0,60,90);
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.03f,0.03f,0.0f);
        glVertex3f(-0.03f,0.03f,0.0f);
        glVertex3f(-0.03f,-0.03f,0.0f);
        glVertex3f(0.03f,-0.03f,0.0f);
        glVertex3f(0.03f,0.03f,0.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.03f,0.03f,0.5f);
        glVertex3f(-0.03f,0.03f,0.5f);
        glVertex3f(-0.03f,-0.03f,0.5f);
        glVertex3f(0.03f,-0.03f,0.5f);
        glVertex3f(0.03f,0.03f,0.5f);
    glEnd();
}
