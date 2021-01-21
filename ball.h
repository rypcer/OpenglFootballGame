#pragma once
#include "libraries.h"
#include "target.h"
#include <vector>
class ball 
{
	//GLuint & textures;
	GLint textureID;
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat z = 0;
	GLfloat startX = 0;
	GLfloat startY = 0;
	GLfloat startZ = 0;
	GLfloat r = 1;
	// Velocity
	GLfloat vX = 0;
	GLfloat vY = 0;
	GLfloat vXR = 0;
	GLfloat vYR = 0;
	bool shot = false;
	bool ini = false;
	GLfloat angle = 0;
	GLfloat angleAmount = 7;

public:

	ball(GLint _textureID,GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _r) :
		textureID(_textureID+2), x(_x), y(_y), z(_z), r(_r){}
	void drawBall();
	void resetPos();
	void updateBall(std::vector<target> &targets, int &score, int &shotsLeft);
	//void collisionTargets();

	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();

	void setStartX(GLfloat _x);
	void setStartY(GLfloat _y);
	void setStartZ(GLfloat _z);

	void setR(GLfloat _r);

	void setShot(GLfloat _shot);
	bool getShot();

	void setVX(GLfloat amount, bool addSub);
	void setVY(GLfloat amount, bool addSub);

};

