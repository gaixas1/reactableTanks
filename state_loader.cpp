#include "state_loader.h"
#include "textures.h"
#include "sounds.h"

using namespace tuio;

state_loader::state_loader(int c, void * param) {
    angle = 0;
    loading = Texturas::getImage("moe.jpg");
    fondo = Sonidos::getSound("LNA.mp3");
    fondo->play();
    next = new state_editor();
//    next = NULL;
    /*
    next = NULL;
    state * t;
    pthread_create(&Hilo,0,prueba2,this);
    //Hilo
    switch(c) {
        case STATE_INICIO:
            t = new state_inicio();
            break;
        case STATE_EDITOR:
            break;
    }
    //Sinconizado
    next = t;
    //Fin hilo
    */
}

state * state_loader::Process() {
    if(next == NULL)
        return this;
    else {
        fondo->stop();
        return next;
    }
}

void state_loader::Draw() {
    ofBackground(0,0,0);
    ofSetColor(240,240,240);

    glPushMatrix();
    glTranslatef(0.5f,0.5f,0.0f);
    glRotatef(angle,0.0f,0.0f,1.0f);
    loading->draw(0.4f,0.0f, 0.1f,0.1f);
    glPopMatrix();
    angle +=0.5;
}
