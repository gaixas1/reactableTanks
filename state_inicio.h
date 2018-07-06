#ifndef STATE_INICIO_H_INCLUDED
#define STATE_INICIO_H_INCLUDED

#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"

#include "state_loader.h"
#include "mapas.h"

namespace tuio
{

class state_inicio : public state {
    public:
    int change2;
    ofImage * fondo;

    state_inicio();
    void Draw();
    state * Process();
    void FingerIN(DirectFinger *);
};
};


#endif // STATE_INICIO_H_INCLUDED
