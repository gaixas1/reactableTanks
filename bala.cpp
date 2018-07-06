#include "bala.h"

using namespace tuio;

Bala::Bala(){}

Bala::Bala(int _type, float _angle, DirectPoint _p)
{
	vel=0.0035f;//GlobalConfig::GetRef("BALA:VEL",0.03f));
	radio=0.002f;//GlobalConfig::GetRef("BALA:RAD",0.03f));
	angulo = _angle;
	tipo = _type;
	p = _p;
	poder = 3;
    Sonidos::getSound("disparo.mp3")->play();
}
Bala::Bala(int _type, float _angle, DirectPoint _p, int _poder)
{
	vel=0.0035f;//GlobalConfig::GetRef("BALA:VEL",0.03f));
	radio=0.002f;//GlobalConfig::GetRef("BALA:RAD",0.03f));
	angulo = _angle;
	tipo = _type;
	p = _p;
	poder = _poder;
    Sonidos::getSound("disparo.mp3")->play();
}

DirectPoint Bala::GoesTo() {
	DirectPoint _p;
	_p.set(p.getX()+cosf(angulo)*vel, p.getY()+sinf(angulo)*vel);
	return _p;
}
void Bala::MoveTo(float x, float y){
    p.set(x,y);
}
void Bala::MoveTo(DirectPoint _p){
    MoveTo(_p.getX(),_p.getY());
}
void Bala::SetAngle(float _angle){
    angulo = _angle;
}

bool Bala::collide(Bala * _b, DirectPoint * _p ) {
    return (p.getDistance(_p) < (_b->radio + radio));
}

void Bala::Draw() {
    ofEnableAlphaBlending();

    ofSetColor(255,255,255);
    glPushMatrix();

    glTranslatef(p.getX(), p.getY(), 1);
    glRotatef(angulo*180/M_PI, 0, 0, 1);
	ofCircle(0,0,2*radio);
    glPopMatrix();
    ofDisableAlphaBlending();
}

Bomba::Bomba()
{
	vel = 0.0f;
	radio = 0.0015f;
	angulo = 0.0f;
	tipo = 4;
	tam = 0;
}
Bomba::Bomba(int pt, DirectPoint _p, int _timer)
{
	vel = 0.0f;
	radio = 0.0015f*pt;
	angulo = 0.0f;
	tipo = 4;
	p = _p;
	poder = pt;
	timer = _timer;
	tam = 0;
	explosion = Texturas::getImage("bomba.png");
	explo = Sonidos::getSound("explosion.mp3");
}

BombaN::BombaN(int pt, DirectPoint _p, int _timer)
{
	vel = 0.0f;
	radio = 0.0015f*pt;
	angulo = 0.0f;
	tipo = 4;
	p = _p;
	poder = pt;
	timer = _timer;
	tam = 0;
	explosion = Texturas::getImage("bomba.png");
	explo = Sonidos::getSound("explosion.mp3");
}

void Bomba::Draw() {
    if(timer == 0) {
        ofEnableAlphaBlending();
        ofSetColor(255,255,255);
        glPushMatrix();

        glTranslatef(p.getX(), p.getY(), 2);
        explosion->draw((-radio-0.01f),(-radio-0.01f),(radio+radio+0.02f),(radio+radio+0.02f));

        glPopMatrix();
        ofDisableAlphaBlending();
        if(tam < 10)
            radio *= 1.15f;
        else
            radio /= 1.05f;
        tam++;
    } else {
        timer--;

        ofEnableAlphaBlending();
        ofSetColor(255,255,255);
        glPushMatrix();

        glTranslatef(p.getX(), p.getY(), 2);
        ofCircle(0,0,0.002f);

        glPopMatrix();
        ofDisableAlphaBlending();

        if(timer==0) {
            explo->play();
        }
    }
}


void BombaN::Draw() {
    ofEnableAlphaBlending();
    ofSetColor(255,255,255);
    glPushMatrix();

    glTranslatef(p.getX(), p.getY(), 2);
    explosion->draw((-radio-0.01f),(-radio-0.01f),(radio+radio+0.02f),(radio+radio+0.02f));

    glPopMatrix();
    ofDisableAlphaBlending();
    if(tam < 10)
        radio *= 1.15f;
    else
        radio /= 1.05f;
    tam++;
}


Mina::Mina(){
    tam = 100;
    radio = TAMMINA*100;
    fondo = Texturas::getImage("mina.png");
    destroyed = false;
    p.set(0.5f,0.5f);
}

Mina::Mina(DirectPoint _p){
    tam = 100;
    radio = TAMMINA*100;
    fondo = Texturas::getImage("mina.png");
    destroyed = false;
    p = _p;
}

void Mina::Draw(){
   // fondo = Texturas::getImage("mina.png");
    ofEnableAlphaBlending();
    glPushMatrix();
    ofSetColor(255,255,255);
    glTranslatef(p.getX(), p.getY(), 1);
    fondo->draw(-radio, -radio, radio*2, radio*2);
    glPopMatrix();
    ofDisableAlphaBlending();

}

void Mina::goTo(float x, float y) {
    p.set(x,y);
    if(tam<100) {
        radio += TAMMINA;
        tam++;
    }
}

void Mina::ini(){
    tam = 0;
    radio = TAMMINA;
    destroyed = false;
}

void Mina::Destroy(){
    destroyed = true;
}
