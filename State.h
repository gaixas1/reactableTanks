#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"
#include "Graphic.hpp"

#define STATE_LOADER 0
#define STATE_INICIO 1
#define STATE_EDITOR 2
#define STATE_JUEGO 3
#define STATE_SEL_MAPA 4

namespace tuio
{

class state  {
    public:
    bool loaded;

    // Funciones base
    virtual state* Process();
    virtual void Draw();

    // Tratamiento de eventos
    virtual void FingerIN(DirectFinger *);
    virtual void FingerOUT(DirectFinger *);
    virtual void FingerUPDATE(DirectFinger *);

    virtual void TAP(float,float);

    virtual void ObjectIN(DirectObject *);
    virtual void ObjectOUT(DirectObject *);
    virtual void ObjectUPDATE(DirectObject *);
};

}
#endif // STATE_H_INCLUDED
