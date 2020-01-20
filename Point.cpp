#include "Point.h"

/// Constructor
Point::Point(int x, int y) {
    this->xPos = x;
    this->yPos = y;
}

/// Destructor
Point::~Point() {}

int Point:: getX() {
    return this->xPos;
}

int Point::getY() {
    return yPos;
}

bool Point::equals(Point point) {
    return (this->xPos == point.getX() && this->yPos == point.getY());
}


