#include "State.h"
    #include "state_loader.h"
#include "juego.h"

using namespace tuio;

Juego::Juego(){
    s = new state_loader(0);
};

void Juego::Draw() {
    s->Draw();
};

void Juego::Process () {
    s = s->Process();
};

void Juego::newCursor(DirectFinger * finger){s->FingerIN(finger);};
void Juego::removeCursor(DirectFinger * finger){s->FingerOUT(finger);};
void Juego::updateCursor(DirectFinger * finger){s->FingerUPDATE(finger);};

void Juego::Tap(float x, float y){s->TAP(x,y);};

void Juego::newObject(DirectObject * object){s->ObjectIN(object);};
void Juego::removeObject(DirectObject * object){s->ObjectOUT(object);};
void Juego::updateObject(DirectObject * object){s->ObjectUPDATE(object);};
