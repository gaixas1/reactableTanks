#include "powerUp.h"

using namespace tuio;

PowerUp::PowerUp(DirectPoint _p, float _radio) {
    p = _p;
    radio = POWERUPRADIO;
    tipo = 0;
    icono = Texturas::getImage("powerUp.png");
    val = 0;
    alive = true;
    timer = 0;
}
PowerUp::PowerUp() {
    radio = POWERUPRADIO;
    tipo = 0;
    icono = Texturas::getImage("powerUp.png");
    val = 0;
    alive = true;
    timer = 0;
}

bool PowerUp::isNear(DirectPoint _p, float _radio) {
    return (p.getDistance(_p)<=radio+_radio);
}

void PowerUp::Draw() {
    if((timer < POWERUPTIME_1) || (timer%2)) {
        ofEnableAlphaBlending();
        glPushMatrix();
        glTranslatef(p.getX(), p.getY(), 1);
        icono->draw(-radio, -radio, radio*2, radio*2);
        glPopMatrix();
        ofDisableAlphaBlending();
    }

    timer++;
    if(timer >= POWERUPTIME_2)
        alive = false;
}

Vida::Vida(DirectPoint _p) {
    p = _p;
    radio = POWERUPRADIO;
    tipo = POWERUP_VIDA;
    icono = Texturas::getImage("powerUp_Vida.png");
    val = 5;
    alive = true;
    timer = 0;
}

Veneno::Veneno(DirectPoint _p) {
    p = _p;
    radio = POWERUPRADIO;
    tipo = POWERUP_VENENO;
    icono = Texturas::getImage("powerUp_Veneno.png");
    val = 10;
    alive = true;
    timer = 0;
}
