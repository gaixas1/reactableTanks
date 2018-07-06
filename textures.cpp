#include "textures.h"

using namespace tuio;

    std::vector<pairImage> Texturas::m;
    ofImage * Texturas::getImage(std::string s){
        for (unsigned int i = 0; i < Texturas::m.size(); i++) {
            if(m[i].first==s)
                return m[i].second;
        }

        ofImage * t = new ofImage();
        t->loadImage(s);
        pairImage p (s, t);
		m.push_back(p);
		return t;
    };
