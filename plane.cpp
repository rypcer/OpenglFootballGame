
#include "plane.h"
void plane::setX(GLfloat _x) { x = _x; }
void plane::setY(GLfloat _y) { y = _y; }
void plane::setZ(GLfloat _z) { z = _z; }
void plane::setTileSizeW(GLfloat _t) { tileSizeW = _t; };
void plane::setTileSizeH(GLfloat _t) { tileSizeH = _t; };
void plane::setTilingOn(GLfloat _t) { tilingOn = _t; };
void plane::setCullFace(GLfloat _c) { cullFace = _c; };

// Draw a Textured Plane
void plane::drawPlane()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angle, xR, yR, zR);
	// Draw face up and then rotated
	glEnable(GL_TEXTURE_2D);

	// Do not calculate inside
	(cullFace)? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

	// Set Color to White 
	glColor3f(1.0, 1.0, 1.0);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, textureID); //textures[image]

	if (tilingOn)
	{
		// Draw Geometry
		glBegin(GL_QUADS);
		// Set Lighting Normal Vectors direction vertically (Y axis), for all vertices
		glNormal3f(0.f, 1.f, 0.f);
		glTexCoord2f(-tileSizeW, -tileSizeH);
		glVertex3f(-width, -height, 0.f);
		glTexCoord2f(tileSizeW, -tileSizeH);
		glVertex3f(width, -height, 0.f);
		glTexCoord2f(tileSizeW, tileSizeH);
		glVertex3f(width, height, 0.f);
		glTexCoord2f(-tileSizeW, tileSizeH);
		glVertex3f(-width, height, 0.f);
		glEnd();
	}
	else
	{
		// Draw Geometry
		glBegin(GL_QUADS);
		// Set Lighting Normal Vectors direction vertically (Y axis), for all vertices
		glNormal3f(0.f, 1.f, 0.f);
		glTexCoord2f(0, 0);
		glVertex3f(-width, -height, 0.f);
		glTexCoord2f(1, 0);
		glVertex3f(width, -height, 0.f);
		glTexCoord2f(1, 1);
		glVertex3f(width, height, 0.f);
		glTexCoord2f(0, 1);
		glVertex3f(-width, height, 0.f);
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);


	glPopMatrix();

}

void plane::rotate(float _angle, GLint _axis) 
{
	angle = _angle;
	try {
		if (_axis == 0)
			xR = 1;
		else if (_axis == 1)
			yR = 1;
		else if (_axis == 2)
			zR = 1;
		else
			throw _axis;
	}
	catch (int axis) 
	{
		std::cout << " Axis must be between 0 - 2, Your Input: " << axis << '\n';
		exit(0);
	}

}