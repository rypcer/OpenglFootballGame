//================================================//
//
//
// Coded by Ajmal Sarif 2021 - w1722688
// For Opengl CW 2
//
//================================================//

//#include "libraries.h"						
#include "ball.h"
#include "plane.h"
#include "target.h"
#include "skybox.h"
#include <vector>
#include <string>
#pragma region Initialization


//can define any number of textures here - we just have 2 images
//these are just integers so you can use them as such
#define Asphalt	0
#define Brick	1
#define Ball	2   
#define Skybox	3   
#define TargetPink	4   
#define TargetBlue	5   
#define TargetGreen	6   
#define TargetRing	7   
#define Graffiti1	8   
#define Graffiti2	9   
#define Ivy		10   
#define Grass	11   
#define Patch	12
#define GroundAO	13
#define Bar	14
#define Knob	15
#define TEXTURE_COUNT 16
GLuint  textures[TEXTURE_COUNT];

//below is simply a character array to hold the file names
//note that you may need to replace the below with the full directory root depending on where you put your image files
//if you put them where the exe is then you just need the name as below - THESE IMAGES  ARE IN THE DEBUG FOLDER, YOU CAN ADD ANY NEW ONES THERE 
const char* textureFiles[TEXTURE_COUNT] = { 
	"asphalt.tga","brickwall.tga","FootballCompleteMap.tga","skyboxNight.tga","targetPink.tga","targetBlue.tga","targetGreen.tga", 
	"targetRing.tga","graffiti1.tga","graffiti2.tga","ivy.tga","grass.tga","patch.tga","groundAO.tga","bar.tga","knob.tga"};


//for lighting if you want to experiment with these
GLfloat mKa[4] = { 0.11f,0.06f,0.11f,1.0f }; //ambient
GLfloat mKd[4] = { 0.43f,0.47f,0.54f,1.0f }; //diffuse
GLfloat mKs[4] = { 1.0f,1.0f,1.0f,1.0f }; //specular
GLfloat mKe[4] = { 0.5f,0.5f,0.0f,1.0f }; //emission

//spot position and direction
GLfloat	 lightPos[] = { 0.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir[] = { 50.0, 25.0, 0.0 };

GLfloat	 lightPos2[] = { 50.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir2[] = { 50.0, 15.0, 0.0 };

GLfloat	 lightPos3[] = { -50.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir3[] = { 50.0, 15.0, 0.0 };


// Useful lighting colour values
GLfloat  whiteLightBright[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  redLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat  greenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat  blueLight[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat  whiteLightLessBright[] = { 0.8f, 0.8f, 0.8f, 1.0f };


//we need these for the texture loader
//they are to do with the image format and size
GLint iWidth, iHeight, iComponents;
GLenum eFormat;
// this is a pointer to memory where the image bytes will be held 
GLbyte* pBytes0;

// Window Paramaters
GLfloat Wwidth;
GLfloat Wheight;

//camera
GLfloat cameraX = 0.0;
GLfloat cameraY = 100.0;
GLfloat cameraZ = 500.0;
bool moveCamera = false;

// Game
bool gameOver = false, WonGame = false, ballShot = false, followBall = false;
int score = 0, shotsLeft = 10;


// Knobs
GLfloat knobPosH = 630;
GLfloat knobPosV = 628;


#pragma endregion


#pragma region Objects

ball football(Ball, 0, 25.0, 280.0, 20.0);

plane asphalt(Asphalt, 500, 900, 0, 0, -300);
plane groundAO(GroundAO, 350, 500, 0, 0.2, -100);
plane wallFront(Brick, 400, 120, 0, 90, -500);
plane wallFrontAO(GroundAO, 400, 120, 0, 90, -499.9);
plane wallRight(Brick, 400, 120, 350, 90, -200);
plane wallRightAO(GroundAO, 400, 120, 349.9, 90, -200);
plane wallLeft(Brick, 400, 120, -350, 90, -200);
plane wallLeftAO(GroundAO, 400, 120, -349.9, 90, -200);
skybox sky(Skybox,0,0,0);

plane graffiti1(Graffiti1,60,60,349,90,-80);
plane graffiti2(Graffiti2,60,60,349,120,-260);

plane ivy(Ivy, 180, 90, -349, 120, -260);
plane grass(Grass, 80, 60, 190, 0, 60);
plane grass2(Grass, 80, 60, 190, 0, 60);
plane grass3(Grass, 50, 50, -70, 0, 320);
plane grass4(Grass, 50, 50, -70, 0, 320);
plane grass5(Grass, 80, 80, -340, -10, 0);
plane grass6(Grass, 60, 60, 50, 0, 380);

plane patch(Patch, 200, 100, 0, 1, 280);
plane knob(Knob, 150, 30, 100,100,0);

std::vector<target> targets;



void init()
{
	// Used to reset position back to initial values
	football.setStartX(football.getX());
	football.setStartY(football.getY());
	football.setStartZ(football.getZ());

	// Create targets
	targets.push_back(target(TargetPink, 50, 50, 0, 50, -499, 1));
	targets.push_back(target(TargetPink, 30, 30, 250, 150, -499, 1));
	targets.push_back(target(TargetPink, 40, 40, -200, 80, -499, 1));
	targets.push_back(target(TargetBlue, 40, 40, -100, 120, -499, 2));
	targets.push_back(target(TargetGreen, 50, 50, 150, 120, -499, 3));
	targets.push_back(target(TargetGreen, 30, 30, -300, 120, -499, 3));
	targets.push_back(target(TargetBlue, 30, 30, 300, 100, -499, 2));

}

#pragma endregion

#pragma region Functions

void drawTargets() 
{
	
	for (target t : targets) {
		t.updateTarget();
		t.setTilingOn(false);
		t.drawPlane();
	}
}


#pragma endregion


void draw3D() 
{

	// Draw Skybox
	sky.drawSkybox();

	// Draw Ground
	asphalt.drawPlane();
	asphalt.rotate(-90, 0);
	// Draw GroundAO
	groundAO.drawPlane();
	groundAO.rotate(-90, 0);
	groundAO.setTilingOn(false);

	//Draw Patch
	patch.drawPlane();
	patch.rotate(-90, 0);
	patch.setTilingOn(false);

	// Draw Front Wall
	wallFront.drawPlane();
	wallFront.setTileSizeW(3);
	wallFront.setTileSizeH(0.9);
	wallFrontAO.drawPlane();
	wallFrontAO.setTilingOn(false);

	// Draw Left Wall
	wallLeft.drawPlane();
	wallLeft.rotate(90, 1);
	wallLeft.setTileSizeW(3);
	wallLeft.setTileSizeH(0.9);
	wallLeftAO.drawPlane();
	wallLeftAO.rotate(90, 1);
	wallLeftAO.setTilingOn(false);

	// Draw Right Wall
	wallRight.drawPlane();
	wallRight.rotate(-90, 1);
	wallRight.setTileSizeW(3);
	wallRight.setTileSizeH(0.9);
	wallRightAO.drawPlane();
	wallRightAO.rotate(-90, 1);
	wallRightAO.setTilingOn(false);

	// Draw graffitis
	graffiti1.drawPlane();
	graffiti1.setTilingOn(false);
	graffiti1.rotate(-90, 1);
	graffiti2.drawPlane();
	graffiti2.setTilingOn(false);
	graffiti2.rotate(-90, 1);

	// Draw ivys
	ivy.drawPlane();
	ivy.setTilingOn(false);
	ivy.rotate(90, 1);


	// Draw grass
	grass.drawPlane();
	grass.rotate(45, 1);
	grass.setTilingOn(false);
	grass2.drawPlane();
	grass2.rotate(-45, 1);
	grass2.setTilingOn(false);

	grass3.drawPlane();
	grass3.rotate(45, 1);
	grass3.setTilingOn(false);
	grass4.drawPlane();
	grass4.rotate(-45, 1);
	grass4.setTilingOn(false);

	grass5.drawPlane();
	grass5.rotate(70, 1);
	grass5.setTilingOn(false);
	grass6.drawPlane();
	grass6.rotate(-65, 1);
	grass6.setTilingOn(false);


	// Draw Targets
	drawTargets();


	// Draw Football
	football.drawBall();


}

void drawText(char* string, float x, float y, GLfloat r, GLfloat g, GLfloat b)
{
	glColor3f(r, g, b);

	char* c;
	glRasterPos2f(x, y);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void drawUI(int image, float width,float height, float x, float y,float z,float angle=0,float g=1)
{

	//glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y,z);
	glRotatef(angle, 0.0f, 0.0f,1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, g);

	//bind the texture 
	glBindTexture(GL_TEXTURE_2D, textures[image]);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(0, 0);

	glTexCoord2f(0.0, 1.0);
	glVertex2f(0, height);

	glTexCoord2f(1.0, 1.0);
	glVertex2f(width, height);

	glTexCoord2f(1.0, 0.0);
	glVertex2f(width, 0);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//glRotatef(-angle, 0.0f, 0.0f, 1.0f);
	//glPopMatrix();
	
}

void drawNumber(float num,float x, float y, GLfloat r, GLfloat g, GLfloat b) {
	char scor[10];
	sprintf_s(scor, "%3.0f", num);
	drawText(scor, x, y, r, g, b);
}

void draw2D() 
{
	// Draw the 2D overlay
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, Wwidth, Wheight, 0);
	glMatrixMode(GL_MODELVIEW);

	//----------------------------//

	// Convert Points Integer to char array


	// Draw Score 
	drawText("Score: ",48,50, 0.9f, 0.9f, 0.9f);
	drawNumber((float)score,120,50, 0.5f, 0.5f, 0.8f);

	//Draw Shots Left
	drawText("Shots Left: ", 48, 80, 0.9f, 0.9f, 0.9f);
	drawNumber((float)shotsLeft,150,80, 0.5f, 0.8f, 0.5f);

	//Draw Game over Screen

	if(gameOver)
		drawText("Game Over, Press R to restart! ", 500,360, 0.9f, 0.1f, 0.3f);
	else if (score >= 130) {
		WonGame = true;
		drawText("WON GAME!, Press R to restart! ", 500, 360, 0.3f, 0.9f, 0.3f);
	}
	// Vertical Bar
	drawUI(Bar, 225, 45, 1100, 630,0,-90);
	drawUI(Knob, 20, 20, 1100, knobPosV,0.1f,-90,0);
	//Horizontal Bar
	drawUI(Bar, 225, 45, 527.5f, 610,0);
	drawUI(Knob, 20, 20, knobPosH, 610, 0.1f);
	//----------------------------//

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}


void Lights() {
	

	GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat  sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat	 lightDir[] = { 0.0f, 0.0f, -1.0f, 0.0f };
	GLfloat  specref[] = { 800.0f, 800.0f, 800.0f, 800.0f };

	glEnable(GL_LIGHTING);
	glLoadIdentity();

	// Ambient Light
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, mKd);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 120.0f);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir);
	glEnable(GL_LIGHT1);

	//Spot Light 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mKd);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glEnable(GL_LIGHT0);

}
// Called to draw scene
void RenderScene(void)
{

	// Clear the window with current clearing colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Switch Camera Look At to ball or scene
	if (followBall)
	{
		gluLookAt(football.getX(), football.getY() + 20, football.getZ() + 180,//eye
			football.getX(), football.getY() + 20, football.getZ(), //centre
			0.00, 5.00, 0.00); //up
	}
	else {
		// view the scene
		gluLookAt(cameraX, cameraY, cameraZ,//eye
			0.00, 0.00, 00.00, //centre
			0.00, 10.00, 0.00); //up
	}
	draw3D();
	draw2D();

	glutSwapBuffers();
}


// This function does any needed initialization on the rendering context.
void SetupRC()
{
	// Texture Setup
	GLuint texture;
	// allocate a texture name
	glGenTextures(1, &texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load textures in a for loop
	glGenTextures(TEXTURE_COUNT, textures);
	//this puts the texture into OpenGL texture memory
	for (int iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
	{
		// Bind to next texture object
		glBindTexture(GL_TEXTURE_2D, textures[iLoop]);

		// Load texture data, set filter and wrap modes
		//note that gltLoadTGA is in the glm.cpp file and not a built-in openGL function
		pBytes0 = gltLoadTGA(textureFiles[iLoop], &iWidth, &iHeight,
			&iComponents, &eFormat);

		glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes0);

		//set up texture parameters

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//try these too
	   // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		// glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		free(pBytes0);
	}

	//enable textures
	glEnable(GL_TEXTURE_2D);

	// Hidden surface removal    
	glEnable(GL_DEPTH_TEST);	

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_POINT_SMOOTH);

	// Setup and enable light for whole scene light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLightBright);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLightBright);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mKs);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
	glEnable(GL_LIGHT0);


	// Spotlight & Ambient Light
	Lights();

	// Enable colour tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR, mKs);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// Black background colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


}

void KeyBoard(unsigned char key, int x, int y)
{
	if (!football.getShot() && !gameOver && !WonGame) {
		switch (key)
		{
		case 'f':
			followBall = !followBall;
			std::cout << followBall;
			break;
		
		case 32:
			football.setShot(true);
			break;

		default:
			break;

		}
	}
	if (key == 'r' && !football.getShot()) {
		// Reset football position,score,shotsLeft & targets
		football.resetPos();
		score = 0;
		shotsLeft = 10;
		gameOver = false;
		WonGame = false;
		followBall = false;
		knobPosH = 630;
		knobPosV = 628;
		for (int i = 0; i < targets.size(); i++)
		{
			targets[i].setHit(false);
		}
	}
	else if (key == 27) {

		if (glutGetWindow())
			glutDestroyWindow(glutGetWindow());
		exit(0);

	}
}


void SpecialKeys(int key, int x, int y) {
	// Change horizontal & vertical angle, cap between (-100 <= Pos => 100)
	// So Knob doesnt go outside Bar
	if (!football.getShot() && !gameOver && !WonGame) {
		switch (key)
		{
		case GLUT_KEY_UP:
			if (knobPosV >= 438) {
				football.setVY(1.3f, true);
				knobPosV -= 20;
			}
			break;
		case GLUT_KEY_DOWN:
			if (knobPosV <= 618) {
				football.setVY(1.3f, false);
				knobPosV += 20;
			}
			break;
		case GLUT_KEY_LEFT:
			if (knobPosH >= 540) {
				football.setVX(0.7f, false);
				knobPosH -= 10;
			}
			break;

		case GLUT_KEY_RIGHT:
			if (knobPosH <= +720) {
				football.setVX(0.7f, true);
				knobPosH += 10;
			}
			break;
		default:
			break;

		}
	}

}


// Update Game
void TimerFunc(int value)
{
	//move camera
	if (moveCamera)
	{
		cameraZ = cameraZ - 2;
	}

	if (shotsLeft < 0) 
	{
		gameOver = true;
	}

	// Rotate Sky
	sky.rotateTimer();
	football.updateBall(targets,score,shotsLeft);
	glutPostRedisplay();
	glutTimerFunc(25, TimerFunc, 1);
}


void Menu(int choice) {

	if (choice == 1) {
		moveCamera = !moveCamera;
		if (!moveCamera) {
			cameraX = 0.0;
			cameraY = 100.0;
			cameraZ = 500.0;
		}
	}

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;
	Wwidth = w;
	Wheight = h;
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Calculate aspect ratio of the window
	fAspect = (GLfloat)w / (GLfloat)h;

	// Set the perspective coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// field of view of 45 degrees, near and far planes 1.0 and 1000
	//that znear and zfar should typically have a ratio of 1000:1 to make sorting out z depth easier for the GPU
	gluPerspective(55.0f, fAspect, 1.0, 2000.0);

	// Modelview matrix reset
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);// a 4:3 ratio
	glutCreateWindow("Street Football");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(25, TimerFunc, 1);
	// Create the Menu (right click on window)
	glutCreateMenu(Menu);
	glutAddMenuEntry("Look Around Scene", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	SetupRC();
	init();
	glutMainLoop();
	return 0;
}



