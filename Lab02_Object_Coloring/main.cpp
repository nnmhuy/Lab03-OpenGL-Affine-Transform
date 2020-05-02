//
//  main.cpp
//  Lab02_Object_Coloring
//
//  Created by Huy Nguyen Ngoc Minh on 5/2/20.
//  Copyright © 2020 Huy Nguyen Ngoc Minh. All rights reserved.
//

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <fstream>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>

#include "Config.hpp"
#include "Point.hpp"
#include "ColorMenu.hpp"
#include "DrawMenu.hpp"
#include "Polygon.hpp"

using namespace std;

int window;
int value;

void RenderScreen(void) {
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Flush drawing commands
    glFlush();
}

//  Set up the rendering state, set only once before rendering
void SetupRC(void) {
    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
}

void mainMenu(int num){
    cout << "MAIN MENU" << endl;
    if(num == 0){
        glutDestroyWindow(window);
        exit(0);
    } else {
        value = num;
    }
    glutPostRedisplay();
}

void createMenu(void){
    int draw_submenu_id = glutCreateMenu(DrawMenu::handleToggleMenu);
    glutAddMenuEntry("Ellipse", 1);
    glutAddMenuEntry("Rectangle", 2);
    glutAddMenuEntry("Polygon", 3);
    
    int color_submenu_id = glutCreateMenu(ColorMenu::handleToggleMenu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    
    Config::main_menu_id = glutCreateMenu(mainMenu);
    glutAddSubMenu("Draw", draw_submenu_id);
    glutAddSubMenu("Color", color_submenu_id);
    glutAddMenuEntry("Exit", 0);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


// Called by GLUT library when the window has changed size
void ChangeSize(GLsizei w, GLsizei h)
{
    // Set Viewport to window dimensions
    // glViewport(x, y, w, h) => (x,y): lower-left point of viewport; (w, h): width, height
    glViewport(0, 0, w, h);
    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();

    glOrtho(0, w, h, 0, 1, -1);
    // all future transformation will affect model
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Point ColorMenu::p;
int ColorMenu::currentColor = 1;
int DrawMenu::shape = 0;
Point DrawMenu::start_point;
Point DrawMenu::end_point;
vector <Point> Polygon::currentPoints;
int Config::main_menu_id;

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(Config::MAX_COORDINATE, Config::MAX_COORDINATE);
    window = glutCreateWindow("Coloring Objects");
    
    SetupRC();
    createMenu();
    glutDisplayFunc(RenderScreen);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
    return 0;
}
