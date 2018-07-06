#ifndef	PAD_H_INCLUDED
#define PAD_H_INCLUDED

#include "DirectPoint.hpp"
#include "InputGestureDirectFingers.hpp"
#include "Graphic.hpp"
#include "textures.h"

#define PAD_PAINT 0x1
#define PAD_CANFIRE 0x2
#define PAD_WEAPON1 0x4
#define PAD_WEAPON2 0x8
#define PAD_WEAPON3 0x10
#define PAD_WEAPON4 0x20


//Definimos por si acaso el centro de la pantalla (mejor no?) xD
const DirectPoint CenterOfScreen(0.5,0.5);

//Definimos el radio por defecto del pad
const float pad_default_radius = 0.01f;

namespace tuio
{
	class Pad
	{
	public:
		//Pad attributes
		DirectPoint position;
		float angle;
		float radius;
		unsigned char status;
		int timer1, timer2, timer3, timer4;

		ofImage *button, *buttonUpLeft, *buttonUpRight, *buttonDownLeft, *buttonDownRight;

		//Constructors
		Pad();
		Pad(DirectPoint _position, float _angle, float _radius);

		//Methods
		int collide(DirectFinger* f);
		void setValues(float x, float y, float _angle);
		void setAngle (float _angle);
		void Draw();
		void update();
		bool isNear(Pad * p);
		void addStatus(unsigned char x);
		void removeStatus(unsigned char x);
	};

};

#endif

