#ifndef _TEST_APP
#define _TEST_APP

#include "juego.h"

#include "TableApp.hpp"
#include "Graphic.hpp"

class testApp : public TableApp{
	public:
        tuio::Juego * j;

		void Setup();
		void Update();
		void Draw();
		void WindowResized(int w, int h);
};

#endif
