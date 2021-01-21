#include "skybox.h"


//---------This is used for the football ball-------//
//GLUquadricObj* quadricFootball;


// here we declare an array of vertices for the cube
GLfloat cubeVertexData[108] = {
    //object vertex coordinates for cube made from triangles
    // Data layout for each line below is:
    // positionX, positionY, positionZ
    //wind counter-clockwise

    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,

    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,

    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    //4
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    //5
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    //6
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f

};

//the texture coordinates - work will skybox texture of this shape +--
GLfloat textureCoordsSkyBox[72] = {
    //face 1
    0.75,0.33,      //    0,1,
    0.75,0.67,     //    1,1,
    0.5,0.33,     //    0,0,
    0.5,0.33,     //    0,0,
    0.75,0.67,    //    1,0,
    0.5,0.67,   //    1,1,

    //face 2
    0.5,1.0, //    1,1,
    0.25,1, //    0,1,
    0.5,0.67, //    1,0,
    0.5,0.67, //    1,0,
    0.25,1.0, //    0,1,
    0.25,0.67, //    1,1,
    //face 3
    0,0.67,//    1,1,
    0,0.33,//    0,1,
    0.25,0.67,//    1,0,
    0.25,0.67,//    1,0,
    0,0.33,//    0,1,
    0.25,0.33,//    0,0,
    //face 4
    0.25,0.0,//    0,1,
    0.5,0.0,//    1,1,
    0.25,0.33,//    0,0,
    0.25,0.33,//    0,0,
    0.5,0.0,//    1,1,
    0.5,0.33,//    0,0,
    //face 5
    0.5,0.67,//    1,0,
    0.25,0.67,//    0,0,
    0.5,0.33,//    1,1,
    0.5,0.33,//    1,1,
    0.25,0.67,//    0,0,
    0.25,0.33,//    0,1,
    //face 6
    0.75,0.33,//    1,1,
    1.0,0.33,//    0,1,
    0.75,0.67,//    1,0,
    0.75,0.67,//    1,0,
    1.0,0.33,//    0,1,
    1.0,0.67//    0,0


};

//the lighting normals - all facing out from each face
GLfloat gCubeVertexdataNormals[108] = {
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f

};

 void skybox::drawSkybox()
{
    glPushMatrix();

    // Invert Texture to Inside of Cube 
    glFrontFace(GL_CW); 

    // Transformations
    glTranslatef(x, y, z);
    glRotatef(-220, 0, 1,0);
    glRotatef(angle, 0, 1,0);
    glScalef(1500, 1500, 1500);
    glColor3f(1,1,1);
    // Bind Texturemap
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, gCubeVertexdataNormals);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, cubeVertexData);
    glTexCoordPointer(2, GL_FLOAT, 0, textureCoordsSkyBox);
    // draw a cube - type - start number - number of vertices to draw (so 3 for single triangle)
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // deactivate vertex arrays after drawing
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glFrontFace(GL_CCW);
    glPopMatrix();

}


 void skybox::setX(GLfloat _x) { x = _x; }
 void skybox::setY(GLfloat _y) { y = _y; }
 void skybox::setZ(GLfloat _z) { z = _z; }

 void skybox::rotateTimer()
 {
     angle+=0.01f;
     if (angle > 360) {
         angle = 0;
     }

 }