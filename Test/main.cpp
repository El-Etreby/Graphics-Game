//
//  main.cpp
//  Test
//
//  Created by Omar Ezzat El-Etreby on 10/7/17.
//  Copyright © 2017 Etro. All rights reserved.

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

void Display();
void Setup();
void Anim();
void Timer(int value);
void KeyPressed(int key, int x, int y);
void KeyReleased(int key, int x, int y);
void DrawSpaceship();
void DrawBackground1();
void DrawBackground2();
void DrawBackground3(float r, float g);
void DrawObstacle1(int x, int y, float r);
void DrawObstacle2(int x, int y, float w, float h);
void DrawObstacle3();
void DrawPowerup(int x, int y, float w, float h, float w2, float h2);
void backgroundMov();
void obstacle1Mov();
void resetObstacle1();
void obstacle2Mov();
void resetObstacle2();
void obstacle3Mov();
void resetObstacle3();
void powerupMov();
void resetPowerup();
void lose();
void win();
float random(float start, float end);

int windowX = 800;
int windowY = 800;

bool lost = false;
bool won = false;

double r = 0.0;
double g = 0.0;
double b = 0.0;

double shipX = 0.0;
double shipY = 0.0;
bool rotateTop = false;
bool rotateBot = false;
double rotationAngle = 5.0;

double obstacle1X = 1.0;
double obstacle1Y = 0.0;
double obstacle1Speed =0.01;
bool obstacle1Entered = false;
double random1Y = random(0.4,1.3) - 1;

double obstacle2X = 2.0;
double obstacle2Y = 0.0;
double angle = 0.0;
double obstacle2Speed = 0.0;
double randomY = random(0.2, 1.6) - 1;
double constantY = 2.0;
bool obstacle2Entered = false;

double obstacle3X = 3.0;
double obstacle3Y = random(0.2, 1.6) - 1;
double zigzagHeight = 0.0;
bool zigzag = false;
bool obstacle3Entered = false;

double obstaclesCount = 0.0;

double background1X = 0.0;
double background2X = 0.0;
double backgroundSpeed = 0.002;
double arrayX [20];
double arrayY [20];
double arrayX2 [20];
double arrayY2 [20];

double powerupX = 1000;
double powerupY = random(0.2, 1.6) - 1;
bool isPowerupMoving = false;

int main(int argc,char** argr)
{
    glutInit(&argc, argr);
    glutInitWindowSize(windowX, windowY);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Game");
    glutDisplayFunc(Display);
    glutIdleFunc(Anim);
    //glutTimerFunc(0.05, Timer, 0);
    glutSpecialFunc(KeyPressed);
    glutSpecialUpFunc(KeyReleased);
    //glLineWidth(100.0);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    gluOrtho2D(-1, 1, -1, 1);
    
    //Random star locations for background 1
    for(int i=0;i<20;i++){
        arrayX[i] = random(0,2) - 1;
        arrayY[i] = random(0,2) - 1;
    }
    
    //Random star locations for background 2
    for(int i=0;i<20;i++){
        arrayX2[i] = random(0,2) - 1;
        arrayY2[i] = random(0,2) - 1;
    }
    
    glutMainLoop();
    return 0;
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glClearColor(0.0, 0.0, 0.0, 0.0f);
    DrawBackground1();
    DrawBackground2();
    DrawSpaceship();
    DrawPowerup(1,0, 0.05, 0.1, 0.1,0.05);
    DrawObstacle1(1,0,0.05);
    DrawObstacle2(1,0,0.1,0.1);
    DrawObstacle3();
    
    if(lost){
        DrawBackground3(1.0, 0.0);
    } else if(won){
        DrawBackground3(0.0, 1.0);
    }
    
    glFlush();
}

void DrawSpaceship()
{
    glPushMatrix();
    //Rotation
    if(rotateTop){
        glRotatef(rotationAngle, 0.0, 0.0, 1.0);
    } else if(rotateBot){
        glRotatef(rotationAngle * -1, 0.0, 0.0, 1.0);
    } else {
        glRotatef(rotationAngle, 0.0, 0.0, 0.0);
    }
    
    glColor3f(0.663f, 0.663f, 0.663f);
    glBegin(GL_POLYGON);
    glVertex3d(shipX-0.02,shipY+0.0,0.0f);
    
    glVertex3d(shipX-0.05,shipY-0.05,0.0f);
    glVertex3d(shipX-0.05,shipY-0.10,0.0f);
    glVertex3d(shipX+0.07,shipY-0.10,0.0f);
    
    glVertex3d(shipX+0.07,shipY+0.10,0.0f);
    glVertex3d(shipX-0.05,shipY+0.10,0.0f);
    glVertex3d(shipX-0.05,shipY+0.05,0.0f);
    glEnd();
    
    glColor3f(0.827f, 0.827f, 0.827f);
    
    //Bottom Triangle
    glBegin(GL_TRIANGLES);
    glVertex3d(shipX-0.01f,shipY-0.10f,0.0f);
    glVertex3d(shipX-0.01f, shipY-0.15f, 0.0f);
    glVertex3d(shipX+0.05f,shipY-0.10f,0.0f);
    glEnd();
    
    //Top Triangle
    glBegin(GL_TRIANGLES);
    glVertex3d(shipX-0.01f,shipY+0.10f,0.0f);
    glVertex3d(shipX-0.01f, shipY+0.15f, 0.0f);
    glVertex3d(shipX+0.05f,shipY+0.10f,0.0f);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(shipX+0.07f,shipY-0.10f,0.0f);
    glVertex3d(shipX+0.07f,shipY+0.10f,0.0f);
    glVertex3d(shipX+0.14f,shipY+0.0f,0.0f);
    glEnd();
    
    glColor3f(1.000f, 0.271f, 0.000f);
    
    // Bottom Fire
    glBegin(GL_LINES);
    glVertex3d(shipX-0.08f,shipY-0.09f,0.0f);
    glVertex3d(shipX-0.05f,shipY-0.09f,0.0f);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex3d(shipX-0.08f,shipY-0.08f,0.0f);
    glVertex3d(shipX-0.05f,shipY-0.08f,0.0f);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex3d(shipX-0.08f,shipY-0.07f,0.0f);
    glVertex3d(shipX-0.05f,shipY-0.07f,0.0f);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex3d(shipX-0.08f,shipY-0.06f,0.0f);
    glVertex3d(shipX-0.05f,shipY-0.06f,0.0f);
    glEnd();
    
    // Top Fire
    glBegin(GL_LINES);
    glVertex3d(shipX-0.08f,shipY+0.09f,0.0f);
    glVertex3d(shipX-0.05f,shipY+0.09f,0.0f);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex3d(shipX-0.08f,shipY+0.08f,0.0f);
    glVertex3d(shipX-0.05f,shipY+0.08f,0.0f);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex3d(shipX-0.08f,shipY+0.07f,0.0f);
    glVertex3d(shipX-0.05f,shipY+0.07f,0.0f);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex3d(shipX-0.08f,shipY+0.06f,0.0f);
    glVertex3d(shipX-0.05f,shipY+0.06f,0.0f);
    glEnd();
    
    glPopMatrix();
}

void DrawBackground1()
{
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(background1X, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3d(-1.0f, 1.0f, 0.0f);
    glVertex3d(-1.0f, -1.0f, 0.0f);
    glVertex3d(1.0f, -1.0f, 0.0f);
    glVertex3d(1.0f, 1.0f, 0.0f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for(int i=0;i<20;i++){
        glVertex3d(arrayX[i], arrayY[i], 0.0);
    }
    glEnd();
    glPopMatrix();
    
}
void DrawBackground2()
{    //glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.2f);
    glTranslatef(background2X, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3d(1.0f, 1.0f, 0.0f);
    glVertex3d(1.0f, -1.0f, 0.0f);
    glVertex3d(3.0f, -1.0f, 0.0f);
    glVertex3d(3.0f, 1.0f, 0.0f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for(int i=0;i<20;i++){
        glVertex3d(arrayX2[i]+2, arrayY2[i], 0.0);
    }
    glEnd();
    glPopMatrix();
}

void DrawBackground3(float r, float g)
{
    //Red background in case of lose and green if won
    glColor3f(r, g, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3d(-1.0f, 1.0f, 0.0f);
    glVertex3d(-1.0f, -1.0f, 0.0f);
    glVertex3d(1.0f, -1.0f, 0.0f);
    glVertex3d(1.0f, 1.0f, 0.0f);
    glEnd();
}


void DrawObstacle1(int x, int y, float r)
{
    glPushMatrix();
    glColor3f(1.000, 0.271, 0.000);
    glTranslatef( obstacle1X + x, obstacle1Y + y, 0);
    GLUquadric *quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, 50, 50);
    glPopMatrix();
}

void DrawObstacle2(int x, int y, float w, float h)
{
    glPushMatrix();
    glColor3f(1.000, 0.271, 0.000);
    glTranslatef( obstacle2X , obstacle2Y , 0);
    glBegin(GL_POLYGON);
    glVertex2f(x-(w/2), y+(h/2));
    glVertex2f(x+(w/2), y+(h/2));
    glVertex2f(x+(w/2), y-(h/2));
    glVertex2f(x-(w/2), y-(h/2));
    glEnd();
    glPopMatrix();
}

void DrawObstacle3()
{
    glPushMatrix();
    glColor3f(1.000, 0.271, 0.000);
    glTranslatef( obstacle3X , obstacle3Y , 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(1,0.05);
    glVertex2f(0.95,-0.05);
    glVertex2f(1.05,-0.05);
    glEnd();
    glPopMatrix();
}

void DrawPowerup(int x, int y, float w, float h, float w2, float h2)
{
    glPushMatrix();
    glColor3f(0.698, 0.133, 0.133);
    glTranslatef(powerupX, powerupY, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x-(w/2), y+(h/2));
    glVertex2f(x+(w/2), y+(h/2));
    glVertex2f(x+(w/2), y-(h/2));
    glVertex2f(x-(w/2), y-(h/2));
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(x-(w2/2), y+(h2/2));
    glVertex2f(x+(w2/2), y+(h2/2));
    glVertex2f(x+(w2/2), y-(h2/2));
    glVertex2f(x-(w2/2), y-(h2/2));
    glEnd();
    glPopMatrix();
}


void Anim()
{
    for(int i=0; i<10000000;i++);
    backgroundMov();
    obstacle1Mov();
    obstacle2Mov();
    obstacle3Mov();
    powerupMov();
    glutPostRedisplay();
}

void KeyPressed( int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
        if(shipY+0.15+0.1<1){
            rotateTop = true;
            shipY += 0.1;
        }
    } else if(key == GLUT_KEY_DOWN){
        if(shipY-0.15-0.1>-1){
            rotateBot = true;
            shipY -= 0.1;
        }
    }
    glutPostRedisplay();
}

void KeyReleased(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
            rotateTop = false;
    } else if(key == GLUT_KEY_DOWN){
            rotateBot = false;
    }
    glutPostRedisplay();
    
}

void powerupMov()
{
    //Straight line
    if(obstaclesCount>=6.0){
        obstaclesCount = 0.0;
        isPowerupMoving = true;
        powerupX = 0.0;
    } else {
        if(isPowerupMoving){
            double powerupSpeed = 0.01;
            
            if(!(shipX+0.14<powerupX+1-(0.1/2)) && !(shipY+0.15< powerupY+0-(0.1/2)) && !(shipX-0.08>powerupX+1+(0.1/2)) && !(shipY-0.15> powerupY+0+(0.1/2))){
                //The spaceship gets the powerup
                isPowerupMoving = false;
                if (shipX < 0.5714285714){
                    shipX += 0.2857142857;
                    resetPowerup();
                } else {
                    win();
                }
            } else {
                powerupX-= powerupSpeed;
                if(powerupX< -2){
                    resetPowerup();
                }
            }
        }
    }
}

void resetPowerup()
{
    powerupX = 1000.0;
    powerupY = random(0.2, 1.6) - 1;
    isPowerupMoving = false;

}

void obstacle1Mov()
{
    //Sin wave
    if(obstacle1X-0.05 < 1.0 && obstacle1Entered == false){
        obstaclesCount++;
        obstacle1Entered = true;
    }
    
    if(!(shipX+0.14 < obstacle1X+1-0.05) && !(shipY+0.15< obstacle1Y-0.05) && !(shipY-0.15> obstacle1Y+0.05) && !(shipX-0.08>obstacle1X+1+0.05)){
        //The obstacle hits the spaceship
        if (shipX > -0.5714285714){
            shipX -= 0.2857142857;
            resetObstacle1();
        } else {
            lose();
        }
    } else {
        obstacle1Y = sin(obstacle1X *15)*0.25 + random1Y;
        obstacle1X -= obstacle1Speed;
        if(obstacle1X+1+0.05 < -1){
            resetObstacle1();
        }
    }
}

void resetObstacle1()
{
    obstacle1X = 1.0;
    obstacle1Y = 0.0;
    random1Y = random(0.4,1.3) - 1;
    obstacle1Entered = false;
}

void obstacle2Mov()
{
    //Moving in a circular way
    double r = 0.1;
    
    if(obstacle2X+1-(0.1/2) < 1.0 && obstacle2Entered == false){
        obstaclesCount++;
        obstacle2Entered = true;
    }
    if(!(shipX+0.14 < obstacle2X+1-(0.1/2)) && !(shipY+0.15<obstacle2Y+0-(0.1/2)) && !(shipY-0.15> obstacle2Y+0+(0.1/2)) && !(shipX-0.08>obstacle2X+1+(0.1/2))){
        if (shipX > -0.5714285714){
            shipX -= 0.2857142857;
            resetObstacle2();
        } else {
            lose();
        }
    } else {
        obstacle2Speed += 0.01;
        obstacle2X = r * cos(angle) - obstacle2Speed + constantY;
        obstacle2Y = r * sin(angle) + randomY;
        angle+= 0.25;
        
        if(obstacle2X+1+(0.1/2) < -1){
            resetObstacle2();
        }
        
        if(angle>365){
            angle = 0.0;
        }
    }
}

void resetObstacle2()
{
    obstacle2X = 2.0;
    obstacle2Y = 0.0;
    obstacle2Speed = 0.0;
    randomY = random(0.2, 1.6) - 1;
    constantY = 2.0;
    obstacle2Entered = false;
    angle = 0.0;
}

void obstacle3Mov()
{
    //Zigzag
    if(obstacle3X+0.95 == 1.0 && obstacle3Entered == false){
        obstaclesCount++;
        obstacle3Entered = true;
    }
    
    if(!(shipX+0.14 < obstacle3X+0.95) && !(shipY+0.15<obstacle3Y-0.05) && !(shipY-0.15> obstacle3Y+0.05) && !(shipX-0.08>obstacle3X+1.05)){
        if (shipX > -0.5714285714){
            shipX -= 0.2857142857;
            resetObstacle3();
        } else {
            lose();
        }
    } else {
        obstacle3X-=0.01;
        if(zigzag){
            obstacle3Y-=0.003;
            zigzagHeight-=0.003;
            if(zigzagHeight <= 0.0){
                zigzag = false;
                zigzagHeight = 0.0;
            }
        } else {
            obstacle3Y+=0.003;
            zigzagHeight+=0.003;
            if(zigzagHeight >= 0.3){
                zigzag = true;
                zigzagHeight = 0.3;
            }
        }
        if(obstacle3X+1.05<-1){
            resetObstacle3();
        }
    }
    
}

void resetObstacle3()
{
    obstacle3X = 3.0;
    obstacle3Y = random(0.2, 1.6) - 1;
    obstacle3Entered = false;
}

void lose()
{
    shipX = -1;
    lost = true;
}

void win()
{
    shipX = -1;
    won = true;
}

void backgroundMov()
{
    if(background1X + 1 <= -1) {
        background1X = 2.0;
    }
    if(background2X + 3 <= -1 ){
        background2X = 0.0;
    }
    
    background1X -= backgroundSpeed;
    background2X -= backgroundSpeed;
    
}

float random(float start, float end)
{
    return start +  static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / end));
}


