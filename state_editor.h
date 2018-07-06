#ifndef STATE_EDITOR_H_INCLUDED
#define STATE_EDITOR_H_INCLUDED

#include "State.h"
#include "pieza.h"
#include <vector>

#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"

#define IDEDITORSANGLE 3
#define IDEDITORSTATE 1

namespace tuio
{
class control_point
{
    public:
    int id;
	DirectPoint p;

    control_point(DirectFinger *);
    bool updatePosition(DirectFinger *);
    bool updateFinger(DirectFinger *);
    void deleteFinger(DirectFinger *);
    bool isNear(DirectFinger *);

    float getX();
    float getY();

    void Draw();
};

class control_block {
    public:
    control_point * p1, *p2;

	control_block(control_point *, control_point *);
    void Draw(float);
};

class state_editor : public state
{
    public:
        float angle;

        state_editor();
        void Draw();
        state * Process();
        std::vector<control_point *> puntos;
        std::vector<control_block *> bloques;
        std::vector<pieza *> piezas;

        bool areConnected(control_point *,control_point *);

        void ObjectIN(DirectObject *);
        void ObjectUPDATE(DirectObject *);
        void ObjectOUT(DirectObject *);

        void FingerIN(DirectFinger *);
        void FingerUPDATE(DirectFinger *);
        void FingerOUT(DirectFinger *);
};
};

#endif // STATE_EDITOR_H_INCLUDED
