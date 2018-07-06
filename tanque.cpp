#include "tanque.h"

using namespace tuio;

void Tanque::Draw() {
    if(vida > 0) {
        ofEnableAlphaBlending();


        glPushMatrix();
        glTranslatef(p.getX(), p.getY(), 1);
        glRotatef(angle*180/M_PI, 0, 0, 1);
        for(int i = 0; i < vida; i++) {
            ofSetColor(250-10*i, 10*i, 0, 180);
            ofTriangle(0.0f,0.0f, cos(i*M_PI/10)*(radio+0.02f), sin(i*M_PI/10)*(radio+0.02f), cos((i+1)*M_PI/10)*(radio+0.02f), sin((i+1)*M_PI/10)*(radio+0.02f));
        }
        glPopMatrix();
        switch(id) {
            case 2:
                ofSetColor(255,0,255);
                break;
            case 1:
                ofSetColor(0,255,255);
                break;
            case 4:
                ofSetColor(100,255,100);
                break;
            case 3:
                ofSetColor(255,255,0);
                break;
            default:
                ofSetColor(255,255,255);
        }
        glPushMatrix();
        glTranslatef(p.getX(), p.getY(), 1);
        glRotatef(angleDraw*180/M_PI, 0, 0, 1);
        fondo->draw(-radio, -radio, radio*2, radio*2);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(p.getX(), p.getY(), 1);
        glRotatef(angle*180/M_PI, 0, 0, 1);
        canyon->draw(-radio, -radio, radio*2, radio*2);
        glPopMatrix();

        ofDisableAlphaBlending();
    }
}

Tanque::Tanque (int _id, DirectPoint _p, float _angle) {
    id = _id;
    p.set(_p.getX(),_p.getY());
    angle = _angle;
    radio = TANKSIZE;

    fondo = Texturas::getImage("tanque.png");
    canyon = Texturas::getImage("canyon.png");
    vida = 0;
}

Tanque::Tanque(){
    radio = TANKSIZE;
    angle = 0;
    angleDraw = 0;

    fondo = Texturas::getImage("tanque.png");
    canyon = Texturas::getImage("canyon.png");
    vida = 0;
}

DirectPoint Tanque::GoesTo() {
    if(vida <= 0)
        return p;
    if(mov.size()==0)
        return p;

    DirectPoint _p = mov[0];
    if(p.getDistance(_p) <= MAXVEL) {
        mov.pop_front();
    } else {
        float _angle = p.getAngle(_p);
        _p.set(p.getX()+cosf(_angle)*MAXVEL,p.getY()+sinf(_angle)*MAXVEL);
    }

    float angulo = p.getAngle(_p);
    float angulob = angleDraw;
    if((abs(angulo-angulob) < MAXANGLE) || (abs(angulo-angulob-M_PI*2.0f) < MAXANGLE) || (abs(angulo-angulob+M_PI*2.0f) < MAXANGLE))
        angulob = p.getAngle(_p);
    else {
        if(angulob < angulo) {
            if(angulob+M_PI < angulo)
                angulob += MAXANGLE;
            else
                angulob -= MAXANGLE;
        } else {
            if(angulo+M_PI < angulob)
                angulob -= MAXANGLE;
            else
                angulob += MAXANGLE;
        }

        angleDraw = angulob;
        if(angulob<0)
            angulob += M_PI*2.0f;
        else if(angulob>M_PI*2.0f)
            angulob -= M_PI*2.0f;

    }

    return _p;
}
void Tanque::MoveTo(float x, float y){
    p.set(x,y);
}
void Tanque::MoveTo(DirectPoint _p){
    MoveTo(_p.getX(),_p.getY());
}
void Tanque::SetAngle(float _angle){
    angle = _angle;
}
void Tanque::setID(int _id){
    id = _id;
}

void Tanque::GoTo(DirectPoint _p) {
    if(vida > 0) {
        if(mov.empty())
            mov.push_back(_p);
        else if(p.getDistance(mov.back()) > MINDISTANCE)
            mov.push_back(_p);
    }
}
void Tanque::Stop() {
    mov.clear();
}

bool Tanque::collide(DirectPoint * t) {
    if(vida <= 0)
        return false;
    return ((t->getDistance(p)) < (radio*2));
}

void Tanque::setPad(Pad * _pad) {
	pad = _pad;
}

Bala * Tanque::padTap(DirectFinger * f) {
    if(vida <= 0)
        return NULL;
	int val = pad->collide(f);
	DirectPoint _p;
	Bala * b;
	switch(val) {
		case 1:
			_p.set(p.getX()+DISTSALIDA*cosf(angle+M_PI_2),p.getY()+DISTSALIDA*sinf(angle+M_PI_2));
			b = new Bala(1, angle+M_PI_2, _p, 4);
			return b;
			break;
		case 2:
			_p.set(p.getX()+DISTSALIDA*cosf(angle+M_PI_2),p.getY()+DISTSALIDA*sinf(angle+M_PI_2));
			b =new Bala(2, angle+M_PI_2, _p);
			return b;
			break;
		case 3:
			_p.set(p.getX()+DISTSALIDA*cosf(angle+M_PI_2),p.getY()+DISTSALIDA*sinf(angle+M_PI_2));
			b =new Bala(3, angle+M_PI_2, _p, 6);
			return b;
			break;
		case 4:
			_p.set(p.getX(),p.getY());
			b = new Bomba(vida, _p, 1);
			vida = 0;
			return b;
			break;
		default:
			return NULL;
	}
}

bool Tanque::collideBala(Bala * b) {
    if(vida <= 0)
        return false;
    return (p.getDistance(b->p) <= (radio + b->radio));
}


bool Tanque::golpear(int poder) {
    vida -= poder;

    if(vida <= 0) {
        return true;
    } else {
        return false;
    }
}

void Tanque::addVida(int live) {
    if(vida > 0)
        vida += live;
    if(vida>20)
        vida = 20;
}

void Tanque::removeVida(int live) {
    if(vida > live)
        vida -= live;
    else
        vida = 1;
}

Torreta::Torreta() {
    radio = TORRETASIZE;
    angleInc = MAXANGLE;
    angle = 0;
    angleDraw = 0;
    balaType = 0;
    fondo = Texturas::getImage("torreta.png");
    canyon = Texturas::getImage("canyonT.png");
    vida = 0;
    p.set(0.5f,0.5f);
}
Torreta::Torreta(int ty, DirectPoint _p, bool dir) {
    radio = TORRETASIZE;
    if(dir)
        angleInc = MAXANGLE;
    else
        angleInc = -MAXANGLE;
    balaType = ty;
    angle = 0;
    angleDraw = 0;

    p = _p;

    fondo = Texturas::getImage("torreta.png");
    canyon = Texturas::getImage("canyonT.png");

    vida = 0;
}

void Torreta::Draw() {
    ofEnableAlphaBlending();
    glPushMatrix();
    ofSetColor(255,255,255);
    glTranslatef(p.getX(), p.getY(), 1);
    fondo->draw(-radio, -radio, radio*2, radio*2);
    glRotatef(angle*180/M_PI, 0, 0, 1);
    canyon->draw(-radio, -radio, radio*2, radio*2);
    glPopMatrix();
    ofDisableAlphaBlending();
}

Bala * Torreta::Disparar() {
    DirectPoint _p;
    Bala * b;
    switch(balaType) {
        case 0:
			_p.set(p.getX()+DISTSALIDAT*cosf(angle+M_PI_2),p.getY()+DISTSALIDAT*sinf(angle+M_PI_2));
			b = new Bala(1, angle+M_PI_2, _p, 4);
			return b;
			break;
		case 1:
			_p.set(p.getX()+DISTSALIDAT*cosf(angle+M_PI_2),p.getY()+DISTSALIDAT*sinf(angle+M_PI_2));
			b =new Bala(2, angle+M_PI_2, _p);
			return b;
			break;
		case 2:
			_p.set(p.getX()+DISTSALIDAT*cosf(angle+M_PI_2),p.getY()+DISTSALIDAT*sinf(angle+M_PI_2));
			b =new Bala(3, angle+M_PI_2, _p, 6);
			return b;
			break;
			default :
        return NULL;
    }
}

bool Torreta::collideBala(Bala * b) {
    return (p.getDistance(b->p) <= (radio + b->radio));
}

void Torreta::Inc() {
    angle += angleInc;
    float pi2 = M_PI+M_PI;
    while(angle <= 0) {
        angle += pi2;
    }
    while(angle > pi2) {
        angle -= pi2;
    }
}
