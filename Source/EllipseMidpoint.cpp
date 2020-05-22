//
//  EllipseMidpoint.cpp
//  Lab01
//
//  Created by Huy Nguyen Ngoc Minh on 4/24/20.
//  Copyright © 2020 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include "EllipseMidpoint.hpp"

void EllipseMidpoint::getParameters(Point start_point, Point end_point){
    center.x = (start_point.x + end_point.x) / 2;
    center.y = (start_point.y + end_point.y) / 2;
    rx = abs(start_point.x - end_point.x) / 2;
    ry = abs(start_point.y - end_point.y) / 2;
    draw();
}

void EllipseMidpoint::ellipseSymmetric4(GLint x, GLint y) {
    // glVertex2i(x + center.x, y + center.y);
    // glVertex2i(x + center.x, -y + center.y);
    // glVertex2i(-x + center.x, y + center.y);
    // glVertex2i(-x + center.x, -y + center.y);
    base_points.push_back(Point(x + center.x, y + center.y));
    base_points.push_back(Point(x + center.x, -y + center.y));
    base_points.push_back(Point(-x + center.x, y + center.y));
    base_points.push_back(Point(-x + center.x, -y + center.y));
}


void EllipseMidpoint::draw() {
    cout << "Drawing ellipse" << endl;
    
    bool isSwap = false;
    if (ry > rx) {
        swap(rx, ry);
        isSwap = true;
    }
    
    GLdouble p = ry*ry + 0.25*rx*rx - rx*rx*ry;
    
    GLdouble x = 0;
    GLdouble y = ry;
    GLdouble dx = 2*ry*ry*x;
    GLdouble dy = 2*rx*rx*y;
    
    
    glBegin(GL_POINTS); // Select points as the primitive
        while (dx < dy) {
            if (!isSwap) {
                ellipseSymmetric4(x, y);
            } else {
                ellipseSymmetric4(y, x);
            }
            if (p < 0) {
                x = x + 1;
                dx = 2*ry*ry*x;
                p = p + dx + ry*ry;
            } else {
                x = x + 1;
                y = y - 1;
                dx = 2*ry*ry*x;
                dy = 2*rx*rx*y;
                p = p + dx - dy + ry*ry;
            }
        }
    
        p = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);
        dx = 2*ry*ry*x;
        dy = 2*rx*rx*y;
        while (y >= 0) {
            if (!isSwap) {
                ellipseSymmetric4(x, y);
            } else {
                ellipseSymmetric4(y, x);
            }
            if (p > 0) {
                y = y - 1;
                dy = 2*rx*rx*y;
                p = p + rx*rx - dy;
            } else {
                y = y - 1;
                x = x + 1;
                dx = 2*ry*ry*x;
                dy = 2*rx*rx*y;
                p = p + dx - dy + rx*rx;
            }
        }
    glEnd(); // Done drawing points
    
    if (isSwap) {
        swap(rx, ry);
    }
}


void EllipseMidpoint::drawScreen() {
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_POINTS); // Select points as the primitive
        // draw from stored based points
        for (int i = 0; i < (int)base_points.size(); ++i) {
            // glVertex2i(base_points[i].x, base_points[i].y);
            Point p = base_points[i];
            p.rotate(center, alpha);
            glVertex2i(p.x, p.y);
        }
    glEnd(); // Done drawing points
}

void EllipseMidpoint::scale(double dx, double dy) {
    rx *= dx;
    ry *= dy;
    base_points.clear();
    draw();
}

bool EllipseMidpoint::isPointInside(Point point) {
    double value = ((point.x - center.x) * (point.x - center.x)) / (rx * rx)
        + ((point.y - center.y) * (point.y - center.y)) / (ry * ry)
        - 1;
    if (value <= 0) return true;
    return false;
}
