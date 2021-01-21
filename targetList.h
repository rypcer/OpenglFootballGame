#pragma once
#include "plane.h"

class target : plane
{
	//GLuint & textures;

	GLint targetID;
	GLint points;
public:

	target(GLint _textureID,GLint _width, GLint _height,GLfloat _x, GLfloat _y, GLfloat _z, GLint _targetColor) :
		 plane(_textureID+2,_width,_height,_x,_y,_z), targetID(_targetColor) {}
	
	GLint getPoints();
};

