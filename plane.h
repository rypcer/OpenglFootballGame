#pragma once
#include "libraries.h"

class plane
{
protected:
	//GLuint & textures;
	GLint textureID;
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat z = 0;
	GLint width;
	GLint height;
	GLfloat tileSizeW = 2;
	GLfloat tileSizeH = 2;
	bool tilingOn = 1;
	bool cullFace = 1;
	GLfloat xR = 0;
	GLfloat yR = 0;
	GLfloat zR = 0;
	GLfloat angle = 0;
public:

	plane(GLint _textureID,GLint _width, GLint _height,GLfloat _x, GLfloat _y, GLfloat _z) :
		textureID(_textureID+2),width(_width),height(_height), x(_x), y(_y), z(_z){}
	void drawPlane();
	void setX(GLfloat _x);
	void setY(GLfloat _y);
	void setZ(GLfloat _z);
	void setTileSizeW(GLfloat _t);
	void setTileSizeH(GLfloat _t);
	void setTilingOn(GLfloat _t);
	void setCullFace(GLfloat _c);
	void rotate(float angle, GLint axis);

};

