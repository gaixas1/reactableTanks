#include "pieza.h"
#include "ofGraphics.h"
#ifndef M_PI_4
#define M_PI_4 M_PI/4
#endif
using namespace tuio;

piezas::piezas () {}
piezas::piezas (float _angle, std::list<pzCV> * _centros, pieza ** _p, int _id_pieza) {
    angle = _angle;
    centros = _centros;
    p = _p;
    id_pieza = _id_pieza;
}


void piezas::Draw() {
    for (std::list <pzCV>::iterator it= centros->begin(); it != centros->end(); ++it){
        pzCV * ob = &(*it);
        glPushMatrix();
        glTranslatef(ob->c.getX(),ob->c.getY(),0);
        glRotatef(180*angle/M_PI,0.0f,0.0f,1.0f);
        p[id_pieza]->Draw(ob->vida);
        glPopMatrix();
    }
}

void pieza::Draw(int vida) {
    textura->draw(-0.01f,-0.01f,0.02f,0.02f);
}

pieza::pieza() {
    lado = 0.01f;
    textura = Texturas::getImage("p_1.png");
}

pieza1::pieza1() {
    lado = 0.01f;
    textura = Texturas::getImage("p_1.png");
    texturas[4] = Texturas::getImage("p_1.png");
    texturas[3] = Texturas::getImage("p_2.png");
    texturas[2] = Texturas::getImage("p_3.png");
    texturas[1] = Texturas::getImage("p_4.png");
    texturas[0] = Texturas::getImage("p_5.png");
}


pieza2::pieza2() {
    lado = 0.01f;
    textura = Texturas::getImage("p_1.png");
    texturas[4] = Texturas::getImage("p_1.png");
    texturas[3] = Texturas::getImage("p_2.png");
    texturas[2] = Texturas::getImage("p_3.png");
    texturas[1] = Texturas::getImage("p_4.png");
    texturas[0] = Texturas::getImage("p_5.png");
}

pieza3::pieza3() {
    textura = Texturas::getImage("fuego.jpg");
    lado = 0.015f;
}
pieza4::pieza4() {
    textura = Texturas::getImage("humo.png");
    lado = 0.03f;
}

pieza::pieza(float l) {
    lado = l;
}

float pieza::getLado(){
	return lado;
}

 bool pieza::point_valid(DirectPoint * o, float dist) {
     float distance = 0.05f + dist;
    if(o->getDistance(0.05f,0.5f) <= distance) {
        return false;
    } else if(o->getDistance(0.95f,0.5f) <= distance) {
        return false;
    } else if(o->getDistance(0.5f,0.05f) <= distance) {
        return false;
    } else if(o->getDistance(0.5f,0.95f) <= distance) {
        return false;
    }
    return true;
 }


void pieza1::Draw(int vida) {
    glColor3d(255,255,255);

    ofEnableAlphaBlending();
    texturas[vida-1]->draw(-lado,-lado,lado+lado,lado+lado);
    ofDisableAlphaBlending();
}

void pieza2::Draw(int vida) {
    glColor3d(255,255,255);
    ofEnableAlphaBlending();
    texturas[(vida-1)/3 ]->draw(-lado,-lado,lado+lado,lado+lado);
    ofDisableAlphaBlending();
}

void pieza3::Draw(int vida) {

    glColor3d(255,255,255);
    textura->draw(-lado,-lado,lado+lado,lado+lado);
}

void pieza4::Draw(int vida) {
    glColor3d(255,255,255);
    ofEnableAlphaBlending();
    textura->draw(-lado-0.01f,-lado-0.01f,lado+lado+0.02f,lado+lado+0.02f);
    ofDisableAlphaBlending();
}

void piezas::deleteDistance(DirectPoint * c, float d) {
    pzCV _p;
    float distance = (d + p[id_pieza]->getLado());
    for (std::list < pzCV>::iterator it= centros->begin(); it != centros->end(); ++it){
        pzCV * ob = &(*it);
        if(ob->c.getDistance(c) < distance)
        {
             (*it) =_p;
        }
    }
    centros->remove(_p);
}

void piezas::guardar(FILE * f) {
    fprintf(f,"--PIEZAS\n");
    fprintf(f,"*TPIEZA(%d)\n",id_pieza);
    fprintf(f,"*NCENTROS(%d)\n",centros->size());
    fprintf(f,"*ANGULO(%f)\n",angle);
    for (std::list <pzCV>::iterator it= centros->begin(); it != centros->end(); ++it){
        pzCV * ob = &(*it);
        fprintf(f,"**(%f, %f)\n",ob->c.getX(),ob->c.getY());
    }
    fprintf(f,"--PIEZAS-END\n");
}

piezas::piezas(FILE * f, pieza ** _p, int tipo) {
    centros = new std::list<pzCV>();
    p = _p;
    id_pieza = tipo;
    int c;
    fscanf(f,"*NCENTROS(%d)\n",&c);
    fscanf(f,"*ANGULO(%f)\n",&angle);
    pzCV ob;
    for (int i = 0; i < c; i++){
        float x, y;
        fscanf(f,"**(%f, %f)\n",&x,&y);
        ob.c.set(x,y);
		if(tipo==0)
			ob.vida = 5;
		else if(tipo==1)
			ob.vida = 10;
        centros->push_back(ob);
    }
}

void piezas::read(FILE * f, pieza ** _p, int tipo) {
    centros = new std::list<pzCV>();
    p = _p;
    id_pieza = tipo;
    int c;
    fscanf(f,"*NCENTROS(%d)\n",&c);
    fscanf(f,"*ANGULO(%f)\n",&angle);
    pzCV ob;
    for (int i = 0; i < c; i++){
        float x, y;
        fscanf(f,"**(%f, %f)\n",&x,&y);
        ob.c.set(x,y);
		if(tipo==0)
			ob.vida = 5;
		else if(tipo==1)
			ob.vida = 15;
        centros->push_back(ob);
    }
}

piezas piezas::Copy() {
	std::list<pzCV> * _centros = new std::list<pzCV>(*centros);
    piezas _p(angle, _centros, p, id_pieza);
    return _p;
}


void piezas::collideBomba(Bomba * _b) {
    float distance = _b->radio + p[id_pieza]->getLado()/cosf(M_PI_4);
    pzCV _p;
    for (std::list < pzCV>::iterator it= centros->begin(); it != centros->end(); ++it) {
        pzCV * me = &(*it);
        if(me->c.getDistance(_b->p) < distance)
        {
            DirectPoint p0, p1, p2, p3, p4;
            p0.set((_b->p.getX()-me->c.getX())/distance,(_b->p.getY()-me->c.getY())/distance);
            float co = cosf(angle-M_PI_4);
            float si = sinf(angle-M_PI_4);
            p1.set(co, si);
            p2.set(-si, co);
            p3.set(-co, -si);
            p4.set(si, -co);

            int counter = 0;
            float xinters;

            float x_ = p0.getX(), y_ = p0.getY(), x0, y0, x1, y1;
            //p1-p2
            x0 = p1.getX(); y0 = p1.getY();
            x1 = p2.getX(); y1 = p2.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            //p2-p3
            x0 = p2.getX(); y0 = p2.getY();
            x1 = p3.getX(); y1 = p3.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            //p3-p4
            x0 = p3.getX(); y0 = p3.getY();
            x1 = p4.getX(); y1 = p4.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            //p4-p1
            x0 = p4.getX(); y0 = p4.getY();
            x1 = p1.getX(); y1 = p1.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            if(counter % 2 != 0) {
                me->vida -= _b->poder;
                if(me->vida <= 0) {
                    *it = _p;
                }
            }
        }
    }
    centros->remove(_p);
}
bool piezas::collide(DirectPoint * _p, float _rad) {
    float distance = _rad + p[id_pieza]->getLado()/cosf(M_PI_4);
    for (std::list < pzCV>::iterator it= centros->begin(); it != centros->end(); ++it) {
        pzCV * me = &(*it);
        if(me->c.getDistance(_p) < distance)
        {
            DirectPoint p0, p1, p2, p3, p4;
            p0.set((_p->getX()-me->c.getX())/distance,(_p->getY()-me->c.getY())/distance);
            float co = cosf(angle-M_PI_4);
            float si = sinf(angle-M_PI_4);
            p1.set(co, si);
            p2.set(-si, co);
            p3.set(-co, -si);
            p4.set(si, -co);

            int counter = 0;
            float xinters;

            float x_ = p0.getX(), y_ = p0.getY(), x0, y0, x1, y1;
            //p1-p2
            x0 = p1.getX(); y0 = p1.getY();
            x1 = p2.getX(); y1 = p2.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            //p2-p3
            x0 = p2.getX(); y0 = p2.getY();
            x1 = p3.getX(); y1 = p3.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            //p3-p4
            x0 = p3.getX(); y0 = p3.getY();
            x1 = p4.getX(); y1 = p4.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            //p4-p1
            x0 = p4.getX(); y0 = p4.getY();
            x1 = p1.getX(); y1 = p1.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            if(counter % 2 != 0) {
                return true;
            }
        }
    }

    return false;
}
bool piezas::collide(DirectPoint * _p, float _rad, float * anguloSalida) {
    float distance = _rad + p[id_pieza]->getLado()/cosf(M_PI_4);
    for (std::list < pzCV>::iterator it= centros->begin(); it != centros->end(); ++it) {
        pzCV * me = &(*it);
        if(me->c.getDistance(_p) < distance)
        {
            DirectPoint p0, p1, p2, p3, p4;
            p0.set((_p->getX()-me->c.getX())/distance,(_p->getY()-me->c.getY())/distance);
            float co = cosf(angle-M_PI_4);
            float si = sinf(angle-M_PI_4);
            p1.set(co, si);
            p2.set(-si, co);
            p3.set(-co, -si);
            p4.set(si, -co);

            int counter = 0;
            float xinters;

            float x_ = p0.getX(), y_ = p0.getY(), x0, y0, x1, y1;
            //p1-p2
            x0 = p1.getX(); y0 = p1.getY();
            x1 = p2.getX(); y1 = p2.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            //p2-p3
            x0 = p2.getX(); y0 = p2.getY();
            x1 = p3.getX(); y1 = p3.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            //p3-p4
            x0 = p3.getX(); y0 = p3.getY();
            x1 = p4.getX(); y1 = p4.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            //p4-p1
            x0 = p4.getX(); y0 = p4.getY();
            x1 = p1.getX(); y1 = p1.getY();
            if ((y_ ) > min(y0, y1))
                if ((y_) <= max(y0, y1))
                    if ((x_) <= max(x0, x1))
                        if (y0 != y1) {
                            xinters = (y_ - y0) * (x1 - x0) / (y1 - y0) +x0;
                            if (x0 == x1 || (x_) <= xinters) {
                                counter++;
                            }
                        }
            if(counter % 2 != 0) {
				float _res = *anguloSalida;
				float dch = atan2(y_, x_);
				float tang = angle;

				while(_res<=0) {
					_res += 2*M_PI;
				}
				while(_res > 2*M_PI) {
					_res -= 2*M_PI;
				}
				while(dch<=0) {
					dch += 2*M_PI;
				}
				while(dch>2*M_PI) {
					dch -= 2*M_PI;
				}

				while(tang>0) {
					tang -= 2*M_PI;
				}

				float ant = tang - M_PI_4;
				float act = tang + M_PI_4;

                bool dentro = true;
                while(dentro) {
                    if(dch <= act) {
						_res = M_PI+act + ant - *anguloSalida;
                        dentro = false;
                    } else {
                        ant = act;
                        act +=M_PI_2;
                    }
                }

                *anguloSalida = _res;
                return true;
            }
        }
    }

    return false;
}
