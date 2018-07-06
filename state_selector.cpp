#include "state_loader.h"
#include "state_selector.h"
#include "textures.h"
#include "sounds.h"
#include <stdio.h>

using namespace tuio;

state_selector::state_selector() {
    actual = 0;
    mapas = Mapas::getCount();
    act = Mapas::getMapa(actual);
}
state * state_selector::Process()
{
    if(estado == 1) {
        return new state_play(actual);
    } else if(estado == 2)
        return new state_loader(0);
    return this;
}

void state_selector::Draw() {
    ofBackground(0,0,0);
    act->Draw();

        ofSetColor(200,50,50);
        ofCircle(-0.1f,0.5f,0.2f);

        ofSetColor(50,50,200);
        ofCircle(1.1f,0.5f,0.2f);

        ofSetColor(50,200,50);
        ofCircle(0.5f,-0.1f,0.2f);

        ofSetColor(50,200,50);
        ofCircle(0.5f,1.1f,0.2f);
}

void state_selector::TAP(float x, float y) {
    DirectObject o;
    o.set(x,y);
    if(o.getDistance(-0.1f,0.5f) <= 0.2f) {
        if(actual == 0)
            actual = mapas-1;
        else
            actual--;
        act = Mapas::getMapa(actual);
    } else if(o.getDistance(1.1f,0.5f) <= 0.2f) {
        if(actual == mapas-1)
            actual = 0;
        else
            actual++;
        act = Mapas::getMapa(actual);
    } else if(o.getDistance(0.5f,1.1f) <= 0.2f) {
        estado = 1;
    } else if(o.getDistance(0.5f,-0.1f) <= 0.2f) {
        estado = 1;
    }
}

void state_selector::ObjectIN(DirectObject * o) {
    if(o->f_id == IDEDITORSALIR) {
        estado = 2;
    }
}
void state_selector::ObjectUPDATE(DirectObject * o) {
    ObjectIN(o);
}
