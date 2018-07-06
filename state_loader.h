#ifndef STATE_LOADER_H_INCLUDED
#define STATE_LOADER_H_INCLUDED

#include "State.h"
#include "state_editor.h"

namespace tuio
{

class state_loader : public state
{
    public:
        ofImage * loading;
        ofSoundPlayer * fondo;
        state * next;
        float angle;
       // pthread_t Hilo;

        state_loader(int, void* = NULL);
        void Draw();
        state * Process();
};

};

#endif // STATE_LOADER_H_INCLUDED
