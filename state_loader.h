#ifndef STATE_LOADER_H_INCLUDED
#define STATE_LOADER_H_INCLUDED

#include "State.h"
#include "state_editor.h"
#include "state_inicio.h"
#include "state_selector.h"
#include "state_play.h"

namespace tuio
{
class state_loader : public state
{
    public:
        state * next;

        state_loader(int, unsigned int = 99999999);
        void Draw();
        state * Process();
};

};

#endif // STATE_LOADER_H_INCLUDED
