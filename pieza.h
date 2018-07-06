#ifndef PIEZA_H_INCLUDED
#define PIEZA_H_INCLUDED
#include "textures.h"

#include <list>
#include "DirectPoint.hpp"
#include <stdio.h>
#include "bala.h"

namespace tuio
{

class pzCV {
	public:
	DirectPoint c;
	int vida;
	bool operator ==(pzCV p) {
		return ((vida == p.vida) && (c.getX() == p.c.getX()) && (c.getY() == p.c.getY()));
	}
};

class pieza
{
    public:
        float lado;
        ofImage * textura;

        pieza();
        pieza(float);
        virtual void Draw(int);
        float getLado();
        virtual bool point_valid(DirectPoint *, float);
};
class piezas
{
	public:
	float angle;
	std::list<pzCV> * centros;
	pieza ** p;
	int id_pieza;

    piezas ();
    piezas (float, std::list<pzCV> *, pieza **, int);
	piezas (FILE *, pieza **, int);
	void read (FILE *, pieza **, int);
	void Draw();
	void deleteDistance(DirectPoint *, float);
	void guardar(FILE *);
    piezas Copy();

    void collideBomba(Bomba *);
    bool collide(DirectPoint *, float);
    bool collide(DirectPoint *, float, float *);

};



class pieza1 : public pieza
{
    public:
        ofImage * texturas[5];
        virtual void Draw(int);
        pieza1();
};

class pieza2 : public pieza
{
    public:
        ofImage * texturas[5];
        virtual void Draw(int);
        pieza2();
};
class pieza3 : public pieza
{
    public:
        pieza3();
        virtual void Draw(int);
};
class pieza4 : public pieza
{
    public:
        pieza4();
        virtual void Draw(int);
};
};

#endif // STATE_LOADER_H_INCLUDED
