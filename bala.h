#ifndef BALA_H_INCLUDED
#define BALA_H_INCLUDED

//#include "GlobalConfig.hpp"
#include "InputGestureDirectObjects.hpp"
#include "textures.h"
#include "sounds.h"

#define TAMMINA 0.0003f

namespace tuio
{
class Bala
{
	public:
	int tipo;
    DirectPoint p;
	float angulo;
	int poder;
	int timer;

	float vel;
	float radio;

	Bala();
	Bala(int, float, DirectPoint);
	Bala(int, float, DirectPoint, int);

	DirectPoint GoesTo();
	void MoveTo(float, float);
    void MoveTo(DirectPoint);
    void SetAngle(float);

    bool collide(Bala *, DirectPoint *);

	virtual void Draw();
};

class Bomba : public Bala
{
    public:
    int timer;
    int tam;
    Bomba();
    Bomba(int, DirectPoint, int);
    ofImage * explosion;
    ofSoundPlayer * explo;
    virtual void Draw();
};


class BombaN : public Bomba
{
    public:
    BombaN(int, DirectPoint, int);
    void Draw();
};

class Mina
{
    public:
    DirectPoint p;
    int tam;
    ofImage * fondo;
    float radio;
    bool destroyed;

    Mina();
    Mina(DirectPoint);
    void Draw();
    void goTo(float, float);
    void ini();

    void Destroy();

};
};
#endif
