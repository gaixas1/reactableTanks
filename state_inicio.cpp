#include "state_inicio.h"
#include "textures.h"
#include "sounds.h"
#include "mapas.h"
#include <stdio.h>

using namespace tuio;

state_inicio::state_inicio() {
    change2 = 0;

    FILE * l = fopen ("mapas/maps.list","r");
    if (l != NULL) {
        char file[500];
        while(!feof(l)) {
            fscanf(l, "%s\n", file);
            FILE * f;
            f = fopen (file,"r");
            if (f!=NULL)
            {
                mapa * m;
                int pack = 0;
                fscanf(f,"-MAPA\n");
                fscanf(f,"PACK(%d)\n",&pack);
                switch(pack) {
                    case 1:
                        m = new mapaB(f);
                        break;
                    case 2:
                        m = new mapaC(f);
                        break;
                    case 3:
                        m = new mapaD(f);
                        break;
                    default:
                        m = new mapa(f);
                        break;
                }
                Mapas::addMapa(m);
                fclose(f);
            }
        }
    }

    Texturas::getImage("fuego.jpg");
    Texturas::getImage("humo.png");
    Texturas::getImage("piedra.jpg");
    fondo = Texturas::getImage("inicio.jpg");

    Sonidos::getSound("explosion.mp3");
    Sonidos::getSound("disparo.mp3");
    Sonidos::getSound("Suna_no_Oshiro.mp3")->setLoop(true);
    Sonidos::getSound("Suna_no_Oshiro.mp3")->play();
}

state * state_inicio::Process() {
    if(change2 == 0)
        return this;
    else {
        return new state_loader(change2);
    }
}

void state_inicio::Draw() {
    ofSetColor(255,255,255);
    fondo->draw(0.0f,0.0f,1.0f,1.0f);
}


void state_inicio::FingerIN(DirectFinger * f) {
    if((f->getX() < 0.5f && f->getY() > 0.5f) || (f->getX() > 0.5f && f->getY() < 0.5f)) {
        change2 = 1;
    } else {
        change2 = 2;
    }
}
