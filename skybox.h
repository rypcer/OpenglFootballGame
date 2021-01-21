#pragma once
#include "libraries.h"

class skybox
{
	//GLuint & textures;
	GLint textureID;
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat z = 0;
	GLfloat xR = 0;
	GLfloat yR = 0;
	GLfloat zR = 0;
	GLfloat angle = 0;
public:

	skybox(GLint _textureID, GLfloat _x, GLfloat _y, GLfloat _z) :
		textureID(_textureID+2), x(_x), y(_y), z(_z){}
	void drawSkybox();
	void setX(GLfloat _x);
	void setY(GLfloat _y);
	void setZ(GLfloat _z);
	void rotateTimer();
	
};

