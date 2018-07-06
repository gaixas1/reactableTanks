#include "mapas.h"

using namespace tuio;

    std::vector<mapa *> Mapas::mapas;

    mapa * Mapas::getMapa(int id) {

        if (mapas.size() <= id) {
            return new mapa();
        } else {
            return mapas[id];
        }
    };

    int Mapas::addMapa(mapa * m) {
        mapas.push_back(m);
        return mapas.size()-1;
    }
    int Mapas::getCount()
    {
        return mapas.size();
    }
