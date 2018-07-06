#ifndef STATE_PLAY_H_INCLUDED
#define STATE_PLAY_H_INCLUDED

#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"

#include "State.h"
#include "map.h"
#include "tanque.h"
#include "pad.h"
#include "bala.h"
#include "powerUp.h"
#include <vector>

#define T1PIEZA 1
#define T2PIEZA 2
#define T3PIEZA 3
#define T4PIEZA 4

#define PAD1PIEZA 5
#define PAD2PIEZA 6
#define PAD3PIEZA 7
#define PAD4PIEZA 8

namespace tuio
{

class state_play : public state {
    public:
    mapa * m;
    Tanque t1, t2, t3, t4;
	Pad p1, p2, p3, p4;
	std::list<Bala *> balas;
	std::list<Bomba *> bombas;
	std::list<PowerUp *> ups;
	bool ini;
    int estado;
    int timer;
    int tanks;
    float angle;



    ofImage * ready, * go, * end;

    state_play(int);
    void Draw();
    state * Process();
    void ObjectIN(DirectObject *);
    void ObjectOUT(DirectObject *);
    void ObjectUPDATE(DirectObject *);

	void TAP(float, float);

	void WindowsResize(int, int);
};
};


#endif // STATE_INICIO_H_INCLUDED
