#include "state_editor.h"
#include "textures.h"
#include "sounds.h"
#include <time.h>

#include "InputGestureDirectFingers.hpp"

#include "state_loader.h"

using namespace tuio;

state_editor::state_editor() {
    angle=0;
    cajaAct = 0;
    pack = 0;
    estado = STEDITOR_INICIO;
    fondo[0] = Texturas::getImage("terreno_1.jpg");
    fondo[1] = Texturas::getImage("terreno_2.jpg");
    fondo[2] = Texturas::getImage("terreno_3.jpg");
    fondo[3] = Texturas::getImage("terreno_4.jpg");
    terrenos = Texturas::getImage("terrenos.jpg");
}

void state_editor::Draw() {
    switch(estado) {
        case STEDITOR_INICIO :
            ofSetColor(255,255,255);
            terrenos->draw(0.0f,0.0f,1.0f,1.0f);
            break;
        case STEDITOR_CAPA :
            ofSetColor(255,255,255);
            fondo[pack]->draw(0.0f,0.0f,1.0f,1.0f);

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

            ofEnableAlphaBlending();

            for (std::list < piezas>::iterator it= pzs.begin(); it != pzs.end(); ++it) {
                piezas * me = &(*it);
                me->Draw();
            }

            for (std::list < control_point>::iterator it= puntos.begin(); it != puntos.end(); ++it) {
                control_point * me = &(*it);
                me->Draw(angle);
            }

            for (std::list < control_block>::iterator it= bloques.begin(); it != bloques.end(); ++it) {
                control_block * me = &(*it);
                me->Draw(angle);
            }
            ofDisableAlphaBlending();
            break;

        case STEDITOR_PIEZAS :
            ofSetColor(255,255,255);
            fondo[pack]->draw(0.0f,0.0f,1.0f,1.0f);

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

            ofEnableAlphaBlending();
            for (std::list < piezas>::iterator it= pzs.begin(); it != pzs.end(); ++it) {
                piezas * me = &(*it);
                me->Draw();
            }
            ofDisableAlphaBlending();
            break;
    }

}

state * state_editor::Process() {
    if(estado == STEDITOR_GUARDA) {
        char * file = guardar();
        FILE * f;
        f = fopen (file,"r");
        int ret = 0;
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
            int ret = Mapas::addMapa(m);
            fclose(f);
            return new state_loader(3, ret);
        }
    } else if(estado == STEDITOR_SALIR) {
        return new state_loader(0);
    }
        return this;
}

void state_editor::ObjectIN(DirectObject * o) {
    bool process;
    switch(estado) {
        case STEDITOR_PIEZAS :
            switch(o->f_id) {
                case IDERITORGUARDADO:
                    estado = STEDITOR_GUARDA;
                    break;
                case IDEDITORSTATE:
                    estado = STEDITOR_CAPA;
                    break;
                case IDEDITORSALIR:
                    estado = STEDITOR_SALIR;
                    break;
            }
            break;
        case STEDITOR_CAPA :
            float distancia_borrado = 0.02f;
            switch(o->f_id) {
                case IDEDITORSTATE:
                    process = false;
                    if(o->getDistance(0.05f,0.5f) <= 0.05f) {
                        if(cajaAct!=0) {
                            cajaAct = 0;
                            process = true;
                        }
                    } else if(o->getDistance(0.95f,0.5f) <= 0.05f) {
                        if(cajaAct!=1) {
                            cajaAct = 1;
                            process = true;
                        }
                    } else if(o->getDistance(0.5f,0.05f) <= 0.05f) {
                        if(cajaAct!=2) {
                            cajaAct = 2;
                            process = true;
                        }
                    } else if(o->getDistance(0.5f,0.95f) <= 0.05f) {
                        if(cajaAct!=3) {
                            cajaAct = 3;
                            process = true;
                        }
                    }
                    if(process) {
                        for (std::list < control_point>::iterator it= puntos.begin(); it != puntos.end(); ++it) {
                            control_point * me = &(*it);
                            me->setPz(cajas[cajaAct]);
                        }

                        for (std::list < control_block >::iterator it= bloques.begin(); it != bloques.end(); ++it) {
                            control_block * me = &(*it);
                            me->setPz(cajas[cajaAct]);
                        }
                    }
                    break;
                case IDERITORGUARDADO:
                    pzs.push_back(discretizar());
                    estado = STEDITOR_GUARDA;
                    break;
                case IDEDITORSANGLE:
                    angle = o->angle;
                    break;
                case IDEDITORBORRADOR:
                    {
                    control_point _P;
                    control_block _B;
                    for (std::list < control_point>::iterator it= puntos.begin(); it != puntos.end(); ++it){
                        control_point * ob = &(*it);
                        if (o->getDistance(ob->getX(),ob->getY()) <= distancia_borrado) {
                            for (std::list < control_block>::iterator it2= bloques.begin(); it2 != bloques.end(); ++it2){
                                control_block * c = &(*it2);
                                if( (c->p1 == ob) || (c->p2 == ob) ) {
                                    (*it2) =_B;
                                }
                            }
                            bloques.remove( _B);
                            (*it) = _P;
                        }
                    }
                    puntos.remove( _P);
                    }
                    break;
                case IDERITORBORRADORCON:
                    {
                    control_block _B;
                    for (std::list < control_block>::iterator it= bloques.begin(); it != bloques.end(); ++it){
                        control_block * c = &(*it);
                        float dist1 = powf(o->getX()-c->p1->getX(),2)+powf(o->getY()-c->p1->getY(),2);
                        float dist2 = powf(o->getX()-c->p2->getX(),2)+powf(o->getY()-c->p2->getY(),2);
                        float difY = (c->p2->getY() - c->p1->getY());
                        float difX = (c->p2->getX() - c->p1->getX());
                        float radio = powf(difX,2)+powf(difY,2);
                        if((radio >= dist1) && (radio >= dist2)) {
                            float A, B, Xcorte, Ycorte;

                            if(difY == 0) {
                                Ycorte = c->p2->getY();
                                Xcorte = o->getX();
                            } else if(difX == 0) {
                                Xcorte = c->p2->getX();
                                Ycorte = o->getY();
                            } else {
                                A = difY/difX;
                                B = -difX/difY;
                                Xcorte = (o->getY() - c->p1->getY() + A*c->p1->getX() - B*o->getX())/(A-B);
                                Ycorte = A*(Xcorte - c->p1->getX()) + c->p1->getY();
                            }

                            if(o->getDistance(Xcorte,Ycorte) < distancia_borrado) {
                                (*it) =_B;
                            }
                        }
                    }
                    bloques.remove(_B);
                    }
                    break;
                case IDEDITORSALIR:
                    estado = STEDITOR_SALIR;
                    break;
            }
            break;
    }
}
void state_editor::ObjectUPDATE(DirectObject * o) {
    ObjectIN(o);
}
void state_editor::ObjectOUT(DirectObject * o) {

    switch(estado) {
        case STEDITOR_CAPA :
            switch(o->f_id) {
                case IDEDITORSTATE:
                    pzs.push_back(discretizar());
                    bloques.clear();
                    puntos.clear();
                    estado = STEDITOR_PIEZAS;
                    break;
            }
            break;
    }
}

bool state_editor::areConnected(control_point * p1,control_point * p2) {
    for (std::list < control_block>::iterator it= bloques.begin(); it != bloques.end(); ++it) {
        control_block * c = &(*it);
        if( (c->p1 == p1) && (c->p2 == p2) )
            return true;
        if( (c->p2 == p1) && (c->p1 == p2) )
            return true;
    }
    return false;
}

void state_editor::FingerIN(DirectFinger * f) {
    switch(estado) {
        case STEDITOR_INICIO :
            if(f->getX() > 0.5f) {
                if(f->getY() > 0.5f) {
                    pack = 2;
                    cajas[0] = new pieza1();
                    cajas[1] = new pieza2();
                    cajas[2] = new pieza3();
                    cajas[3] = new pieza4();
                } else {
                    pack = 1;
                    cajas[0] = new pieza1();
                    cajas[1] = new pieza2();
                    cajas[2] = new pieza3();
                    cajas[3] = new pieza4();
                }
            } else {
                if(f->getY() > 0.5f) {
                    pack = 3;
                    cajas[0] = new pieza1();
                    cajas[1] = new pieza2();
                    cajas[2] = new pieza3();
                    cajas[3] = new pieza4();
                } else {
                    pack = 0;
                    cajas[0] = new pieza1();
                    cajas[1] = new pieza2();
                    cajas[2] = new pieza3();
                    cajas[3] = new pieza4();
                }
            }
            estado = STEDITOR_CAPA;
            break;
        case STEDITOR_PIEZAS :
            for (std::list < piezas >::iterator it= pzs.begin(); it != pzs.end(); ++it){
                piezas * ob = &(*it);
                ob->deleteDistance(f, 0.0f);
            }
            break;
        case STEDITOR_CAPA :
            bool processed = false;
            for (std::list < control_point >::iterator it= puntos.begin(); !processed && it != puntos.end(); ++it) {
                control_point * me = &(*it);
                processed |= me->updateFinger(f);
            }
            if(!processed) {
                control_point p(f, cajas[cajaAct]);
                puntos.push_back(p);
            }
            break;
    }
}

void state_editor::FingerOUT(DirectFinger * f) {

    switch(estado) {
        case STEDITOR_CAPA :
            for (std::list < control_point >::iterator it= puntos.begin(); it != puntos.end(); ++it) {
                control_point * me = &(*it);
                me->deleteFinger(f);
            }
            break;
    }
}

void state_editor::FingerUPDATE(DirectFinger * f) {

    switch(estado) {
        case STEDITOR_CAPA :
            for (std::list < control_point >::iterator it= puntos.begin(); it != puntos.end(); ++it) {
                control_point * me =&(*it);
                if(me->updatePosition(f))
                    for (std::list < control_point >::iterator it2= puntos.begin(); it2 != puntos.end(); ++it2) {
                        control_point * mi = &(*it2);
                        if(me!=mi)
                            if(mi->isNear(f))
                                if(!areConnected(mi,me)) {
                                    control_block _b(me,mi, cajas[cajaAct]);
                                    bloques.push_back(_b );
                                }
                    }
            }
            break;
        case STEDITOR_PIEZAS :
            for (std::list < piezas >::iterator it= pzs.begin(); it != pzs.end(); ++it){
                piezas * ob = &(*it);
                ob->deleteDistance(f, 0.0f);
            }
            break;
    }
}


control_point::control_point(DirectFinger *f,pieza * _pz) {
    pz = _pz;
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
    return (p.getDistance(f->getX(), f->getY()) < 2*pz->getLado());
}

bool control_point::updateFinger(DirectFinger * f){
    if((id == 0)&&(p.getDistance(f->getX(), f->getY()) < pz->getLado())) {
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

void control_point::Draw(float angle){
    glPushMatrix();
    glTranslatef(p.getX(),p.getY(), 0.0f);

    ofEnableAlphaBlending();
    glRotatef(180*angle/M_PI,0.0f,0.0f,1.0f);
    pz->Draw(0);

    ofSetColor(55,20,20,80);
    ofCircle(0.0f,0.0f, 2*pz->getLado());
    ofDisableAlphaBlending();
    ofSetColor(255,50,50);
    ofCircle(0.0f, 0.0f, pz->getLado());
    glPopMatrix();
}


control_block::control_block(control_point * _p1, control_point * _p2, pieza *_pz) {
    p1 = _p1;
    p2 = _p2;
    pz = _pz;
}

void control_block::Draw(float angle) {
    ofSetColor(90,0,200);
    ofLine(p1->getX(), p1->getY(), p2->getX(), p2->getY());

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
        repeticiones = (int) floor(abs(radius*cosf(lineAngle)/(2*pz->getLado())));
        dx = radius*cosf(lineAngle) / (float) repeticiones;
        dy = dx * tanf(lineAngle);
    } else {
        repeticiones = (int) floor(abs(radius*sinf(lineAngle)/(2*pz->getLado())));
        dy = radius*sinf(lineAngle) / (float) repeticiones;
        dx = dy / tanf(lineAngle);
    }


    glPushMatrix();
    glTranslatef(p1->getX(),p1->getY(), 0.0f);
    glRotatef(180*angle/M_PI,0.0f,0.0f,1.0f);
    for(int i = 0; i< repeticiones-1; i++) {
        glTranslatef(dx, dy,0.0f);
        glPushMatrix();
        pz->Draw(0);
        glPopMatrix();
    }
    glPopMatrix();
}

piezas state_editor::discretizar() {
    std::list<pzCV> * centros = new std::list<pzCV>();

    for (std::list < control_point>::iterator it= puntos.begin(); it != puntos.end(); ++it) {
        control_point * me = &(*it);
        if(me->pz->point_valid(&me->p, me->pz->getLado())) {
            if(pack==0 || pack==3 || cajaAct==3) {
                pzCV _p;
                _p.vida = 5;
                _p.c.set(me->getX(),me->getY());
                centros->push_back(_p);
            } else {
                float lim1 = 1.0f/8.0f - me->pz->getLado();
                float lim2 = 7.0f/16.0f - me->pz->getLado();
                bool collide = false;
                if((me->getX()>lim1)&&(me->getX()<1-lim1)&&(me->getY()>lim2)&&(me->getY()<1-lim2))
                    collide = true;
                if((me->getX()>lim2)&&(me->getX()<1-lim2)&&(me->getY()>lim1)&&(me->getY()<1-lim1))
                    collide = true;

                if(!collide){
                    pzCV _p;
                    _p.vida = 5;
                    _p.c.set(me->getX(),me->getY());
                    centros->push_back(_p);
                }

            }
        }
    }

    for (std::list < control_block >::iterator it= bloques.begin(); it != bloques.end(); ++it) {
        control_block * me = &(*it);
        me->discretizar(centros, angle,(pack==0 || pack==3 || cajaAct==3));
    }

    piezas _p(angle,centros,cajas,cajaAct);
    return _p;
}

void control_block::discretizar( std::list<pzCV> * centros, float angle, bool easy) {

    float dx, dy;
    int repeticiones;

    float Ax = p2->getX()-p1->getX();
    float Ay = p2->getY()-p1->getY();

    float lineAngle = atan2f(Ay, Ax) - angle;
    float radius = sqrtf(powf(Ax,2)+powf(Ay,2));

    float lim1 = 1.0f/8.0f - pz->getLado();
    float lim2 = 7.0f/16.0f - pz->getLado();

    float Dx, Dy;
    Dx = radius*cosf(lineAngle);
    Dy = radius*sinf(lineAngle);

    if (abs(Dx)>= abs(Dy)) {
        repeticiones = (int) floor(abs(radius*cosf(lineAngle)/(2*pz->getLado())));
    } else {
        repeticiones = (int) floor(abs(radius*sinf(lineAngle)/(2*pz->getLado())));
    }
    dx = Ax / (float) repeticiones;
    dy = Ay / (float) repeticiones;
    float x = p1->getX();
    float y = p1->getY();
    for(int i = 0; i< repeticiones-1; i++) {
        x += dx;
        y += dy;
		pzCV _p;
		_p.vida = 5;
		_p.c.set(x,y);
        if(pz->point_valid(&(_p.c), pz->getLado()))
        {
            if(easy)
                centros->push_back(_p);
            else {
                bool collide = false;
                if((_p.c.getX()>lim1)&&(_p.c.getX()<1-lim1)&&(_p.c.getY()>lim2)&&(_p.c.getY()<1-lim2))
                    collide = true;
                if((_p.c.getX()>lim2)&&(_p.c.getX()<1-lim2)&&(_p.c.getY()>lim1)&&(_p.c.getY()<1-lim1))
                    collide = true;

                if(!collide)
                    centros->push_back(_p);
            }

        }
    }
}
void control_block::setPz( pieza * _pz) {
    pz = _pz;
}
void control_point::setPz( pieza * _pz) {
    pz = _pz;
}

char * state_editor::guardar() {
    FILE * f, *l;

    time_t rawtime;
    time ( &rawtime );
    char filename[50];
    char * file = (char*) malloc(sizeof(char)*100);
    file[0] = '\0';
    strcpy(file, "mapas/");
    sprintf (filename,"%d", rawtime);
    strcat(filename, ".mapfile");
    strcat(file, filename);
    f = fopen (file,"w");
    l = fopen ("mapas/maps.list","a");
    if ((f!=NULL) && (l!=NULL))
    {
        fprintf(f,"-MAPA\n");
        fprintf(f,"PACK(%d)\n",pack);
        fprintf(f,"NPIEZAS(%d)\n",pzs.size());

        for (std::list < piezas >::iterator it= pzs.begin(); it != pzs.end(); ++it) {
            piezas * me = &(*it);
            me->guardar(f);
        }
        fprintf(f,"-MAPA-END\n");

        fprintf(l,"%s\n",file);

        fclose (f);
        fclose (l);
    }

    return file;
}

control_point::control_point(){};
control_block::control_block(){};

 bool control_point::operator==(control_point other) {
     bool ret = true;
        ret &= (getX() == other.getX());
        ret &= (getY() == other.getY());
     return ret;
}
 bool control_block::operator==(control_block other) {
     bool ret = true;
        ret &= (p1 == other.p1);
        ret &= (p2 == other.p2);
     return ret;
}
