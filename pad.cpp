#include "pad.h"

using namespace tuio;

Pad::Pad()
{
	//Hay que cargar las texturas!
	this->button = Texturas::getImage("pad_bloq.png");
	this->buttonDownLeft = Texturas::getImage("pad_down_left.png");
	this->buttonDownRight = Texturas::getImage("pad_down_right.png");
	this->buttonUpLeft = Texturas::getImage("pad_up_left.png");
	this->buttonUpRight = Texturas::getImage("pad_up_right.png");

	this->radius = 0.1f;
	status = 0;
	timer1 = timer2 = timer3 = 0;
	timer4 = 0;
}

Pad::Pad(DirectPoint _position, float _angle, float _radius)
{
	this->position = _position;
	this->radius = _radius;
	this->angle = _angle;

	this->button = Texturas::getImage("pad_bloq.png");
	this->buttonDownLeft = Texturas::getImage("pad_down_left.png");
	this->buttonDownRight = Texturas::getImage("pad_down_right.png");
	this->buttonUpLeft = Texturas::getImage("pad_up_left.png");
	this->buttonUpRight = Texturas::getImage("pad_up_right.png");


	timer1 = timer2 = timer3 = 0;
	timer4 = 0;
}

int Pad::collide(DirectFinger *f)
{
    if(!(status & PAD_CANFIRE) || !(status & PAD_PAINT))
        return 0;
	if (f->getDistance(this->position) <= this->radius)
	{
	    float angulo = (f->getAngle(this->position)-angle);
			angulo /= M_PI_2;
	    while(angulo <= 0)
            angulo +=4;
        while(angulo >= 5)
            angulo -= 4;
		switch((int)angulo)
		{
		case 0:
            return 1;//Sin delay
            if(timer1==0) {
                timer1 = 15;
                return 1;
            } else
                return 0;
			break;
		case 1:
            if(timer2==0) {
                timer2 = 30;
                return 2;
            } else
                return 0;
			break;
		case 2:
            if(timer3==0) {
                timer3 = 90;
                return 3;
            } else
                return 0;
			break;
		case 3:
            if(timer4 > 0)
                return 4;
            else {
                timer4 = 60;
                return 0;
            }
			break;
		}
	}

	return 0;
}

void Pad::Draw()
{
    if (this->status & PAD_PAINT)
	{
		glPushMatrix();
		ofEnableAlphaBlending();
		ofSetColor(255,255,255,255);
		glTranslatef(this->position.getX(),this->position.getY(), 1);
		glRotatef(this->angle*180/M_PI,0,0,1);

		button->draw(-this->radius,-this->radius,this->radius*2,this->radius*2);

		if(status & PAD_CANFIRE) {
            if(timer1 == 0)
                this->buttonUpLeft->draw(-this->radius,-this->radius,this->radius*2,this->radius*2);
            else
                timer1--;
            if(timer2 == 0)
                this->buttonUpRight->draw(-this->radius,-this->radius,this->radius*2,this->radius*2);
            else
                timer2--;
            if(timer4 == 0)
                this->buttonDownLeft->draw(-this->radius,-this->radius,this->radius*2,this->radius*2);
            else
                timer4--;
            if(timer3 == 0)
                this->buttonDownRight->draw(-this->radius,-this->radius,this->radius*2,this->radius*2);
            else
                timer3--;
		}
		ofDisableAlphaBlending();
		glPopMatrix();
	}

}

void Pad::setValues(float x, float y, float _angle)
{
	this->position.set(x,y);
	this->angle = _angle;
}

void Pad::addStatus(unsigned char x)
{
	this->status |= x;
}

void Pad::removeStatus(unsigned char x)
{
	this->status &= 0xFF-x;
}

bool Pad::isNear(Pad * p)
{
    if(!(status & PAD_PAINT))
        return false;
    if(!(p->status & PAD_PAINT))
        return false;
	if(this->position.getDistance(p->position) <= (this->radius + p->radius))
	{
		return true;
	}
	return false;
}

void Pad::setAngle(float _angle)
{
	this->angle = _angle;
}


