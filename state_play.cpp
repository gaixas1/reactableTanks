#include "state_play.h"
#include "textures.h"
#include "sounds.h"
#include "mapas.h"
#include "state_loader.h"
#include "tanque.h"

using namespace tuio;

state_play::state_play(int d) {
    m = Mapas::getMapa(d);
    m->CreateGameCopy();

	p1.removeStatus(PAD_PAINT|PAD_CANFIRE);
	p2.removeStatus(PAD_PAINT|PAD_CANFIRE);
	p3.removeStatus(PAD_PAINT|PAD_CANFIRE);
	p4.removeStatus(PAD_PAINT|PAD_CANFIRE);

	timer = -1;
	estado = 1;
	tanks = 0;
	angle = 0.0f;

	ready = Texturas::getImage("ready.png");
	go = Texturas::getImage("go.png");
}

state * state_play::Process() {
    DirectPoint t1_p, t2_p, t3_p, t4_p;
    bool t1_collide,t2_collide,t3_collide,t4_collide;
    tanks = 0;
    if(t1.vida>0)
        tanks++;
    else
        p1.removeStatus(PAD_PAINT|PAD_CANFIRE);
    if(t2.vida>0)
        tanks++;
    else
        p2.removeStatus(PAD_PAINT|PAD_CANFIRE);
    if(t3.vida>0)
        tanks++;
    else
        p3.removeStatus(PAD_PAINT|PAD_CANFIRE);
    if(t4.vida>0)
        tanks++;
    else
        p4.removeStatus(PAD_PAINT|PAD_CANFIRE);

    switch(estado) {
        case 1:
            if(timer>0) {
                timer--;
                if((timer > 60) && (tanks == 4)) {
                    timer = 60;
                }
            } else if(timer==0) {
                estado = 2;
            }
            break;
        case 2:
            t1_p = t1.GoesTo();
            t2_p = t2.GoesTo();
            t3_p = t3.GoesTo();
            t4_p = t4.GoesTo();

            t1_collide = m->tankCollide(&t1, t1_p);
            t2_collide = m->tankCollide(&t2, t2_p);
            t3_collide = m->tankCollide(&t3, t3_p);
            t4_collide = m->tankCollide(&t4, t4_p);

            p1.addStatus(PAD_CANFIRE);
            p2.addStatus(PAD_CANFIRE);
            p3.addStatus(PAD_CANFIRE);
            p4.addStatus(PAD_CANFIRE);

            if(p1.isNear(&p2)) {
                p1.removeStatus(PAD_CANFIRE);
                p2.removeStatus(PAD_CANFIRE);
            }
            if(p1.isNear(&p3)) {
                p1.removeStatus(PAD_CANFIRE);
                p3.removeStatus(PAD_CANFIRE);
            }
            if(p1.isNear(&p4)) {
                p1.removeStatus(PAD_CANFIRE);
                p4.removeStatus(PAD_CANFIRE);
            }
            if(p2.isNear(&p3)) {
                p2.removeStatus(PAD_CANFIRE);
                p3.removeStatus(PAD_CANFIRE);
            }
            if(p2.isNear(&p4)) {
                p2.removeStatus(PAD_CANFIRE);
                p4.removeStatus(PAD_CANFIRE);
            }
            if(p3.isNear(&p4)) {
                p3.removeStatus(PAD_CANFIRE);
                p4.removeStatus(PAD_CANFIRE);
            }

            if(!t1_collide) {
                t1_collide |= t2.collide(&t1_p);
                t1_collide |= t3.collide(&t1_p);
                t1_collide |= t4.collide(&t1_p);
            }

            if(!t2_collide) {
                t2_collide |= t1.collide(&t2_p);
                t2_collide |= t3.collide(&t2_p);
                t2_collide |= t4.collide(&t2_p);
            }

            if(!t3_collide) {
                t3_collide |= t1.collide(&t3_p);
                t3_collide |= t2.collide(&t3_p);
                t3_collide |= t4.collide(&t3_p);
            }

            if(!t4_collide) {
                t4_collide |= t1.collide(&t4_p);
                t4_collide |= t2.collide(&t4_p);
                t4_collide |= t3.collide(&t4_p);
            }

            if(t1_collide)
                t1.Stop();
            else
                t1.MoveTo(t1_p);

            if(t2_collide)
                t2.Stop();
            else
                t2.MoveTo(t2_p);

            if(t3_collide)
                t3.Stop();
            else
                t3.MoveTo(t3_p);

            if(t4_collide)
                t4.Stop();
            else
                t4.MoveTo(t4_p);

            if(timer>=630) {
                float angl = (99*rand()/(2.0*(RAND_MAX + 1.0)));
                float radi = (rand()/(2.0*(RAND_MAX + 1.0)));
                DirectPoint _p(radi*cosf(angl)+0.5f, radi*sinf(angl)+0.5f);
                switch(rand()%1) {
                    case 0:
                        ups.push_back(new Veneno(_p));
                        break;
                    default:
                        ups.push_back(new Vida(_p));
                }
                timer = 0;
            }
            timer++;

            for (std::list <PowerUp *>::iterator it= ups.begin(); it != ups.end(); ++it) {
                PowerUp * b = (*it);
                if(t1.vida>0)
                    if(b->isNear(t1.p,t1.radio)) {
                        switch(b->tipo) {
                            case POWERUP_VIDA :
                                t1.addVida(b->val);
                                break;
                            case POWERUP_VENENO :
                                t1.removeVida(b->val);
                                break;
                        }
                        *it = NULL;
                    }
                if(t2.vida>0)
                    if(b->isNear(t2.p,t2.radio)) {
                        switch(b->tipo) {
                            case POWERUP_VIDA :
                                t2.addVida(b->val);
                                break;
                            case POWERUP_VENENO :
                                t2.removeVida(b->val);
                                break;
                        }
                        *it = NULL;
                    }
                if(t3.vida>0)
                    if(b->isNear(t3.p,t3.radio)) {
                        switch(b->tipo) {
                            case POWERUP_VIDA :
                                t3.addVida(b->val);
                                break;
                            case POWERUP_VENENO :
                                t3.removeVida(b->val);
                                break;
                        }
                        *it = NULL;
                    }
                if(t4.vida>0)
                    if(b->isNear(t4.p,t4.radio)) {
                        switch(b->tipo) {
                            case POWERUP_VIDA :
                                t4.addVida(b->val);
                                break;
                            case POWERUP_VENENO :
                                t4.removeVida(b->val);
                                break;
                        }
                        *it = NULL;
                    }
                if(b->alive == false)
                    *it = NULL;
                if(*it == NULL)
                    delete b;
            }
            ups.remove(NULL);


            for (std::list <Bomba *>::iterator it= bombas.begin(); it != bombas.end(); ++it) {
                Bomba * b = (*it);
                if(b->tam == 10) {
                    float _rad = b->radio;
                    if(t1.collideBala(b)){
                        int _vida = t1.vida;
                        if(t1.golpear(b->poder)) {
                            bombas.push_back(new Bomba(3, t1.p, _vida));
                            tanks--;
                        }
                    }
                    if(t2.collideBala(b)){
                        int _vida = t2.vida;
                        if(t2.golpear(b->poder)) {
                            bombas.push_back(new Bomba(3, t2.p, _vida));
                            tanks--;
                        }
                    }
                    if(t3.collideBala(b)){
                        int _vida = t3.vida;
                        if(t3.golpear(b->poder)) {
                            bombas.push_back(new Bomba(3, t3.p, _vida));
                            tanks--;
                        }
                    }
                    if(t4.collideBala(b)) {
                        int _vida = t4.vida;
                        if(t4.golpear(b->poder)) {
                            bombas.push_back(new Bomba(3, t4.p, _vida));
                            tanks--;
                        }
                    }

                    for (std::list <Bala *>::iterator it2= balas.begin(); it2 != balas.end(); ++it2) {
                        Bala * b2 = (*it2);
                        if(b2->collide(b, &(b->p))) {
                            *it2 = NULL;
                            bombas.push_back(new Bomba(b2->poder, b2->p, 1));
                            delete b2;
                        }
                    }
                    balas.remove(NULL);
                    m->bombaCollide(b);

                } else if(b->tam > 20) {
                    *it = NULL;
                    delete b;
                }
            }
            bombas.remove(NULL);

            for (std::list <Bala *>::iterator it= balas.begin(); it != balas.end(); ++it) {
                Bala * b = (*it);
                if(b!=NULL) {
                    DirectPoint _p = b->GoesTo();
                    bool collided = false;
                    if (t1.collideBala(b)) {
                        *it = NULL;
                        bombas.push_back(new Bomba(b->poder, b->p, 1));
                        delete b;
                    } else if (t2.collideBala(b)) {
                        *it = NULL;
                        bombas.push_back(new Bomba(b->poder, b->p, 1));
                        delete b;
                    } else if (t3.collideBala(b)) {
                        *it = NULL;
                        bombas.push_back(new Bomba(b->poder, b->p, 1));
                        delete b;
                    } else if (t4.collideBala(b)) {
                        *it = NULL;
                        bombas.push_back(new Bomba(b->poder, b->p, 1));
                        delete b;
                    } else if((b->tipo == 2) && (b->poder > 1)) {
                        if(m->balaCollide(b,_p, &(b->angulo))) {
                            (b->poder)--;
                        }
                        bool alive = true;
                        for (std::list <Bala *>::iterator it2= balas.begin(); it2 != balas.end(); ++it2) {
                            Bala * b2 = (*it2);
                            if((b2 != NULL)&&(b2 != b)) {
                                if(b2->collide(b, &_p)) {
                                    alive = false;
                                    bombas.push_back(new Bomba(b2->poder, b2->p, 1));
                                    *it2 = NULL;
                                    delete b2;
                                }
                            }
                        }
                        if(alive){
                            b->MoveTo(_p);
                        } else {
                            *it = NULL;
                            bombas.push_back(new Bomba(b->poder, b->p, 1));
                            delete b;
                        }
                    } else {
                         if(m->balaCollide(b,_p)) {
                            *it = NULL;
                            if(b->tipo == 3)
                                bombas.push_back(new Bomba(b->poder, b->p, 200));
                            else
                                bombas.push_back(new Bomba(b->poder, b->p, 1));
                            delete b;
                            collided = true;
                        } else {
                            bool alive = true;
                            for (std::list <Bala *>::iterator it2= balas.begin(); it2 != balas.end(); ++it2) {
                                Bala * b2 = (*it2);
                                if((b2 != NULL)&&(b2 != b)) {
                                    if(b2->collide(b, &_p)) {
                                        alive = false;
                                        bombas.push_back(new Bomba(b2->poder, b2->p, 1));
                                        *it2 = NULL;
                                        delete b2;
                                    }
                                }
                            }

                            if(alive){
                                b->MoveTo(_p);
                            } else {
                                *it = NULL;
                                bombas.push_back(new Bomba(b->poder, b->p, 1));
                                delete b;
                            }
                        }
                    }
                }
            }
            balas.remove(NULL);
            if(tanks <= 1) {
                estado = 3;
                timer = 300;
                if(t1.vida>0)
                    end = Texturas::getImage("P1.png");
                else if(t2.vida>0)
                    end = Texturas::getImage("P2.png");
                else if(t3.vida>0)
                    end = Texturas::getImage("P4.png");
                else if(t4.vida>0)
                    end = Texturas::getImage("P4.png");
                else
                    end = Texturas::getImage("lose.png");
            }
            m->actuar(&balas, &bombas);
            break;
        case 3:
            if(timer > 0) {
                timer--;
            }
            for (std::list <Bomba *>::iterator it= bombas.begin(); it != bombas.end(); ++it) {
                Bomba * b = (*it);
                if(b->tam == 10) {
                    float _rad = b->radio;
                    for (std::list <Bala *>::iterator it2= balas.begin(); it2 != balas.end(); ++it2) {
                        Bala * b2 = (*it2);
                        if(b2->collide(b, &(b->p))) {
                            *it2 = NULL;
                            bombas.push_back(new Bomba(b2->poder, b2->p, 1));
                            delete b2;
                        }
                    }
                    balas.remove(NULL);
                    m->bombaCollide(b);

                } else if(b->tam > 20) {
                    *it = NULL;
                    delete b;
                }
            }
            bombas.remove(NULL);

            for (std::list <Bala *>::iterator it= balas.begin(); it != balas.end(); ++it) {
                Bala * b = (*it);
                if(b!=NULL) {
                    DirectPoint _p = b->GoesTo();
                    bool collided = false;
                    if((b->tipo == 2) && (b->poder > 1)) {
                        if(m->balaCollide(b,_p, &(b->angulo))) {
                            (b->poder)--;
                        }
                        bool alive = true;
                        for (std::list <Bala *>::iterator it2= balas.begin(); it2 != balas.end(); ++it2) {
                            Bala * b2 = (*it2);
                            if((b2 != NULL)&&(b2 != b)) {
                                if(b2->collide(b, &_p)) {
                                    alive = false;
                                    bombas.push_back(new Bomba(b2->poder, b2->p, 1));
                                    *it2 = NULL;
                                    delete b2;
                                }
                            }
                        }
                        if(alive){
                            b->MoveTo(_p);
                        } else {
                            *it = NULL;
                            bombas.push_back(new Bomba(b->poder, b->p, 1));
                            delete b;
                        }
                    } else {
                         if(m->balaCollide(b,_p)) {
                            *it = NULL;
                            if(b->tipo == 3)
                                bombas.push_back(new Bomba(b->poder, b->p, 200));
                            else
                                bombas.push_back(new Bomba(b->poder, b->p, 1));
                            delete b;
                            collided = true;
                        } else {
                            bool alive = true;
                            for (std::list <Bala *>::iterator it2= balas.begin(); it2 != balas.end(); ++it2) {
                                Bala * b2 = (*it2);
                                if((b2 != NULL)&&(b2 != b)) {
                                    if(b2->collide(b, &_p)) {
                                        alive = false;
                                        bombas.push_back(new Bomba(b2->poder, b2->p, 1));
                                        *it2 = NULL;
                                        delete b2;
                                    }
                                }
                            }

                            if(alive){
                                b->MoveTo(_p);
                            } else {
                                *it = NULL;
                                bombas.push_back(new Bomba(b->poder, b->p, 1));
                                delete b;
                            }
                        }
                    }
                }
            }
            balas.remove(NULL);

            break;
    }
    if(estado == 3 && timer == 0) {
        return new state_loader(2);
    } else {
        return this;
    }
}

void state_play::Draw() {

    m->DrawFondo(estado==1);
    for (std::list <PowerUp *>::iterator it= ups.begin(); it != ups.end(); ++it) {
        PowerUp * b = (*it);
        b->Draw();
    }
    t1.Draw();
    t2.Draw();
    t3.Draw();
    t4.Draw();

    for (std::list <Bala *>::iterator it= balas.begin(); it != balas.end(); ++it) {
        Bala * b = (*it);
        b->Draw();
    }
    for (std::list <Bomba *>::iterator it= bombas.begin(); it != bombas.end(); ++it) {
        Bomba * b = (*it);
        b->Draw();
    }
    m->DrawSup();
    p1.Draw();
    p2.Draw();
    p3.Draw();
    p4.Draw();

    if(estado==1)
    {
        glPushMatrix();
        glTranslatef(0.5f,0.5f,0.0f);
        glRotatef(angle,0.0f,0.0f,1.0f);
        ofEnableAlphaBlending();
        ofSetColor(255,255,255,255);
        if((timer < 60)&&(timer >= 0)) {
            float lim = 0.35f-timer*0.002f;
            go->draw(-lim,-lim,lim+lim,lim+lim);
        } else {
            ready->draw(-0.35f,-0.35f,0.7f,0.7f);
        }

        ofDisableAlphaBlending();
        glPopMatrix();
        angle += 0.1f;
    } else if(estado==3){
        ofEnableAlphaBlending();
        glPushMatrix();
        glTranslatef(0.5f,0.5f,0.0f);
        ofSetColor(255,255,255,255);
        glRotatef(angle,0.0f,0.0f,1.0f);
        end->draw(-0.35f,-0.35f,0.7f,0.7f);
        glPopMatrix();
        ofDisableAlphaBlending();
        angle += 0.1f;
    }
}


void state_play::ObjectIN(DirectObject * o){
    switch(estado) {
        case 1:
            switch(o->f_id) {
                case T1PIEZA:
                    if(t1.vida==0) {
                        if(o->getDistance(0.5f,0.05f) <= 0.05f) {
                            t1.setID(1);
                            t1.SetAngle(0);
                            t1.MoveTo(0.5f,0.05f);
                            t1.setPad(&p1);
                            t1.golpear(-LIVE);
                            tanks++;
                            if(tanks == 2)
                                timer = 1000;
                        }
                    }
                    break;
                case T2PIEZA:
                    if(t2.vida==0) {
                        if(o->getDistance(0.05f,0.5f) <= 0.05f) {
                            t2.setID(2);
                            t2.SetAngle(3.0f*M_PI/2.0f);
                            t2.MoveTo(0.05f,0.5f);
                            t2.setPad(&p2);
                            t2.golpear(-LIVE);
                            tanks++;
                            if(tanks == 2)
                                timer = 1000;
                        }
                    }
                    break;
                case T3PIEZA:
                    if(t3.vida==0) {
                        if(o->getDistance(0.5f,0.95f) <= 0.05f) {
                            t3.setID(3);
                            t3.SetAngle(M_PI);
                            t3.MoveTo(0.5f,0.95f);
                            t3.setPad(&p3);
                            t3.golpear(-LIVE);
                            tanks++;
                            if(tanks == 2)
                                timer =1000;
                        }
                    }
                    break;
                case T4PIEZA:
                    if(t4.vida==0) {
                        if(o->getDistance(0.95f,0.5f) <= 0.05f) {
                            t4.setID(4);
                            t4.SetAngle(M_PI/2.0f);
                            t4.MoveTo(0.95f,0.5f);
                            t4.setPad(&p4);
                            t4.golpear(-LIVE);
                            tanks++;
                            if(tanks == 2)
                                timer = 1000;
                        }
                    }
                    break;
            }
            break;
        case 2:
            switch(o->f_id) {
                case T1PIEZA:
                    t1.GoTo(*o);
                    t1.SetAngle(o->angle);
                    break;
                case T2PIEZA:
                    t2.GoTo(*o);
                    t2.SetAngle(o->angle);
                    break;
                case T3PIEZA:
                    t3.GoTo(*o);
                    t3.SetAngle(o->angle);
                    break;
                case T4PIEZA:
                    t4.GoTo(*o);
                    t4.SetAngle(o->angle);
                    break;
                case PAD1PIEZA:
                    p1.setValues(o->getX(),o->getY(),o->angle);
                    p1.addStatus(PAD_PAINT);
                    break;
                case PAD2PIEZA:
                    p2.setValues(o->getX(),o->getY(),o->angle);
                    p2.addStatus(PAD_PAINT);
                    break;
                case PAD3PIEZA:
                    p3.setValues(o->getX(),o->getY(),o->angle);
                    p3.addStatus(PAD_PAINT);
                    break;
                case PAD4PIEZA:
                    p4.setValues(o->getX(),o->getY(),o->angle);
                    p4.addStatus(PAD_PAINT);
                    break;
            }
            break;
    }
}
void state_play::ObjectOUT(DirectObject * o){
    if(estado==2)
        switch(o->f_id) {
            case T1PIEZA:
                t1.Stop();
                break;
            case T2PIEZA:
                t2.Stop();
                break;
            case T3PIEZA:
                t3.Stop();
                break;
            case T4PIEZA:
                t4.Stop();
                break;
            case PAD1PIEZA:
                p1.removeStatus(PAD_PAINT|PAD_CANFIRE);
                break;
            case PAD2PIEZA:
                p2.removeStatus(PAD_PAINT|PAD_CANFIRE);
                break;
            case PAD3PIEZA:
                p3.removeStatus(PAD_PAINT|PAD_CANFIRE);
                break;
            case PAD4PIEZA:
                p4.removeStatus(PAD_PAINT|PAD_CANFIRE);
                break;
        }
}
void state_play::ObjectUPDATE(DirectObject * o){
    ObjectIN(o);
}

void state_play::TAP(float x, float y){
    if(estado==2) {
        DirectFinger _p;
        _p.set(x,y);

        Bala * _b = NULL;
        if((_b = t1.padTap(&_p)) == NULL)
        if((_b = t2.padTap(&_p)) == NULL)
        if((_b = t3.padTap(&_p)) == NULL)
        _b = t4.padTap(&_p);

        if(_b != NULL) {
            if(_b->tipo == 4) {
                bombas.push_back((Bomba*) _b);
            } else {
                balas.push_back(_b);
            }
        }
    }
}
