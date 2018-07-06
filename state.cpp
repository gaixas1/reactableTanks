#include "State.h"

using namespace tuio;
    // Tratamiento de eventos
    void state::Draw(){};
    state * state::Process(){return this;};

    void state::FingerIN(DirectFinger *){};
    void state::FingerOUT(DirectFinger *){};
    void state::FingerUPDATE(DirectFinger *){};

    void state::TAP(float,float){};

    void state::ObjectIN(DirectObject *){};
    void state::ObjectOUT(DirectObject *){};
    void state::ObjectUPDATE(DirectObject *){};
