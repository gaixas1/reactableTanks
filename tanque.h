#ifndef TANQUE_H_INCLUDED
#define TANQUE_H_INCLUDED

#include "Graphic.hpp"
#include "textures.h"
#include "InputGestureDirectObjects.hpp"
#include "InputGestureDirectFingers.hpp"
#include <deque>
#include "bala.h"
#include "Pad.h"

#define MAXVEL 0.002f
#define MINDISTANCE 0.02f
#define TANKSIZE 0.025f
#define MAXANGLE 0.02f
#define DISTSALIDA 0.03f
#define LIVE 20

#define TORRETASIZE 0.035f
#define DISTSALIDAT 0.04f

namespace tuio
{
class Tanque
{
    public:
        int id;
        DirectPoint p;
        float angle;
        float angleDraw;
        std::deque<DirectPoint> mov;
        float radio;
        int vida;

		Pad * pad;

        ofImage *fondo, *canyon;

        Tanque();
        Tanque(int, DirectPoint, float);
        virtual void Draw();
        void GoTo(DirectPoint);
        DirectPoint GoesTo();
        void MoveTo(float, float);
        void MoveTo(DirectPoint);
        void SetAngle(float);
        void setID(int);
        void Stop();

        void addVida(int);
        void removeVida(int);

        bool collideBala(Bala *);

		void setPad(Pad*);

        bool collide(DirectPoint *);

		Bala * padTap(DirectFinger *);

		bool golpear (int);
};

class Torreta : public Tanque
{
    public:
        float angleInc;
        int balaType;

        Torreta();
        Torreta(int, DirectPoint, bool);
        void Draw();
        void Inc();
        Bala * Disparar();
        bool collideBala(Bala *);
};
};


#endif // JUEGO_H_INCLUDED
