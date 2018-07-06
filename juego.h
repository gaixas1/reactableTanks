#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "State.h"

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"

#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"

namespace tuio
{

class Juego : public OnTable < CanTap < CanDirectFingers < CanDirectObjects < Graphic > > > >
{
    public:
        state * s;

        Juego();
        void Draw();
        void Process();

        void newCursor(DirectFinger *);
        void removeCursor(DirectFinger *);
        void updateCursor(DirectFinger *);

        void Tap(float, float);

        void newObject(DirectObject * object);
        void removeObject(DirectObject * object);
        void updateObject(DirectObject * object);
};
};


#endif // JUEGO_H_INCLUDED
