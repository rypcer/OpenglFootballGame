#pragma once
#include "plane.h"

class target : public plane
{
	//GLuint & textures;

	GLint targetID;
	GLint textureIDR;
	GLint points=0;
	bool hit = false;
public:

	target(GLint _textureID,GLint _width, GLint _height,GLfloat _x, GLfloat _y, GLfloat _z, GLint _targetID) :
		 plane(_textureID,_width,_height,_x,_y,_z), targetID(_targetID), textureIDR(_textureID+2) {}
	
	GLint getPoints();
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
	GLfloat getR();
	void setHit(bool _hit);
	bool getHit();
	void resetTarget();
	void updateTarget();
};

