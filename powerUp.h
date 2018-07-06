#ifndef POWERUP_H_INCLUDED
#define POWERUP_H_INCLUDED

#include "Graphic.hpp"
#include "InputGestureDirectFingers.hpp"
#include "textures.h"
#include <vector>
#include <utility>
#include <string>

#define POWERUP_VIDA 1
#define POWERUP_VENENO 2

#define POWERUPRADIO 0.027f

#define POWERUPTIME_1 550
#define POWERUPTIME_2 630

namespace tuio
{
class PowerUp
{
    public:
    DirectPoint p;
    float radio;
    int tipo;
    ofImage * icono;
    int val;
    int timer;
    bool alive;

    PowerUp ();
    PowerUp (DirectPoint, float);
    bool isNear(DirectPoint, float);
    virtual void Draw();
};

class Vida : public PowerUp
{
    public:
    Vida (DirectPoint);
};

class Veneno : public PowerUp
{
    public:
    Veneno (DirectPoint);
};
};


#endif // JUEGO_H_INCLUDED
