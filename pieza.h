#ifndef PIEZA_H_INCLUDED
#define PIEZA_H_INCLUDED

#include <vector>
#include "DirectPoint.hpp"

namespace tuio
{

class pieza
{
    public:
        virtual void Draw();
};
class piezas
{
	public:
	float angle;
	std::vector<DirectPoint> * centros;
	pieza * p;

    piezas (float, std::vector<DirectPoint> *, pieza *);
	void Draw();
};

};

#endif // STATE_LOADER_H_INCLUDED
