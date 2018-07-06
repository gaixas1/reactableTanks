#include "map.h"
#include "textures.h"
#include "sounds.h"
#include "ofGraphics.h"

using namespace tuio;

mapa::mapa() {
    cajas[0] = new pieza1();
    cajas[1] = new pieza2();
    cajas[2] = new pieza3();
    cajas[3] = new pieza4();
    fondo = Texturas::getImage("terreno_1.jpg");
}

mapa::mapa(FILE * f) {
    cajas[0] = new pieza1();
    cajas[1] = new pieza2();
    cajas[2] = new pieza3();
    cajas[3] = new pieza4();
    int size;
	piezas _p;
    fscanf(f,"NPIEZAS(%d)\n",&size);
    for (int i = 0; i < size; i++) {
        fscanf(f,"--PIEZAS\n");
        int tpieza;
        fscanf(f,"*TPIEZA(%d)\n",&tpieza);
        _p.read(f,cajas, tpieza);
        switch(tpieza) {
            case 0 :
            case 1 :
                pzs0.push_back(_p);
                break;
            case 2 :
                pzs2.push_back(_p);
                break;
            case 3 :
                pzs3.push_back(_p);
                break;
        }
        fscanf(f,"--PIEZAS-END\n");
    }
    fondo = Texturas::getImage("terreno_1.jpg");
}

mapaB::mapaB() {
    cajas[0] = new pieza1();
    cajas[1] = new pieza2();
    cajas[2] = new pieza3();
    cajas[3] = new pieza4();
    fondo = Texturas::getImage("terreno_2.jpg");
}

mapaB::mapaB(FILE * f) {
    cajas[0] = new pieza1();
    cajas[1] = new pieza2();
    cajas[2] = new pieza3();
    cajas[3] = new pieza4();
    int size;
	piezas _p;
    fscanf(f,"NPIEZAS(%d)\n",&size);
    for (int i = 0; i < size; i++) {
        fscanf(f,"--PIEZAS\n");
        int tpieza;
        fscanf(f,"*TPIEZA(%d)\n",&tpieza);
        _p.read(f,cajas, tpieza);
        switch(tpieza) {
            case 0 :
            case 1 :
                pzs0.push_back(_p);
                break;
            case 2 :
                pzs2.push_back(_p);
                break;
            case 3 :
                pzs3.push_back(_p);
                break;
        }
        fscanf(f,"--PIEZAS-END\n");
    }
    fondo = Texturas::getImage("terreno_2.jpg");
}

mapaC::mapaC() {
    cajas[0] = new pieza1();
    cajas[1] = new pieza2();
    cajas[2] = new pieza3();
    cajas[3] = new pieza4();
    fondo = Texturas::getImage("terreno_3.jpg");
    timer = 0;
}

mapaC::mapaC(FILE * f) {
    cajas[0] = new pieza1();
    cajas[1] = new pieza2();
    cajas[2] = new pieza3();
    cajas[3] = new pieza4();
    int size;
	piezas _p;
    fscanf(f,"NPIEZAS(%d)\n",&size);
    for (int i = 0; i < size; i++) {
        fscanf(f,"--PIEZAS\n");
        int tpieza;
        fscanf(f,"*TPIEZA(%d)\n",&tpieza);
        _p.read(f,cajas, tpieza);
        switch(tpieza) {
            case 0 :
            case 1 :
                pzs0.push_back(_p);
                break;
            case 2 :
                pzs2.push_back(_p);
                break;
            case 3 :
                pzs3.push_back(_p);
                break;
        }
        fscanf(f,"--PIEZAS-END\n");
    }
    fondo = Texturas::getImage("terreno_3.jpg");
    timer = 0;
}

mapaD::mapaD() {
    cajas[0] = new pieza1();
    cajas[1] = new pieza2();
    cajas[2] = new pieza3();
    cajas[3] = new pieza4();
    fondo = Texturas::getImage("terreno_4.jpg");

    x[0] = 0.3f; y[0] = 0.3f;
    x[1] = 0.7f; y[1] = 0.3f;
    x[2] = 0.7f; y[2] = 0.7f;
    x[3] = 0.3f; y[3] = 0.7f;
    timer[0] = 180;
    timer[1] = 90;
    timer[2] = 0;
    timer[3] = 270;
    for(int i = 0; i<4; i++) {
        float _x = x[i]+cosf(timer[i]*2*M_PI/360)*MINACIRCLE;
        float _y = y[i]+sinf(timer[i]*2*M_PI/360)*MINACIRCLE;
        minas[i].goTo(_x, _y);
    }
}

mapaD::mapaD(FILE * f) {
    cajas[0] = new pieza1();
    cajas[1] = new pieza2();
    cajas[2] = new pieza3();
    cajas[3] = new pieza4();
    int size;
	piezas _p;
    fscanf(f,"NPIEZAS(%d)\n",&size);
    for (int i = 0; i < size; i++) {
        fscanf(f,"--PIEZAS\n");
        int tpieza;
        fscanf(f,"*TPIEZA(%d)\n",&tpieza);
        _p.read(f,cajas, tpieza);
        switch(tpieza) {
            case 0 :
            case 1 :
                pzs0.push_back(_p);
                break;
            case 2 :
                pzs2.push_back(_p);
                break;
            case 3 :
                pzs3.push_back(_p);
                break;
        }
        fscanf(f,"--PIEZAS-END\n");
    }
    fondo = Texturas::getImage("terreno_4.jpg");
    x[0] = 0.3f; y[0] = 0.3f;
    x[1] = 0.7f; y[1] = 0.3f;
    x[2] = 0.7f; y[2] = 0.7f;
    x[3] = 0.3f; y[3] = 0.7f;
    timer[0] = 180;
    timer[1] = 90;
    timer[2] = 0;
    timer[3] = 270;
    for(int i = 0; i<4; i++) {
        float _x = x[i]+cosf(timer[i]*2*M_PI/360)*MINACIRCLE;
        float _y = y[i]+sinf(timer[i]*2*M_PI/360)*MINACIRCLE;
        minas[i].goTo(_x, _y);
    }
}

void mapa::CreateGameCopy() {

    pzsg.clear();

    for (std::list < piezas>::iterator it= pzs0.begin(); it != pzs0.end(); ++it) {
        piezas * me = &(*it);
        pzsg.push_back(me->Copy());
    }

}

void mapa::Draw() {
    ofSetColor(255,255,255);
    fondo->draw(0.0f,0.0f,1.0f,1.0f);

    ofEnableAlphaBlending();
    ofSetColor(255,0,255,150);
    ofCircle(0.05f,0.5f, 0.05f);

    ofSetColor(0,255,255,150);
    ofCircle(0.5f,0.05f, 0.05f);

    ofSetColor(100,255,100,150);
    ofCircle(0.95f,0.5f, 0.05f);

    ofSetColor(255,255,0,150);
    ofCircle(0.5f,0.95f, 0.05f);
    ofDisableAlphaBlending();

    for (std::list < piezas>::iterator it= pzs2.begin(); it != pzs2.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }

    for (std::list < piezas>::iterator it= pzs0.begin(); it != pzs0.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }

    for (std::list < piezas>::iterator it= pzs3.begin(); it != pzs3.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }
}

void mapa::DrawFondo(bool all) {
    ofSetColor(255,255,255);
    fondo->draw(0.0f,0.0f,1.0f,1.0f);
    if(all) {
        ofEnableAlphaBlending();
        ofSetColor(255,0,255,150);
        ofCircle(0.05f,0.5f, 0.05f);

        ofSetColor(0,255,255,150);
        ofCircle(0.5f,0.05f, 0.05f);

        ofSetColor(100,255,100,150);
        ofCircle(0.95f,0.5f, 0.05f);

        ofSetColor(255,255,0,150);
        ofCircle(0.5f,0.95f, 0.05f);
        ofDisableAlphaBlending();
    }


    for (std::list < piezas>::iterator it= pzs2.begin(); it != pzs2.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }

    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }
}

void mapa::DrawSup() {
    for (std::list < piezas>::iterator it= pzs3.begin(); it != pzs3.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }
}

bool mapa::tankCollide(Tanque * t, DirectPoint p) {

    if(p.getDistance(0.5f,0.5f) > (0.5f-t->radio))
        return true;

    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, t->radio))
            return true;
    }
    for (std::list < piezas>::iterator it= pzs2.begin(); it != pzs2.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, t->radio))
            return true;
    }
    return false;
}

bool mapa::balaCollide(Bala * b, DirectPoint p) {

    if(p.getDistance(0.5f,0.5f) > (0.5f-b->radio))
        return true;

    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, b->radio))
            return true;
    }
    return false;
}

void mapa::bombaCollide(Bomba * _b) {
    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        me->collideBomba(_b);
    }
}

bool mapa::balaCollide(Bala * b, DirectPoint p, float * angulo_col) {

    if(p.getDistance(0.5f,0.5f) > (0.5f-b->radio)) {
        float dch = atan2f( p.getY()-0.5f  , p.getX()-0.5f);
		*angulo_col = (M_PI + dch + dch - *angulo_col);
        return true;
    }

    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, b->radio, angulo_col))
            return true;
    }
    return false;
}


void mapa::actuar(std::list<Bala *> * balas, std::list<Bomba *> * bombas) {}

bool mapaC::tankCollide(Tanque * t, DirectPoint p) {

    if(p.getDistance(0.5f,0.5f) > (0.5f-t->radio))
        return true;
    float lim1 = 1.0f/8.0f - t->radio;
    float lim2 = 7.0f/16.0f - t->radio;
    if((p.getX()>lim1)&&(p.getX()<1-lim1)&&(p.getY()>lim2)&&(p.getY()<1-lim2))
        return true;
    if((p.getX()>lim2)&&(p.getX()<1-lim2)&&(p.getY()>lim1)&&(p.getY()<1-lim1))
        return true;

    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, t->radio))
            return true;
    }
    for (std::list < piezas>::iterator it= pzs2.begin(); it != pzs2.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, t->radio))
            return true;
    }
    return false;
}

void mapaB::actuar(std::list<Bala *> * balas, std::list<Bomba *> * bombas) {
    srand ( rand()*13 );
    timerA+= rand()%5 + 1;

    srand ( rand()*17 );
    timerB+= rand()%5 + 1;

    srand ( rand()*19 );
    timerC+= rand()%5 + 1;

    if(timerA >= 25) {
        timerA = 0;
        srand(rand()*5);
        float a = (rand()%1000)*5/(16000.0f)+1.0f/8.0f; //ofRandom(1.0f/8.0f, 7.0f/16.0f);
        srand(rand()*7);
        float b = (rand()%1000)/(8000.0f)+7.0f/16.0f;//, 9.0f/16.0f);
        DirectPoint _p;
        srand(rand()*3);
        switch(rand()%4)
        {
            case 0:
                _p.set(a,b);
                break;
            case 1:
                _p.set(b,a);
                break;
            case 2:
                _p.set(1-a,b);
                break;
            case 3:
                _p.set(b,1-a);
                break;
        }
        bombas->push_back(new BombaN(5, _p, 1));
    }
    if(timerB >= 25) {
        timerA = 0;
        srand(rand()*5);
        float a = (rand()%1000)*5/(16000.0f)+1.0f/8.0f; //ofRandom(1.0f/8.0f, 7.0f/16.0f);
        srand(rand()*7);
        float b = (rand()%1000)/(8000.0f)+7.0f/16.0f;//, 9.0f/16.0f);
        DirectPoint _p;
        srand(rand()*3);
        switch(rand()%4)
        {
            case 0:
                _p.set(a,b);
                break;
            case 1:
                _p.set(b,a);
                break;
            case 2:
                _p.set(1-a,b);
                break;
            case 3:
                _p.set(b,1-a);
                break;
        }
        bombas->push_back(new BombaN(5, _p, 1));
    }
    if(timerC >= 25) {
        timerA = 0;
        srand(rand()*5);
        float a = (rand()%1000)*5/(16000.0f)+1.0f/8.0f; //ofRandom(1.0f/8.0f, 7.0f/16.0f);
        srand(rand()*7);
        float b = (rand()%1000)/(8000.0f)+7.0f/16.0f;//, 9.0f/16.0f);
        DirectPoint _p;
        srand(rand()*3);
        switch(rand()%4)
        {
            case 0:
                _p.set(a,b);
                break;
            case 1:
                _p.set(b,a);
                break;
            case 2:
                _p.set(1-a,b);
                break;
            case 3:
                _p.set(b,1-a);
                break;
        }
        bombas->push_back(new BombaN(5, _p, 1));
    }
}


void mapaC::actuar(std::list<Bala *> * balas, std::list<Bomba *> * bombas) {
    timer++;
    T.Inc();
    if(timer >= rand()%2000) {
        timer = 0;
        balas->push_back(T.Disparar());
    }
}


void mapaC::Draw() {
    ofSetColor(255,255,255);
    fondo->draw(0.0f,0.0f,1.0f,1.0f);

    ofEnableAlphaBlending();
    ofSetColor(255,0,255,150);
    ofCircle(0.05f,0.5f, 0.05f);

    ofSetColor(0,255,255,150);
    ofCircle(0.5f,0.05f, 0.05f);

    ofSetColor(100,255,100,150);
    ofCircle(0.95f,0.5f, 0.05f);

    ofSetColor(255,255,0,150);
    ofCircle(0.5f,0.95f, 0.05f);
    ofDisableAlphaBlending();

    for (std::list < piezas>::iterator it= pzs2.begin(); it != pzs2.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }

    for (std::list < piezas>::iterator it= pzs0.begin(); it != pzs0.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }

    for (std::list < piezas>::iterator it= pzs3.begin(); it != pzs3.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }
    T.Draw();
}

void mapaC::DrawFondo(bool all) {
    ofSetColor(255,255,255);
    fondo->draw(0.0f,0.0f,1.0f,1.0f);
    if(all) {
        ofEnableAlphaBlending();
        ofSetColor(255,0,255,150);
        ofCircle(0.05f,0.5f, 0.05f);

        ofSetColor(0,255,255,150);
        ofCircle(0.5f,0.05f, 0.05f);

        ofSetColor(100,255,100,150);
        ofCircle(0.95f,0.5f, 0.05f);

        ofSetColor(255,255,0,150);
        ofCircle(0.5f,0.95f, 0.05f);
        ofDisableAlphaBlending();
    }


    for (std::list < piezas>::iterator it= pzs2.begin(); it != pzs2.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }

    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }
    T.Draw();
}


bool mapaC::balaCollide(Bala * b, DirectPoint p) {

    if(p.getDistance(0.5f,0.5f) > (0.5f-b->radio))
        return true;

    if(T.p.getDistance(p) <= (T.radio+b->radio))
        return true;


    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, b->radio))
            return true;
    }
    return false;
}

bool mapaC::balaCollide(Bala * b, DirectPoint p, float * angulo_col) {

    if(p.getDistance(0.5f,0.5f) > (0.5f-b->radio)) {
        float dch = atan2f( p.getY()-0.5f  , p.getX()-0.5f);
		*angulo_col = (M_PI + dch + dch - *angulo_col);
        return true;
    }

    if(T.p.getDistance(p) <= (T.radio+b->radio)) {
        float dch = atan2f( p.getY()-T.p.getY()  , p.getX()-T.p.getX());
		*angulo_col = (M_PI + dch + dch - *angulo_col);
        return true;
    }

    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, b->radio, angulo_col))
            return true;
    }
    return false;
}

bool mapaD::balaCollide(Bala * b, DirectPoint p) {

    if(p.getDistance(0.5f,0.5f) > (0.5f-b->radio))
        return true;

    if(minas[0].p.getDistance(p) <= (minas[0].radio+b->radio)) {
        minas[0].Destroy();
        return true;
    }
    if(minas[1].p.getDistance(p) <= (minas[1].radio+b->radio)) {
        minas[1].Destroy();
        return true;
    }
    if(minas[2].p.getDistance(p) <= (minas[2].radio+b->radio)) {
        minas[2].Destroy();
        return true;
    }
    if(minas[3].p.getDistance(p) <= (minas[3].radio+b->radio)) {
        minas[3].Destroy();
        return true;
    }


    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, b->radio))
            return true;
    }
    return false;
}

bool mapaD::balaCollide(Bala * b, DirectPoint p, float * angulo_col) {

    if(p.getDistance(0.5f,0.5f) > (0.5f-b->radio)) {
        float dch = atan2f( p.getY()-0.5f  , p.getX()-0.5f);
		*angulo_col = (M_PI + dch + dch - *angulo_col);
        return true;
    }

    if(minas[0].p.getDistance(p) <= (minas[0].radio+b->radio)) {
        minas[0].Destroy();
        return true;
    }
    if(minas[1].p.getDistance(p) <= (minas[1].radio+b->radio)) {
        minas[1].Destroy();
        return true;
    }
    if(minas[2].p.getDistance(p) <= (minas[2].radio+b->radio)) {
        minas[2].Destroy();
        return true;
    }
    if(minas[3].p.getDistance(p) <= (minas[3].radio+b->radio)) {
        minas[3].Destroy();
        return true;
    }

    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, b->radio, angulo_col))
            return true;
    }
    return false;
}

bool mapaD::tankCollide(Tanque * t, DirectPoint p) {
    if(p.getDistance(0.5f,0.5f) > (0.5f-t->radio))
        return true;
    if(t->vida >0)
        for(int i = 0; i<4; i++) {
            if(minas[i].p.getDistance(p) <= (minas[i].radio+t->radio)) {
                minas[i].Destroy();
                return true;
            }
        }

    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, t->radio))
            return true;
    }
    for (std::list < piezas>::iterator it= pzs2.begin(); it != pzs2.end(); ++it) {
        piezas * me = &(*it);
        if(me->collide(&p, t->radio))
            return true;
    }
    return false;
}



void mapaD::actuar(std::list<Bala *> * balas, std::list<Bomba *> * bombas) {
    for (int i = 0; i<4; i++) {
        if(minas[i].destroyed) {
            timer[i] -=180;
            minas[i].ini();
            bombas->push_back(new Bomba(10, minas[i].p, 1));
        }
        timer[i] += 1;

        while(timer[i] >= 360)
            timer[i] -= 360;
        while(timer[i] < 0)
            timer[i] += 360;
        float _x = x[i]+cosf(timer[i]*2*M_PI/360)*MINACIRCLE;
        float _y = y[i]+sinf(timer[i]*2*M_PI/360)*MINACIRCLE;
        minas[i].goTo(_x, _y);
    }
}

void mapaD::Draw() {
    ofSetColor(255,255,255);
    fondo->draw(0.0f,0.0f,1.0f,1.0f);

    ofEnableAlphaBlending();
    ofSetColor(255,0,255,150);
    ofCircle(0.05f,0.5f, 0.05f);

    ofSetColor(0,255,255,150);
    ofCircle(0.5f,0.05f, 0.05f);

    ofSetColor(100,255,100,150);
    ofCircle(0.95f,0.5f, 0.05f);

    ofSetColor(255,255,0,150);
    ofCircle(0.5f,0.95f, 0.05f);
    ofDisableAlphaBlending();

    for (std::list < piezas>::iterator it= pzs2.begin(); it != pzs2.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }

    for (std::list < piezas>::iterator it= pzs0.begin(); it != pzs0.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }

    for (std::list < piezas>::iterator it= pzs3.begin(); it != pzs3.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }
    for (int i = 0; i<4; i++) {
        minas[i].Draw();
    }
}

void mapaD::DrawFondo(bool all) {
    ofSetColor(255,255,255);
    fondo->draw(0.0f,0.0f,1.0f,1.0f);
    if(all) {
        ofEnableAlphaBlending();
        ofSetColor(255,0,255,150);
        ofCircle(0.05f,0.5f, 0.05f);

        ofSetColor(0,255,255,150);
        ofCircle(0.5f,0.05f, 0.05f);

        ofSetColor(100,255,100,150);
        ofCircle(0.95f,0.5f, 0.05f);

        ofSetColor(255,255,0,150);
        ofCircle(0.5f,0.95f, 0.05f);
        ofDisableAlphaBlending();
    }


    for (std::list < piezas>::iterator it= pzs2.begin(); it != pzs2.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }

    for (std::list < piezas>::iterator it= pzsg.begin(); it != pzsg.end(); ++it) {
        piezas * me = &(*it);
        me->Draw();
    }
    for (int i = 0; i<4; i++) {
        minas[i].Draw();
    }
}
