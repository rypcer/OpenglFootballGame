#include "ball.h"


//---------This is used for the football ball-------//
GLUquadricObj* quadricFootball;

 void ball::drawBall()
{
	glPushMatrix();
	glFrontFace(GL_CCW);
	glTranslatef(x, y, z);
	glRotatef(angle,1, 0, 0);
	// Create and texture the ball
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// glDisable(GL_LIGHTING);
	glColor3f(0.5, 0.5, 0.5);
	quadricFootball = gluNewQuadric();
	gluQuadricDrawStyle(quadricFootball, GLU_FILL);
	gluQuadricNormals(quadricFootball, GLU_SMOOTH);
	gluQuadricOrientation(quadricFootball, GLU_OUTSIDE);
	gluQuadricTexture(quadricFootball, GL_TRUE);
	gluSphere(quadricFootball, r, 50, 35);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


 void ball::updateBall(std::vector<target> &targets,int &score,int &shotsLeft ) 
 {

	 // Update position
	 if (shot)
	 {
		 // Reset velocity to beggining
		 if (!ini) {
			 vX = vXR;
			 vY = vYR;
			 ini = true;
			 angleAmount = 7;
			 shotsLeft--;
		 }
		 // Move Ball 
		 z -= 15;
		 x += vX;
		 y += vY;

		 // Apply Gravity
		 vY-=0.25f;

		 // Apply rotation to ball and decrease rotation Amount
		 angle+=angleAmount;
		 if(angleAmount > 0)
			angleAmount-=0.1f;

	 }

	 // If Ball outside or Hit target Reset
	 if (z <= -480) 
	 {
		 z = startZ;
		 x = startX;
		 y = startY;
		 shot = false;
		 ini = false;
	 }

	 // If ball on ground
	 if (y <= 25)
		 y = 25;

	  // Check if collided with any targets
	 //
	 //for (target t : targets) 
	 //{
		// float dx = x - t.getX();
		// float dy = y - t.getY();

		// float distance = sqrt(dx * dx + dy * dy);

		// // Checks in x y for circle collision and for z if it is at the wall
		// if (distance < r + t.getR() && z <= -470 && t.getHit()==false) {
		//	 t.setHit(true);
		//	 score += t.getPoints();
		// }

	 //}

	 for (int i = 0 ; i<targets.size(); i++)
	 {
		 float dx = x - targets[i].getX();
		 float dy = y - targets[i].getY();

		 float distance = sqrt(dx * dx + dy * dy);

		 // Checks in x y for circle collision and for z if it is at the wall
		 if (distance < r + targets[i].getR() && z <= -470 && targets[i].getHit() == false) {
			 targets[i].setHit(true);
			 score += targets[i].getPoints();
		 }

	 }


 }

 void ball::resetPos() 
 {
	 x = startX;
	 y = startY;
	 z = startZ;
	 vXR = 0;
	 vYR = 0;
 }
 GLfloat ball::getX() { return x; }
 GLfloat ball::getY() { return y; }
 GLfloat ball::getZ() { return z; }

 void ball::setStartX(GLfloat _x) { startX = _x; }
 void ball::setStartY(GLfloat _y) { startY = _y; }
 void ball::setStartZ(GLfloat _z) { startZ = _z; }

 void ball::setR(GLfloat _r) { r = _r; }

 void ball::setShot(GLfloat _shot) { shot = _shot; }
 bool ball::getShot() { return shot; }

 void ball::setVX(GLfloat amount, bool addSub) { (!addSub) ? vXR -= amount : vXR += amount; }
 void ball::setVY(GLfloat amount, bool addSub) { (!addSub) ? vYR -= amount : vYR += amount;}