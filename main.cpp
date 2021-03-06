//
//  main.cpp
//  Takagism
//
//  Created by 张函祎 on 15/6/22.
//  Copyright (c) 2015年 Sylvanus. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <cv.h>
#include <highgui.h>

#include "Game.h"

int window_width  = 1000;
int window_height = 750;

Game game;

/// Keyboard Messenge
void keyboard(unsigned char key, int x, int y)
{
    switch ( key )
    {
        case 'a': {
            if (game.camera.direct==0)
                game.camera.changeHead();
            game.camera.changeDirect();
            break;
        }
        case 'd': {
            if (game.camera.direct==2)
                game.camera.changeHead();
            game.camera.changeDirect();
            break;
        }
        case 'w': {
            int x=game.x, y=game.y;
            if (game.camera.direct==2 && game.camera.head==1)
                x++;
            if (game.camera.direct==2 && game.camera.head==-1)
                x--;
            if (game.camera.direct==0 && game.camera.head==1)
                y++;
            if (game.camera.direct==0 && game.camera.head==-1)
                y--;
            if (game.map[x][y]==0) {
                game.camera.moveCamera();
                game.x=x;
                game.y=y;
            }
            std::cout<<game.x<<","<<game.y<<std::endl;
            break;
        }
        case 's': {
            game.camera.changeHead();
            break;
        }
        case 'q': {
            game.camera.moveCenter(-0.1);
            break;
        }
        case 'e': {
            game.camera.moveCenter(0.1);
            break;
        }
        case 'z': {
            game.camera.lookUpDown(-0.1);
            break;
        }
        case 'c': {
            game.camera.lookUpDown(0.1);
            break;
        }
        case 'i': {
            game.camera.zoomIn();
            break;
        }
        case 'o': {
            game.camera.zoomOut();
            break;
        }
        case 'x': {
            game.camera.torch=!game.camera.torch;
            break;
        }
        case '=': {
            if (game.camera.intensity<1.0)
                game.camera.intensity+=0.1;
            break;
        }
        case '-': {
            if (game.camera.intensity>0)
                game.camera.intensity-=0.1;
            break;
        }

        default:
            break;
    }
    
    glutPostRedisplay();
}

/// Display the Object
void display()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(game.camera.eye[0], game.camera.eye[1], game.camera.eye[2],
              game.camera.center[0], game.camera.center[1], game.camera.center[2],
              0, 1, 0);
    
    glEnable(GL_DEPTH_TEST);
    
    game.drawScene();
    
    glutSwapBuffers();
}

void init() {
    game.init();
}

/// Idle function
void idle(void)
{
    glutPostRedisplay();
}

/// Reshape the Window
void reshape(int w, int h)
{
    // Update the window's width and height
    window_width  = w;
    window_height = h;
    
    // Reset the viewport
    glViewport(0, 0, window_width, window_height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, (float)window_width/(float)window_height, 0.01f, 200.0f);
    
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    // Initialize the GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(150, 120);
    glutCreateWindow("TAKAGISM");
    init();
    
    // Set the callback function
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    return 0;
}