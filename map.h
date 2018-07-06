#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"

#include <list>
#include <stdio.h>
#include "pieza.h"
#include "tanque.h"
#include "bala.h"

#define MINACIRCLE 0.15f

namespace tuio
{

class mapa {
    public:
    std::list<piezas> pzs0, pzs2, pzs3, pzsg;
    pieza * cajas[4];
    ofImage * fondo;

    mapa();
    mapa(FILE *);
    virtual void Draw();
    virtual void DrawFondo(bool = false);
    void DrawSup();
    void CreateGameCopy();

    virtual bool tankCollide(Tanque *, DirectPoint);
    virtual void bombaCollide(Bomba *);
    virtual bool balaCollide(Bala *, DirectPoint);
    virtual bool balaCollide(Bala *, DirectPoint, float *);

    virtual void actuar(std::list<Bala *> *, std::list<Bomba *> *);
};

class mapaB : public mapa
{
    public:
    int timerA, timerB, timerC;
    mapaB();
    mapaB(FILE *);
    void actuar(std::list<Bala *> *, std::list<Bomba *> *);
};

class mapaC : public mapa
{
    public:
    int timer;
    Torreta T;

    mapaC();
    mapaC(FILE *);

    bool tankCollide(Tanque *, DirectPoint);

    void Draw();
    void DrawFondo(bool = false);
    void actuar(std::list<Bala *> *, std::list<Bomba *> *);
    bool balaCollide(Bala *, DirectPoint);
    bool balaCollide(Bala *, DirectPoint, float *);
};
class mapaD : public mapa
{
    public:
    int timer[4];
    Mina minas[4];
    float x[4], y[4];
    mapaD();
    mapaD(FILE *);

    void Draw();
    void DrawFondo(bool = false);

    void actuar(std::list<Bala *> *, std::list<Bomba *> *);
    bool balaCollide(Bala *, DirectPoint);
    bool balaCollide(Bala *, DirectPoint, float *);
    bool tankCollide(Tanque *, DirectPoint);
};
};


#endif // STATE_INICIO_H_INCLUDED
