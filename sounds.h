#ifndef SOUNDS_H_INCLUDED
#define SOUNDS_H_INCLUDED

#include "ofSoundPlayer.h"
#include <vector>
#include <utility>
#include <string>

namespace tuio
{
typedef pair<std::string, ofSoundPlayer *> pairSound;
class Sonidos
{
    public:
        static std::vector<pairSound> m;
        static ofSoundPlayer * getSound(std::string);
};
};


#endif // JUEGO_H_INCLUDED
