#include "state_editor.h"
#include "textures.h"
#include "sounds.h"

#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"

using namespace tuio;

state_editor::state_editor() {
    angle=0;
}

void state_editor::Draw() {
    ofSetColor(50,100,200);
    ofLine(0.5f,0.5f,0.5f+0.5f*cos(angle),0.5f+0.5f*sin(angle));



    for(int i = 0; i < puntos.size(); i++)
        puntos[i]->Draw();

    for(int i = 0; i < bloques.size(); i++)
        bloques[i]->Draw(angle);
}

state * state_editor::Process() {
    return this;
}

void state_editor::ObjectIN(DirectObject * o) {
    if(o->f_id==IDEDITORSANGLE) {
        angle = o->angle;
    }
}
void state_editor::ObjectUPDATE(DirectObject * o) {
    if(o->f_id==IDEDITORSANGLE) {
        angle = o->angle;
    }
}
void state_editor::ObjectOUT(DirectObject * o) {
    if(o->f_id==IDEDITORSTATE) {
        //Bloques a piezas
        //Vaciar vectores
    }
}

bool state_editor::areConnected(control_point * p1,control_point * p2) {
    for(int i = 0; i < bloques.size(); i++) {
        control_block * c = bloques[i];
        if( (c->p1 == p1) && (c->p2 == p2) )
            return true;
        if( (c->p2 == p1) && (c->p1 == p2) )
            return true;
    }
    return false;
}

void state_editor::FingerIN(DirectFinger * f) {
	bool processed = false;
    for(int i = 0; i < puntos.size() && !processed; i++) {
        processed |= (puntos[i]->updateFinger(f));
    }
    if(!processed) {
		control_point * p = new control_point(f);
		for(int i = 0; i < puntos.size() && !processed; i++) {
            control_point * q = puntos[i];
			if(q->isNear(f))
				bloques.push_back(new control_block(q, p));
		}
		puntos.push_back(p);
    }
}

void state_editor::FingerOUT(DirectFinger * f) {
    for(int i = 0; i < puntos.size(); i++) {
        puntos[i]->deleteFinger(f);
    }
}

void state_editor::FingerUPDATE(DirectFinger * f) {
    for(int i = 0; i < puntos.size(); i++)
        if(puntos[i]->updatePosition(f))
            for(int j = 0; j < puntos.size(); j++)
                if(i!=j)
                    if(puntos[j]->isNear(f))
                        if(!areConnected(puntos[j], puntos[i]))
                            bloques.push_back(new control_block(puntos[i], puntos[j]));
}


control_point::control_point(DirectFinger *f) {
    p.setX(f->getX());
    p.setY(f->getY());
    id = f->s_id;
}

float control_point::getX() {
    return p.getX();
}

float control_point::getY() {
    return p.getY();
}

bool control_point::isNear(DirectFinger * f) {
    return (p.getDistance(f->getX(), f->getY()) < 0.1f);
}

bool control_point::updateFinger(DirectFinger * f){
    if((id == 0)&&(p.getDistance(f->getX(), f->getY()) < 0.05f)) {
        p.setX(f->getX());
        p.setY(f->getY());
        id = f->s_id;
        return true;
    }
    return false;
}

bool control_point::updatePosition(DirectFinger * f){
    if(id == f->s_id) {
        p.setX(f->getX());
        p.setY(f->getY());
        return true;
    }
    return false;
}

void control_point::deleteFinger(DirectFinger * f){
    if(id == f->s_id) {
        p.setX(f->getX());
        p.setY(f->getY());
        id = 0;
    }
}

void control_point::Draw(){
    ofSetColor(55,20,20);
    ofCircle(p.getX(), p.getY(), 0.1f);
    ofSetColor(255,50,50);
    ofCircle(p.getX(), p.getY(), 0.03f);
}


control_block::control_block(control_point * _p1, control_point * _p2) {
    p1 = _p1;
    p2 = _p2;
}

void control_block::Draw(float angle) {
    ofSetColor(90,0,200);
    ofLine(p1->getX(), p1->getY(), p2->getX(), p2->getY());
    pieza p;

    float dx, dy;
    int repeticiones;

    float Ax = p2->getX()-p1->getX();
    float Ay = p2->getY()-p1->getY();

    float lineAngle = atan2f(Ay, Ax) - angle;
    float radius = sqrtf(powf(Ax,2)+powf(Ay,2));

    float Dx, Dy;
    Dx = radius*cosf(lineAngle);
    Dy = radius*sinf(lineAngle);

    if (abs(Dx)>= abs(Dy)) {
        repeticiones = (int) abs(floor(radius*cosf(lineAngle)/0.06f))-1;
        dx = radius*cosf(lineAngle) / (float) repeticiones;
        dy = dx * tanf(lineAngle);
    } else {
        repeticiones = (int) abs(floor(radius*sinf(lineAngle)/0.06f))-1;
        dy = radius*sinf(lineAngle) / (float) repeticiones;
        dx = dy / tanf(lineAngle);
    }

    glPushMatrix();
    glTranslatef(p1->getX(),p1->getY(), 0.0f);
    glRotatef(180*angle/M_PI,0.0f,0.0f,1.0f);
    p.Draw();
    for(int i = 0; i< repeticiones; i++) {
        glTranslatef(dx, dy,0.0f);
        glPushMatrix();
        p.Draw();
        glPopMatrix();
    }
    glPopMatrix();
}
