// Created by Simon Bradlow on 1/9/23.
#ifndef SPRITEENGINE_LINEDRAWER_H
#define SPRITEENGINE_LINEDRAWER_H

#include "shape.h"

class LineDrawer : public Rect {
public:
    point2D v1;
    point2D v2;
    LineDrawer() = default;
    LineDrawer(point2D p1, point2D p2) {
        v1 = p1;
        v2 = p2;
    }
    LineDrawer(double x1, double y1, double x2, double y2) {
        v1 = point2D(x1, y1);
        v2 = point2D(x2, y2);
    }
    void draw() const override {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor4d(getRed(), getGreen(), getBlue(), getOpacity());
        glBegin(GL_LINES);
        glVertex2d(v1.x, v1.y);
        glVertex2d(v2.x, v2.y);
        glEnd();
    }
};

#endif //SPRITEENGINE_LINEDRAWER_H