#ifndef MAPAS_H_INCLUDED
#define MAPAS_H_INCLUDED

#include <vector>
#include "map.h"
#include <stdio.h>

namespace tuio
{
class Mapas
{
    public:
        static std::vector<mapa *> mapas;
        static mapa * getMapa(int);
        static int addMapa(mapa *);
        static int getCount();
};
};


#endif // JUEGO_H_INCLUDED
