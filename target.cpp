
#include "target.h"


GLint target::getPoints() {

	if (targetID == 1)
		return 10;
	else if (targetID == 2)
		return 20;
	else if (targetID == 3)
		return 30;
}

GLfloat target::getX() { return x; }
GLfloat target::getY() { return y; }
GLfloat target::getZ() { return z; }
GLfloat target::getR() { return width; }
void target::setHit(bool _hit) { hit = _hit; }
bool target::getHit() { return hit; }
void target::updateTarget() 
{
	if (hit) {
		textureID = 9;
	}
	else
	{
		textureID = textureIDR;
	}
}

void target::resetTarget()
{
	
	
}