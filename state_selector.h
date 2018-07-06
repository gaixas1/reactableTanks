#ifndef STATE_SELECTOR_H_INCLUDED
#define STATE_SELECTOR_H_INCLUDED

#include "State.h"
#include "map.h"

#define IDEDITORSALIR 6

namespace tuio
{

class state_selector : public state
{
    public:
        mapa * act;
        int mapas, actual;
        int estado;

        state_selector();
        void Draw();
        state * Process();

        void TAP(float,float);
        void ObjectIN(DirectObject *);
        void ObjectUPDATE(DirectObject *);
};

};

#endif // STATE_SELECTOR_H_INCLUDED
