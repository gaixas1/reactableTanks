#ifndef STATE_EDITOR_H_INCLUDED
#define STATE_EDITOR_H_INCLUDED

#include "State.h"
#include "pieza.h"
#include <list>
#include <stdio.h>

#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"

//Estados
#define STEDITOR_INICIO 0
#define STEDITOR_CAPA 1
#define STEDITOR_PIEZAS 2
#define STEDITOR_GUARDA 3
#define STEDITOR_SALIR 4

//Piezas
#define IDEDITORSANGLE 5
#define IDEDITORSTATE 1
#define IDEDITORBORRADOR 2
#define IDERITORBORRADORCON 3
#define IDERITORGUARDADO 4
#define IDEDITORSALIR 6

namespace tuio
{
class control_point
{
    public:
    int id;
	DirectPoint p;
    pieza * pz;
    int estado;

    control_point();
    control_point(DirectFinger *, pieza *);
    bool updatePosition(DirectFinger *);
    bool updateFinger(DirectFinger *);
    void deleteFinger(DirectFinger *);
    bool isNear(DirectFinger *);
    void setPz(pieza *);

    float getX();
    float getY();

    void Draw(float);

    bool operator==(control_point);
};

class control_block {
    public:
    control_point * p1, *p2;
    pieza * pz;

	control_block();
	control_block(control_point *, control_point *, pieza *);
    void Draw(float);
    void control_block::discretizar( std::list<pzCV> *, float, bool=true);
    void setPz(pieza *);
    bool operator==(control_block);

};

class state_editor : public state
{
    public:
        float angle;
        int pack;

        state_editor();
        void Draw();
        state * Process();
        std::list<control_point> puntos;
        std::list<control_block> bloques;
        std::list<piezas> pzs;
        ofImage * fondo[4], * terrenos;

        int estado;
        pieza * cajas[4];
        int cajaAct;

        bool areConnected(control_point *,control_point *);

        void ObjectIN(DirectObject *);
        void ObjectUPDATE(DirectObject *);
        void ObjectOUT(DirectObject *);

        void FingerIN(DirectFinger *);
        void FingerUPDATE(DirectFinger *);
        void FingerOUT(DirectFinger *);

        piezas discretizar();
        char * guardar();
};
};

#endif // STATE_EDITOR_H_INCLUDED
