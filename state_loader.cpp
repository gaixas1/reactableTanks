#include "state_loader.h"
#include "textures.h"
#include "sounds.h"

using namespace tuio;

state_loader::state_loader(int c, unsigned int param) {
    next = NULL;
    switch(c) {
        case 0:
            next = new tuio::state_inicio();
            break;
        case 1:
            next = new tuio::state_editor();
            break;
        case 2:
            next = new tuio::state_selector();
            break;
        case 3:
            next = new tuio::state_play(param);
            break;
    }
}

state * state_loader::Process() {
    if(next == NULL)
        return this;
    else {
        return next;
    }
}

void state_loader::Draw() {
    ofBackground(0,0,0);
    ofSetColor(255,255,255);
}

