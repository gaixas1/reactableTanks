#ifndef STATE_INICIO_H_INCLUDED
#define STATE_INICIO_H_INCLUDED

#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"

namespace tuio
{

class state_inicio : public state {
    public:
    unsigned char change2;

    state_inicio();
};
}


#endif // STATE_INICIO_H_INCLUDED
