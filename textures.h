#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "Graphic.hpp"
#include <vector>
#include <utility>
#include <string>

namespace tuio
{
typedef pair<std::string, ofImage *> pairImage;
class Texturas
{
    public:
        static std::vector<pairImage> m;
        static ofImage * getImage(std::string);
};
};


#endif // JUEGO_H_INCLUDED
