#include "sounds.h"

using namespace tuio;

    std::vector<pairSound> Sonidos::m;
    ofSoundPlayer * Sonidos::getSound(std::string s){
        for (unsigned int i = 0; i < Sonidos::m.size(); i++) {
            if(m[i].first==s)
                return m[i].second;
        }

        ofSoundPlayer * t = new ofSoundPlayer();
        t->loadSound(s);
        pairSound p (s, t);
		m.push_back(p);
		return t;
    };
