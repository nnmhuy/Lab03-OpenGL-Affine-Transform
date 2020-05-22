//
//  Rectangle.hpp
//  Lab02_Object_Coloring
//
//  Created by Huy Nguyen Ngoc Minh on 5/2/20.
//  Copyright © 2020 Huy Nguyen Ngoc Minh. All rights reserved.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <iostream>
#include <math.h>

#include "Object.hpp"
#include "Point.hpp"

class Rectangle: public Object {
public:
    void getParameters(Point start_point, Point end_point) override;
    void draw() override;
    void drawScreen() override;
};


#endif /* Rectangle_hpp */
