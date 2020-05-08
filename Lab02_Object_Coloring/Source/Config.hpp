#ifndef Config_hpp
#define Config_hpp

#include <stdio.h>
#include <GL/glut.h>

class Config {
public:
    const static int ORIGINAL_WIDTH = 500;
    const static int ORIGINAL_HEIGHT = 500;
    static int WIDTH;
    static int HEIGHT;
    static int color;
    static int main_menu_id;
};

#endif /* Config_hpp */
