#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <GL/glut.h>
#include "imageloader.h"
#include "common.h"
#include "validator.h"


using namespace std;
float _Hangle = 165.0f;
float _Vangle = 100.0f;
float _x = 1.0f;
float _y = 0.0f;
float _z = -8.0f;
int _Rows = 8;
int _Zet = 0;
int _Position = 0;
float _ZMax = ((_Rows/2.0f)*1.2f)+0.2f;
float _positionColor = 0.0f;
bool _positionColorUp = true;
GLuint _textureBoard;
GLuint _textureManual;
bool _isAanzet = true;
bool _isLeftKeyPressed = false;
bool _isRightKeyPressed = false;
bool _isUpKeyPressed = false;
bool _isDownKeyPressed = false;
bool _isPlusKeyPressed = false;
bool _isMinKeyPressed = false;
bool _isAKeyPressed = false;
bool _isDKeyPressed = false;
bool _isSKeyPressed = false;
bool _isWKeyPressed = false;
bool _isEnterKeyPressed = false;
bool _isSpaceKeyPressed = false;
bool _isBackspaceKeyPressed = false;
int _balls[12][4];
int _pawns[12][4];

//ontvang alle antwoorden tot nu toe!
void addAnswer() {
	if(_Zet == 0){
		generateTable();
		_balls[_Zet][0] = (int) a; 
		_balls[_Zet][1] = (int) b;
		_balls[_Zet][2] = (int) c; 
		_balls[_Zet][3] = (int) d; 
	}
        else if(_Zet == 1){
		_balls[_Zet][0] = (int) b;
		_balls[_Zet][1] = (int) c;
		_balls[_Zet][2] = (int) d;
		_balls[_Zet][3] = (int) e;
		
	}
	else if(_Zet == 2){
		_balls[_Zet][0] = (int) c;
		_balls[_Zet][1] = (int) d;
		_balls[_Zet][2] = (int) e;
		_balls[_Zet][3] = (int) f;		
	} 
	if((_Zet-1) >=0) {
		Code cd; Pins pins;
		cd[0] = (eColor) _balls[_Zet-1][0];
		cd[1] = (eColor) _balls[_Zet-1][1];
		cd[2] = (eColor) _balls[_Zet-1][2];
		cd[3] = (eColor) _balls[_Zet-1][3];
		
		pins[0] = (ePin) _pawns[_Zet-1][0];
		pins[1] = (ePin) _pawns[_Zet-1][1];
		pins[2] = (ePin) _pawns[_Zet-1][2];
		pins[3] = (ePin) _pawns[_Zet-1][3];
		
		addRecordToHistory(cd,pins);
	}	
	if(_Zet > 2){
		int count = 0;
		for(int i=0; i<tablepointer; i++){
			if(m_table[i][0] != empty){
				if(!validateCode(m_table[i], m_history)){
					m_table[i][0] = empty;
				} else {					
					_balls[_Zet][0] = m_table[i][0];
					_balls[_Zet][1] = m_table[i][1];
					_balls[_Zet][2] = m_table[i][2];
					_balls[_Zet][3] = m_table[i][3];
					m_table[i][0] = empty;
					break;
				}
			}
		}
	}
	_isAanzet = true;
} 

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: exit(0); break;
		case 43: _isPlusKeyPressed = true; break;
		case 45: _isMinKeyPressed = true; break;
		case 97: _isAKeyPressed = true; break;
		case 100: _isDKeyPressed = true; break;
		case 115: _isSKeyPressed = true; break;
		case 119: _isWKeyPressed = true; break;
	}
}

void handleKeyReleased(unsigned char key, int x, int y) {
	switch (key) {
		case 8: _isBackspaceKeyPressed = true; break;
		case 13: _isEnterKeyPressed = true; break;
		case 32: _isSpaceKeyPressed = true; break;
		case 43: _isPlusKeyPressed = false; break;
		case 45: _isMinKeyPressed = false; break;
		case 97: _isAKeyPressed = false; break;
		case 100: _isDKeyPressed = false; break;
		case 115: _isSKeyPressed = false; break;
		case 119: _isWKeyPressed = false; break;
	}
}

void handleSpecialKeypress(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: _isLeftKeyPressed = true; break;
		case GLUT_KEY_RIGHT: _isRightKeyPressed = true; break;
		case GLUT_KEY_UP: _isUpKeyPressed = true; break;
		case GLUT_KEY_DOWN:_isDownKeyPressed = true; break;
	}
}

void handleSpecialKeyReleased(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: _isLeftKeyPressed = false; break;
		case GLUT_KEY_RIGHT:_isRightKeyPressed = false; break;
		case GLUT_KEY_UP: _isUpKeyPressed = false; break;
		case GLUT_KEY_DOWN:_isDownKeyPressed = false; break;
	}
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE,image->pixels);
	return textureId; //Returns the id of the texture
}


void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glClearColor(0.0f, 0.05f, 0.15f, 1.0f);

	Image* image = loadBMP("board.bmp");
	_textureBoard = loadTexture(image);
	delete image;
	Image* image2 = loadBMP("manual.bmp");
	_textureManual = loadTexture(image2);
	delete image2;
}

void handleResize(int w, int h) {
	glutFullScreen();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	gluPerspective(45.0,(double)w / (double)h,0.1,300.0);
}

void drawTriangle(float topX, float topY,float topZ, float width, float height,float thickness) {
	glBegin(GL_TRIANGLES); 
	    //bottom
	    glNormal3f(0.0f, 1.0f, 0.0f);
	    glTexCoord2f(topX, topZ);
	    glVertex3f(topX, topY, topZ);
	    glTexCoord2f(topX-(width/2), topZ-height);
	    glVertex3f(topX-(width/2), topY, topZ-height);
	    glTexCoord2f(topX+(width/2), topZ-height);
	    glVertex3f(topX+(width/2), topY, topZ-height);

	    //top
	    glNormal3f(0.0f, 1.0f, 0.0f);
	    glTexCoord2f(topX, topZ);
	    glVertex3f(topX, topY+thickness, topZ);
	    glTexCoord2f(topX-(width/2), topZ-height);
	    glVertex3f(topX-(width/2), topY+thickness, topZ-height);
	    glTexCoord2f(topX+(width/2), topZ-height);
	    glVertex3f(topX+(width/2), topY+thickness, topZ-height);
	glEnd();
	glBegin(GL_QUADS); 
	   //front
	   glNormal3f(0.0f, 0.0f, -1.0f);
	   glTexCoord2f(topX-(width/2), topY);
	   glVertex3f(topX-(width/2), topY, topZ-height);
	   glTexCoord2f(topX-(width/2), +thickness);
	   glVertex3f(topX-(width/2), topY+thickness, topZ-height);
	   glTexCoord2f(topX+(width/2), topY+thickness);
	   glVertex3f(topX+(width/2), topY+thickness, topZ-height);
	   glTexCoord2f(topX+(width/2), topY);
	   glVertex3f(topX+(width/2), topY, topZ-height);

	   //left
	   glNormal3f(-0.5f, 0.0f, 0.5f);
	   glTexCoord2f(topX, topY);
	   glVertex3f(topX, topY, topZ);
	   glTexCoord2f(topX, topY+thickness);
	   glVertex3f(topX, topY+thickness, topZ);
	   glTexCoord2f(topX-(width/2), topY+thickness);
	   glVertex3f(topX-(width/2), topY+thickness, topZ-height);
	   glTexCoord2f(topX-(width/2), topY);
	   glVertex3f(topX-(width/2), topY, topZ-height);
	   
	   //right
	   glNormal3f(0.5f, 0.0f, 0.5f);
	   glTexCoord2f(topX, topY);
	   glVertex3f(topX, topY, topZ);
	   glTexCoord2f(topX, topY+thickness);
	   glVertex3f(topX, topY+thickness, topZ);
	   glTexCoord2f(topX+(width/2), topY+thickness);
	   glVertex3f(topX+(width/2), topY+thickness, topZ-height);
	   glTexCoord2f(topX+(width/2), topY);
	   glVertex3f(topX+(width/2), topY, topZ-height);
	glEnd();
}

void drawCube(float x1, float y1,float z1, float x2, float y2,float z2) {
	glBegin(GL_QUADS); 
	   //bottom
	   glNormal3f(0.0f, -1.0f, 0.0f);
	   glTexCoord2f(x1, z1);
	   glVertex3f(x1, y1, z1);
	   glTexCoord2f(x2, z1);
	   glVertex3f(x2, y1, z1);
	   glTexCoord2f(x2, z2);
	   glVertex3f(x2, y1, z2);
	   glTexCoord2f(x1, z2);
	   glVertex3f(x1, y1, z2);

	   //top
	   glNormal3f(0.0f, 1.0f, 0.0f);
	   glTexCoord2f(x1, z1);
	   glVertex3f(x1, y2, z1);
	   glTexCoord2f(x2, z1);
	   glVertex3f(x2, y2, z1);
	   glTexCoord2f(x2, z2);
	   glVertex3f(x2, y2, z2);
	   glTexCoord2f(x1, z2);
	   glVertex3f(x1, y2, z2);

	   //back
	   glNormal3f(0.0f, 0.0f, -1.0f);
	   glTexCoord2f(x1, y1);
	   glVertex3f(x1, y1, z2);
	   glTexCoord2f(x1, y2);
	   glVertex3f(x1, y2, z2);
	   glTexCoord2f(x2, y2);
	   glVertex3f(x2, y2, z2);
	   glTexCoord2f(x2, y1);
	   glVertex3f(x2, y1, z2);

	   //front
	   glNormal3f(0.0f, 0.0f, 1.0f);
	   glTexCoord2f(x1, y1);
	   glVertex3f(x1, y1, z1);
	   glTexCoord2f(x1, y2);
	   glVertex3f(x1, y2, z1);
	   glTexCoord2f(x2, y2);
	   glVertex3f(x2, y2, z1);
	   glTexCoord2f(x2, y1);
	   glVertex3f(x2, y1, z1);

	   //left
	   glNormal3f(-1.0f, 0.0f, 0.0f);
	   glTexCoord2f(z1, y1);
	   glVertex3f(x1, y1, z1);
	   glTexCoord2f(z1, y2);
	   glVertex3f(x1, y2, z1);
	   glTexCoord2f(z2, y2);
	   glVertex3f(x1, y2, z2);
	   glTexCoord2f(z2, y1);
	   glVertex3f(x1, y1, z2);

	   //right
	   glNormal3f(1.0f, 0.0f, 0.0f);
	   glTexCoord2f(z1, y1);
	   glVertex3f(x2, y1, z1);
	   glTexCoord2f(z1, y2);
	   glVertex3f(x2, y2, z1);
	   glTexCoord2f(z2, y2);
	   glVertex3f(x2, y2, z2);
	   glTexCoord2f(z2, y1);
	   glVertex3f(x2, y1, z2);
	  glEnd();
}

void drawBall(int position, int row, int color) {
	   glPushMatrix();
        glTranslatef( (2.5 - ((position - 1) * 1.2f)), 0.4, ((1.2f * (_Rows - 1))/2) - ((row - 1) * 1.2f));
		switch(color) {
		 case 1: glColor3f(1.0f, 1.0f, 1.0f); break;//white ball
		 case 2: glColor3f(0.1f, 0.1f, 0.1f); break;//black ball
		 case 3: glColor3f(0.7f, 0.0f, 0.0f); break;//red ball
		 case 4: glColor3f(0.0f, 0.7f, 0.0f); break;//green ball
		 case 5: glColor3f(0.0f, 0.0f, 0.7f); break;//blue ball
		 case 6: glColor3f(0.7f, 0.7f, 0.0f); break;//yellow ball
		}
	    glutSolidSphere(0.4, 25, 25);
	   glPopMatrix();
}

void drawPawn(int position, int row, int color) {
	   glPushMatrix();
	    float z = ((1.2f * (_Rows - 1))/2) - ((row - 1) * 1.2f);
		if(position == 1 || position == 2) {
			z = z + 0.3f;
		} else {
			z = z - 0.3f;
		}
		float x = -2.75f;
		if(position == 1 || position == 3) {
			x = -2.15f;
		}
        glTranslatef( x, 0.15, z );
		switch(color) {
		 case 1: glColor3f(1.0f, 1.0f, 1.0f); break;//white pawn
		 case 2: glColor3f(0.7f, 0.0f, 0.0f); break;//red pawn
		}
	    glutSolidSphere(0.15, 15, 15);
	   glPopMatrix();
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat ambientColor[] = {0.5f, 0.5f, 0.5f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.9f, 0.9f, 0.9f, 1.0f};
	GLfloat lightPos0[] = {-5.0f, 5.0f, -5.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glPushMatrix();
	 glTranslatef(_x,_y,_z);
	 glRotatef(_Hangle,0.0f,1.0f,0.0f);
	 glRotatef(_Vangle,1.0f,0.0f,0.0f);
	 glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, _textureManual);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	  glColor3f(0.6f, 0.6f, 0.6f);
	  float x1 = -1.7f;
	  float y1 = -0.15f;
	  float z1 = 2.5f;
	  float x2 = 1.7f;
	  float y2 = -0.1f;
	  float z2 = -2.5f;
	  
	  glBegin(GL_QUADS); 
	   glNormal3f(0.0f, -1.0f, 0.0f);
	   glTexCoord2f(0.75f, 0.0f);
	   glVertex3f(x1, y1, z1);
	   glTexCoord2f(0.0f, 0.0f);
	   glVertex3f(x2, y1, z1);
	   glTexCoord2f(0.0f, 1.0f);
	   glVertex3f(x2, y1, z2);
	   glTexCoord2f(0.75f, 1.0f);
	   glVertex3f(x1, y1, z2);
	  glEnd();
	 glDisable(GL_TEXTURE_2D);

	 glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, _textureBoard);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	  glColor3f(0.6f, 0.6f, 0.6f);
	   //top
	   drawCube(-3.6f, -0.1f, _ZMax, 3.6f, 0.0f, _ZMax*-1.0f);
	   //front
	   drawCube(-3.1f, -0.6f, _ZMax-0.5f, 3.1f, -0.1f, _ZMax-0.6f);
	   //back
	   drawCube(-3.1f, -0.6f, (_ZMax-0.6f)*-1.0f, 3.1f, -0.1f, (_ZMax-0.5f)*-1.0f);

	   //draw topLayer
	  float _tZ = (_Rows/2.0f)*1.2f;
	  for(int i = 0; i < _Rows; i++) {
	   drawCube(-3.4f, 0.0f, _tZ, 3.4f, 0.3f, _tZ-0.15f);
	   drawCube(-3.4f, 0.0f, _tZ-1.05f, 3.4f, 0.3f, _tZ-1.2f);
	   drawCube(-3.4f, 0.0f, _tZ-0.15f, -2.9f, 0.3f, _tZ-1.05f);
	   drawCube(-2.6f, 0.0f, _tZ-0.15f, -2.3f, 0.3f, _tZ-1.05f);
	   drawCube(-2.9f, 0.0f, _tZ-0.45f, -2.6f, 0.3f, _tZ-0.75f);
	   drawCube(-2.3f, 0.0f, _tZ-0.45f, -2.0f, 0.3f, _tZ-0.75f);
	   glPushMatrix();//--------------------------------------------------------------
	    glRotatef(90.0f,0.0f,1.0f,0.0f);
	    drawTriangle((_tZ-0.6f)*-1, 0.0f, -1.7f, 0.9f, 0.3f, 0.3f); //end
	   glPopMatrix();
	   glPushMatrix();
	    glRotatef(180.0f,0.0f,1.0f,0.0f);
	    drawTriangle(1.7f, 0.0f, (_tZ-0.6f)*-1, 0.6f, 0.45f, 0.3f);
	   glPopMatrix();
	   drawTriangle(-1.7f, 0.0f, _tZ-0.6f, 0.6f, 0.45f, 0.3f);
	   glPushMatrix();
	    glRotatef(180.0f,0.0f,1.0f,0.0f);
	    drawTriangle(0.5f, 0.0f, (_tZ-0.6f)*-1, 0.6f, 0.45f, 0.3f);
	   glPopMatrix();
	   drawTriangle(-0.5f, 0.0f, _tZ-0.6f, 0.6f, 0.45f, 0.3f);
	   glPushMatrix();
	    glRotatef(180.0f,0.0f,1.0f,0.0f);
	    drawTriangle(-0.7f, 0.0f, (_tZ-0.6f)*-1, 0.6f, 0.45f, 0.3f);
	   glPopMatrix();
	   drawTriangle(0.7f, 0.0f, _tZ-0.6f, 0.6f, 0.45f, 0.3f);
	   glPushMatrix();
	    glRotatef(180.0f,0.0f,1.0f,0.0f);
	    drawTriangle(-1.9f, 0.0f, (_tZ-0.6f)*-1, 0.6f, 0.45f, 0.3f);
	   glPopMatrix();
	   drawTriangle(1.9f, 0.0f, _tZ-0.6f, 0.6f, 0.45f, 0.3f);
	   glPushMatrix();
	    glRotatef(180.0f,0.0f,1.0f,0.0f);
	    drawTriangle(-3.1f, 0.0f, (_tZ-0.6f)*-1, 0.6f, 0.45f, 0.3f);
	   glPopMatrix();
	   drawTriangle(3.1f, 0.0f, _tZ-0.6f, 0.6f, 0.45f, 0.3f);
	   glPushMatrix();
	    glRotatef(270.0f,0.0f,1.0f,0.0f);
	    drawTriangle(_tZ-0.6f, 0.0f, -3.1f, 0.9f, 0.3f, 0.3f); //end
	   glPopMatrix();
	   
	   _tZ = _tZ - 1.2f;
	  }
	  //huidige positie
	  if(_isAanzet) {
	   float z = ((1.2f * (_Rows - 1))/2) - ((_Zet) * 1.2f);
	   if(_Position == 0 || _Position == 1) {
		z = z + 0.3f;
	   } else {
		z = z - 0.3f;
	   }
	   float x = -2.75f;
	   if(_Position == 0 || _Position == 2) {
		x = -2.15f;
	   }
	   glColor3f(_positionColor, _positionColor, _positionColor);
	   drawCube(x + 0.15f, 0.0f, z + 0.15f, x - 0.15f, 0.01f, z - 0.15f);
	   if(_positionColorUp) _positionColor = _positionColor + 0.05f;
	   else _positionColor = _positionColor - 0.05f;
	   if(_positionColor > 1.0f) _positionColorUp = false;
	   if(_positionColor < 0.0f) _positionColorUp = true;
	  }

	 glDisable(GL_TEXTURE_2D);
	 int i = 0;
	 for(i=0; i<(_Zet + 1); i++) {
	  int j = 0;
	  for(j=0; j<4; j++) {
	   if(_balls[i][j] > 0 && _balls[i][j] <= 6) drawBall(j+1, i+1, _balls[i][j]);
	   if(_pawns[i][j] > 0 && _pawns[i][j] <= 2) drawPawn(j+1, i+1, _pawns[i][j]);
	  }
	 }
	glPopMatrix();
	glutSwapBuffers();
}

void update(int value) {
	//angle horizontal
	if(_isLeftKeyPressed) _Hangle += 2.0f;
	if(_isRightKeyPressed) _Hangle -= 2.0f;
	if (_Hangle > 360) _Hangle -= 360;
	if (_Hangle < 0) _Hangle += 360;
	//angle vertical
	if(_isUpKeyPressed) _Vangle += 2.0f;
	if(_isDownKeyPressed) _Vangle -= 2.0f;
	if (_Vangle > 360) _Vangle -= 360;
	if (_Vangle < 0) _Vangle += 360;
	//zoom
	if(_isPlusKeyPressed == true && _z < -5.0f) _z = _z + 0.5f;
	if(_isMinKeyPressed == true && _z > -50.0f) _z = _z - 0.5f;
	//move vertical
	if(_isSKeyPressed == true && _y < 8.0f) _y = _y + 0.1f;
	if(_isWKeyPressed == true && _y > -8.0f) _y = _y - 0.1f;
	//move horizontal
	if(_isAKeyPressed == true && _x < 8.0f) _x = _x + 0.1f;
	if(_isDKeyPressed == true && _x > -8.0f) _x = _x - 0.1f;
	//if your turn:
	if(_isAanzet == true) {
	 if(_isSpaceKeyPressed == true) {
	  _isSpaceKeyPressed = false;
	  _pawns[_Zet][_Position] = _pawns[_Zet][_Position] + 1;
	  if(_pawns[_Zet][_Position] == 3) _pawns[_Zet][_Position] = 0;
	 }
	 if(_isEnterKeyPressed == true) {
	  _isEnterKeyPressed = false;
	  if(_Position == 3) {
	   _Zet = _Zet + 1;
	   _isAanzet = false;
	   _Position = 0;
	   if(_pawns[_Zet - 1][0] == 2 && _pawns[_Zet - 1][1] == 2 && _pawns[_Zet - 1][2] == 2 && _pawns[_Zet - 1][3] == 2) {
		//computer heeft gewonnen
		exit(0);
	   } else {
		if(_Zet >= _Rows) {
	     //computer heeft verloren
	     exit(0);
	    } else {
		 addAnswer();
	    }
	   }
	  } else {
	   _Position = _Position + 1;
	  }
	 }
	 if(_isBackspaceKeyPressed == true) {
	  _isBackspaceKeyPressed = false;
	  if(_Position > 0) _Position = _Position - 1;
	 }
	}
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {

	addAnswer(); //to start

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	
	glutCreateWindow("Mastermind");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(handleKeyReleased);
	glutSpecialFunc(handleSpecialKeypress);
	glutSpecialUpFunc(handleSpecialKeyReleased);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}
